/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ����3G��GPSҵ��
**  date           :  2014.9.25
**
**  version       :  1.0
**  author        :  sven
********************************************************************************/
#include <pthread.h>
#include <string.h>
#include <unistd.h>
    
#include "const.h"
#include "serial.h"
#include "thread.h"
#include "debug.h"
#include "malloc.h"
#include "threegSerial.h"
#include "gpsCom.h"
#include "gpsGprmc.h"
#include "atGps.h"
#include "threegGps.h"
    
#define THREEG_GPS_BUFSIZE	2048
static int g_threegGpsFlag = FI_FALSE;
    
static int ThreegGpsErr( THREEG_GPS_COMMUNICATE *pThreegGps, char *pLine )
{
	pThreegGps->anaDataSize = 0;
	return 0;
}

static int ThreegGpsGprmc( THREEG_GPS_COMMUNICATE *pThreegGps, char *pLine )
{
	FiGpsParseGprmc( pLine );
    
	pThreegGps->anaDataSize = 0;
	return 0;
}

/*
*  func         : �����յ�������������Ƿ��кϸ���У�GPS_MSG_START�� GPS_MSG_STOP ֮�����Ϊ�ϸ���
*  checkedSize	: out,�Ѿ����������ݴ�С��
*  pLine	    : ���ҵ�����Ч�п����� pLine  
*  ����         : 0,�ҵ��ϸ���; -1,�Ҳ����ϸ���.
*/
static int ThreegGpsCheck( THREEG_GPS_COMMUNICATE *pThreegGps, char *pLine, int *pCheckedSize )
{        
	int ret = -1;
	int checkedSize = 0, cpySize, secondKeySize;
	int rcLfLen = strlen(GPS_MSG_START);
	char *pRcLfFirst, *pRcLfSecond;

	if( NULL == pThreegGps || NULL == pLine || NULL == pCheckedSize )
    {
    	SVPrint( "NULL == pThreegGps || NULL == pLine || NULL == pCheckedSize\r\n" );
    	return -1;
    }
    
	pRcLfFirst = strstr( pThreegGps->sockBuf, GPS_MSG_START );
	if( NULL == pRcLfFirst )
    {        
    	checkedSize += pThreegGps->sockDataSize;
    }
	else
    {
    	do	// ȥ���������� GPS_MSG_START
        {
        	pRcLfFirst += rcLfLen;
        }while( 0 == memcmp( pRcLfFirst, GPS_MSG_START, rcLfLen ) );
        
    	checkedSize += ( pRcLfFirst - pThreegGps->sockBuf - rcLfLen );
    	ret = 0;
    }

	if( ret != -1)
    {
    	ret = -1;
        
    	pRcLfSecond     = strstr( pRcLfFirst, GPS_MSG_STOP );
    	secondKeySize     = strlen( GPS_MSG_STOP );
        
    	if( NULL != pRcLfSecond )    // �ҵ��ڶ���"\r\n"
        {
        	cpySize = pRcLfSecond - pRcLfFirst;
        	cpySize = (cpySize > (GPS_LINE_SIZE - 1)) ? (GPS_LINE_SIZE - 1) : cpySize;
        	memcpy( pLine, pRcLfFirst, cpySize );
        	pLine[cpySize] = '\0';
        	checkedSize += ( cpySize + rcLfLen + secondKeySize); 
        	ret = 0;
        }
    	else if( pThreegGps->sockDataSize >= GPS_LINE_SIZE ) // û���ҵ��ڶ���"\r\n",ͬʱ���ջ����������ˡ�
        {
        	checkedSize = pThreegGps->sockDataSize;
        }
    }
    
    *pCheckedSize = checkedSize;
    
	return ret;
} 


static THREEG_GPS_MSG_FUNC g_threegGpsMsgFunc[] = 
{
    { GPS_MSG_GPRMC_KEY,     	ThreegGpsGprmc         }
};
/*
* func	: ����һ����������������
* pLine : ��3Gģ���л�ȡ����һ������������
*/
static THREEG_GPS_FUNC ThreegGpsGetFunc( char *pLine)
{
	THREEG_GPS_FUNC func = ThreegGpsErr;
	int loopTimes, i;
	loopTimes = sizeof( g_threegGpsMsgFunc ) / sizeof( THREEG_GPS_MSG_FUNC ) ;
    
	for( i = 0; i < loopTimes; ++i )
    {
    	if( NULL != strstr( pLine, g_threegGpsMsgFunc[i].msgKey ) )
        {
        	func = g_threegGpsMsgFunc[i].func;
        	break;
        }
    }

	return func;
}
/*
* func	: ����һ����������������
* pLine : ��3Gģ���л�ȡ����һ������������
* ����	: ���ݸ������Ҫ�������ĺ���
*/
static THREEG_GPS_FUNC ThreegGpsParseCmdLine( char *pLine )
{
	THREEG_GPS_FUNC func;
	if( NULL == pLine )
    {
    	SVPrint( "NULL == pLine\r\n" );
    	return NULL;
    }

	func = ThreegGpsGetFunc( pLine );
    
	return func;
}

/*
*  func : ������յ������ݡ�
*  phandledSize : out, ����������ݵĴ�С 
*  ���� : 0,�ɹ�������һ������; -1,û�гɹ���������
*/
static int ThreegGpsHandleRecvMsg( THREEG_GPS_COMMUNICATE *pThreegGps, int *phandledSize )
{
	int 	ret;
	char	line[GPS_LINE_SIZE];
	int 	checkedSize = 0;
	THREEG_GPS_FUNC	doFunc;
    
	if( NULL == pThreegGps )
    {
    	SVPrint( "NULL == pThreegGps!\r\n" );
    	return -1;
    }

	ret = ThreegGpsCheck( pThreegGps, line, &checkedSize);
	if( ret == 0 ) // �ҵ�һ����ɵ���Ϣ
    {
    	doFunc = ThreegGpsParseCmdLine( line );
    	if( NULL != doFunc ) ret = doFunc( pThreegGps, line );
        // ���� line ������Ӧ����Ϣ
    }
    
    *phandledSize = checkedSize;
    
	return ret;
}

void *ThreegGpsRecvThread( void *arg )
{
	char *pRecvBuf;
	THREEG_GPS_COMMUNICATE threegGps;     
	int ret, recvSize, handedSize;

	threegGps.sockBuf	= (char *)Malloc( THREEG_GPS_BUFSIZE );
	if( NULL == threegGps.sockBuf )
    {        
    	SVPrint( "error:NULL == threegGps.sockBuf!\r\n" );
    	Free( threegGps.sockBuf );
    	Free( threegGps.anaBuf );
    	return NULL;
    }
	threegGps.sockBuf[0] = '\0';
	threegGps.sockDataSize = 0;
    
	SVPrint( "start ThreegGpsRecvThread(%d)!\r\n", ThreadSelf() );
	while( FI_TRUE == g_threegGpsFlag )
    {
    	pRecvBuf = threegGps.sockBuf + threegGps.sockDataSize; // -1 ����Ϊ���е��ַ�����Ҫ�ŵ�'\0'ǰ
    	recvSize = THREEG_GPS_BUFSIZE - threegGps.sockDataSize - 1;
    	ret = FiThreegSerialRecvData( SERIAL_TYPE_GPS, pRecvBuf, recvSize );
    	if( ret > 0 )
        {    
        	threegGps.sockDataSize += ret;
        	threegGps.sockBuf[threegGps.sockDataSize] = '\0';
        	do
            {
            	ret = ThreegGpsHandleRecvMsg( &threegGps, &handedSize );
            	if( ret == 0 )
                {                    
                	threegGps.sockDataSize -= handedSize;
                	memmove( threegGps.sockBuf, threegGps.sockBuf + handedSize, threegGps.sockDataSize );
                	threegGps.sockBuf[threegGps.sockDataSize] = '\0';                 
                }
            	usleep(5);
            }while( ret == 0 );
        }    

        
    	usleep(500000);
    } // end while( FI_TRUE == g_threegGpsFlag )

	Free( threegGps.sockBuf );
	Free( threegGps.anaBuf );
	SVPrint( "stop ThreegGpsRecvThread!\r\n" );

	return NULL;
}

static pthread_t	g_threegGps;
int ThreegGpsStartService()
{
	int ret;

	ret = FiAtGpsCtl( AT_GPS_ON );
	if( ret != 0 )
    {
    	SVPrint( "Gps start failed, will not start gps recv thread!\r\n" );
    	return ret;
    }
    
	g_threegGpsFlag = FI_TRUE;
	ret = ThreadCreateCommonPriority( &g_threegGps, ThreegGpsRecvThread, NULL );
	if ( ret != 0 )
    {
    	g_threegGpsFlag = FI_FALSE;
    	SVPrint( "ThreadCreateCommonPriority() error:%s\r\n", STRERROR_ERRNO );
    }

	return ret;
}

int ThreegGpsStopService()
{    
	g_threegGpsFlag = FI_FALSE;
	if( 0 != ThreadJoin( g_threegGps, NULL ) )
    {
    	SVPrint( "ThreadJoin error:%s!\r\n", STRERROR_ERRNO );
    	return FI_FAILED;
    }
	GpsComDeInit();
	return FI_SUCCESSFUL;
}
    
    

