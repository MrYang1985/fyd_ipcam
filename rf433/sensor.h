#ifndef __SENSOR_H__
#define __SENSOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif



/** �����������ϱ� */
typedef struct
{
	unsigned char sensor_addr[2];   ///< ��ַ��
	unsigned char sensor_type;      ///< ����
	unsigned char sensor_data;      ///< ������
}sensor_ask_data_t;



#ifdef __cplusplus
}
#endif

#endif

