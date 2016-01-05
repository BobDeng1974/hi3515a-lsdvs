#ifndef __SNAPAPP_H__
#define __SNAPAPP_H__

typedef struct _SnapWorkTimer_
{
	int	enable;        // �Ƿ�ʹ�ܶ�ʱץ��
	int startSec;    // ��ʼʱ��,ÿ��ĵ���һ��
	int stopSec;    // ֹͣʱ��,ÿ��ĵ���һ��
	int interval;    // ץ�ļ��
} SNAP_WORK_PARAM_T;

void StartSnapAppThread();
void StopSnapAppThread();
int SnapAppMessageSend( int channel, int snapType );

void AddSnapTimer();
void InitSnapWorkParam();
void SnapTimerReleaseWorkParam();

#endif

