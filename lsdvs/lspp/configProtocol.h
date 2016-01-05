/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ��ͷ�ļ��ṩ��DVS���估����Э��ĺ����ӿ�
**  �ο��ĵ�: <<DVS���估����Э��.doc>> V1.0
**  date           :  2013.11.11
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef _CONFIG_PROTOCOL_H
#define _CONFIG_PROTOCOL_H

#include "ttypes.h"
#include "sysConfig.h"

//
// ���ݰ�����
//
enum MsgCfgDataPackType
{
	MSG_CFG_HEART_BEAT	                = 0x0000,        // ����
	MSG_CFG_GET_SYS_INFO	            = 0x0100,        // ��ȡϵͳ�汾��Ϣ
	MSG_CFG_RESET_DEFAULT_PARAM	        = 0x0200,        // �ָ���������
	MSG_CFG_GET_SYS_TIME	            = 0x0300,        // ��ȡϵͳʱ��
	MSG_CFG_SET_SYS_TIME	            = 0x0400,        // ����ϵͳʱ��
	MSG_CFG_GET_NET_PARAM	            = 0x0500,        // ��ȡ�������
	MSG_CFG_SET_NET_PARAM	            = 0x0600,        // �����������
	MSG_CFG_GET_VIDEO_PARAM	            = 0x0700,        // ��ȡ��Ƶ����
	MSG_CFG_SET_VIDEO_PARAM	            = 0x0800,        // ������Ƶ����
	MSG_CFG_GET_USER_PARAM	            = 0x0900,        // ��ȡ�û�����
	MSG_CFG_SET_USER_PARAM	            = 0x0A00,        // �����û�����
	MSG_CFG_GET_PTZ_CONTROL	            = 0x0B00,        // ��ȡ��̨���Ʋ���
	MSG_CFG_SET_PTZ_CONTROL	            = 0x0C00,        // ������̨���Ʋ���
	MSG_CFG_GET_PTZ_PROTOCOL	        = 0x0D00,        // ��ȡ��̨����Э�� 
	MSG_CFG_SET_PTZ_PROTOCOL	        = 0x0E00,        // ������̨����Э�� 
	MSG_CFG_GET_NTP_PARAM	            = 0x0F00,        // ��ȡNTP���� 
	MSG_CFG_SET_NTP_PARAM	            = 0x1000,        // ����NTP���� 
	MSG_CFG_GET_OSD_PARAM	            = 0x1100,        // ��ȡͨ��OSD ���� 
	MSG_CFG_SET_OSD_PARAM	            = 0x1200,        // ����ͨ��OSD ���� 
	MSG_CFG_GET_EMAIL_PARAM	            = 0x1300,        // ��ȡ�ʼ����� 
	MSG_CFG_SET_EMAIL_PARAM	            = 0x1400,        // �����ʼ����� 
	MSG_CFG_GET_AUDIO_ENCODE	        = 0x1500,        // ��ȡ��Ƶ�������
	MSG_CFG_SET_AUDIO_ENCODE	        = 0x1600,        // ������Ƶ�������
	MSG_CFG_GET_VIDEO_ENCODE	        = 0x1700,        // ��ȡ��Ƶ�������
	MSG_CFG_SET_VIDEO_ENCODE	        = 0x1800,        // ������Ƶ�������
	MSG_CFG_GET_CHANNEL_PARAM	        = 0x1900,        // ��ȡͨ������
	MSG_CFG_SET_CHANNEL_PARAM	        = 0x1A00,        // ����ͨ������
	MSG_CFG_GET_AUTO_MAINTAIN	        = 0x1B00,        // ��ȡ�Զ�ά������
	MSG_CFG_SET_AUTO_MAINTAIN	        = 0x1C00,        // �����Զ�ά������
	MSG_CFG_GET_RECORD_PARAM	        = 0x1D00,        // ��ȡ¼�����
	MSG_CFG_SET_RECORD_PARAM	        = 0x1E00,        // ����¼�����
	MSG_CFG_SEARCH_PTZ_PROTOCOL	        = 0x1F00,        // ������̨����Э��
	MSG_CFG_GET_SYS_BASE	            = 0x2000,        // ��ȡϵͳ��������
	MSG_CFG_SET_SYS_BASE	            = 0x2100,        // ����ϵͳ��������
	MSG_CFG_SET_PTZ_CMD	                = 0x2200,        // ������̨��������
	MSG_CFG_GET_SD_CARD_INFO	        = 0x2300,        // ��ȡSD����Ϣ
	MSG_CFG_GET_USB_HD_INFO	            = 0x2400,        // ��ȡUSBӲ����Ϣ	
	MSG_CFG_GET_ALARM_PARAM	            = 0x2500,        // ��ȡ�澯��Ϣ
	MSG_CFG_SET_ALARM_PARAM	            = 0x2600,        // ���ø澯��Ϣ
	MSG_CFG_GET_RS232_PARAM	            = 0x2700,        // ��ȡRS232����
	MSG_CFG_SET_RS232_PARAM	            = 0x2800,        // ����RS232����
	MSG_CFG_REBOOT_SYSTEM	            = 0x2900,        // ϵͳ����
	MSG_CFG_SEND_EMAIL	                = 0x2A00,        // ����Email
	MSG_CFG_AUTH_RAND_NUM	            = 0x2B00,        // ��ȡ��֤�����
	MSG_CFG_LOGIN_AUTH	                = 0x2C00,        // ��¼��֤
	MSG_CFG_SEARCH_RECORD	            = 0x2D00,        // ����¼��
	MSG_CFG_SEARCH_SNAP_FILE	        = 0x2E00,        // ����ץ���ļ�
	MSG_CFG_GET_PC_PARAM	            = 0x2F00,        // ��ȡPC����
	MSG_CFG_SET_PC_PARAM	            = 0x3000,        // ����PC����
	MSG_CFG_GET_LICENCE_INFO	        = 0x3100,        // ��ȡlicence��Ϣ
	MSG_CFG_SET_MIDSYS_CONFIG	        = 0x3200,        // �����м������
	MSG_CFG_GET_MIDSYS_CONFIG	        = 0x3300,        // ��ȡ�м������
	MSG_CFG_GET_DOOR_RULE	            = 0x3400,        // ��ȡ�Ź�����Ϣ
	MSG_CFG_SET_DOOR_RULE	            = 0x3500,        // �����ǹ�����Ϣ
	MSG_CFG_GET_PC_CONFIG	            = 0x3600,        // ��ȡPC����
	MSG_CFG_SET_PC_CONFIG	            = 0x3700,        // ����PC����
	MSG_CFG_GET_LP_PARAM	            = 0x3800,        // ��ȡLP����
	MSG_CFG_SET_LP_PARAM	            = 0x3900,        // ����LP����
	MSG_CFG_GET_DATA_UPLOAD	            = 0x3A00,        // ��ȡ�����ϴ�����
	MSG_CFG_SET_DATA_UPLOAD	            = 0x3B00,        // ���������ϴ�����
	MSG_CFG_GET_ABDOOR_PARAM	        = 0x3C00,        // ��ȡAB�Ų���
	MSG_CFG_SET_ABDOOR_PARAM	        = 0x3D00,        // ����AB�Ų���
	MSG_CFG_GET_FIV_PARAM	            = 0x3E00,        // ��ȡFIV����
	MSG_CFG_SET_FIV_PARAM	            = 0x3F00,        // ����FIV����
	MSG_CFG_GET_FIV_CONFIG	            = 0x4000,        // ��ȡFIV����
	MSG_CFG_SET_FIV_CONFIG	            = 0x4100,        // ����FIV����	
	MSG_CFG_GET_RF433_CONFIG            = 0x4200,       // ��ȡRF433����������
    MSG_CFG_SET_RF433_CONFIG            = 0x4300,       // ����RF433����������
	MSG_CFG_GET_EYE_CONFIG	            = 0x4400,        // ��ȡEYE����
	MSG_CFG_SET_EYE_CONFIG	            = 0x4500,        // ����EYE����
	MSG_CFG_CLEAR_PC_NUM	            = 0x4600,        // ��������
	MSG_CFG_GET_IO_CONFIG	            = 0x4700,        // ��ȡIO����
	MSG_CFG_SET_IO_CONFIG	            = 0x4800,        // ����IO����
	MSG_CFG_GET_RF433M_PUBLIC	        = 0x4900,        // ��ȡRF433M��������
	MSG_CFG_SET_RF433M_PUBLIC	        = 0x4A00,        // ����RF433M��������
	MSG_CFG_GET_LED_SHOW_SETTING	    = 0x4B00,       // ��ȡLED��ʾ����
	MSG_CFG_SET_LED_SHOW_SETTINT	    = 0x4C00,        // ����LED��ʾ����
	MSG_CFG_GET_LED_BOARD_SETTING	    = 0x4D00,        // ��ȡLED��������
	MSG_CFG_SET_LED_BOARD_SETTING	    = 0x4E00,        // ����LED��������	
	MSG_CFG_GET_MASTERSLAVER_SETTING	= 0x4F00,        // ��ȡ�����豸����
	MSG_CFG_SET_MASTERSLAVER_SETTING	= 0x5000,        // ���������豸����	
	MSG_CFG_SET_URUMCHILP_SERVER_PARAM	= 0x5400,        // ������³ľ�복�ƶԽӷ���������
	MSG_CFG_GET_URUMCHILP_SERVER_PARAM	= 0x5500,        // ��ȡ��³ľ�복�ƶԽӷ���������	
	MSG_CFG_GET_THREEG_PARAM	        = 0x5100,        // ��ȡ3G�豸����
	MSG_CFG_SET_THREEG_PARAM	        = 0x5200,        // ����3G�豸����
	MSG_CFG_GET_THREEG_STATE	        = 0x5300,        // ��ȡ3G�豸״̬
	MSG_CFG_GET_WIFI_SCAN_RESULT	    = 0x5600,        // ��ȡwifi�����豸�Ľ��
	MSG_CFG_GET_WIFI_NETWORK_CONFIG     = 0x5700,        // ��ȡwifi��������
	MSG_CFG_SET_WIFI_NETWORK_CONFIG     = 0x5800,        // ����wifi��������
	MSG_CFG_GET_WIFI_CONNECT_CONFIG	    = 0x5900,        // ��ȡwifi��������
	MSG_CFG_SET_WIFI_CONNECT_CONFIG	    = 0x5A00,        // ����wifi��������
	MSG_CFG_GET_SYNOVATE_CONFIG	          = 0x5B00,        // /*synovate_add*/
	MSG_CFG_SET_SYNOVATE_CONFIG	          = 0x5C00,        // /*synovate_add*/
	MSG_CFG_GET_FTP_REC                 = 0x5D00,         // ��ȡFTP¼����ز��� 
	MSG_CFG_SET_FTP_REC                 = 0x5E00,         // ����FTP¼����ز��� 
 	MSG_CFG_GET_RS485_PARAM	            = 0x5F00,        // ��ȡRS485����
	MSG_CFG_SET_RS485_PARAM	            = 0x6000,        // ����RS485����
	MSG_CFG_GET_FTP_UPLOAD	            = 0x6100,        // ��ȡFTP�ϴ�������Ϣ��ز��� 
	MSG_CFG_SET_FTP_UPLOAD                 = 0x6200,        // ����FTP�ϴ�������Ϣ��ز��� 
	MSG_CFG_GET_RLW_TXTPATH             = 0x6300,       // �г�ƣ��Ӧ�û�ȡ�����ļ�·��
 	MSG_CFG_UPLOAD_ALARM                 = 0x6400,        // �������ޱ����ϴ�
};

//
// ����������
//
enum MsgCfgDataSubType
{
	MSG_CFG_DATA_REQUEST	            = 0x01,        // ����
	MSG_CFG_DATA_RESPONSE	            = 0x02,        // Ӧ��
	MSG_CFG_DATA_ERROR	                = 0x03,        // ����
	MSG_CFG_DATA_ALARM	                = 0X04,        // ����
};


#define PACK_ALIGN	__attribute__((packed))



//�������� 
#define MSG_ALARM_PC_UPPER_LIMIT 0xA001 //�������޸澯 

//�����ϴ��ṹ�� 
typedef struct dvsAlarm 
{ 
	int 	channel;         //����ͨ�� 
	int 	alarmType;         //��������
	char 	alarmTime[20];     //�澯������ʱ��,��ʽ���硰2011-9-30 16:12:11�� 
	char 	alarmInfo[64];     //�������� 
	char 	reserved[128];

} PACK_ALIGN DVS_ALARM; 

//
// ϵͳ������Ϣ
//
typedef struct ConfigSysInfo
{
	char	configureVersion[16];        // ���ð汾��
	char	softwareVersion[16];        // ����汾��
	char	hardwareVersion[16];        // Ӳ���汾��
	char	serialNo[16];                // ��Ʒ���к�
	int 	authorization;                // Ϊ�����㷨���ݲ���int��������ʾ�Ƿ���Ȩ
                                          /*0 ��ʾ��ʼ���㷨����
                                          1	��ʾ��ʼ���㷨�ɹ��������Ѿ���Ȩ
                                          2 ��ʾ��ʼ���㷨�ɹ�������û����Ȩ*/
} PACK_ALIGN CONFIG_SYS_INFO;

typedef struct ConfigBase 
{
	char	    	devName[32];        // �豸����
	char	    	devId[32];            // �豸ID
	unsigned char	chipNum;            // 3512оƬ����
	unsigned char	channelNum;            // ʵ�ʵ�ͨ����
	unsigned char	ptzNum;                // ʵ�ʵ���̨����Э������
	int	        	langID;                // ����ID
	char	timeZone;            // ʱ�� �ϵ�
	unsigned char	year;                // ϵͳʱ��
	unsigned char	month;
	unsigned char	day;
	unsigned char	hour;
	unsigned char	minute;
	unsigned char	second;
	unsigned char	ntpType;            // 0,NONE,1,PC,2,NTP
	char	    	ntpAddr[81];        // �ǿ�ʱ���SNTP ������ͬ��ʱ��
	unsigned short	ntpPort;            // Ĭ��Ϊ123
	int	        	videoStandard;        // ��Ƶ��ʽ: 0:PAL�ơ�1:NTSC��
	unsigned short	serverPort;            // �����Լ����ö˿�
	unsigned short	httpPort;            // http�˿�
	int	        	talkPort;            // �Խ��˿ڣ���/��һ���˿�
	int	        	streamPort;            // ý�����˿�
	int	        	talkVoiceInLevel;    // �Խ���������
	int	        	talkVoiceOutLevel;    // �Խ��������
	char	    	dsEnableFlag;        // �ر�˫����:0, ��˫����:1, Ĭ��0
	unsigned char	videoPortInput;        // ��Ƶ����˿ڸ���
	unsigned char	videoPortOutput;    // ��Ƶ����˿ڸ���
	unsigned char	audioPortInput;        // ��Ƶ����˿ڸ���
	unsigned char	audioPortOutput;    // ��Ƶ����˿ڸ���	
	unsigned char	alarmPortInput;        // �澯����˿�
	unsigned char	alarmPortOutput;    // �澯����˿�	
	int         	timeIntZone;
	int             iDevMACNum;            // �豸��,��MAC��ַ����,���ɺ���Ϊ:FiNetConvertMacToInt(),��д��Flash
	unsigned int	shopID;                // ���̺�,���ڵ���0,Ĭ��Ϊ0,����Ftp�ϴ�������ϢĿ¼����
} PACK_ALIGN CONFIG_BASE;

//
// ��Ƶ����
//
typedef struct ConfigVideoParam
{
	unsigned char	channel;            // ͨ����
	int	        	brightness;            // ��ͨ��������ֵ 0-255
	int	        	contrast;            // ��ͨ���ĶԱȶ�ֵ
	int	        	hue;                // ��ͨ����ɫ��
	int	        	saturation;            // ��ͨ���ı��Ͷ�
	int	        	exposure;            // ��ͨ���ı����
} PACK_ALIGN CONFIG_VIDEO_PARAM;

//
// ��������б�
//
typedef struct ConfigNetwork
{
	unsigned char	netType;            // 0-DHCP, 1-STATIC, 2-ADSL
	unsigned char	dhcpType;            // dhcpʹ�ܱ�ʶ, 0: ��ֹ 1: ʹ��
	char	    	ip[80];                // support domain
	char	    	netmask[16];        // ��������
	char	    	gateway[16];        // ����
	char	    	dns[16];            // ��DNS
	char	    	dns2[16];            // ����DNS
	char	    	mac[24];            // �����ַ
	char	    	broadAddr[16];        // �㲥��ַ
	char	    	webPort[8];            // web�˿�	

} PACK_ALIGN CONFIG_NETWORK;

//
// 3G�豸����
//
typedef struct ConfigThreegNetParam
{
	int 	enableFlag;        //0��ʾ��ʹ��3G���磬1��ʾʹ��3G����.
	int 	connectState;    //0��ʾ3G�����ѶϿ���1��ʾ3G����������.--ֻ��
	char 	wanIP[16];         //���ųɹ����ȡ�Ĺ���IP���������ʧ�ܣ����ֵ��"0.0.0.0".--ֻ��
	char 	reserve[64];    //Ԥ�����ƹ���
} PACK_ALIGN CONFIG_THREEG_NET_PARAM;

//
//3G�豸״̬
//
typedef struct ThreegDevState
{
	int 	signalState;     //3G�����ź�״̬��0��ʾ���źţ�1 ~ 5 ��5���źŵȼ���5���źű�ʾ�ź�ǿ����ǿ.--ֻ��
	char 	reserve[64];    //Ԥ�����ƹ���
} PACK_ALIGN CONFIG_THREEG_DEV_STATE;

//
// �û�����
//
typedef struct ConfigUser 
{
	char	    	userName[32];        // �û���
	char	    	pwd[32];            // ����
	int	        	level;                // �û��ļ���; 0,NONE,1,ADMIN,2,����û�;
	unsigned int	capability;            // �û���Ȩ��;
} PACK_ALIGN CONFIG_USER;

typedef char PTZ_NAME[32];
typedef struct ConfigPtzName
{
	int	        	ptzNum;                // Э������
	PTZ_NAME		ptzName[1];            // Э������

} PACK_ALIGN CONFIG_PTZ_NAME;

//
// ��̨Э������
//
typedef struct ConfigPtzProtocol
{    
	char	    	ptzName[32];        // Э������
	unsigned char	bWaitResponse;        // �豸�������Ƿ�Ӧ��
	unsigned char	cSpeedPanDefault;    // ˮƽ�ٶ�
	unsigned char	cSpeedPanMin;
	unsigned char	cSpeedPanMax;
	unsigned char	cSpeedTiltDefault;    // ��ֱ�ٶ�
	unsigned char	cSpeedTiltMin;
	unsigned char	cSpeedTiltMax;
	unsigned char	cSpeedZoomDefault;    // �Ŵ���С�ٶ�
	unsigned char	cSpeedZoomMin;
	unsigned char	cSpeedZoomMax;
	unsigned char	cPosDefault;        // Ԥ��λ
	unsigned char	cPosMin;
	unsigned char	cPosMax;
	PTZ_CONTROL_CMD	cmd[MAX_CMD_PER_PTZ];
	unsigned char	bIsManual;            // �Ƿ��û��Զ���Э��	
} PACK_ALIGN CONFIG_PTZ_PROTOCOL;

//
// ��̨��������
//
typedef struct ConfigPtzControl
{
	unsigned char	channel;            // ͨ����
	char	    	ptzName[32];        // Э������
	unsigned int	baudRate;            // ������
	unsigned char	dataBits;            // ����λ
	unsigned char	stopBits;            // ֹͣλ
	unsigned char	parity;                // У��λ
	unsigned char	cAddr;                // ��ַλ
	unsigned char	cSpeedPan;            // ��ǰˮƽ�ٶ�
	unsigned char	cSpeedTilt;            // ��ǰ��ֱ�ٶ�
	unsigned char	cSpeedZoom;            // ��ǰ�Ŵ���С�ٶ�
	unsigned char	cPos;                // ��ǰԤ��λ
} PACK_ALIGN CONFIG_PTZ_CONTROL;

//
// NTP����
//
typedef struct ConfigNtp
{
	unsigned char	ntpType;            // 0,NONE,1,PC,2,NTP
	unsigned short	ntpPort;            // Ĭ��Ϊ123	
	char	    	ntpAddr[81];        // �ǿ�ʱ���SNTP ������ͬ��ʱ��

} PACK_ALIGN CONFIG_NTP;
    
//
// OSD��������
//
typedef struct ConfigOsdInfo 
{
	unsigned char	channel;            // ͨ����
	CONFIG_OSD_TIME	osdTime;            // OSD ʱ��
	CONFIG_OSD_LOGO	osdLogo;            // OSD Logo
} PACK_ALIGN CONFIG_OSD_INFO;

//
// ��Ƶ�������
//
typedef struct ConfigVideoEncode 
{
	unsigned char	channel;            // ͨ����
	unsigned char	chType;                // 0:������, 1:������
	int	        	videoStandard;        // ��Ƶ��ʽ: 0:PAL�ơ�1:NTSC��
	int	        	resolution;            // �ֱ���: 0:Qicf��1:Cif��2:HD1��3:D1
	int	        	bitrateType;        // λ������: 0:CBR��1:VBR
	int	        	quality;            // ����
	int	        	frameRate;            // ֡��
	int         	iFrameInterval;        // I֡���
	int         	preferFrame;        // ֡������
	int         	qp;                    // ����ϵ��
	int         	encodeType;            // ����Ƶ��:0����Ƶ��:1����Ƶ��:2
} PACK_ALIGN CONFIG_VIDEO_ENCODE;

//
// ��Ƶ�������
//
typedef struct ConfigAudioEncode
{
	unsigned char	channel;            // ͨ����
	int	        	sampleRate;            // ������
	char	    	bitWidth;            // λ��
	char	    	encodeType;            // ���뷽ʽ
	char	    	amrMode;            // amr����ģʽ
	char	    	amrFormat;            // amr�����ʽ
} PACK_ALIGN CONFIG_AUDIO_ENCODE;

//
// �ʼ�����
//
typedef struct ConfigEmailParam
{
	int	        	activeFlag;
	char	    	serverName[64];
	int	        	serverPort;
	char	    	userName[64];
	char	    	password[32];
	char	    	senderName[32];
	char	    	emailTitle[64];
	char	    	recvAddr1[64];
	char	    	recvAddr2[64];
	char	    	recvAddr3[64];
} PACK_ALIGN CONFIG_EMAIL_PARAM;

//
// �Զ�ά��
//
typedef struct ConfigAutoMaintain
{
	unsigned char	rebootFlag;            // ������ʶ
	unsigned int	rebootDate;            // 0:none; 1��7:����һ����; 8:everyDay;
	unsigned int	rebootTime;
	int	        	delFileFlag;        // �Ƿ��Զ�ɾ���ļ�
	int	        	dayNumber;            // ������֮ǰɾ����

} PACK_ALIGN CONFIG_AUTO_MAINTAIN_PARAM;

//
// ¼�����
//
typedef struct ConfigRecordParam
{
	unsigned char	    	channel;    // ͨ����
	CONFIG_RECORD_PUBLIC	recPublic;    // ��������
	CONFIG_RECORD_HAND		recHand;    // �ֶ�¼�����
	CONFIG_RECORD_TIMER		recTimer;    // ��ʱ¼�����
} PACK_ALIGN CONFIG_RECORD_PARAM;

//
// ͨ������
//
typedef struct ConfigChannelParam
{
	unsigned char	channel;            // ͨ����
	char	    	channelName[32];    // ͨ������
	int	        	voiceInput;            // ��������
	int	        	voiceOutput;        // �������
} PACK_ALIGN CONFIG_CHANNEL_PARAM;

//
// PTZ�������
//
typedef struct ConfigPtzCmd
{
	unsigned char	channel;            // ͨ����
	char	    	cmd[32];            // ����
	int	        	param;                // ����
} PACK_ALIGN CONFIG_PTZ_CMD;

//
// �澯����
//
typedef struct ConfigAlarmParam
{
	unsigned char	alarmInId;
	unsigned char   enalbeFlag;            // 0: close; 1: open;
	unsigned char   type;                // 0: ����; 1: ���գ�
	char	    	alarmInName[32];
	CONFIG_ALARM_TIMER		alarmInDetectTimer;
	CONFIG_ALARM_TRIGGER	trigger;
	char            reserve[29];
} PACK_ALIGN CONFIG_ALARM_PARAM;

//
// SD����Ϣ
//
typedef struct ConfigSdCardInfo
{
	unsigned char   enalbeFlag;
} PACK_ALIGN CONFIG_SD_CARD_INFO;

//
// USBӲ����Ϣ
//
typedef struct ConfigUsbHdInfo
{
	unsigned char   enalbeFlag;
} PACK_ALIGN CONFIG_USB_HD_INFO;

//
// RS232����
//
typedef struct ConfigRs232Param
{
	unsigned int	baudRate;            // ������
	unsigned char	dataBits;            // ����λ
	unsigned char	stopBits;            // ֹͣλ
	unsigned char	parity;                // У��λ
} PACK_ALIGN CONFIG_RS232_PARAM;

//
// RS485����
//
typedef struct ConfigRs485Param
{
	unsigned int	baudRate;            // ������
	unsigned char	dataBits;            // ����λ
	unsigned char	stopBits;            // ֹͣλ
	unsigned char	parity;                // У��λ
} PACK_ALIGN CONFIG_RS485_PARAM;
//
// ��¼��֤
//
typedef struct ConfigLoginAuth 
{
	char	    	userName[32];        // �û���
	char	    	auth[32];            // ��֤��Ϣ: md5(��֤�����+����)
	int	        	level;                // �û��ļ���: 0,NONE; 1,ADMIN; 2,����û�;
	unsigned int	capability;            // �û���Ȩ��;
} PACK_ALIGN CONFIG_LOGIN_AUTH;

//
// ����������Ϣ
//
typedef struct ConfigSearchInfo
{
	unsigned char	channel;            // ͨ����
	char	    	startTime[19];        // ��ʼʱ��(YYYY-MM-DD hh:mm:ss)
	char	    	endTime[19];        // ����ʱ��(YYYY-MM-DD hh:mm:ss)
	unsigned long	fileType;            // �ļ�����
	int	        	offset;                // ƫ��
} PACK_ALIGN CONFIG_SEARCH_INFO;

//
// ¼���б�
//
typedef struct ConfigRecordNode
{
	char	    	recordName[128];    // ¼���ļ���
	char	    	startTime[19];        // ��ʼʱ��(YYYY-MM-DD hh:mm:ss)
	char	    	endTime[19];        // ����ʱ��(YYYY-MM-DD hh:mm:ss)
	unsigned long	recordLen;            // ¼�񳤶�
	unsigned long	recordType;            // ¼������	
} PACK_ALIGN CONFIG_RECORD_NODE;

typedef struct ConfigRecordList
{
	int	            	totalNum;        // �ܸ���
	int	            	recordNum;        // ¼�����
	CONFIG_RECORD_NODE  recordList[1];    // ¼���б�
} PACK_ALIGN CONFIG_RECORD_LIST;

//
// ץ���б�
//
typedef struct ConfigSnapNode
{
	char	    	snapName[128];        // ץ���ļ���
	char	    	snapTime[19];        // ץ��ʱ��(YYYY-MM-DD hh:mm:ss)
	unsigned long	snapLen;            // ץ���ļ�����
	unsigned long	snapType;            // ץ���ļ�����	
} PACK_ALIGN CONFIG_SNAP_NODE;

typedef struct ConfigSnapList
{
	int	            	totalNum;        // �ܸ���
	int	            	snapNum;        // ץ���ļ�����
	CONFIG_SNAP_NODE	snapList[1];    // ץ���ļ��б�
} PACK_ALIGN CONFIG_SNAP_LIST;

//
// PC����
//
typedef struct ConfigPcParam
{
	unsigned char	channel;        // ͨ����
	int	        	nWidth;            // ͼ����
	int	        	nHeight;        // ͼ��߶�
	int	        	nRoiLeft;        // ��������������
	int	        	nRoiTop;        // ������򶥱�����
	int	        	nRoiRight;        // ��������ұ�����
	int	        	nRoiBottom;        // �������ױ�����
	int	        	bOriVertical;    // ����߶�����(����ͷ��AB�ż�ⷽ��: 1 ��ֱ�߶���0 ˮƽ�߶�)
	int	        	nLoiterTime;     // �������ʱ������ʱ��(��λ������), ��Χ: ���롫10��(256֡/25֡)
	int	        	nFPSOfDet;        // ���֡��: ����ʵ���ܵ�֡�����ã���ΧΪ��5֡/�롫25֡/��(Ҳ��������Ϊ0, ��ʾ�˲�����Ч )
	int	        	nMaxMatchDist;    // �����ͷƥ����룬�����ͷ��������������Ϊ���µ���ͷ�����ƥ�������0��150��5����ͷ����Ĭ��Ϊ30��1����ͷ��
                                    // ���߱��˵���ͷ��Ĭ��ֵΪ30, �����Ҫ�������ڼ�������
                                    // �ƶ��ٶ������ã�����ƶ�����������С��ֵ���ƶ��Ͽ������ô�ֵ��
	int	        	bOriEnter;        // ������������
	int	        	bOpenPcDetect;    // �Ƿ��������㷨
	int	        	videoMode;        // ��Ƶģʽ: Cif, 1/9D1, QCif
	int	        	nStepMotion;    // �Ƿ�̨���˶�; 1:̨���˶�, 0:ƽ���˶�.
	int         	nMinHeadWidth;    /* ��С��ͷ��ȣ���λ���أ�Ĭ��40���أ���С30����*/
    
	int         	nMaxHeadWidth;  /* �����ͷ��ȣ���λ���أ�Ĭ��60���أ����100����*/
	int         	bHighPrecision;    /* ʹ�ܸ߾���ѡ����ͳ��ֵ�Ŀ��Ŷȣ���δ������߻��߽���ͳ��ֵ

                               ==TRUE��ʹ�ܸ߾��ȣ������þ�ֹ�ڵ��������˵��㷨�������ڴ��ڱ�����ͳ�����صĻ�����
                                	�����ã���ֹ�ڵ㲻�ᵼ�����˼�������ʱ��һ����ͣ���ˣ�
                                	�����ã����Ч�����õ���ͷ����⵽�Ĵ���ƫ�٣�����©����

                               ==FALSE����ֹ�߾��ȣ��رվ�ֹ�ڵ����������㷨�������ڲ����ڱ�����ͳ�ƵĻ�����
                                	�����ã����Ч�����õ���ͷ����⵽�Ĵ���ƫ�٣������ڶ�©����
                                	�����ã���ֹ�ڵ���ܵ������˼�������ʱ��һ����ͣ���ˣ�

                            	�������������ڱ�����ͳ�����صĻ���������ΪTRUE����������ΪFALSE��*/
} PACK_ALIGN CONFIG_PC_PARAM;

//
// Licence��Ϣ
//
typedef struct ConfigLicenceInfo
{
	unsigned int	flag;                            // �ļ�ͷ���
	unsigned char	oemVersion;                        // OEM�汾
	unsigned char	platform;                        // ƽ̨
	unsigned int	odType[MAX_CHANNEL_NUM];        // �㷨����: ����ͬʱ֧�ֶ����㷨 OD_PC|OD_FIV
	unsigned char	odFlag[MAX_CHANNEL_NUM];        // �Ƿ����㷨
	unsigned char	encodeFlag[MAX_CHANNEL_NUM];    // �Ƿ�������
	unsigned char	serialType;                        // ��������
	unsigned char	protocolType;                    // Э������
	unsigned char	pcType;                            // ����ϵͳ����:��������,�ǳ�������
	unsigned char	dataUploadFlag;                    // �Ƿ�֧��ʵʱ�����ϴ�
	unsigned char	fivRf433mFlag;                    // �Ƿ��������FIV
	unsigned char   led             : 1;            // 1 - LED��־ - 1
	unsigned char	mainSlave	    : 1;            // 2 - ���ӱ�־ - 2
	unsigned char	fivType         : 1;            // 4 - fiv��ͬ��Э������ - 4	
	unsigned char	threeg	        : 1;            // 8 - 3Gģ���־ - 8
	unsigned char	wifi	        : 1;            // 1 - wifiģ���־ - 1
	unsigned char	wlPlatform	    : 1;            // 2 - ��³ľ�복�Ʋ�׽��,���Ϊ0,��ͻ��˲���Ҫ��ʾƽ̨������������
	unsigned char	bsl             : 1;            // 4 - ������Э��,(�������Ҫ�ͻ��˹���)
	unsigned char	synovate	    : 1;            // ˼γЭ��
	unsigned char	czcf	        : 1;            // ���д�����ץ��
	unsigned char	shelterf	    : 1;            // �ڵ�����ץ��	
    unsigned char 	qirui	        : 1;            // ��������
    unsigned char   jyzht             : 1;            // ��Ӣ��ͨ
    unsigned char   rlweye             : 1;            // �г�ƣ�ͼ��,add at 2013.07.31(��ÿʮ���ӵ������֤)
	unsigned char	bjgq	        : 1;             // ��������(led)&��������
	unsigned char	reserved	    : 2;            // ����


	unsigned char	devType;                        // �豸����, 0x01��ʾ��һ�����0x02��ʾ��һ�����0x03��ʾ2·LTY DVS��0x04��ʾ3·wkp DVS��0x05��ʾ4·����DVS��0x06��ʾ3512��·D1
	char	    	unused[2];                        // ��չ	

} PACK_ALIGN CONFIG_LICENCE_INFO;


//
// �Ź������
//
typedef struct ConfigDoorRule
{
	int		pcType;
	int		doorType;
	int		doorRule;
} PACK_ALIGN CONFIG_DOOR_RULE;

//
// ���˲���
//
typedef struct ConfigPcConfig
{
	char	bSaveHistoryData;
	char	countTime[2][12];            // �������˵�ʱ���,ʱ���1Ĭ��:00:00-23:59;ʱ���2Ĭ��:0
    char    clrCountTime[2][9];         // JSYD�� �����ƶ�licence, ��������ʱ��㡣ʱ������磺12:00:00.
   	char 	upModNum;                    //�ϳ�ģʽ������ֵ
	char 	downModNum;                    //�³�ģʽ������ֵ
	char 	remainPercent;                //����ʣ����������������İٷֱ�
	int		limitedNumber;            // ������������������(��-��)    
	char	reserved[206];
} PACK_ALIGN CONFIG_PC_CONFIG;

//
// ���Ƽ���㷨����
//
typedef struct ConfigLpParam
{
	unsigned char	channel;                // ͨ����
	int	        	nWidth;                    // ͼ����
	int	        	nHeight;                // ͼ��߶�	
	int	        	nMinTrackFrame;            // ���ٸ���֡��
	int	        	nMaxLostFrame;            // ���ʧ��֡��
	int	        	nMaxDistance;            // ������ٵ������
	int	        	nDetectCarType;            // �Ƿ��⳵ͷ: 0 ��ֹ;  1 ��⳵ͷ;  2 ��⳵β
	int	        	bDetectPlate;            // �Ƿ��⳵��: 1 ʹ��; 0 ��ֹ
	int	        	bEnableTrackCar;        // �Ƿ���������: 1 ʹ��; 0 ��ֹ
	int	        	bEnableTrackPlate;        // �Ƿ���������: 1 ʹ��; 0 ��ֹ
} PACK_ALIGN CONFIG_LP_PARAM;

//
// �����ϴ�Э��
//
typedef struct ConfigDataUpload
{
	int		flag;            // 1Ϊ����, 0Ϊ�ر�
	char	ip[80];            // ������IP
	int		port;            // �������˿�
	int		interval;        // ������10��������
	int		mode;            // 1: ��ʾ����ģʽ, 0: ��ʾ��ͨģʽ
} PACK_ALIGN CONFIG_DATA_UPLOAD;

//
// AB�Ų���
//
typedef struct ConfigABDoorParam
{
	unsigned char	channel;            // ͨ����
	int	        	nWidth;                // ͼ����
	int	        	nHeight;            // ͼ��߶�
	int	        	nRoiLeft;            // ��������������
	int	        	nRoiTop;            // ������򶥱�����
	int	        	nRoiRight;            // ��������ұ�����
	int	        	nRoiBottom;            // �������ױ�����
	int	        	bOriVertical;        // ����߶�����(����ͷ��AB�ż�ⷽ��: 1 ��ֱ�߶���0 ˮƽ�߶�)
	int	        	nLoiterTime;         // �������ʱ������ʱ��(��λ������)
	int	        	nFPSOfDet;            // ���֡��
	int	        	nMaxMatchDist;        // �����ͷƥ����룬�����ͷ��������������Ϊ���µ���ͷ
                                        // ���߱��˵���ͷ��Ĭ��ֵΪ30, �����Ҫ�������ڼ�������
                                        // �ƶ��ٶ������ã�����ƶ�����������С��ֵ���ƶ��Ͽ������ô�ֵ��
	int	        	bOriEnter;            // ������������
                                        // ��ֱ����: 0��ʾ���ϵ����ǽ��뷽�� 1��ʾ���µ����ǽ��뷽�� 
                                        // ˮƽ����: 0��ʾ�������ǽ��뷽�� 1��ʾ���ҵ����ǽ��뷽��
	int	        	bOpenABDoorDetect;    // �Ƿ��������㷨
	int	        	stayerNum;            // ��������
	int	        	sensitivity;        // ������ (1 - 9)
	int	        	videoMode;            // ��Ƶģʽ
} PACK_ALIGN CONFIG_ABDOOR_PARAM;

//
// Fiv����
//
typedef struct ConfigFivParam
{
	unsigned char	channel;            // ͨ����
	float	    	fAlpha;                // ����ѧϰ�ʣ�0��0.3����Ĭ��ȡ0.01
	float	    	fFactor;            // �жϷ�ֵF��0.5��3.5����Ĭ��ȡ2.5
	float	    	fT;                    // �жϷ�ֵT��0.3~0.9����Ĭ��ȡ0.7
	int	        	nWindowSize;        // ���㾫�ȣ���С���㴰�ڣ�1��5����Ĭ��ȡ3������3x3��
	int	        	nTargetSize;        // ������С�ߴ磨��λΪ"����"��1��10000����Ĭ��ȡ36��6*6��
	int	        	nMaxLost;            // ��ඪʧ֡������λΪ"֡"�����������ؼ�λ��֮֡������ʧ��֡������Ĭ��ȡ3
	int	        	nMinFrame;            // ���ٴ���֡������λΪ"֡"��������ڶ��ٹؼ�λ��֡���ж�Ϊ��Ч���󣩣�Ĭ��ȡ1
	int	        	nMaxDistance;        // �������ٹؼ�λ�����ƥ����루��λΪ�����ء��������˾��룬��Ϊ����ͬһ�����󣩣�Ĭ��ȡ10
} PACK_ALIGN CONFIG_FIV_PARAM;

//
// Fiv����
//
typedef struct ConfigFivConfig
{
	unsigned char	channel;        // ͨ����
	int	        	width;            
	int	        	height;
	int	        	left;            // �������Ĭ������������
	int	        	top;
	int	        	right;
	int	        	bottom;
	int	        	fivFlag;        // 0: �����1��������
	int	        	fivType;        // 0: ��Ч��1: ������2�����У�3��Խ��
	struct RGN
    {
    	int rgnType;                // 0: ��Ч; 1: ���Σ�2��Բ�Σ�3���ߣ�4����ͷ
    	struct Rect
        {
        	int x1;
        	int y1;
        	int x2;
        	int y2;
        } rect;
    } rgn[FIV_MAX_RECT_NUM];
} PACK_ALIGN CONFIG_FIV_CONFIG;

//
// RF433M����
//
// �ͻ�������Ľṹ��
typedef struct ConfigRf433mReq
{
	unsigned char 	totalFlag;    // �Ƿ��������еĴ���������, 0: ����; 1: ��
	char	    	id[5];        // �������ID�ŵô���������,���totalFlag = 1,���ֶ���Ч
} PACK_ALIGN CONFIG_RF433M_REQ;

// ����RF433M��Ӧ�Ľṹ��
typedef struct ConfigRf433mConfig
{
	char	    	id[5];                    // ���豸ID
	unsigned char	type;                    // ���豸����
	char	    	name[32];                // ���豸����
	unsigned char 	guard;                    // 0: ����; 1: ���
	CONFIG_ALARM_TIMER     	timerGuard;        // ��ʱ����,���
	CONFIG_ALARM_TRIGGER	trigger;        // ������Щ����	
	char                 	reserved[10];    
} PACK_ALIGN CONFIG_RF433M_CONFIG;

//
// ƣ�ͼ������
//
typedef struct ConfigEyeConfig
{
	unsigned char	        	channel;        // ͨ����
	short	                	bFaceDetect;    // �Ƿ�������
    //CONFIG_EYE_SENSITIVITY	sensitivity[8];    // ���������
	unsigned char             	sensitivity;
	char                         reserved[40];
} PACK_ALIGN CONFIG_EYE_CONFIG;

//
// IO����
//
typedef struct ConfigIoConfig
{
	unsigned short	bNormalOpen;    // ������Ĭ�ϼ��Ľ��Ϊ1�����ֱ���֮��Ϊ0�����շ�֮��

} PACK_ALIGN CONFIG_IO_CONFIG;

//
// �����豸��������
//
typedef struct _ConfigRf433mPublic_
{
	unsigned char 	bSupportRf433m;        //1:֧�ִ����豸; 0:��֧��
	char	    	reserved[23];        
} PACK_ALIGN CONFIG_RF433M_PUBLIC;

//
// LED��ʾ����
//
typedef struct ConfigLedShowSetting
{    
	unsigned int	displaySetting;        // ��������ö�����ͣ�OR��ʽ
	char	    	customInfo[64];        // �ͻ�������ʾ����Ϣ
	unsigned char	reserved[64];        // Ԥ��
} PACK_ALIGN CONFIG_LEDSHOW_SETTING;

//
// LED���������
//
enum MOVE_ACTION_STYLE
{
    	NOW         = 0x00, //-������ʾ
    	LEFT	    = 0x01, //-����
    	RIGHT	    = 0x02, //-����
    	UP	        = 0x03, //-����
    	DOWN	    = 0x04, //-����
    	L_CURTAIN	= 0x05, //-����Ļ
    	D_CURTAIN	= 0x06, //-����Ļ
    	R_CURTAIN	= 0x07, //-����Ļ
    	ARAB_R	    = 0x08, //-����������
    	H_WIN	    = 0x09, //-ˮƽ��Ҷ��
    	CABINET	    = 0x0A,    //-�ѻ�ľ
    	V_WIN	    = 0x0B, //-��ֱ��Ҷ��
    	MID_CLOSE	= 0x0C, //-�к�
    	MID_OPEN	= 0x0D, //-�п�
    	UD_CLOSE	= 0x0E, //-���º�
    	UD_OPEN	    = 0x0F, //-���¿�
    	H_CROSS	    = 0x10, //-ˮƽ����
    	V_CROSS	    = 0x11, //-���½���
    	RAND	    = 0x12, //-���
};
    
enum ROL_FRAME_STYLE
{
    	NONE	    = 0x00, //-�޻�����˸
    	RED4	    = 0x10, //-��4��
    	GREEN4	    = 0x20, //-��4��
    	YELLOW4	    = 0x30, //-��4��
    	RED1	    = 0x40, //-��1��
     	GREEN1	    = 0x50, //-��1��
    	YELLOW1	    = 0x60, //-��1��
    	RED_S_F	    = 0x70, //-�쵥����˸
    	GREEN_S_F	= 0x80, //-�̵�����˸
    	YELLOW_S_F	= 0x90, //-�Ƶ�����˸
    	RED_S_ROL	= 0xA0, //-�쵥�߻���
    	GREEN_S_ROL	= 0xB0, //-�̵��߻���
    	YELLOW_S_ROL= 0xC0, //-�Ƶ��߻���
    	RED_D_ROL	= 0xD0, //-��˫�߻���
    	GREEN_D_ROL	= 0xE0, //-��˫�߻���
    	YELLOW_D_ROL= 0xF0, //-��˫�߻���
};

enum DISPLAY_COLOR
{
    	SINGLE_DISPLAY	= 0x01,     // ��ɫ��
    	D_REG	        = 1 << 0,     // ��ɫ
    	D_GREEN	        = 1 << 1,     // ��ɫ
    	D_YELLOW	    = D_REG|D_GREEN,// ��ɫ
};

typedef struct ConfigLedBoardSetting
{
	unsigned char 	move_action;        // ������ʽ
    unsigned char 	move_speed;         // �����ٶ�, 0x00-0x0F������Խ��Խ��
    unsigned char 	rol_frame;          // ���Ʊ߿�, ȡ��4λ
    unsigned char 	stop_delay;         // ͣ��ʱ��, 0x00-0xFF��������������Ļ������ʾ8���֣���ǰ��Ϣ��16���֣���ôǰ8�����ƶ���Ϻ󣬿���ѡ������Ļ��ͣ��һ�������ʾ��8���֡�
    unsigned char 	color;              // ��ʾ��ɫ
    unsigned char 	font_class;         // ��������, ��ʱ��Ĭ��0x01
	unsigned char	reserved[64];        // Ԥ��
} PACK_ALIGN CONFIG_LEDBOARD_SETTING;

//
// (�����豸)
//
typedef struct ConfigGroupSetting
{
	unsigned char	enable;                // ʹ�ܱ�־=1ʹ�ܣ�=0��ʹ��
	unsigned char	masterTag;            // =1���豸��=0���豸
	char	    	ip[80];                // ���豸��ʾ����IP,���豸��ʾҪ���ӵ����豸IP
	unsigned short	syncInterval;        // ���豸ͬ����Ϣ���	
	unsigned char	clrHour;            // ����Сʱ
	unsigned char	clrMinute;            // ������ӣ�һ��Ŀ�ʼʱ�䣩
	unsigned int	limitPeople;        // ������������
	unsigned int	alarmPeople;        // ����Ԥ������
	unsigned char	reserved[64];        // Ԥ��
} PACK_ALIGN CONFIG_GROUP_SETTING;

// 
// ��³ľ��ƽ̨
//
typedef struct _WlPlateformServerParam_
{
	char	    	ip[80];         // IP
	unsigned short	port;            // �˿�
	int	        	devId;            // ��MAC���ɵ��豸ID,��Э��ʹ��,�ڿͻ�����ʾ,�ÿ�֪���豸��ͼƬ�Ķ�Ӧ��ϵ��
	char	    	reserved[60];    // ����
} PACK_ALIGN WLPLATFORM_SERVER_PARAM;

//
// (1)wifi�������
//
typedef struct _ConfigWifiNetwork_
{
	unsigned char	enableWifi;            // �Ƿ�������������,1-����;0-������
	unsigned char	netType;            // 0-DHCP, 1-STATIC, 2-ADSL
	char	    	ip[16];                // ip
	char	    	netmask[16];        // ��������
	char	    	gateway[16];        // ����
	char	    	broadAddr[16];        // �㲥��ַ	
	char	    	mac[24];            // �����ַ,ֻ��
	char	    	useWifiGateway;        // ʹ��wifi������ΪĬ������,0-��,1-��
	char	    	reserved[25];        
} PACK_ALIGN CONFIG_WIFI_NETWORK;

/*synovate_add*/
typedef struct _NetConfigSynovate
{    /*20��int���ͣ�8��short���ͣ�����char����*/        
	int setdaylight;
	int keepInt[19];
	unsigned short	synovatePort;            
	unsigned short	other;            
	unsigned short  keepShort[6];

	char fdaylight;
	char start[6];
	char end[6];
	char Ch;    
	char sn[6];        /*20��*/
	char	    	synovateIp[41];                    
	char	    	reserved[48];        // ������չ
} PACK_ALIGN NETWORK_SYNOVATE;


// 
// ftp¼����ز���
//
typedef struct configFtpRec
{
	char recFlag;        //1 ����ftp¼��0 ������ftp¼��
	char host[80];        //ftp������url
	char user[16];          //ftp�û���
	char passwd[16];    //ftp�û�����
	char reserved[16];  //����
} PACK_ALIGN CONFIG_FTP_REC;


//
// ��������ʱ��β���(�����ƶ�)
//
typedef struct ConfigClearPcPeriod
{
	char firstPeriod[9];  //��һ��ʱ��Σ����磺12:00:00.
	char secondPeriod[9]; //�ڶ���ʱ��Σ����磺12:00:00.
} PACK_ALIGN CONFIG_CLEAR_PC_PERIOD;

// 
// ftp�ϴ�������Ϣ��ز���
//
typedef struct ConfigFtpUpload
{
	int nUploadInterval;        /* �ϴ��ļ����(��λ:��)(ǰ̨����ѡ��Χ |1|5|10|20|30| ����,��ת��Ϊ��) */
	int nUploadFileFormat;        /* �ϴ��ļ���ʽ(����ֵ��ʾ  1=ʱ��η�ʽ, 2= ��ϸ���ݷ�ʽ) */

	int  nRunFlag;                /* �Ƿ���Ftp�ϴ�������Ϣ����, 0=�ر�, 1=���� */
	int  nPort;                    /* ftp�������˿�( 1 <= iPort <= 65535 ) */
	char strHost[64+1];            /* ftp������ip(����: 192.168.1.10) */
	char strUserName[64+1];        /* ftp�û��� (������Ϊ��)*/
	char strPassword[64+1];        /* ftp�û����� (������Ϊ��) */

	char reserved[16];            /* ���� */
} PACK_ALIGN CONFIG_FTP_UPLOAD;

//
//�г�ƣ�ͼ��
//
typedef struct
{
    char txtpath[50];//��ű�����Ϣ�����ļ���·��
    int  nFileLen;   //�ļ�����
} PACK_ALIGN RLW_TXT_PATH;

#undef PACK_ALIGN

#define DATA_READ	0
#define DATA_WRITE	1

//void ChangeTimeToInt( char tBuf[19], time_t &t );
int DealConfigDataProcess( unsigned char *dataBuf, int &dataLen, const int bufSize );
int CheckConfigDataProcess( unsigned char *dataBuf, int dataLen, int bufSize, int &offset );
int CfgManageSetPcClsCountTime( CONFIG_CLEAR_PC_PERIOD *clsPeriod );
extern int WifiScanResult( WIFI_SCAN_RESULT **pWifiScanResult, int *pScanSize );
int GetAlarmPack( unsigned char *dataBuf, int &dataLen, const int bufSize );

int ConfigProtocolEmpowerment( int type, int *pData );

#endif  // _CONFIG_PROTOCOL_H

