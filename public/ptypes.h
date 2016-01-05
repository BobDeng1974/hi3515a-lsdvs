#ifndef __PTYPES_H__
#define __PTYPES_H__

#include "const.h"

#define PARAM_CONFIG_MAX_MEMBERS	200

#define PACK_ALIGN	__attribute__((packed))

//�˽ṹ��Ĵ�С�̶�Ϊ512bytes
typedef struct _ParamConfigStoreHead_
{
	uint	size;            // SYS_CONFIG ���ýṹ��Ĵ�С	
	uint 	totalMembers;    // SYS_CONFIG �ж��ٸ���Ա
	ushort 	memberSize[PARAM_CONFIG_MAX_MEMBERS];    //ÿ���ṹ��Ĵ�С
	char	mark[16];         //  ��ʶ
	char	reserved[80];
} PACK_ALIGN PARAM_CONFIG_STORE_HEAD;

// 
// �����ṹ��
//
//1.ʱ��
typedef struct _TimeSt_
{
	uchar 	hour;        
	uchar 	minute;
	uchar 	second;
	char	reserved[1];
} PACK_ALIGN TIME_ST;

//2.ʱ���
typedef struct _TimeSegSt_
{
	TIME_ST		timeStart;    
	TIME_ST		timeEnd;
} PACK_ALIGN TIME_SEG_ST;

//3.һ��Ĺ���ʱ��ѡ��
typedef struct _DayWorkTime_
{
	TIME_SEG_ST		timeSeg[MAX_DAY_TIME_SEG];    // ʱ��� 
	uchar	    	enableFlag;        // 1: ʱ�����Ч, 0: ʱ�����Ч
	char	    	reserved[3];
} PACK_ALIGN DAY_WORK_TIME;

//4.һ�ܵĹ���ʱ��
typedef struct _WeekWorkTime_
{
	DAY_WORK_TIME		day[MAX_WEEK_DAY];    // һ�ܵĹ���ʱ�� 
} PACK_ALIGN WEEK_WORK_TIME;

//5.��������
typedef struct _SerialSt_
{
	uint	baudRate;    // ������
	uchar	dataBits;    // ����λ
	uchar	stopBits;    // ֹͣλ
	uchar	parity;        // У��λ
	uchar	comNum;        // ����һ������
	char 	reserved[4];
} PACK_ALIGN SERIAL_ST;

// ���ýṹ��ͷ
typedef struct _ParamConfigHead_
{
	char	signature[8];        // �����ļ���ʶ	
	char	reserved[16];
} PACK_ALIGN PARAM_CONFIG_HEAD;

//
// �豸������Ϣ
//
typedef struct _ParamConfigBaseInfo_ 
{
	char	devModel[24];                // �豸�ͺ�	
	char	serialNo[16];                // ��Ʒ���к�	
	char	hardwareVersion[32];        // Ӳ���汾��
	char	softwareVersion[32];        // ����汾��
	char	configureVersion[8];        // ���ð汾��	
	char	devName[32];        // �豸����
	uchar	chipNum;            // 3515aоƬ����
	uchar	channelNum;            // ʵ�ʵ�ͨ����
	uchar	videoInputNum;        // ��Ƶ����˿ڸ���
	uchar	videoOutputNum;        // ��Ƶ����˿ڸ���
	uchar	alarmInputNum;        // �澯����˿ڸ���
	uchar	alarmOutputNum;        // �澯����˿ڸ���	
	char	reserved[6];        // 
}PACK_ALIGN PARAM_CONFIG_BASE_INFO;

//
// �������
//
// 1.DNS
typedef struct _ConfigNetworkDns_
{
	char	dns1[16];            // ��DNS
	char	dns2[16];            // ����DNS
}PACK_ALIGN CONFIG_NETWORK_DNS;
// 2.�˿�
typedef struct _ConfigNetworkPort_
{
	ushort	searchPort;         // �����˿�
	ushort	msgPort;            // ��Ϣ�˿�,���˿� = ��Ϣ�˿� + 1.
	ushort	webPort;            // web�˿�
	char	reserved[14];
} PACK_ALIGN CONFIG_NETWORK_PORT;
// 3.����
typedef struct _ConfigNetworkCark_ 
{    
	char	mac[24];            // �����ַ
	char	ip[16];             // ip��ַ 
	char	netmask[16];        // ��������
	char	gateway[16];        // ����	
	char	broadAddr[16];      // �㲥��ַ
	uchar	dhcpEnable;         // 1: DHCP, 0: STATIC
	uchar	enableFlag;         // 1: ����, 0: ͣ��,����������������
	char	reserved[6];        
} PACK_ALIGN CONFIG_NETWORK_CARD;
//���������ܽṹ��,û�п���pppoe,3G,�Ժ��õ����Զ���
typedef struct _ParamConfigNetwork_
{
	CONFIG_NETWORK_CARD     	wired;   // ����
	CONFIG_NETWORK_CARD     	wifi;    // wifi
	CONFIG_NETWORK_DNS         	dns;     // dns
	CONFIG_NETWORK_PORT	    	port;    // �˿�
} PACK_ALIGN PARAM_CONFIG_NETWORK;

//
// �û�����
//
typedef struct _ParamConfigUser_ 
{
	char	name[32];          // �û���
	char	pwd[32];           // ����
	uint	permission;        // ÿ1 bit��ʶһ��Ȩ��;
	uchar	level;             // �û��ļ���:0,NONE,1,ADMIN,2,����û�;
	uchar	enable;            // ���û��Ƿ���Ч 
	char	reserved[6];    
} PACK_ALIGN PARAM_CONFIG_CLIENT_USER;

//
// ��Ƶ��������
//
typedef struct _ParamConfigVideoBaseParam_
{
	uchar	brightness;            // ����, 0~255
	uchar	contrast;              // �Աȶ�, 0~255
	uchar	saturation;            // ���Ͷ�, 0~255
	uchar	exposure;              // �ع��, 0~255
	short	hue;                   // ɫ��, -128~128
	char	reserved[6];
} PACK_ALIGN PARAM_CONFIG_VIDEO_BASE_PARAM;

//
// OSD��������
//
typedef struct _ParamConfigOsdLogo_
{
	uchar	enable;                // �Ƿ���ʾOSD 1: enable, 0: disable
	uchar	colorRed;              // ��ɫ
	uchar	colorGreen;            // ��ɫ
	uchar	colorBlue;             // ��ɫ
	ushort	xPos;                  // ����
	ushort	yPos;                  // ����
	char	logo[64];              // ���֧��64Bytes��logo
	uchar	bgTransparence;        // ����͸���� 0(��͸��)~100(100%͸��),��ʾ0%~100%
	char	reserved[7];
} PACK_ALIGN PARAM_CONFIG_OSD_LOGO;

typedef struct _ParamConfigOsdTime_
{
	uchar	enable;
	uchar	colorRed;    
	uchar	colorGreen;    
	uchar	colorBlue;    
	ushort	xPos;    // ��λ(����)
	ushort	yPos;
	uchar	bgTransparence;        // ����͸���� 0(��͸��)~100(100%͸��),��ʾ0%~100%
	char	reserved[7];
} PACK_ALIGN PARAM_CONFIG_OSD_TIME;

//
// ��Ƶ�������
//
typedef struct _ParamConfigVideoEncodePublic_
{
	uchar		videoStandard;        // ��Ƶ��ʽ: 0:PAL�ơ�1:NTSC��   2:AUTO
	char		reserved[3];        // 
} PACK_ALIGN PARAM_CONFIG_VIDEO_ENCODE_PUBLIC;

typedef struct _ParamConfigVideoEncode_
{    
	uchar		resolution;            // �ֱ���: 0:Qicf��1:Cif��3:HD1��4:D1 �ο�PIC_SIZE_E
	uchar		bitrateType;        // λ������: 0:VBR��1:CBR, �ο�RC_MODE_E
	uchar		frameRate;            // ֡��,��6λ��ʶ����֡�ʡ�bit7 �� bit8 ��ʶ֡�����ֵ,00:���ֵΪ25,01:���ֵΪ30,��������
	uchar		iFrameInterval;        // I֡���, [1,1000]
	uchar		preferFrame;        // ֡������, 0 or 1
	uchar		encodeType;            // 0:����Ƶ��, 1:��Ƶ��
	ushort		bitrate;            // λ��, ��λkbits/��, 200~3000
	char		reserved[4];        // 
} PACK_ALIGN PARAM_CONFIG_VIDEO_ENCODE;

//
// ��Ƶ�������
//
typedef struct _ParamConfigAudioEncode_
{
	uchar	sampleRate;            // ������, 0:8k, 1:16k, Ĭ��ֵ 0
	uchar	encodeType;            // ���뷽ʽ,0:adpcm, 1:g711, 2:g726, Ĭ��ֵ 0
	uchar	bitWidth;            // λ��,0:8bits, 1:16bits, Ĭ��ֵ 1
	uchar	chMode;                // ͨ��ģʽ, 0:��ͨ��, 1:������, Ĭ��ֵ 0
	uchar	amrMode;            // amr����ģʽ
	uchar	amrFormat;            // amr�����ʽ
	char	reserved[10];
} PACK_ALIGN PARAM_CONFIG_AUDIO_ENCODE;

//
// �Զ�ά��
//
typedef struct _ParamConfigAutoMaintain_
{
	TIME_ST	    	rebootTime[MAX_WEEK_DAY];    // ����ʱ��
	uchar	    	rebooDatetFlag;                // bit 0~6 �ֱ��ʶ�����յ�������,��bitΪ1��ʶ����ʱ����Ч,��֮��Ч
	char	    	reserved[7]; 
} PACK_ALIGN PARAM_CONFIG_AUTO_MAINTAIN;

//
// ¼�����
//
//1.¼�񹫹�����
typedef struct _ParamConfigRecordPublic_
{    
	uint	delSpace;        // Ӳ��¼��ռ䱨��ֵ  >= 50M  <= 10000M
	uint	delSize;        // reserve,��λ M
	uchar	loopRecord;        // ѭ��¼��,0:��֧��,1:֧��.
	uchar	preRecord;        // Ԥ¼,0:ֹͣ,1:����. 
	uchar	switchFileTime;    // reserve,¼���ļ��л�ʱ�� 10~30����(�̶�Ϊ20����)        
	char 	reserved[13];
} PACK_ALIGN PARAM_CONFIG_RECORD_PUBLIC;

//2.�ֶ�¼��
typedef struct _ParamConfigRecordHand_
{
	uchar	recFlag;        // 0:ֹͣ�ֶ�¼��,1:�����ֶ�¼��
	char	reserved[11];
} PACK_ALIGN PARAM_CONFIG_RECORD_HAND;

//3.¼���ܽṹ��
typedef struct _ParamConfigRecordParam_
{
	PARAM_CONFIG_RECORD_HAND	recHand;    //�ֶ�¼�� 
	WEEK_WORK_TIME	        	recTimer;    //��ʱ¼��
} PACK_ALIGN PARAM_CONFIG_RECORD_PARAM;

//
// ��������
//
//��������
typedef struct _ConfigAlarmlinkage_
{
	uint	linkageAlarmOut;    //�����������,ÿ1bit��ʶһ���������
	uchar	alarmOutDuration;    //�������ʱ��, ��λ��, 1 ~ 255 
	char	unused[3];            // ����
	uint   	linkageCapture;        //����ץ��,ÿ1bit��ʶһ��ͨ��
	uchar	captureNum;            //ץ������, 1 ~ 255     
	char	unused1[3];            // ����
	uint	linkageRecord;        //����¼��,ÿ1bit��ʶһ��ͨ��	
	uchar	recordDuration;        //����¼��ʱ��, ��λ��, 1 ~ 255 
	uchar   linkageBuzzer;        //���������� 0: no linkage; 1: linkage;
	uchar	buzzerDuration;        //buzzer�����ʱ��, ��λ��, 1 ~ 255     
	uchar   linkageEmail;        //����eamil. 0: not send; 1: send;
	uint	linkageEmailPicture;//����email����ͼƬ,ÿ1bit��ʶһ��ͨ��
	char    reserve[36];
} PACK_ALIGN CONFIG_ALARM_LINKAGE_T;

//2.IO(�ɽ�̽ͷ)����
typedef struct SysConfigAlarmIo
{    
	char	            	alarmDevName[32];    // ��IO�����豸������
	WEEK_WORK_TIME	    	armTimer;            // ��ʱ����
	CONFIG_ALARM_LINKAGE_T	linkage;            // ��������	
	uchar               	normalcy;            // ��̬, 0:����; 1:����	
	uchar               	armFlag;            // 0: ����; 1: �����������ֶ�Ϊ1,�򡰶�ʱ �������ֶ���Ч 
	char                	unused[2];    
	uchar                 	scoutInterval;        // �����ʱ��,��λ�� (10~255)
	char	            	reserved[7];
} PACK_ALIGN PARAM_CONFIG_ALARM_IO;

//
// ��������, ���֧��10�����ʹ�ô���(����RS232��RS485) 
//
typedef struct _ParamConfigSerial_
{
	SERIAL_ST	ptz;        //ͬһ���豸������ptz��ʹ��ͬһ���������� 
	SERIAL_ST	reserved[9];
} PACK_ALIGN PARAM_CONFIG_SERIAL;

//
// NTP����
//
typedef struct _ParamConfigNtp_
{
	uchar	    	enable;        // �Ƿ�ʹ��
	char	    	zone;        // ����ʱ��
	ushort	    	interval;    // ����ö�ʱһ��,��λ��	
	char	    	host[64];    // ֧������
	char	    	reserved[12];        // 
} PACK_ALIGN PARAM_CONFIG_NTP;

//
// Email����
//
typedef struct _ParamConfigEmail_
{    
	char serverIP[64];        // �����ʼ�������, �� smtp.163.com	
	ushort  port;            // �������˿�, Ĭ����25
	char align[2];
	char loginName[64];      // ��¼ID, ����ע������ abc@163.com,��ô���ֿ���Ϊabc,Ҳ����Ϊabc@163.com
	char password[32];        // ��¼���������
    char fromAddr[64];        // �ʼ��Ӹ����䷢��,        
    char userName[32];        // �����յ��ʼ�ʱ����������
    char toAddr[256];        // �����˵�ַ, ֧�ֶ���ռ���    
	char subject[64];       // �ʼ�����	
	char reserved[12];        // 
} PACK_ALIGN PARAM_CONFIG_EMAIL;

// 
// �ƶ���ⱨ��
//
// �ƶ��������
typedef struct _ConfigMoveDetectArea_
{
	ushort	area[12];    //��һ֡�ֳ�(12*16)�����,area[n]�е�ÿһ��bit��ʶ��n�е�ÿһ������Ƿ��ƶ������
	char	reserved[8];
} PACK_ALIGN CONFIG_MOVE_DETECT_AREA;

typedef struct _ParamConfigAlarmMoveDetect_
{
	WEEK_WORK_TIME	    	armTimer;        // ��ʱ����
	CONFIG_ALARM_LINKAGE_T	linkage;        // ��������	
	CONFIG_MOVE_DETECT_AREA detectArea;        // �������
	uchar     	sensitiveLevel;        // ������,1~9,ֵԽ��������Խ��
	uchar     	scoutInterval;        // �����ʱ��,��λ�� 
	uchar   	armFlag;            // 0: ����; 1: �����������ֶ�Ϊ1,�򡰶�ʱ �������ֶ���Ч 
	char		reserved[9];                
} PACK_ALIGN PARAM_CONFIG_ALARM_MOVE_DETECT;

//
// ��Ƶ�ڵ�
//
// �����ڵ�����Ĳ���
typedef struct _ConfigVideoOverlay_
{
	uint	color;
	ushort	x_start;
	ushort	y_start;
	ushort	width;
	ushort	height;
} PACK_ALIGN CONFIG_VIDEO_OVERLAY;//

typedef struct _ParamConfigVideoOverlay_
{
	uchar enable;
	uchar num;
	uchar align[2];    
	CONFIG_VIDEO_OVERLAY overlay[4];
} PACK_ALIGN PARAM_CONFIG_VIDEO_OVERLAY;

//
// ��Ƶ��ʧ����
//
typedef struct _ParamConfigAlarmVideoLose_
{
	WEEK_WORK_TIME	    	armTimer;            // ��ʱ����
	CONFIG_ALARM_LINKAGE_T	linkage;            // ��������	
	uchar               	armFlag;            // 0: ����; 1: �����������ֶ�Ϊ1,�򡰶�ʱ �������ֶ���Ч 
	uchar                 	scoutInterval;        // �����ʱ��,��λ�� (10~255)
	char	            	reserved[5];
    
} PACK_ALIGN PARAM_CONFIG_ALARM_VIDEO_LOSE;

//
// ftp ����
//
typedef struct _ParamConfigFtp_
{
	ushort 	enable;        // �Ƿ�ʹ��
	ushort 	port;        // �������˿�
	char	ip[64];                // ������ip
	char 	user[32];        // �û���
	char   	passwd[32];        // ����
	char	jpgUpChannel[16]; // ��Щͨ��ͨ��ftp �ϴ�jpg ͼƬ, 0, ���ϴ�; 1, �ϴ�
	char	reserved[8];                
} PACK_ALIGN PARAM_CONFIG_FTP;

//
// ��ʱץ�Ĳ���
//
typedef struct _ParamConfigSnapTimer_
{
	int	  enable;        // �Ƿ�ʹ��
	int   interval;        // ץ�ļ�� 10��36000 ��
	char  startTime[TIME_LEN];     // ��ʼʱ��	
	char  stopTime[TIME_LEN];     // ����ʱ��	    
} PACK_ALIGN PARAM_CONFIG_SNAP_TIMER;

//
// icmp ����
//
typedef struct _ParamConfigIcmp_
{
	uchar 	enable;                    // �Ƿ�ʹ��icmp
	char	unused[3];
	char	ipAddr[NET_ADDRSIZE];    // ��ping ��ip ��ַ
	int		interval;                // ���������ÿ���೤ʱ�䷢��һ�������� 5��100s
	int		timeOut;                // ����ping ����ȴ����յĳ�ʱʱ�� 5��100s
	int		fcount;                    // failed count, ping��ͨ�������ping ���ٴ�Ҳ����ping ��-c ������ 5��100 ��
	int		finterval;                // ��������·ʱ������ICMP���ļ��ʱ�� 10��100s	
	char	reserve[8];
} PACK_ALIGN PARAM_CONFIG_ICMP;

//
// ddns ����
//
typedef struct _ParamConfigDdns_
{
	uchar 	enable;                            // �Ƿ�ʹ��ddns
	uchar	vender;                            // �� DDNS_VENDER_EN
	ushort	port;                            // �������Ķ˿�
	char	userName[NORMAL_USER_NAME_LEN];    // ��½���û���
	char	passwd[NORMAL_PASSWD_LEN];        // ����
	char	url[NORMAL_URL_LEN];            // ��ʹ�õ�����
	char	ifName[MAX_PATH_LEVEL];            // �ӿ�����, eth0/eth1/ppp0/rw0
	int		interval;                        // ���µ�ʱ���� 120~65535 s	
	char	reserve[8];
} PACK_ALIGN PARAM_CONFIG_DDNS;

//
// dtu
//
typedef struct _ParamConfigDtu_
{
	uchar 	enable;                        // 0,��ʹ��; 1,ʹ��
	uchar 	transProtocol;                // ����Э��, 0,tcp; 1,udp;
	ushort	serverPort;                    // �������˿�
	char	severIp[NET_ADDRSIZE];        // ������IP ��ַ
	char	heartbeatContent[76];        // ������������,���32 ������,�ɰ������֡����֡�Ӣ�Ĵ�Сд��ĸ��
	ushort	interval;                    // �������ķ��ͼ��1��65535s
	char	reserve[10];
} PACK_ALIGN PARAM_CONFIG_DTU;

//
// wifi��������
//
typedef struct _ParamConfigWifiConnect_
{
	char	    	essid[32];        // ���֧��32���ֽ�,֧���ֶ�����ʹ������л�ȡ
	char	    	key[64];        // ����
	unsigned char 	connectFlag;    // ֻ��, 0-û�����ӵ�����·��;1-�Ѿ����ӵ�����·��
	unsigned char 	signalLevel;    // ֻ��, �ź�ǿ��, 1~5��
	char	    	reserved[14];
} PACK_ALIGN PARAM_CONFIG_WIFI_CONNECT_T;

typedef struct _ParamConfigThreeg_
{
	uchar 	enableFlag;    // 1,ʹ��3G��ΪĬ������
	char	reserved[63];     
} PARAM_CONFIG_THREEG_T;

//
// ��Ƶ�ڵ�
//
typedef struct _ParamConfigVideoShelter_
{
	WEEK_WORK_TIME	    	armTimer;            // ��ʱ����
	CONFIG_ALARM_LINKAGE_T	linkage;            // ��������	
	uchar               	armFlag;            // 0: ����; 1: �����������ֶ�Ϊ1,�򡰶�ʱ �������ֶ���Ч 
	uchar                 	scoutInterval;        // �����ʱ��,��λ�� (10~255)
	uchar	sensitivity;   //������  ��VIDEO_SHELTER_SENSITIVITY_EN
	char	reserved[5];     
} PARAM_CONFIG_ALARM_VIDEO_SHELTER;


#undef PACK_ALIGN

#endif 

