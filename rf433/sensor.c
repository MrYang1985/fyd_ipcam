#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#include <sys/msg.h>
#include <sys/stat.h>

#include "serialport.h"
#include "sensor.h"
#include "common_def.h"
#include "errno.h"

#define MSGQ_PATH "/tmp/msgq"
#define MSGQ_BUFF_SIZE  32

typedef unsigned char BOOL;


typedef struct
{
    /*
      ��Ϣ���нṹ�壬��һ���ֶα���Ϊlong���ͣ�msgsnd
      ��msgszָ���Ĵ�С��������Ϣ����ռ�����ֽ�
     */
    long type;
    char mtext[MSGQ_BUFF_SIZE];
}msg_buf_t;


static int g_msg_id;

static int init_msg_queue(void)
{
    key_t key = ftok(MSGQ_PATH, 'a');
    g_msg_id = msgget(key, S_IRUSR | S_IWUSR | IPC_CREAT);// | IPC_EXCL);	
    if (g_msg_id == -1)
    {
        printf("Message Queue init error\n");
        return -1;
    }

    return 0;
}

static int send_to_msg_queue(msg_type_e type, void *mtext, int mtextLen)
{
    int ret;
    msg_buf_t msgBuf;

    msgBuf.type = (long)type;
    memcpy(msgBuf.mtext, mtext, mtextLen);

    ret = msgsnd(g_msg_id, &msgBuf, mtextLen, IPC_NOWAIT);
    if (-1 == ret)
    {
        printf("%s error, %s\n", __func__, strerror(errno));
        return -1;
    }

    return 0;
}

static int recv_from_msg_queue(msg_type_e type, msg_buf_t *msg)
{
    int ret;
    int msgflags;

    msgflags = MSG_NOERROR | IPC_NOWAIT;
    ret = msgrcv(g_msg_id, msg, MSGQ_BUFF_SIZE, type, msgflags);
    if (-1 == ret)
    {
        if (ENOMSG == errno) //Queue no messages
        {
            return 0;
        }
        printf("%s error, %s\n", __func__, strerror(errno));
        return -1;
    }

    return ret;
}

static void process_sensor_data(unsigned char *buf, int len)
{
	unsigned char protocol_head[64] = {0};
	unsigned char protocol_data[512] = {0};
	
    memcpy(protocol_head, buf + 1, 5);
    memcpy(protocol_data, buf + 6, len - 7);
	
	if (protocol_head[0] == 0x01) //��������������
	{
		if (protocol_head[1] == 0x02) //�Զ����������ݸ�ʽ
		{
			if (protocol_data[1]==0x02)//ASKģʽ����
			{
				sensor_ask_data_t ask_data;
				
				ask_data.sensor_addr[0] = protocol_data[4];
				ask_data.sensor_addr[1] = protocol_data[5];
				ask_data.sensor_data = protocol_data[8];
                
                //���͸���������
                printf("sensor addr %02X %02X  data %02X\n", ask_data.sensor_addr[0], ask_data.sensor_addr[1], ask_data.sensor_data);

                send_to_msg_queue(MSG_TYPE_433_DATA, &ask_data, sizeof(sensor_ask_data_t));
            }

		}
	}

}
	
static unsigned char generate_checksum(const unsigned char *data, int len)
{
    unsigned char checksum = 0;

    while (len-- > 0)
    {
        checksum += *data++;
    }

    return checksum;
}

static void recv_serial_data_thread(void)
{
    int data_len;
    int i;
    unsigned char rbuf[32];
    int rlen;
    unsigned char packet[256];
    int packet_len = 0;
    BOOL packet_start = FALSE;
    char ch;

    
    memset(rbuf, 0, sizeof(rbuf));
    while (1)
    {

        rlen = serial_recv(rbuf, sizeof(rbuf));
        if (rlen <= 0)
        {
            continue;
        }
        
        //printf("recv data from uart len=%d\n", rlen);

        for (i = 0; i < rlen; i++)
        {
            ch = rbuf[i];
            //printf("ch[%d]=%02X\n", i, ch);

            if (!packet_start && ch == 0x7E)      //����ʼ
            {
                //printf("packet start\n");
                packet_start = TRUE;
                packet_len = 0;
                memset(packet, 0, sizeof(packet));
                packet[packet_len++] = ch;
            }
            else if (packet_start && ch == 0x7D)  //������
            {
                packet[packet_len++] = ch;

                //��ͷ��DATA������Ϣ������
                if (packet_len <= 8)
                {
                    printf("packet_len < 8\n");
                    continue;
                }

                data_len = packet[6];  //DATA���ݳ���
                
                //��DATA���ֳ���0x7D
                if (packet_len < data_len + 8)
                {
                    //printf("find 0x7D in data,it is not data end\n");
                    continue;
                }

                packet_start = FALSE;
                
                //DATA����У�鲻ͨ��
                if (packet[packet_len - 2] != generate_checksum(&packet[6], packet_len - 8))
                {
                    printf("checksum error packet[%d]=0x%X  checksum=0x%X\n", 
                        packet_len - 2, packet[packet_len - 2], generate_checksum(&packet[6], packet_len - 8));
                    continue;
                }

                switch (packet[1])
                {
                    case 0x01:      //����������
                        //printf("sensor data\n");
                        process_sensor_data(packet, packet_len);
                        break;

                    default:        //δ֪����
                        printf("unknown serial data type\n");
                        break;
                }
            }
            else if (packet_start)                //������
            {
                packet[packet_len++] = ch;
                if (packet_len == 6)
                {
                    unsigned char checksum;
                    checksum = generate_checksum(&packet[1], 4);
                    
                    
                    if(checksum != packet[5])     //����У����󣬶���
                    {
                        printf("Check Error: packet[5]=%d  generate_checksum=%d\n", packet[5], checksum);
                        packet_start = FALSE;
                    }
                }
                
                //�������ݳ��ȼ���������ݽ�����δ����0x7D
                if (packet_len > 6 && (packet[6] + 8) <= packet_len)
                {
                    printf("packet end no 0x7D\n");
                    packet_start = FALSE;
                }
            }

        }

        memset(rbuf, 0, sizeof(rbuf));
    }
}

int main(int argc,char **argv) 
{ 

    if (serial_init() < 0)
    {
        return -1;
    }

    if (init_msg_queue() < 0)
    {
        return -1;
    }

    

    recv_serial_data_thread();

    return 0;
    
} 


