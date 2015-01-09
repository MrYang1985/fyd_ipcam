/**
 * goolink_apiv2.h
 *
 * External APIs for device side implementation.
 *
 * Created by Morningstar Shen  2013-11-27
 */

#ifndef __GOO_LINK_APIV2_H__
#define __GOO_LINK_APIV2_H__

#ifdef __cplusplus
extern "C" {
#endif


#include<stdint.h>
#include<inttypes.h>

#define GLNKPACKET_STR_LEN_32		32
#define GLNKPACKET_STR_LEN_16		16

//

//G711 wave format, G711 means for G711a
#ifndef GLNK_WAVE_FORMAT_G711
#define GLNK_WAVE_FORMAT_G711					0x7A19
#endif

//G726 wave format
#ifndef GLNK_WAVE_FORMAT_G726
#define GLNK_WAVE_FORMAT_G726					0x7A20
#endif

//AMR_NB CBR wave format
#ifndef GLNK_WAVE_FORMAT_AMR_CBR
#define GLNK_WAVE_FORMAT_AMR_CBR 				0x7A21
#endif

//AMR VBR Not support yet
#ifndef GLNK_WAVE_FORMAT_AMR_VBR
#define GLNK_WAVE_FORMAT_AMR_VBR 				0x7A22
#endif

//SPEEX nb mode wave format
#ifndef GLNK_WAVE_FORMAT_SPEEX_NB_MODE
#define GLNK_WAVE_FORMAT_SPEEX_NB_MODE           0x7A23
#endif

//SPEEX wb mode wave format
#ifndef GLNK_WAVE_FORMAT_SPEEX_WB_MODE
#define GLNK_WAVE_FORMAT_SPEEX_WB_MODE           0x7A24
#endif

//G711U wave format
#ifndef GLNK_WAVE_FORMAT_G711U
#define GLNK_WAVE_FORMAT_G711U                   0x7A25
#endif

#ifndef WAVE_FORMAT_AAC
#define WAVE_FORMAT_AAC                   0x7A26
#endif

//AMR_WB Wave format
#ifndef GLNK_WAVE_FORMAT_VOICEAGE_AMR_WB
#define GLNK_WAVE_FORMAT_VOICEAGE_AMR_WB			0xA104
#endif


#define GLNK_CODEC_H264							0x34363248	//H264
#define CODEC_MJPEG							0x45464758	//mjpeg

#define GLNK_ERR_NOERR             0       // No error
#define GLNK_ERR_MUTEX             -0x101  // Mutex creation error
#define GLNK_ERR_THREAD            -0x102  // Thread creation error
#define GLNK_ERR_SOCKET            -0x103  // Socket creation error
#define GLNK_ERR_SOCK_OPT          -0x104  // Socket option setting error
#define GLNK_ERR_SOCK_BIND         -0x105  // Socket bind error
#define GLNK_ERR_TIMEOUT           -0x106  // timeout error
#define GLNK_ERR_NOMEM             -0x107  // memory error
#define GLNK_ERR_PARAM             -0x108  // invalid param
#define GLNK_ERR_IVALSID           -0x109  // invalid session id
#define GLNK_ERR_NAT_TRAVERSAL     -0x10A  // NAT traversal failure
#define GLNK_ERR_PROTOCOL     -0x10B  // 
#define GLNK_ERR_MAX               -0x200  //
#define GLNK_ERR_BUFNOTEXIST       -0x202  // buffer not exist
#define GLNK_ERR_NOTSTART          -0x203  // goolink module not start
#define GLNK_ERR_CLOSING           -0x204  // goolink module is closing
#define GLNK_ERR_NOENOUTGMEM       -0X205  // not enough memery
#define GLNK_ERR_APINOTSUPPORT     -0x206  // in the case the api is not support
#define GLNK_ERR_BUSY              -0x205  // busy



typedef struct InitNetParam
{
	char 			dev[8];
	uint16_t 			localTCPport;
	uint16_t 			localUDPport;
	char 			udid[32];
	unsigned char			channelnum;		// 1-16
	unsigned char 			issupportsubvideostream;	// 0-1
	unsigned char			maxsession;				// 1-16
	char reserve;
}InitNetParam;


typedef enum _PushAlarmType
{
    PAT_VIDEO_FRAME    = 0,       // Video frame detection
    PAT_DEVICE_RESTART = 1,       // Device restart
    PAT_MOTION_DETECT  = 2,       // Motion Detection
    PAT_VIDEO_LOSS     = 3,       // Video Loss
    PAT_DISK_FULL      = 4,       // Disk full
    PAT_BLIND_DETECT   = 5,       // Blind detection
    PAT_SD_ERROR       = 6,       // SD card error
    PAT_ADDR_CONFLICT  = 7,       // Address confliction
    PAT_INFRARED       = 8,       // Infrared alarm
    PAT_VIDEO_ALARM    = 9,       // Video alarm
    PAT_AUDIO_ALARM    = 10,      // Audio alarm
    PAT_TEMPERATURE    = 11,      // Temperature alarm
    PAT_FUME           = 12,      // Fume sensor alarm
    PAT_INVASION       = 13,      // Invasion alarm
    PAT_CALLING_ALARM  = 14,	  // USER call Alarm
    PAT_BREAKDOOR_ALARM = 15,		  // Door break alarm
    PAT_IMAGEMOVE_ALARM =  16, //Ӱ���Ƅӱ���
    PAT_SOUND_ALARM = 17, //������
    PAT_DEVICEMOVE_ALARM = 18, //�C���Ƅӱ���
    PAT_ENERGYREMOVE_ALARM = 19, //�Դ�γ�����
    PAT_SDCARDREMOVE_ALARM = 20, //SDCARD�γ��|�l
    PAT_SDCARDFULL_ALARM = 21, //SDCARD�����ѝM�|�l
    PAT_IO01_ALARM = 22,  //I /O����
    PAT_IO02_ALARM = 23, // I/O 1����
    PAT_IO03_ALARM =24,// I/O 2����
    PAT_IO04_ALARM =25, // I/O 3����
    PAT_IO05_ALARM =26,  //I/O 4����
    PAT_IO06_ALARM =27, // I/O 5����
    PAT_IO07_ALARM =28, //  I/O 6����
    PAT_IO08_ALARM =29,  // I/O 7����
    PAT_IO09_ALARM =30,  //I/O 8����
    PAT_IO10_ALARM =31,  //  I/O 9����
    PAT_IO11_ALARM =32,  //  I/O 10����
    PAT_IO12_ALARM =33,  //  I/O 11����
    PAT_IO13_ALARM =34,  //  I/O 12����
    PAT_IO14_ALARM =35,  //  I/O 13����
    PAT_IO15_ALARM =36,  //  I/O 14����
    PAT_IO16_ALARM =37,  //  I/O 15����
    PAT_IO17_ALARM =38  //  I/O 16����
} PushAlarmType;

typedef struct _GooTime
{
    uint16_t  year;    // YYYY, eg. 2009
    uint16_t  month;   // MM, 1-12
    uint8_t   day;     // DD, 1-31
    uint8_t   hour;    // HH, 0-24
    uint8_t   minute;  // MM, 0-59
    uint8_t   second;  // SS, 0-59
} GooTime;

/* 日期定义 */
typedef struct _GLNK_Date
{
	uint16_t year;		       // YYYY, 2012
	uint8_t month;		       // MM, 1-12
	uint8_t day;			       // DD, 01-31
} GLNK_Date;

typedef struct _PushAlarm
{
    short   alarm_type;
    short   channel;
    GooTime   timestamp;
} PushAlarm;

/*
 // TLV        : GLNK_T_AUDIO_INFO
 // Direction  : Device -> Client
 // Description:
 //    channelId    : ��Ƶͨ����
 //    reserve      : ����
 //    checksum     : У���.ĿǰΪ0δ��
 //    time         : ʱ���, ��Ƶ���ݲ���ʱ��
 // Note       : �豸Ӧ����GLNK_T_AUDIO_INFO, GLNK_T_AUDIO_DATA��˳�������ݡ�
 */
typedef struct _GLNK_V_AudioInfo
{
	unsigned char  channelId;
	unsigned char  reserve;
	unsigned short checksum;
	unsigned int time;
}GLNK_V_AudioInfo;

typedef struct _GLNK_VideoDataFormat
{
	unsigned int codec;			//���뷽ʽ
	unsigned int bitrate;        //������, bps
	unsigned short width;			//ͼ����
	unsigned short height;			//ͼ��߶�
	unsigned char framerate;		//֡��, fps
	unsigned char colorDepth;		//should be 24 bits
	unsigned char frameInterval;   //I֡���
	unsigned char reserve;

} GLNK_VideoDataFormat;

//��Ƶ���ݸ�ʽ
typedef struct _GLNK_AudioDataFormat
{
	unsigned int samplesRate;	//ÿ�����
	unsigned int bitrate;		//������, bps
	unsigned short waveFormat;		//�����ʽ
	unsigned short channelNumber;	//��Ƶͨ���ŵ�ͨ��1 ˫ͨ��2
	unsigned short blockAlign;		//�����, channelSize * (bitsSample/8)
	unsigned short bitsPerSample;	//ÿ����������
	unsigned short frameInterval;	//֡���, ��λms
	unsigned short reserve;

} GLNK_AudioDataFormat;

typedef struct _GLNK_V_DeviceInfo
{
	char companyId[GLNKPACKET_STR_LEN_16];
	char productId[GLNKPACKET_STR_LEN_16];
	char name[GLNKPACKET_STR_LEN_16];
	char softwareVersion[GLNKPACKET_STR_LEN_16];
	GLNK_Date	manufactureDate;
	unsigned char channelNum;
	unsigned char alarmType;
	unsigned char reserve1;
	unsigned char reserve2;
} GLNK_V_DeviceInfo;

/*
 // TLV        : GLNK_T_PTZ_CONTROL_REQ
 // Direction  : Client -> Device
 // Description:
 //    deviceId     : �豸ID
 //    channelId    : ��Ӧ����Ƶͨ����
 //    cmdCode      : ����������, �μ�GLNK_PTZControlCmd
 //    size         : ���Ʋ������ݳ���,���size==0 ��ʾ�޿��Ʋ���
 // Note       : GLNK_V_ControlRequest��������Ʋ������ݿ�, ���ݿ�Ĵ�С��sizeȷ����
 //    size = sizeof(ControlArgData)
 */
typedef struct _GLNK_V_PTZControlRequest
{
	unsigned int deviceId;
	unsigned char  channel;
	unsigned char  cmdCode;
	unsigned short size;
} GLNK_V_PTZControlRequest;

// ControlArgData
//   GLNK_PTZ_MV_STOP   ����
//   GLNK_PTZ_ZOOM_DEC  ��arg1, ����
//   GLNK_PTZ_ZOOM_INC  ��arg1, ����
//   GLNK_PTZ_FOCUS_INC ��arg1, ����
//   GLNK_PTZ_FOCUS_DEC ��arg1, ����
//   GLNK_PTZ_MV_UP     ��arg1, ˮƽ�ٶ�; arg2, ��ֱ�ٶ�; arg3, ����
//   GLNK_PTZ_MV_DOWN   ��arg1, ˮƽ�ٶ�; arg2, ��ֱ�ٶ�; arg3, ����
//   GLNK_PTZ_MV_LEFT   ��arg1, ˮƽ�ٶ�; arg2, ��ֱ�ٶ�; arg3, ����
//   GLNK_PTZ_MV_RIGHT  ��arg1, ˮƽ�ٶ�; arg2, ��ֱ�ٶ�; arg3, ����
//   GLNK_PTZ_IRIS_INC  ��arg1, ����
//   GLNK_PTZ_IRIS_DEC  ��arg1, ����
//   GLNK_PTZ_AUTO_CRUISE  : arg1, 1 = ��ʼѲ��, 0 = ֹͣѲ��; arg2, ˮƽ�ٶ�; arg3, ��ֱ�ٶ�
//   GLNK_PTZ_GOTO_PRESET  : arg1, Ԥ�õ���
//   GLNK_PTZ_SET_PRESET   : arg1, Ԥ�õ���
//   GLNK_PTZ_CLEAR_PRESET : arg1, Ԥ�õ���, ���Ϊ0xFFFFFFFF��ʶ���ȫ��
//   GLNK_PTZ_ACTION_RESET
//   GLNK_PTZ_MV_LEFTUP    ��arg1, ˮƽ�ٶ�; arg2, ��ֱ�ٶ�; arg3, ����
//   GLNK_PTZ_MV_LEFTDOWN  ��arg1, ˮƽ�ٶ�; arg2, ��ֱ�ٶ�; arg3, ����
//   GLNK_PTZ_MV_RIGHTUP   ��arg1, ˮƽ�ٶ�; arg2, ��ֱ�ٶ�; arg3, ����
//   GLNK_PTZ_MV_RIGHTDOWN ��arg1, ˮƽ�ٶ�; arg2, ��ֱ�ٶ�; arg3, ����
//   GLNK_PTZ_CLEAR_TOUR   ��arg1, ��·���
//   GLNK_PTZ_ADD_PRESET_TO_TOUR : arg1, Ԥ�õ���; arg2, ��·���
//   GLNK_PTZ_DEL_PRESET_TO_TOUR : arg1, Ԥ�õ���; arg2, ��·���

typedef enum _GLNK_PTZControlCmd
{
	GLNK_PTZ_MV_STOP      = 0,    // ֹͣ�˶�
	GLNK_PTZ_ZOOM_DEC     = 5,
	GLNK_PTZ_ZOOM_INC     = 6,
	GLNK_PTZ_FOCUS_INC    = 7,    //����
	GLNK_PTZ_FOCUS_DEC    = 8,
	GLNK_PTZ_MV_UP        = 9,    //����
	GLNK_PTZ_MV_DOWN      = 10,   //����
	GLNK_PTZ_MV_LEFT      = 11,   //����
	GLNK_PTZ_MV_RIGHT     = 12,   //����
	GLNK_PTZ_IRIS_INC     = 13,   //��Ȧ
	GLNK_PTZ_IRIS_DEC     = 14,   //
	GLNK_PTZ_AUTO_CRUISE  = 15,	  //�Զ�Ѳ��
	GLNK_PTZ_GOTO_PRESET  = 16,   //��תԤ��λ
	GLNK_PTZ_SET_PRESET   = 17,   //����Ԥ��λ��
	GLNK_PTZ_CLEAR_PRESET = 18,   //���Ԥ��λ��
	GLNK_PTZ_ACTION_RESET = 20,   //PTZ��λ
	GLNK_PTZ_MV_LEFTUP    = 21,
	GLNK_PTZ_MV_LEFTDOWN  = 22,
	GLNK_PTZ_MV_RIGHTUP   = 23,
	GLNK_PTZ_MV_RIGHTDOWN = 24,
	GLNK_PTZ_CLEAR_TOUR   = 25,
	GLNK_PTZ_ADD_PRESET_TO_TOUR  = 26,
	GLNK_PTZ_DEL_PRESET_TO_TOUR  = 27
} GLNK_PTZControlCmd;

typedef struct _GLNK_ControlArgData
{
	unsigned int arg1;
	unsigned int arg2;
	unsigned int arg3;
	unsigned int arg4;
} GLNK_ControlArgData;



/* ����ʱ�䶨�� */
typedef struct _GLNK_DateTime
{
	uint32_t		m_microsecond;	//����	0-1000
	uint32_t 	m_year;			//��,2009
	uint32_t		m_month;		//��,1-12
	uint32_t		m_day;			//��,1-31
	uint32_t		m_hour;			//0-24
	uint32_t		m_minute;		//0-59
	uint32_t		m_second;		//0-59
} GLNK_DateTime;


/*
 // TLV        : GLNK_T_SEARCH_FILE_REQ
 // Direction  : client -> device
 // Description:
 //     deviceId       : �豸��ţ�Ĭ��Ϊ0��
 //     channelMask    : ͨ������, ��Ҫ������Щͨ����¼��, ����λ��1. 0xFFFF FFFF��ʾ����ͨ��
 //     index          : �ļ�����, ��Ϊ0
 //     count          : �������ݸ���, Ĭ��Ϊ10
 //     recordTypeMask : ¼���������� 0x01 = �������澯¼��, 0x02 = �ƶ����¼��, 0x04 = ����¼��, 0x08 = �ֶ�¼�� 0xFF = ȫ��¼��
 //     startTime: ��ѯ��ʼʱ��
 //     endTime  : ��ѯ��ֹʱ��
 */
typedef struct _GLNK_V_SearchFileRequest
{
	uint32_t deviceId;
	uint32_t	channelMask;
	GLNK_DateTime startTime;
	GLNK_DateTime endTime;
	uint32_t  recordTypeMask;
	uint32_t  index;
	uint32_t	count;
	uint32_t  reserve;
} GLNK_V_SearchFileRequest;

/*
 // TLV        : GLNK_T_FILE_INFO
 // Direction  : device -> client
 // Description:
 //     fileName   : �ļ���, ����·��
 //     deviceId   : �豸ID��Ĭ��Ϊ0��
 //     length     : �ļ��ܳ���
 //     frames     : ��֡��
 //     startTime  : ��ʼʱ��
 //     endTime    : ����ʱ��
 //     channel    : ¼��ͨ����
 //     recordType : ¼���������� 0x01 = �������澯¼��, 0x02 = �ƶ����¼��,
 //                  0x04 = ����¼��, 0x08 = �ֶ�¼��
 //     reserve    : ����
 */
typedef struct _GLNK_V_FileInfo
{
	char	        fileName[260];
	uint32_t       deviceId;
	uint32_t       length;
	uint32_t       frames;
	GLNK_DateTime	startTime;
	GLNK_DateTime	endTime;
	uint8_t	      channel;
	uint8_t        recordType;
	uint8_t        reserve[2];
} GLNK_V_FileInfo;



typedef enum _GLNK_WifiSignalLevel
{
	GLNK_Signal_Strong = 0,		//�ź�ǿ							
	GLNK_Signal_Mid,				//�ź�һ��				
	GLNK_Signal_Weak			//�ź���								
}GLNK_WifiSignalLevel;


typedef struct _GLNK_V_WifiInfo
{
	char name[GLNKPACKET_STR_LEN_32];
	char ssid[GLNKPACKET_STR_LEN_32];
	GLNK_WifiSignalLevel level;
}GLNK_V_WifiInfo;


typedef struct _GLNK_V_RecordChgRequest
{
    uint32_t  command;
    GLNK_DateTime   startTime;
    GLNK_DateTime   endTime;
}GLNK_V_RecordChgRequest;

typedef struct _GLNK_V_WifiConfigRequest
{
	char name[GLNKPACKET_STR_LEN_32];
	char ssid[GLNKPACKET_STR_LEN_32];
	char password[GLNKPACKET_STR_LEN_32];
}GLNK_V_WifiConfigRequest;



typedef enum _OWSP_VIDEO_RESOLUTION
{
	RESOLUTION_1080P = 0,
	RESOLUTION_720P,
	RESOLUTION_D1,
	RESOLUTION_VGA,
	RESOLUTION_CIF,
	RESOLUTION_QVGA,
	RESOLUTION_QCIF,
	RESOLUTION_QQVGA
}OWSP_VIDEO_RESOLUTION;


/*
 *	TLV: TLV_T_VA_GET_CONFIG_RSP
 *	Direction: Deivce -> Client
 *	Description: 
 *		channel: the channel of 
 */
typedef struct _TLV_V_VA_GET_CONFIG_RSP
{
	unsigned char 	channel;
	unsigned char  isOpenAudio;
	unsigned char	reverse[2];
	OWSP_VIDEO_RESOLUTION mainStreamResolution;
	unsigned int	mainStreamFrameRate;
	unsigned int mainStreamBitRate;
	
	OWSP_VIDEO_RESOLUTION subStreamResolution;
	unsigned int subStreamFrameRate;
	unsigned int subStreamBitRate;
}TLV_V_VA_GET_CONFIG_RSP;


/*
 *	TLV: TLV_T_VA_SET_CONFIG_REQ
 *	Direction: Client -> Device
 *	Description:
 *
 */

typedef struct _TLV_V_VA_SET_CONFIG_REQ
{
	unsigned char 	channel;
	unsigned char  isOpenAudio;
	unsigned char	reverse[2];
	OWSP_VIDEO_RESOLUTION mainStreamResolution;
	unsigned int	mainStreamFrameRate;
	unsigned int mainStreamBitRate;
	
	OWSP_VIDEO_RESOLUTION subStreamResolution;
	unsigned int subStreamFrameRate;
	unsigned int subStreamBitRate;
}TLV_V_VA_SET_CONFIG_REQ;



typedef struct _TLV_V_Network
{
	unsigned int deviceId;
	unsigned char  hostIP[4];
	unsigned char    hostName[32];
	unsigned char  gateway[4];
	unsigned char  dnsServer[4];
	unsigned char  dnsServer2[4];
	unsigned char  subnetMask[4];

	unsigned char  wifiHostIP[4];
	unsigned char  wifiHostName[32];
	unsigned char  wifiGateway[4];
	unsigned char  wifiDnsServer[4];
	unsigned char  wifiDnsServer2[4];
	unsigned char  wifiSubnetMask[4];
	unsigned char  wifiMac[8];
	unsigned char  mac[8];
	unsigned char  wifiIPMode;
	unsigned char  IPMode;
	unsigned char  reverse[2];
} TLV_V_Network;




/////////////////////////////////////
///////     GT2.0
/////////////////////////////////////

// Functionality:
//   Get GooLink version.
// Parameters:
//   N/A
// Return:
//   current GooLink version
//
unsigned long glnk_get_version();

// Functionality:
//   Terminate GooLink service, but not recycle.
// Parameters:
//   N/A
// Return:
//   1;
int glnk_stop();

// Functionality:
//   Terminate GooLink service, all resources will be released.
// Parameters:
//   N/A
// Return:
//   0 on success, otherwise errorno.
int glnk_destroy();


// Functionality:
//   Push an alarm to GooLink cloud
// Parameters:
//   @[in]alarm: the alarm 
// Return:
//   1 : succeed
//   0:  fail
int glnk_push_alarm(PushAlarm alarm);

// Functionality:
//   get the state of connection to the server
//   
// Return:
//   return 0 fail , module is not build yet
//   return 1 begin to init
//   return 2 sock is opened
//   return 3 connected to server successfully
//   return 4 wait for register respone from server
//   return 5 registered successfully
//   return 6 disconnected from forward server
//   return 7 fail to register from server
//   return 8 reconnecting to server
int glnk_get_state_to_server();





// Functionality:
//   Initialize GooLink terminal services. If net_params is not NULL, the setting
//   will be used to configure the device network interface.
// Parameters:
//   @[in]netparam: init info
//   @[in]upnpparams: network parameter settings, support multiple settings.
//   @[in]param_size: number of network parameter settings
// Return:
//   0 on success, other values on error
//
int glnk_init( InitNetParam* netparam);


// Functionality:
//   Packet video frame packet to the dest OwspData
// Parameters:
//   @[in] channel: the channel of the video data
//     @[in] ismainorsub: is main or subnumber videostream
//	 @[in] isIFrame: 1 for the frame is I frame, 0 for the frame is P frame
//	 @[in] videoData: the video data of the frame
//	 @[in] videoDataLen: the video data length
//	 @[out] ptrDst: last finish owsp data. containing the source data;
// Return:
//   packeted length

int glnk_sendvideodata( unsigned char  channel,
						unsigned char ismainorsub,
			                    char isIFrame, 
			                    void* videoData, 
			                    uint32_t videoDataLen);

// Functionality:
//   Packet audio frame to the dest OwspData
// Parameters:
//   @[in] channel: the channel of the video data
//	 @[in] audioDataLen: the video data of the frame
//	 @[in] audioDataLen: the video data length
//	 @[out] ptrDst: last finish owsp data. containing the source data;
// Return:
//   packeted length
//
int glnk_sendaudiodata(	unsigned char channel, 
						void* audioData, 
						uint32_t audioDataLen);


// Functionality:
//   change network ifname
// Parameters:
//   @[in] ifname: name of network
// Return:
//   1 success 0 fail
//
int glnk_set_ifname(char* ifname);

// Functionality:
//   print the session info, for debugging usage
// Parameters:
//   void
// Return:
//   void
//
void glnk_print_sessions();



#ifdef __cplusplus
}
#endif

#endif // __GOO_LINK_API_H__
