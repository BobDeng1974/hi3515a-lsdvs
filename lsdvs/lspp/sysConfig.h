/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ��ͷ�ļ��ṩ��ϵͳ������صĺ����Ľӿڡ�
**  date           :  2013.11.11
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef _SYS_CONFIG_H
#define _SYS_CONFIG_H

#include "const.h"
#include "ttypes.h"

enum TypeSysConfig
{
	TYPE_SYS_CONFIG_ALL	= 0,
	TYPE_SYS_CONFIG_HEADER,
	TYPE_SYS_CONFIG_BASE,
	TYPE_SYS_CONFIG_NETWORK,
	TYPE_SYS_CONFIG_USER,
	TYPE_SYS_CONFIG_PTZ_PROTOCOL,
	TYPE_SYS_CONFIG_PTZ_CONTROL,
	TYPE_SYS_CONFIG_VIDEO_BASE_PARAM,
	TYPE_SYS_CONFIG_OSD_INFO,
	TYPE_SYS_CONFIG_VIDEO_ENCODE,
	TYPE_SYS_CONFIG_VIDEO_SUB_ENCODE,
	TYPE_SYS_CONFIG_AUDIO_ENCODE,
	TYPE_SYS_CONFIG_AUDIO_ENCODE_TALKBACK,
	TYPE_SYS_CONFIG_EMAIL_PARAM,
	TYPE_SYS_CONFIG_AUTO_MAINTAIN_PARAM,
	TYPE_SYS_CONFIG_RECORD_PARAM,
	TYPE_SYS_CONFIG_RECORD_PUBLIC,
	TYPE_SYS_CONFIG_CHANNEL_PARAM,
	TYPE_SYS_CONFIG_ALARM_PARAM,
	TYPE_SYS_CONFIG_RS232_PARAM,
	TYPE_SYS_CONFIG_DOOR_RULE,
	TYPE_SYS_CONFIG_DATA_UPLOAD,
	TYPE_SYS_CONFIG_PC_PARAM,
	TYPE_SYS_CONFIG_MID_PARAM,
	TYPE_SYS_CONFIG_PC_CONFIG,
	TYPE_SYS_CONFIG_LP_PARAM,
	TYPE_SYS_CONFIG_ABDOOR_PARAM,
	TYPE_SYS_CONFIG_FIV_PARAM,
	TYPE_SYS_CONFIG_FIV_CONFIG,    
	TYPE_SYS_CONFIG_RF433M_CONFIG,
	TYPE_SYS_CONFIG_EYE_CONFIG,
	TYPE_SYS_CONFIG_IO_CONFIG,
	TYPE_SYS_CONFIG_RF433M_PUBLIC,
	TYPE_SYS_CONFIG_UBOOT_ENV_BACKUP,
	TYPE_SYS_CONFIG_LED_SHOW_SETTING,
	TYPE_SYS_CONFIG_LED_BOARD_SETTING,
	TYPE_SYS_CONFIG_GROUP_SETTING,
	TYPE_SYS_CONFIG_WL_PLATFORM,
	TYPE_SYS_CONFIG_THREEG_NET_PARAM,
	TYPE_SYS_CONFIG_WIFI_NETWORK,
	TYPE_SYS_CONFIG_WIFI_CONNECT,
	TYPE_SYS_CONFIG_SYNOVATE,
	TYPE_SYS_CONFIG_FTP_REC,
	TYPE_SYS_CONFIG_RS485_PARAM,
	TYPE_SYS_CONFIG_FTP_UPLOAD,
};

enum LANG
{
	LANG_ENGLISE = 1,
	LANG_CHINESE = 2,
};

enum TypeVideoMode
{
	TYPE_VIDEO_MODE_CIF = 0,
	TYPE_VIDEO_MODE_NINTH_D1,
	TYPE_VIDEO_MODE_QCIF,
	TYPE_VIDEO_MODE_D1,
	TYPE_VIDEO_MODE_FNINTH_D1,
    
	TYPE_VIDEO_MODE_10 = 11,
	TYPE_VIDEO_MODE_20,
	TYPE_VIDEO_MODE_30,
	TYPE_VIDEO_MODE_40,
	TYPE_VIDEO_MODE_50,
	TYPE_VIDEO_MODE_60,
	TYPE_VIDEO_MODE_70,
	TYPE_VIDEO_MODE_80,
	TYPE_VIDEO_MODE_90,
};

#define SYS_CONFIG_SIGNATURE	            "DVS_FI"
#define SYS_CONFIG_VERSION_CONFIG	        "1.0"
#define SYS_CONFIG_VERSION_SOFTWARE	        "beta1.0"
#define SYS_CONFIG_VERSION_HARDWARE	        "1.0"
#define SYS_CONFIG_DEVICE_NAME	            "DVS"
#define SYS_CONFIG_DEFAULT_TIME_ZONE		8
#define SYS_CONFIG_DEFAULT_USER	            "admin"
#define SYS_CONFIG_DEFAULT_PWD	            "88888888"
#define SYS_CONFIG_SUPER_PWD	            "2598219"
#define SYS_CONFIG_DEFAULT_IP	            "192.168.18.25"
#define SYS_CONFIG_DEFAULT_NETMASK	        "255.255.255.0"
#define SYS_CONFIG_DEFAULT_GATEWAY	        "192.168.18.1"
#define SYS_CONFIG_DEFAULT_DNS	            "202.96.134.133"
#define SYS_CONFIG_DEFAULT_DNS2	            "202.96.128.68"
#define SYS_CONFIG_DEFAULT_MAC	            "00:28:AC:32:28:AB"
#define SYS_CONFIG_DEFAULT_BROADADDR	    "255.255.255.255"
#define SYS_CONFIG_DEFAULT_WEBPORT	        "80"
#define	SYS_CONFIG_DEFAULT_NTP_PORT	    	123
#define SYS_CONFIG_DEFAULT_NTP_ADDR	        "210.72.145.44"        // ������ʱ����IP
#define SYS_CONFIG_DEFAULT_LANG	        	LANG_CHINESE
#define SYS_CONFIG_THTTPD_CONFIG	        "/tmp/thttpd.conf"

#define SYS_CONFIG_DEFAULT_WLPLATFORM_IP	"192.168.18.106"
#define SYS_CONFIG_DEFAULT_WLPLATFORM_PORT	40077


#define MAX_USER_NUM	                	5
#define MAX_PTZ_NUM	                    	30
#define MAX_CMD_PER_PTZ	                	30
#define MAX_DATA_UPLOAD_NUM	            	10
#define MAX_WEEK_DAY	                	7
#define MAX_TIME_SEG_NUM	            	4
#define DEFAULT_PTZ_PROTOCOL_NUM	    	3
#define FIV_MAX_RECT_NUM	            	4
#define FIV_MAX_RECT_FROM_NET	        	2
#define MAX_MIDWARE_USER_NUM	        	5	// ���֧��5���м��
#define MAX_RF433M_SLAVE_NUM	        	32	// ���֧��32��RF433���豸
#define EYE_MAX_SENSITIVITY_NUM	        	8

#define FIV_ENABLE_DEFENSE	            	0
#define FIV_DISABLE_DEFENSE	            	1

#define DEF_MAXMATCHDIST	            	50          // �����ͷƥ�����Ĭ��ֵ
#define DEF_STEP_LEN	                	DEF_MAXMATCHDIST // ��󲽳�Ĭ��ֵ
#define MIN_STEP_LEN	                	8	     // ��󲽳���Сֵ

// ���к���Ҫ��������u-boot��ʱ�����u-boot������Ҫ��һЩ�������趨��
#define	UBOOT_ENV_ERASE_FLAG	        	0xFF884422
#define UBOOT_ENV_DEFAULT_MAC	            "00:0c:72:18:81:aa" // lty���ӵ�Ĭ��mac
#define UBOOT_ENV_DEFAULT_MAC_CIM	        "00:0c:72:18:83:aa"    // һ�����Ĭ��mac


#ifndef PACK_ALIGN
#define PACK_ALIGN __attribute__((packed))
#endif

//
// ����ͷ�ṹ
//
typedef struct SysConfigHeader 
{
	char	signature[16];                // �����ļ���ʶ
	int		size;                        // �����ļ���С
	char	configureVersion[16];        // ���ð汾��
	char	softwareVersion[16];        // ����汾��
	char	hardwareVersion[16];        // Ӳ���汾��
	char	serialNo[16];                // ��Ʒ���к�
	unsigned char	reserved[28];        // ������չ
} PACK_ALIGN SYS_CONFIG_HEADER;

//
// ϵͳ��������
//
typedef struct SysConfigBase 
{
	char	    	devName[32];        // �豸����
	char	    	devId[32];            // �豸ID
	unsigned char	chipNum;            // 3512оƬ����
	unsigned char	channelNum;            // ʵ�ʵ�ͨ����
	unsigned char	ptzNum;                // ʵ�ʵ���̨����Э������
	int	        	langID;                // ����ID
	char	    	timeZone;            // ʱ��
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
    //char	    	reserved[23];        // ������չ	
	int         	timeIntZone;
    //char	    	reserved[19];        // ������չ	
	unsigned int	shopID;                // ���̺�,���ڵ���0,Ĭ��Ϊ0,����Ftp�ϴ�������ϢĿ¼����
	char	    	reserved[15];        // ������չ	
} PACK_ALIGN SYS_CONFIG_BASE;

//
// �������
//
typedef struct SysConfigNetwork 
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
	char	    	reserved[62];        // ������չ
} PACK_ALIGN SYS_CONFIG_NETWORK_F;

/*synovate_add*/
typedef struct SysConfigSynovate
{    /*20��int���ͣ�8��short���ͣ�����char����*/        
	int setdaylight;

    #if 1
	int startMonth;/*ftypedaylight ==2 ʱ��Ч����ʾ�ڼ����£�*/
	int startWhichDis;/*�ڼ��ܣ�����ǵ�һ��=1����Χ��1��5������ǵ�����һ��=-1�������ڶ���=-2����Χ��-5��-1*/
	int startWhichDay;/*�ڼ��죬��һ�쵽������*/
	int startHour;/*Сʱ��0��23*/

	int endMonth;/*ͬ��*/
	int endWhichDis;
	int endWhichDay;
	int endHour;
    #endif
    
	int keepInt[19];
	unsigned short	synovatePort;            
	unsigned short	other;            
	unsigned short  keepShort[6];

	char fdaylight;/*����ʱ�ܿ���*/
    #if 1
	char ftypedaylight;/*����ʱ���������ͣ�=1�����þ���ʱ����5��1�գ�=2���������ʱ����5�µĵ�һ��������*/
    #endif
	char start[6];
	char end[6];
	char Ch;    
	char sn[6];        /*20��*/
	char	    	synovateIp[41];                    
	char	    	reserved[48];        // ������չ
} PACK_ALIGN SYS_CONFIG_SYNOVATE;
//
//3G�豸����
//
typedef struct SysConfigThreegNetParam
{
	int 	enableFlag;        //0��ʾ��ʹ��3G���磬1��ʾʹ��3G����.
	char 	smsAuthPasswd[6];
	char 	reserve[64-6];    //Ԥ�����ƹ���
} PACK_ALIGN SYS_CONFIG_THREEG_NET_PARAM;

//
// �û�����
//
typedef struct SysConfigUser 
{
	char	    	userName[32];        // �û���
	char	    	pwd[32];            // ����
	int	        	level;                // �û��ļ���; 0,NONE,1,ADMIN,2,����û�;
	unsigned int	capability;            // �û���Ȩ��;
	char	    	reserved[32];
} PACK_ALIGN SYS_CONFIG_USER;

//
// ��̨Э������
//
typedef struct PtzControlCmd 
{ 
	char	    	cmdName[16];        // ��������
	unsigned char	cmd[64];            // ÿ���������62�ֽ� (�� '\0' ����)
	unsigned char	bIsManual;            // �Ƿ��û��Զ�������
} PACK_ALIGN PTZ_CONTROL_CMD;

typedef struct SysConfigPtzProtocol
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
    
} PACK_ALIGN SYS_CONFIG_PTZ_PROTOCOL;

//
// ��̨��������
//
typedef struct SysConfigPtzControl
{
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
} PACK_ALIGN SYS_CONFIG_PTZ_CONTROL;

//
// ��Ƶ����
//
typedef struct SysConfigVideoBaseParam
{
	int	        	brightness;            // ����
	int	        	contrast;            // �Աȶ�
	int	        	hue;                // ɫ��
	int	        	saturation;            // ���Ͷ�
	int	        	exposure;            // �ع��
	char	    	reserved[32];
} PACK_ALIGN SYS_CONFIG_VIDEO_BASE_PARAM;

#if 0
//
// OSD��������
//
typedef struct ConfigOsdLogo
{
	unsigned char	enable;                // �Ƿ���ʾOSD 1: enable, 0: disable
	unsigned char	colorRed;            // ��ɫ
	unsigned char	colorGreen;            // ��ɫ
	unsigned char	colorBlue;            // ��ɫ
	unsigned short	xPos;                // ����
	unsigned short	yPos;                // ����
	char	    	logo[64];            // ���֧��64Bytes��logo
} PACK_ALIGN CONFIG_OSD_LOGO;

typedef struct ConfigOsdTime
{
	unsigned char	enable;
	unsigned char	colorRed;    
	unsigned char	colorGreen;    
	unsigned char	colorBlue;    
	unsigned short	xPos;
	unsigned short	yPos;
} PACK_ALIGN CONFIG_OSD_TIME;
#endif

typedef struct SysConfigOsdInfo 
{
	CONFIG_OSD_TIME	osdTime;
	CONFIG_OSD_LOGO	osdLogo;
} PACK_ALIGN SYS_CONFIG_OSD_INFO;

//
// ��Ƶ�������
//
typedef struct SysConfigVideoEncode 
{
	int		videoStandard;        // ��Ƶ��ʽ: 0:PAL�ơ�1:NTSC��
	int		resolution;            // �ֱ���: 0:Qicf��1:Cif��2:HD1��3:D1
	int		bitrateType;        // λ������: 0:CBR��1:VBR
	int		quality;            // ����
	int		frameRate;            // ֡��
	int		iFrameInterval;        // I֡���
	int		preferFrame;        // ֡������
	int		qp;                    // ����ϵ��
	int		encodeType;            // ����Ƶ��:0����Ƶ��:1����Ƶ��:2
	char	reserved[12];        // ������չ
} PACK_ALIGN SYS_CONFIG_VIDEO_ENCODE;

//
// ��Ƶ�������
//
typedef struct SysConfigAudioEncode
{
	int		sampleRate;            // ������
	char	bitWidth;            // λ��
	char	encodeType;            // ���뷽ʽ
	char	amrMode;            // amr����ģʽ
	char	amrFormat;            // amr�����ʽ
	char	reserved[6];
} PACK_ALIGN SYS_CONFIG_AUDIO_ENCODE;

//
// �ʼ�����
//
typedef struct SysConfigEmailParam
{
	int		activeFlag;
	char	serverName[64];
	int		serverPort;
	char	userName[64];
	char	password[32];
	char	senderName[32];
	char	emailTitle[64];
	char	recvAddr1[64];
	char	recvAddr2[64];
	char	recvAddr3[64];
	char	reserved[128];
} PACK_ALIGN SYS_CONFIG_EMAIL_PARAM;

//
// �Զ�ά��
//
typedef struct SysConfigAutoMaintain
{
	unsigned char	rebootFlag;            // 0:���Զ�����; 1:�Զ�����
	unsigned int	rebootDate;            // 0~6:������~������; 7:ÿ��;
	unsigned int	rebootTime;            // 0~86400 ��;
	int	        	delFileFlag;        // �Ƿ��Զ�ɾ���ļ�
	int	        	dayNumber;            // ������֮ǰɾ����

	char	    	reserved[31]; 

} PACK_ALIGN SYS_CONFIG_AUTO_MAINTAIN_PARAM;

//
// ¼��ṹ��
//
typedef struct ConfigRecordPublic
{    
	unsigned long	delSpace;        // Ӳ��¼��ռ䱨��ֵ  >= 100M  <= 10000M
	unsigned long	delSize;        // reserve,ɾ��¼��Ĵ�С(�̶�Ϊ����ɾ��)
	unsigned char	loopRecord;        // ѭ��¼��,0:��֧��,1:֧��.
	unsigned char	preRecord;        // Ԥ¼,0:ֹͣ,1:����. 
	unsigned char	switchFileTime;    // reserve,¼���ļ��л�ʱ�� 10~30����(�̶�Ϊ20����)        
	char reserved[13];
} PACK_ALIGN CONFIG_RECORD_PUBLIC;

typedef struct ConfigRecordHand
{
	unsigned char	recHand;        // 0:ֹͣ�ֶ�¼��,1:�����ֶ�¼��
	char	    	reserved[3];
} PACK_ALIGN CONFIG_RECORD_HAND;

typedef struct ConfigRecTimeSeg
{
	unsigned char	startHour;
	unsigned char	startMinute;
	unsigned char	startSecond;
	unsigned char	stopHour;
	unsigned char	stopMinute;
	unsigned char	stopSecond;
	unsigned char	reserved[2];
} PACK_ALIGN CONFIG_RECORD_TIME_SEG;

typedef struct ConfigTimerWeek
{
	CONFIG_RECORD_TIME_SEG	timeSeg[MAX_TIME_SEG_NUM];
	char	    	enableFlag;        // 1: enable, 0: disable
	char	    	reserved[3];
} PACK_ALIGN CONFIG_TIMER_WEEK;

typedef struct ConfigRecordTimer
{
	CONFIG_TIMER_WEEK		timerWeek[MAX_WEEK_DAY];
} PACK_ALIGN CONFIG_RECORD_TIMER;

typedef struct SysConfigRecordParam
{
	CONFIG_RECORD_PUBLIC	recPublic;
	CONFIG_RECORD_HAND		recHand;
	CONFIG_RECORD_TIMER		recTimer;
} PACK_ALIGN SYS_CONFIG_RECORD_PARAM;

typedef struct SysConfigRecordPublic
{
	unsigned char loopRecordFlag;
	char reserve[15];
} PACK_ALIGN SYS_CONFIG_RECORD_PUBLIC;

//
// ͨ������
//
typedef struct SysConfigChannelParam
{
	char	channelName[32];        // ͨ������
	int		voiceInput;                // ��������
	int		voiceOutput;            // �������
} PACK_ALIGN SYS_CONFIG_CHANNEL_PARAM;

//
// ��������漰�������ALARM,���������ALARM IN����ALARM OUT��������ͨ����Ŀ��1��
// ע��: �˳��������޸� !!!
//
static const int MAX_ALARM_NUM	    = 17;    

typedef struct ConfigAlarmTimeSeg
{
	unsigned char	startHour;
	unsigned char	startMinute;
	unsigned char	startSecond;
	unsigned char	stopHour;
	unsigned char	stopMinute;
	unsigned char	stopSecond;
	unsigned char	reserved[2];
} PACK_ALIGN CONFIG_ALARM_TIME_SEG;

typedef struct ConfigAlarmWeek
{
	CONFIG_ALARM_TIME_SEG	timeSeg[MAX_TIME_SEG_NUM];
	char	    	enableFlag;        // 1: enable, 0: disable
	char	    	reserved[3];
} PACK_ALIGN CONFIG_ALARM_WEEK;

typedef struct ConfigAlarmTimer
{
	CONFIG_ALARM_WEEK		timerWeek[MAX_WEEK_DAY];
} PACK_ALIGN CONFIG_ALARM_TIMER;

typedef struct ConfigAlarmTrigger
{
	unsigned char	enableAlarmOut;
	unsigned char	triggerAlarmOut[MAX_ALARM_NUM];
	unsigned char	enableCapture;    
	unsigned char   triggerCapture[MAX_CHANNEL_NUM];
	unsigned char	enableRec;
	unsigned char 	triggerRec[MAX_CHANNEL_NUM];
	unsigned char   triggerBuzzer;        // 0: no trigger; 1: trigger;
	unsigned char   triggerEmailSend;    // 0: not send; 1: send;
	unsigned char	enableFiv;            // 0: not start FIV; 1: start FIV
	unsigned short	triggerFiv;            // ÿbit��ʶһ��ͨ��, eg, bit3 = 1:����ͨ��3��FIV; bit0 = 0:������ͨ��3��FIV
	unsigned int	recType;            // ¼������,��¼��ģ�鶨�������һ��,�ͻ��˲������� 
	unsigned int	capType;            // ץ������,��ץ��ģ�鶨�������һ��,�ͻ��˲������� 
	unsigned char	rf433mNum;            // fiv+rf433mר��,��ʾ�ñ�������������ע���rf433m�е���һ�������ġ�
	unsigned char	enableSendVsip;        // 1: �������͵�vsip; 0: ��֮ 
	char            reserved[29];
} PACK_ALIGN CONFIG_ALARM_TRIGGER;

typedef struct SysConfigAlarmParam
{
	unsigned char	alarmInId;
	unsigned char   enalbeFlag;            // 0: close; 1: open;
	unsigned char   type;                // 0: ����; 1: ���գ�
	char	    	alarmInName[32];
	CONFIG_ALARM_TIMER		alarmInDetectTimer;
	CONFIG_ALARM_TRIGGER	trigger;
	char            reserve[29];
} PACK_ALIGN SYS_CONFIG_ALARM_PARAM;

typedef struct SysConfigRs232Param
{
	unsigned int	baudRate;            // ������
	unsigned char	dataBits;            // ����λ
	unsigned char	stopBits;            // ֹͣλ
	unsigned char	parity;                // У��λ
} PACK_ALIGN SYS_CONFIG_RS232_PARAM;

typedef struct SysConfigRs485Param
{
	unsigned int	baudRate;            // ������
	unsigned char	dataBits;            // ����λ
	unsigned char	stopBits;            // ֹͣλ
	unsigned char	parity;                // У��λ
} PACK_ALIGN SYS_CONFIG_RS485_PARAM;

typedef struct SysConfigDoorRule
{
	int		pcType;
	int		doorType;
	int		doorRule;
} PACK_ALIGN SYS_CONFIG_DOOR_RULE;

typedef struct SysConfigDataUpload
{
	int		flag;                // �Ƿ��������ϴ�����
	char	ip[80];                // ��������ַ
	int		port;                // �������˿�
	int		interval;            // �����ϴ�ʱ����
	int		lastTime;            // ���һ�������ϴ��ɹ���ʱ��
	int		mode;                // ��ͨģʽ: 0 ����ģʽ: 1 
	int		reserve[7];
} PACK_ALIGN SYS_CONFIG_DATA_UPLOAD;

typedef struct SysConfigPcParam
{
	int		nWidth;                // ͼ����
	int		nHeight;            // ͼ��߶�
	int		nRoiLeft;            // ��������������
	int		nRoiTop;            // ������򶥱�����
	int		nRoiRight;            // ��������ұ�����
	int		nRoiBottom;            // �������ױ�����
	int		bOriVertical;        // ����߶�����(����ͷ��AB�ż�ⷽ��: 1 ��ֱ�߶���0 ˮƽ�߶�)
	int		nLoiterTime;         // �������ʱ������ʱ��(��λ������), ��Χ: ���롫10��(256֡/25֡)
	int		nFPSOfDet;            // ���֡��: ����ʵ���ܵ�֡�����ã���ΧΪ��5֡/�롫25֡/��(Ҳ��������Ϊ0, ��ʾ�˲�����Ч )
	int		nMaxMatchDist;        // �����ͷƥ����룬�����ͷ��������������Ϊ���µ���ͷ�����ƥ�������0��150��5����ͷ����Ĭ��Ϊ30��1����ͷ��
                                // ���߱��˵���ͷ��Ĭ��ֵΪ30, �����Ҫ�������ڼ�������
                                // �ƶ��ٶ������ã�����ƶ�����������С��ֵ���ƶ��Ͽ������ô�ֵ��
	int		bOriEnter;            // (����㷨����û�е�)������������
                                // ��ֱ����: 0��ʾ���ϵ����ǽ��뷽�� 1��ʾ���µ����ǽ��뷽�� 
                                // ˮƽ����: 0��ʾ�������ǽ��뷽�� 1��ʾ���ҵ����ǽ��뷽��
	int		bOpenPcDetect;        // (����㷨����û�е�)�Ƿ��������㷨
	int		videoMode;            // (����㷨����û�е�)��Ƶģʽ: Cif, 1/9D1, QCif, D1, 4/9 D1
	int 	nStepMotion;        // �Ƿ�̨���˶�; 1:̨���˶�, 0:ƽ���˶�.
	int 	nMaxStepLen;         // ��󲽳���ȡֵ��ΧΪ8 ~ nMaxMatchDist,  Ĭ��ֵΪ nMaxMatchDist. add 0812. 

	int 	nMinStepCount;        /* ((ֵΪ0 ʱ,�رչ���))���ٲ��������ڹ淶���˵��˶��ٶȡ�*/
	int 	nMinHeadWidth;        /* ��С��ͷ��ȣ���λ���أ�Ĭ��40���أ���С30����*/    
	int 	nMaxHeadWidth;      /* �����ͷ��ȣ���λ���أ�Ĭ��60���أ����100����*/
	int  	bHighPrecision;        /* ʹ�ܸ߾���ѡ����ͳ��ֵ�Ŀ��Ŷȣ���δ������߻��߽���ͳ��ֵ

                               ==TRUE��ʹ�ܸ߾��ȣ������þ�ֹ�ڵ��������˵��㷨�������ڴ��ڱ�����ͳ�����صĻ�����
                                	�����ã���ֹ�ڵ㲻�ᵼ�����˼�������ʱ��һ����ͣ���ˣ�
                                	�����ã����Ч�����õ���ͷ����⵽�Ĵ���ƫ�٣�����©����

                               ==FALSE����ֹ�߾��ȣ��رվ�ֹ�ڵ����������㷨�������ڲ����ڱ�����ͳ�ƵĻ�����
                                	�����ã����Ч�����õ���ͷ����⵽�Ĵ���ƫ�٣������ڶ�©����
                                	�����ã���ֹ�ڵ���ܵ������˼�������ʱ��һ����ͣ���ˣ�

                            	�������������ڱ�����ͳ�����صĻ���������ΪTRUE����������ΪFALSE��*/    
	char	reserve[52];
                            
} PACK_ALIGN SYS_CONFIG_PC_PARAM;

typedef struct ConfigMidWareSerial
{
	unsigned int		baudRate;        // ������
	unsigned char		dataBits;        // ����λ
	unsigned char		stopBits;        // ֹͣλ
	unsigned char		parity;            // У��λ
	unsigned char		cAddr;            // ��ַλ(485��ʱ����Ч)
} PACK_ALIGN CONFIG_MIDWARE_SERIAL;

typedef struct ConfigMidWareNet
{
	char             	ip[80];                // IP
	unsigned short		port;                // �˿�
} PACK_ALIGN CONFIG_MIDWARE_NET;

typedef struct ConfigMidWareAuth
{
	char	        	user[32];            // �û�
	char	        	passwd[32];            // ����
} PACK_ALIGN CONFIG_MIDWARE_AUTH;

typedef struct SysConfigMidware
{
	char                 	transType;        // ���䷽ʽ0-��Ч,1-TCP,2-UDP,3-RS232,4-RS485
	char	            	regEnable;        // 1-ʹ��ע�ᣬ0-��ע��
	CONFIG_MIDWARE_NET		net;            // ���䷽ʽΪ����ʱ��Ч��������0
	CONFIG_MIDWARE_SERIAL	serial;            // ���䷽ʽΪRS232/RS485ʱ��Ч��������0
	CONFIG_MIDWARE_AUTH		auth;            // ��֤
} PACK_ALIGN SYS_CONFIG_MIDWARE;

typedef struct SysConfigPcConfig
{
	char	bSaveHistroyData;            // �Ƿ񱣴���ʷ���ݵ�flash 
	char	countTime[2][12];            // �������˵�ʱ���,ʱ���1Ĭ��:00:00-23:59;ʱ���2Ĭ��:0
   	char    clrCountTime[2][9];            // JSYD, �����ƶ�licence, ��������ʱ���
   	char 	upModNum;                    //�ϳ�ģʽ������ֵ
	char 	downModNum;                    //�³�ģʽ������ֵ
	char 	remainPercent;                //����ʣ����������������İٷֱ�	
	int		limitedNumber;                // ������������������(��-��)    
	char	reserved[206];    
} PACK_ALIGN SYS_CONFIG_PC_CONFIG;

typedef struct SysConfigLpParam
{
	int		nWidth;                    // ͼ����
	int		nHeight;                // ͼ��߶�	
	int		nMinTrackFrame;            // ���ٸ���֡��
	int		nMaxLostFrame;            // ���ʧ��֡��
	int		nMaxDistance;            // ������ٵ������
	int		nDetectCarType;            // �Ƿ��⳵ͷ: 0 ��ֹ;  1 ��⳵ͷ;  2 ��⳵β
	int		bDetectPlate;            // �Ƿ��⳵��: 1 ʹ��; 0 ��ֹ
	int		bEnableTrackCar;        // �Ƿ���������: 1 ʹ��; 0 ��ֹ
	int		bEnableTrackPlate;        // �Ƿ���������: 1 ʹ��; 0 ��ֹ
	int		reserve[15];    
} PACK_ALIGN SYS_CONFIG_LP_PARAM;

typedef struct SysConfigABDoorParam
{
	int		nWidth;                // ͼ����
	int		nHeight;            // ͼ��߶�
	int		nRoiLeft;            // ��������������
	int		nRoiTop;            // ������򶥱�����
	int		nRoiRight;            // ��������ұ�����
	int		nRoiBottom;            // �������ױ�����
	int		bOriVertical;        // ����߶�����(����ͷ��AB�ż�ⷽ��: 1 ��ֱ�߶���0 ˮƽ�߶�)
	int		nLoiterTime;         // �������ʱ������ʱ��(��λ������)
	int		nFPSOfDet;            // ���֡��
	int		nMaxMatchDist;        // �����ͷƥ����룬�����ͷ��������������Ϊ���µ���ͷ
                                // ���߱��˵���ͷ��Ĭ��ֵΪ30, �����Ҫ�������ڼ�������
                                // �ƶ��ٶ������ã�����ƶ�����������С��ֵ���ƶ��Ͽ������ô�ֵ��
	int		bOriEnter;            // ������������
                                // ��ֱ����: 0��ʾ���ϵ����ǽ��뷽�� 1��ʾ���µ����ǽ��뷽�� 
                                // ˮƽ����: 0��ʾ�������ǽ��뷽�� 1��ʾ���ҵ����ǽ��뷽��
	int		bOpenABDoorDetect;    // �Ƿ��������㷨
	int		stayerNum;            // ��������
	int		sensitivity;        // ������ (1 - 9)
	int		videoMode;            // ��Ƶģʽ: Cif, 1/9D1, QCif
	int		reserve[17];    
} PACK_ALIGN SYS_CONFIG_ABDOOR_PARAM;

typedef struct SysConfigFivParam
{
	float	fAlpha;                // ����ѧϰ�ʣ�0��0.3����Ĭ��ȡ0.01
	float	fFactor;            // �жϷ�ֵF��0.5��3.5����Ĭ��ȡ2.5
	float	fT;                    // �жϷ�ֵT��0.3~0.9����Ĭ��ȡ0.7
	int		nWindowSize;        // ���㾫�ȣ���С���㴰�ڣ�1��5����Ĭ��ȡ3������3x3��
	int		nTargetSize;        // ������С�ߴ磨��λΪ�����ء���1��10000����Ĭ��ȡ36��6*6��
	int		nMaxLost;            // ��ඪʧ֡������λΪ��֡�������������ؼ�λ��֮֡������ʧ��֡������Ĭ��ȡ3
	int		nMinFrame;            // ���ٴ���֡������λΪ��֡����������ڶ��ٹؼ�λ��֡���ж�Ϊ��Ч���󣩣�Ĭ��ȡ1
	int		nMaxDistance;        // �������ٹؼ�λ�����ƥ����루��λΪ�����ء��������˾��룬��Ϊ����ͬһ�����󣩣�Ĭ��ȡ10
	int		bOpenFivDetect;        // �Ƿ���FIV�㷨
	int		reserve[7];
} PACK_ALIGN SYS_CONFIG_FIV_PARAM;

enum FivType
{
	FIV_TYPE_INVALID = 0,        // ��Ч
	FIV_TYPE_RESTRICTED_AREA,    // ����
	FIV_TYPE_RETROGRADE,        // ����
	FIV_TYPE_CROSS_LINE,        // Խ��
};

#define FIV_MAX_RECT_NUM	    	4
#define FIV_MAX_RECT_FROM_NET		2

typedef struct SysConfigFivConfig
{
	int		width;            
	int		height;
	int		left;            // �������Ĭ������������
	int		top;
	int		right;
	int		bottom;
	int		fivFlag;        // 0: �����1��������
	int		fivType;        // 0: ��Ч��1: ������2�����У�3��Խ��
	struct  RGN
    {
    	int rgnType;        // 0: ��Ч; 1: ���Σ�2��Բ�Σ�3���ߣ�4����ͷ
    	struct Rect
        {
        	int x1;
        	int y1;
        	int x2;
        	int y2;
        } rect;
    } rgn[FIV_MAX_RECT_NUM];
	int		reserve[36];
} PACK_ALIGN SYS_CONFIG_FIV_CONFIG;

// 
// RF433���豸����
//
typedef struct ConfigRf433SlaveAlarm
{
	char	    	id[5];                    // ���豸ID
	unsigned char	type;                    // ���豸����
	char	    	name[32];                // ���豸����
	unsigned char 	guard;                    // 0: ����; 1: ���
	CONFIG_ALARM_TIMER     	timerGuard;        // ��ʱ����,���
	CONFIG_ALARM_TRIGGER	trigger;        // ������Щ����	
	char                 	reserved[10];    
} PACK_ALIGN CONFIG_RF433M_PARAM;

typedef struct Rf433SlaveAlarmList
{
	unsigned char	    	num;            // ʵ����������RF433���豸����(���֧�� MAX_RF433_SLAVE_NUM ��)
	CONFIG_RF433M_PARAM		alarmIn[MAX_RF433M_SLAVE_NUM];    // RF433��������	
} PACK_ALIGN SYS_CONFIG_RF433M_PARAM;

//
// EYE
//
typedef struct ConfigEyeSensitivity
{
	unsigned short	carSpeed;                    // ���� (��λ: ǧ��/Сʱ)
	unsigned short	detectTime;                    // ���ʱ��	(��λ: ����)
} PACK_ALIGN CONFIG_EYE_SENSITIVITY;

typedef struct SysConfigEyeConfig
{
	short	                	bFaceDetect;                            // �Ƿ�������
	CONFIG_EYE_SENSITIVITY		sensitivity[EYE_MAX_SENSITIVITY_NUM];    // ���������
	char	                	bslSensitivity;                            // ��������Ŀ�ļ��������(1~5,Ĭ��3)
	char	                	reserved[29];
} PACK_ALIGN SYS_CONFIG_EYE_CONFIG;

//
// IO����
//
typedef struct SysConfigIoConfig
{
	unsigned short	bNormalOpen;        // ������Ĭ�ϼ��Ľ��Ϊ1�����ֱ���֮��Ϊ0�����շ�֮��
	short	    	reserved[31];
} PACK_ALIGN SYS_CONFIG_IO_CONFIG;

//
// �����豸��������
//
typedef struct SysConfigRf433mPublic
{
	unsigned char 	bSupportRf433m;        //1:֧�ִ����豸; 0:��֧��
	char	    	reserved[23];        
} PACK_ALIGN SYS_CONFIG_RF433M_PUBLIC;


//
// LED��ʾ����
//
enum
{
    	DISPLAY_DATETIME     = (1 << 0),    // ����
    	DISPLAY_DAYTOTOLIN     = (1 << 1),    // �����ܽ�����
    	DISPLAY_LASTHOURIN	= (1 << 2),    // ���һСʱ�ܽ�����
    	DISPLAY_INNERCOUNT	= (1 << 3),    // ��������
    	DISPLAY_CUSTOM	    = (1 << 4),    // �ͻ�����
    	DISPLAY_FIRS	    = (1 << 5),    // ���(�̶�������)
};
typedef struct SysConfigLedShowSetting
{
	unsigned int	displaySetting;        // ��������ö�����ͣ�OR��ʽ
	unsigned char	customInfo[64];        // �ͻ�������ʾ����Ϣ
	unsigned char	reserved[64];        // Ԥ��
} PACK_ALIGN SYS_CONFIG_LEDSHOW_SETTING;

//
// LED���������
//
typedef struct SysConfigLedBoardSetting
{
	unsigned char 	move_action;        // ������ʽ
    unsigned char 	move_speed;         // �����ٶ�, 0x00-0x0F������Խ��Խ��
    unsigned char 	rol_frame;          // ���Ʊ߿�, ȡ��4λ
    unsigned char 	stop_delay;         // ͣ��ʱ��, 0x00-0xFF��������������Ļ������ʾ8���֣���ǰ��Ϣ��16���֣���ôǰ8�����ƶ���Ϻ󣬿���ѡ������Ļ��ͣ��һ�������ʾ��8���֡�
    unsigned char 	color;              // ��ʾ��ɫ
    unsigned char 	font_class;         // ��������, ��ʱ��Ĭ��0x01
	unsigned char	reserved[64];        // Ԥ��
} PACK_ALIGN SYS_CONFIG_LEDBOARD_SETTING;

//
// �����豸����
//
typedef struct SysConfigGroupSetting
{
	unsigned char	enable;                // ʹ�ܱ�־=1ʹ�ܣ�=0��ʹ��
	unsigned char	masterTag;            // =1���豸��=0���豸
	unsigned char	ip[80];                // ���豸��ʾ����IP,���豸��ʾҪ���ӵ����豸IP
	unsigned short	syncInterval;        // ���豸ͬ����Ϣ���
	unsigned char	clrHour;            // ����Сʱ
	unsigned char	clrMinute;            // ������ӣ�һ��Ŀ�ʼʱ�䣩
	unsigned int	limitPeople;        // ������������
	unsigned int	alarmPeople;        // ����Ԥ������
	unsigned char	reserved[64];        // Ԥ��
} PACK_ALIGN SYS_CONFIG_GROUP_SETTING;

//
// u-boot���ò�������
//
typedef struct _SysConfigUbootEnvBackup_
{
	unsigned int	flag;        // ��ʶ,== UBOOT_ENV_ERASE_FLAG, ������Ѿ�������; == ����ֵ,�����û�б�����
	char         	mac[24];        // u-boot��������ǰҪ�� u-boot �����mac����
	char         	reserved[1000];    
} PACK_ALIGN SYS_CONFIG_UBOOT_ENV_BACKUP;

//
// ��³ľ��ƽ̨����������
// 
typedef struct _SysWlPlateformConfig_
{
	char         	ipAddr[80];     // ������IP ��ַ
	unsigned short 	port;            // �������˿�
	char	    	reserved[16];
} PACK_ALIGN SYS_CONFIG_WL_PLATFORM;
//
// wifi�������
//
typedef struct SysConfigWifiNetwork
{
	unsigned char	enableWifi;            // �Ƿ�������������,1-����;0-������
	unsigned char	netType;            // 0-DHCP, 1-STATIC, 2-ADSL
	char	    	ip[16];                // 
	char	    	netmask[16];        // ��������
	char	    	gateway[16];        // ����
	char	    	broadAddr[16];        // �㲥��ַ	
	char	    	mac[24];            // �����ַ,ֻ��
	char	    	useWifiGateway;        // ʹ��wifi������ΪĬ������,0-��,1-��
	char	    	reserved[25];        
} PACK_ALIGN SYS_CONFIG_WIFI_NETWORK;

// 
// wifi��������
//
typedef struct SysConfigWifiConnect
{
	char	    	essid[32];        // ���֧��32���ֽ�,֧���ֶ�����ʹ������л�ȡ
	char	    	key[64];        // ����
	unsigned char 	connectFlag;    // ֻ��, 0-û�����ӵ�����·��;1-�Ѿ����ӵ�����·��
	unsigned char 	signalLevel;    // ֻ��, �ź�ǿ��, 1~5��
	char	reserved[14];
} PACK_ALIGN SYS_CONFIG_WIFI_CONNECT;

// 
// ftp¼����ز���
//
typedef struct SysConfigFtpRec
{
	char recFlag;        //1 ����ftp¼��0 ������ftp¼��
	char host[80];        //ftp������url
	char user[16];          //ftp�û���
	char passwd[16];    //ftp�û�����
	char reserved[16];  //����
} PACK_ALIGN SYS_CONFIG_FTP_REC;

// 
// ftp�ϴ�������Ϣ��ز���
//
typedef struct SysConfigFtpUpload
{
	int nUploadInterval;        /* �ϴ��ļ����(��λ:��)(ǰ̨����ѡ��Χ |1|5|10|20|30| ����,��ת��Ϊ��) */
	int nUploadFileFormat;        /* �ϴ��ļ���ʽ(����ֵ��ʾ  1=ʱ��η�ʽ, 2= ��ϸ���ݷ�ʽ) */
	int nRunFlag;                /* �Ƿ���Ftp�ϴ�������Ϣ����, 0=�ر�, 1=���� */

	int  nPort;                    /* ftp�������˿�( 1 <= iPort <= 65535 ) */
	char strHost[64+1];            /* ftp������ip(����: 192.168.1.10) */
	char strUserName[64+1];        /* ftp�û��� (������Ϊ��) */
	char strPassword[64+1];        /* ftp�û����� (������Ϊ��) */

	char reserved[16];            /* ���� */
} PACK_ALIGN SYS_CONFIG_FTP_UPLOAD;

typedef struct SysConfig	// ϵͳ���ýṹ
{
	SYS_CONFIG_HEADER	        	header;
	SYS_CONFIG_BASE	            	base;
	SYS_CONFIG_NETWORK_F	        	network;
	SYS_CONFIG_USER	            	user[MAX_USER_NUM];
	SYS_CONFIG_PTZ_PROTOCOL	    	ptzProtocol[MAX_PTZ_NUM];
	SYS_CONFIG_PTZ_CONTROL	    	ptzControl[MAX_CHANNEL_NUM];
	SYS_CONFIG_VIDEO_BASE_PARAM		videoParam[MAX_CHANNEL_NUM];
	SYS_CONFIG_OSD_INFO	        	osdInfo[MAX_CHANNEL_NUM];
	SYS_CONFIG_VIDEO_ENCODE	    	videoEncode[MAX_CHANNEL_NUM];
	SYS_CONFIG_VIDEO_ENCODE	    	videoSubEncode[MAX_CHANNEL_NUM];
	SYS_CONFIG_AUDIO_ENCODE	    	audioEncode[MAX_CHANNEL_NUM];
	SYS_CONFIG_AUDIO_ENCODE	    	audioEncodeTalkback;
	SYS_CONFIG_EMAIL_PARAM	    	emailParam;
	SYS_CONFIG_AUTO_MAINTAIN_PARAM	autoMaintainParam;
	SYS_CONFIG_RECORD_PARAM	    	recordParam[MAX_CHANNEL_NUM];
	SYS_CONFIG_RECORD_PUBLIC		recordPublic;
	SYS_CONFIG_CHANNEL_PARAM		channelParam[MAX_CHANNEL_NUM];        
	SYS_CONFIG_ALARM_PARAM	    	alarmParam;
	SYS_CONFIG_RS232_PARAM	    	rs232Param;
	SYS_CONFIG_DOOR_RULE	    	doorRule;
	SYS_CONFIG_DATA_UPLOAD	    	dataUpload[MAX_DATA_UPLOAD_NUM];
	SYS_CONFIG_PC_PARAM	        	pcParam[MAX_CHANNEL_NUM];
	SYS_CONFIG_MIDWARE	        	midParam[MAX_MIDWARE_USER_NUM];
	SYS_CONFIG_PC_CONFIG	    	pcConfig;
	SYS_CONFIG_LP_PARAM	        	lpParam[MAX_CHANNEL_NUM];
	SYS_CONFIG_ABDOOR_PARAM	    	abDoorParam[MAX_CHANNEL_NUM];
	SYS_CONFIG_FIV_PARAM	    	fivParam[MAX_CHANNEL_NUM];
	SYS_CONFIG_FIV_CONFIG	    	fivConfig[MAX_CHANNEL_NUM];
	SYS_CONFIG_RF433M_PARAM	    	rf433mParam;
	SYS_CONFIG_EYE_CONFIG	    	eyeConfig[MAX_CHANNEL_NUM];
	SYS_CONFIG_IO_CONFIG	    	ioConfig;
	SYS_CONFIG_RF433M_PUBLIC		rf433mPublic;
	SYS_CONFIG_UBOOT_ENV_BACKUP		ubootEnvBackup;
	SYS_CONFIG_LEDSHOW_SETTING		ledShowSetting;
	SYS_CONFIG_LEDBOARD_SETTING		ledBoardSetting;
	SYS_CONFIG_GROUP_SETTING		groupSetting;
	SYS_CONFIG_WL_PLATFORM	    	wlPlatform;
	SYS_CONFIG_THREEG_NET_PARAM		threegNetParam;
	SYS_CONFIG_WIFI_NETWORK	    	wifiNetwork;
	SYS_CONFIG_WIFI_CONNECT	    	wifiConnect;
	SYS_CONFIG_SYNOVATE	        	synovateSys;
	SYS_CONFIG_FTP_REC             	ftpRec;
	SYS_CONFIG_RS485_PARAM	    	rs485Param;
	SYS_CONFIG_FTP_UPLOAD           ftpUpload;
} PACK_ALIGN SYSCONFIG;

#undef PACK_ALIGN

int ReadSysConfig();
int SyncSysConfig();
int WriteSysConfig();
void *WriteSysConfig( void *args );
void InitDefaultSysConfig();
int LsppInitSysConfig();
int InitThttpdConfig();
int InitLangConfig();

int GetSysConfig( SYSCONFIG *pSysConfig );
int SetSysConfig( SYSCONFIG *pSysConfig );
int GetSysConfig( int type, void *configBuf, int configLen, int n = 0 );
int SetSysConfig( int type, void *configBuf, int configLen, int n = 0 );

int IsHeaderValid( SYSCONFIG *pSysConfig );

#endif  // _SYS_CONFIG_H

