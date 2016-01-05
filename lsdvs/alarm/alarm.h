#ifndef _DEAL_ALARM_MSG_H
#define _DEAL_ALARM_MSG_H

#include "const.h"
#include "paramManage.h"
#include "threadPool.h"

#define ALARM_TIME_NORMAL_COUNT		0
#define ALARM_TIME_RECOUNT	    	1

#define MAX_ALARM_OUTPUT_NUM		16


typedef struct _AlarmGuardHand_
{
	unsigned char 	guardFlag;
	char	    	reserved[3];
} ALARM_GUARD_HAND_T;

// һ������
typedef struct _AlarmGuardWeekTimeSeg_
{
	int timeStart;
	int timeStop;
} ALARM_GUARD_WEEK_TIME_SEG_T;

typedef struct _AlarmGuardTimer_
{
	unsigned char	timeNum;    // ��ʱ����
	char         	reserved[3];
	ALARM_GUARD_WEEK_TIME_SEG_T	timeSeg[MAX_WEEK_DAY*MAX_DAY_TIME_SEG];
} ALARM_GUARD_TIMER_T;

typedef struct _AlarmGuardScheme_
{
	ALARM_GUARD_HAND_T 	guardHand;    // �ֶ�����
	ALARM_GUARD_TIMER_T	guardTimer;    // ��ʱ����
} ALARM_GUARD_SCHEME_T;

typedef struct _AlarmWork_
{
	ALARM_GUARD_SCHEME_T	guard;        // ��������
	CONFIG_ALARM_LINKAGE_T	linkage;    // ��������
	uchar	            	normalcy;    // ��̬ 0:����; 1: ����.        
	uchar	            	interval;    // ̽����
	uchar	            	channel;    // �Ǹ�ͨ����
} ALARM_WORK_T;




int AlarmStartService();
int AlarmStopService();
void AlarmSendMsgIoAlarmParamChange();
void AlarmSendMsgMdAlarmParamChange( int channel );
int AlarmThreadpoolAdd( THREAD_FUN fun, void *args, int argsSize );
void AlarmSendMsgVlossAlarmParamChange( int channel );
void AlarmSendMsgShelterAlarmParamChange( int channel );
int AlarmTransmit(uint type, uint typeSubFlag);
void AlarmUpdateFlag( uint type, uint typeSubFlag );

#endif  // _DEAL_ALARM_MSG_H

