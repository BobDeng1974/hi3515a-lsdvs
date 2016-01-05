/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**	�ļ���: record.h
**  description  : for record.cpp
**  date           :  2013.10.18
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/

#ifndef __RECORD_H__
#define __RECORD_H__

#include <pthread.h>
#include <sys/time.h>
#include "ttypes.h"
#include "paramManage.h"
#include "recordSearch.h"
#include "recordFit.h"

#define RECORD_BARE_STREAM	//ʹ������¼��

#define RECORD_FILENAME_PREFIX	"brec_"

#define MAX_WEEK_DAY		7
#define MAX_TIME_SEG_NUM 	4

#define RECORD_TIME_ERROR_RANGE	    	30	//second
#define RECORD_TIMER_SWITCH_TIME		20	//minute
#define RECORD_TIMER_SWITCH_TIME_ALARM	3	//minute

#define RECORD_INDEX_VERSION	0x1FDF0301	/*�����պ����ʱ�����չ,��2�ֽڹ̶�,��2�ֽڿɱ�*/

typedef struct _RecordThread
{
	int channel;
	pthread_t recordThreadId;    
	pthread_mutex_t recordLock;
	int	recordThreadRunFlag;    
	int recordCtlFlag;
}RECORD_THREAD;

typedef struct _RecordManage
{
	pthread_t recordManageId;
	int recordManageRunFlag;
}RECORD_MANAGE;

enum _RecordCtl
{
	REC_START = 0,    //��ʼ¼��
	REC_STOP,        //ֹͣ¼��
	REC_SWITCH,        //�л�¼��
	REC_WRITE,        //д¼���ļ�
	REC_SLEEP	    //¼��ģ������
};

#ifndef PACK_ALIGN
#define PACK_ALIGN __attribute__((packed))
#endif

/*¼���ýṹ��*/
typedef struct _RecordPublic
{    
	uint delSpace;            //Ӳ��¼��ռ䱨��ֵ  >= 100M  <= 10000M
	uint delSize;            //reserve,ɾ��¼��Ĵ�С(�̶�Ϊ����ɾ��)
	uchar loopRecord;        //ѭ��¼��,0:��֧��,1:֧��.
	uchar preRecord;        //Ԥ¼,0:ֹͣ,1:����. 
	uchar switchFileTime;    //reserve,¼���ļ��л�ʱ�� 10~30����(�̶�Ϊ20����)        
	char reserve[13];                
} PACK_ALIGN RECORD_PUBLIC;

/*�ֶ�¼��*/
typedef struct _RecordHand
{
	uchar recHand;    //0:ֹͣ�ֶ�¼��,1:�����ֶ�¼��
	char reserve[3];
} PACK_ALIGN RECORD_HAND;

/*��ʱ¼��ṹ��*/
typedef struct _RecTimeSeg
{
	uchar	startHour;
	uchar	startMinute;
	uchar	startSecond;
	uchar	stopHour;
	uchar	stopMinute;
	uchar	stopSecond;
	uchar 	reserve[2];
} PACK_ALIGN REC_TIME_SEG;

typedef struct _TimeWeek
{
	REC_TIME_SEG	timeSeg[MAX_TIME_SEG_NUM];
	char	    	enableFlag;    //1: enable, 0: disable
	char	    	reserve[3];
} PACK_ALIGN TIME_WEEK;

typedef struct _RecordTimer
{
	TIME_WEEK timerWeek[MAX_WEEK_DAY];
} PACK_ALIGN RECORD_TIMER;

#undef PACK_ALIGN



typedef struct _RecordPublicConf
{
	char loopRecordFlag;
	char reserve[15];
}RECORD_PUBLIC_CONF;



typedef struct _RecordLedStatus
{
	int openFlag;
	int recStatus[REAL_CHANNEL_NUM];
}RECORD_LED_STATUS;

int FiRecSetRecFileSwitchTime(int switchTime);
int FiRecGetRecFileSwitchTime();
int FiRecSetRecFileSwitchTimeAlarm(int switchTime);
int FiRecGetRecFileSwitchTimeAlarm();

void FiRecStartRecordService(void);
void FiRecStopRecordService(void);
void FiRecRecordInit(void);
void FiRecInitPublic(void);
void FiRecDelRecordInit(void);
int FiRecStartRecord(int channel,uint recType);
int FiRecStopRecord(int channel,uint recType);
int FiRecSetRecordingFilename(int channel,char *rec_name,char *index_name);
int FiRecGetRecordingFilename(int channel,char *rec_name,char *index_name);

int FiRecSetHandRecord( int channel, PARAM_CONFIG_RECORD_PARAM *pRecordParam );

void FiRecGetTimerRecordPolicy(int channel,int weekDay,TIME_WEEK *recTimerPolicy);
int FiRecSetTimerRecordPolicy( int channel, int weekDay, PARAM_CONFIG_RECORD_PARAM *pRecordParam );

time_t FiAppGetSysRunTime(void);
int FiRecIsRecording();
int FiRecIsHandLeRecording(int channel);

// Ϊɾ��¼���ֹͣ¼�����
void RecordStopServiceForDel();
// Ϊɾ��¼�������¼�����
void RecordRestartServiceForDel();


#endif //__RECORD_H__

