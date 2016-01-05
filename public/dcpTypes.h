#ifndef __DCPTYPES_H__
#define __DCPTYPES_H__

#include "ptypes.h"

#define PACK_ALIGN	__attribute__((packed))

typedef struct _ClientMsgHeadSt_
{
	unsigned int	mark;                // һ����Ϣ��ʼ�ı�ʶ��=CLIENT_MSG_MARK
	unsigned short	seq;                // ��Ϣ����
	unsigned short 	msgType;             // ��Ϣ����
	unsigned short 	subType;             // ��Ϣ������
	unsigned short 	ackResult;             // ���ؽ��
	unsigned int 	len;                 // ��Ϣ�峤��	    
	unsigned char 	unused[4];
}PACK_ALIGN DCP_HEAD_T;

typedef PARAM_CONFIG_BASE_INFO             	CONFIG_BASE_INFO;
typedef	PARAM_CONFIG_NETWORK	        	CONFIG_NETWORK;              
typedef	PARAM_CONFIG_CLIENT_USER          	CONFIG_CLIENT_USER;                                                                           
typedef	PARAM_CONFIG_VIDEO_ENCODE_PUBLIC	CONFIG_VIDEO_ENCODE_PUBLIC;                                                                           
typedef	PARAM_CONFIG_VIDEO_ENCODE           CONFIG_VIDEO_ENCODE;                                                                           
typedef	PARAM_CONFIG_VIDEO_BASE_PARAM       CONFIG_VIDEO_BASE_PARAM;                                                                           
typedef	PARAM_CONFIG_OSD_LOGO               CONFIG_OSD_LOGO_T;                                                                           
typedef	PARAM_CONFIG_OSD_TIME               CONFIG_OSD_TIME_T;             
typedef	PARAM_CONFIG_AUDIO_ENCODE	        CONFIG_AUDIO;
typedef	PARAM_CONFIG_AUTO_MAINTAIN          CONFIG_AUTO_MAINTAIN;         
typedef	PARAM_CONFIG_RECORD_PUBLIC          CONFIG_RECORD_PUBLIC;        
typedef	PARAM_CONFIG_RECORD_PARAM           CONFIG_RECORD_PARAM;          
typedef	PARAM_CONFIG_NTP                    CONFIG_NTP;                   
typedef	PARAM_CONFIG_EMAIL                  CONFIG_EMAIL; 
typedef PARAM_CONFIG_ALARM_IO	        	CONFIG_ALARM_IO;
typedef PARAM_CONFIG_ALARM_VIDEO_LOSE		CONFIG_ALARM_VIDEO_LOSE;
typedef PARAM_CONFIG_ALARM_VIDEO_SHELTER	CONFIG_ALARM_VIDEO_SHELTER;
typedef PARAM_CONFIG_ALARM_MOVE_DETECT		CONFIG_ALARM_MOVE_DETECT;


typedef struct _ConfigOsd_
{
	CONFIG_OSD_LOGO_T 	osdLogo;
	CONFIG_OSD_TIME_T 	osdTime;
} PACK_ALIGN CONFIG_OSD;

//
// �ͻ��˵�¼��dvs����, pc->pu
typedef struct _LoginDvsReq_
{
	char user[NORMAL_USER_NAME_LEN];        // �û���
	char passwd[NORMAL_PASSWD_LEN];    // ����
	char reserved[32];    // ����
} PACK_ALIGN LOGIN_DVS_REQ_T;
// ��¼�ظ�, pu->pc
typedef struct _LoginDvsRes_
{
	uint	permission;        // ÿ1 bit��ʶһ��Ȩ��;
	uint	userStreamMark;    // ���û�������ʶ,�ͻ�������������Ƶ��ʱ��Ҫ�������mark
	uchar	level;            // �û��ļ���:0,NONE; 1,Admin; 2,����û�;
	char	reserved[7];    
} LOGIN_DVS_RES_T;

//
// ������Ƶ�� pc->pu
typedef struct _StreamReq_
{
	uint 	userStreamMark; // �ڵ�¼��ʱ���� pu ����
	int		channel;
} STREAM_REQ_T;
// ������Ƶ���ְ� pu->pc
typedef struct _StreamPackHead_
{
	ushort 	len;    // ��������	
	uchar 	seq;    // �����, ��ʹ��tcp �����ʱ�����������Ҫ��
	uchar 	mark;    // ����ʶ, 0Ϊһֻ֡��һ����,1Ϊ��һ��,2Ϊ������,3Ϊ�м��
} STREAM_PACK_HEAD_T;



//
// ʱ�����
typedef struct _DvsTime_
{
	char timeVal[DATETIME_LEN];
} DVS_TIME_T;

//
// ¼���������� pc->pu
typedef struct _DcpSearchRecordCond_
{
	int  channel;        // ͨ����
	uint type;            // ¼������
	char startTime[DATETIME_LEN];     // ��ʼʱ��
	char endTime[DATETIME_LEN];     // ����ʱ��
} DCP_SEARCH_RECORD_COND_T;

//
// ����¼��Ľ�� pu->pc
typedef struct _DcpSearchRecordResult_
{
	char	recordName[NORMAL_FILENAME_LEN];    // ¼���ļ���
	char	startTime[DATETIME_LEN];    // ��ʼʱ��(YYYY-MM-DD hh:mm:ss)
	char	endTime[DATETIME_LEN];        // ����ʱ��(YYYY-MM-DD hh:mm:ss)
	uint	recordLen;                    // ¼�񳤶�
	uint	recordType;                    // ¼������	
} DCP_SEARCH_RECORD_RESULT_T;

// 
// �������� pc->pu 
typedef struct _UpdateReq_ 
{ 
   uint   fileSize;     // �����ļ���С
   char   reserved[64]; 
} DCP_UPDATE_REQ_T;

// 
// ¼���������� pc->pu
typedef struct _DcpRecordReq_
{
	char recFileName[NORMAL_FILENAME_LEN]; // ��������·����¼���ļ���
} DCP_RECORD_REQ_T;

//
// ��־��������
typedef struct _DcpGetLog_
{
    unsigned char logType;      // ��Ҫ���ص���־����
    unsigned char logLevel;  // ��Ҫ��������־��ͼ���
    char reserved[6];
} DCP_GET_LOG_T;

// 
// ��������
/*
�����Ӳ������ݱ������;����� 
���� ��Ƶ��ʧ����  �� 
0��ʾ ͨ��1 
1��ʾ ͨ��2 
2��ʾ ͨ��3 

���IO������ 
0����ʾ��1��IO���� 
1����ʾ��2��IO����
*/
typedef struct _DcpAlarmRes_
{
	uint alarmType;        // ��������   
	uint alarmTypeSub;   // �����Ӳ���   �±��0 ��ʼ
} DCP_ALARM_RES_T;

//
// ��ȡ�洢��Ϣ�ķ��ؽ����ÿ���洢һ���ṹ��
typedef struct _DcpStorageInfo_
{
    int  type;                 // �洢������, �μ� HDD_DEV_TYPE_ST
    uint totalSize;            // �����ܴ�С ��λMBytes
    uint freeSize;             // ����ʣ��ռ� ��λMBytes
} DCP_STORAGE_INFO_T;

//
//����ʱ��
typedef struct _DcpDateTime_
{
	char dateTime[20];   //2013-09-23 09:05:29
	char reserved[8];
} DCP_DATE_TIME_T;

// Ӳ��״̬�쳣
typedef enum _DcpHddStatErrCode_
{
    DCP_HDD_STAT_ERR_FULL = 0,
    DCP_HDD_STAT_ERR_REMOVED,
    DCP_HDD_STAT_ERR_OTHER
} DCP_HDD_STAT_ERR_CODE_EN;

typedef struct _DcpHddStatErr_
{
	int errCode;        // 0. Ӳ���� 1.Ӳ�̰γ� 2.����   
} DCP_HDD_STAT_ERR_T;

#undef  PACK_ALIGN

#endif // __DCPTYPES_H__

