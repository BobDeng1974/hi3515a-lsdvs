/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.09.16
**  description  : RTC
********************************************************************************/
#include <stdlib.h>
#include <sys/time.h>
#include "debug.h"
#include "const.h"
#include "rtc.h"
#include "timeExchange.h"
#include "timer.h"

int RealTimeSetDatetime( int year, int month, int day,
                   	int hour, int minute, int second )
{
	int nRet;
	struct timeval 	tv = {0};
	struct timezone tz = {0};

	tv.tv_sec    = FiTimeHumanToUtc( year, month, day, hour, minute, second );
	tv.tv_usec   = 0;
	nRet         = settimeofday( &tv, &tz );
    
        //CORRECTPRINT( "%s: %4d-%02d-%02d %02d:%02d:%02d!\r\n",
        	//__FUNCTION__, year, month, day, hour, minute, second );
    
	return nRet;
}

/**********************************************************************
* fn: ͬ��rtc ʱ�䵽ϵͳʱ��
***********************************************************************/
static void *RealTimeSyncRtcTimeToDatetime( void *args )
{
	int year, month, day, hour, minute, second;
    
	int nRet = RtcGetTime( &year, &month, &day, &hour, &minute, &second, NULL );
	if ( nRet != -1 ) 
    {
    	RealTimeSetDatetime( year, month, day, hour, minute, second );
    }
    
	return NULL;
}

void RealTimeAddTimer()
{
	AddRTimer( RealTimeSyncRtcTimeToDatetime, NULL, 600 );
}

/*************************************************************************
* fn: ��������ʱͬ��rtc ʱ�䵽ϵͳ
***************************************************************************/
void RealTimeSyncRtcWhenStartSys()
{
	RealTimeSyncRtcTimeToDatetime( NULL );
}

