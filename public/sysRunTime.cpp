/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.01.17
**  description  : ����ϵͳ���������߹���ʱ��
********************************************************************************/
#include <unistd.h>
#include <sys/time.h>
#include "timer.h"

/**************************************************************************
* func: ����ϵͳreset�����߹���ʱ��
***************************************************************************/
static struct timeval g_sysRunTime;
static void *UpdateSysRunTime( void *arg )
{
	static struct timeval base;
	struct timeval now;
	struct timeval sub;

	gettimeofday( &now, NULL );
	if( timercmp(&now, &base, <) )
    {
    	base = now;
    	return NULL;
    }
	timersub( &now, &base, &sub );
	if( sub.tv_sec > 10 )
    {
    	base = now;
    	return NULL;
    }
	base = now;
	timeradd( &g_sysRunTime, &sub, &g_sysRunTime );
    
	return NULL;
}

/********************************************************************
* ����: ϵͳreset�����߹���ʱ��(��)
**********************************************************************/
int SysRunTimeGet()
{    
	int runTime;

	runTime	= g_sysRunTime.tv_sec;

	return runTime;
}

//��һ����ʱ��,����ϵͳ�߹���ʱ��
void SysRunTimeAddTimer()
{
	AddRTimer( UpdateSysRunTime, NULL, 1 );
}

