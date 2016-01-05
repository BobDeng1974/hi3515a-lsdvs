/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ����wifiģ��
**  date           :  2013.10.21
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "debug.h"
#include "malloc.h"
#include "linuxFile.h"
#include "paramConfig.h"

#include "wifiCom.h"
#include "wifiFifo.h"
#include "wifiConf.h"
#include "wifi.h"
#include "sysRunTime.h"
#include "paramManage.h"
#include "network.h"
#include "netIp.h"
#include "netMask.h"
#include "netGateway.h"
/*
*	fn	    : ��һ���л�ȡessid
	����	: ESSID:"lisem1" [7]
*	pLine   : һ������
*	lineLen : �������ݵĳ���
*	pEssid     : ��ȡ����id

*/
static void GetEssid( char *pLine, int lineLen, char *pEssid )
{
	int i;
	char *pStrSrc = pLine, *pStrDst = pEssid;    

	i = 0;
	while( *pStrSrc != '"' && i < lineLen ) 
    {
    	pStrSrc++;
    	i++;
    }
	pStrSrc++;

	for( i = 0; i < 32; i++ )
    {
    	if( *pStrSrc == '"' )
        {
        	break;
        }
        *pStrDst++ = *pStrSrc++;        
    }    
}

static const WIFI_SIGNAL_LEVEL_MAP g_wifiSignal[] = 
{
    { -20, WIFI_SIGNAL_LEVEL_5 },
    { -40, WIFI_SIGNAL_LEVEL_4 },
    { -60, WIFI_SIGNAL_LEVEL_3 }, 
    { -80, WIFI_SIGNAL_LEVEL_2 },
    { -100, WIFI_SIGNAL_LEVEL_1 }
};

/*
*	fn	: ��dbmת�����źŵĸ���
*	dbm	: ��ת����dbmֵ
*	����: ת����ĸ���
*/
int WifiSignalDbmToLevel( int dbm )
{
	unsigned int i;
	int level = 0;
    
	if( dbm >= 0) return 0;
    
	for( i = 0; i < (sizeof(g_wifiSignal) / sizeof(WIFI_SIGNAL_LEVEL_MAP)); i++ )
    {
    	if( dbm >= g_wifiSignal[i].signalVal )
        {
        	level = g_wifiSignal[i].level;
        	break;
        }
    }

	return level;
}

static int GetSignalLevel( char *pLine )
{ 
	int num, level = 0;
	char *ptr;

	ptr = strstr( pLine, WIFI_MARK_SIGNAL );
	if( NULL != ptr )
    {
    	ptr += strlen( WIFI_MARK_SIGNAL );
    	num = atoi( ptr );
    	level = WifiSignalDbmToLevel( num );
    }

	return level;
}

/*
*	fn: ������������ļ��л�ȡwifi·��������Ϣ
*	pScanResultFile : �������ļ���
*	pWifiScanResult : out, ���
*	����:	��������·�����ĸ���,�������-1��ʾ����
*/
int GetWifiScanInfo( char *pScanResultFile, WIFI_SCAN_RESULT **pWifiScanResult )
{    
	char *ptr;
	int ret = -1;
	int fd;
	int essidLineLen, offset, routeCount = 0;    
	WIFI_SCAN_RESULT wifiScanResult; 
	char *pResult = NULL;
	char wifiLine[WIFI_SCAN_MAX_LINE][WIFI_SCAN_LINE_SIZE];    
    
	if( NULL == pWifiScanResult || NULL == pScanResultFile )
    {
    	SVPrint( "error:NULL == pWifiScanResult || NULL == pScanResultFile!\r\n" );
    	return -1;
    }

	if( -1 != (fd = open( pScanResultFile, O_RDONLY)) )
    {        
    	while( (essidLineLen = Readline(fd, wifiLine[0], sizeof( wifiLine[0] ))) > 0)
        {            
        	if( (ptr = strstr( wifiLine[0], WIFI_MARK_ESSID)) != NULL )    // ����ESSID
            {                
            	memset( &wifiScanResult, 0x00, sizeof(wifiScanResult) );
            	if((ret = Readline( fd, wifiLine[1], sizeof(wifiLine[1]) )) > 0) // ��ȡ�ź�ǿ��
                {
                	wifiScanResult.signalLevel = GetSignalLevel( wifiLine[1] );
                }
            	if( ret > 0 && (ret = Readline( fd, wifiLine[2], sizeof(wifiLine[2]) )) > 0 ) // �鿴�Ƿ��м���
                {
                	if( strstr( wifiLine[2], WIFI_MARK_KEY_ON ) != NULL )
                    {
                    	wifiScanResult.encType = WIFI_ENC_WEP;
                    }
                }
            	if( ret > 0  && wifiScanResult.encType != WIFI_ENC_NONE
                    && (ret = Readline( fd, wifiLine[3], sizeof(wifiLine[3]) )) > 0 ) // �鿴���ܷ�ʽ
                {
                	if( strstr( wifiLine[3], WIFI_MARK_ESSID ) != NULL )
                    {
                    	offset = 0 - ret;
                    	lseek( fd, offset, SEEK_CUR);
                    }
                	else if( strstr( wifiLine[3], WIFI_MARK_WIFI_ENC_WPA ) != NULL )
                    {
                    	wifiScanResult.encType = WIFI_ENC_WPA;
                    }
                	else if( strstr( wifiLine[3], WIFI_MARK_WIFI_ENC_WPAPSK) != NULL )
                    {
                    	wifiScanResult.encType = WIFI_ENC_WPAPSK;
                    }
                }
            	GetEssid( wifiLine[0], essidLineLen, wifiScanResult.essid );

            	FiPrint2( "wifiScanResult.encType = %d!\r\n", wifiScanResult.encType );

            	routeCount++;
            	if( NULL == pResult )
                {
                	pResult = (char *)Malloc( sizeof(WIFI_SCAN_RESULT) );
                }
            	else
                {
                	pResult = (char *)realloc( pResult, sizeof(WIFI_SCAN_RESULT) * routeCount );
                }    
            	memcpy( pResult + sizeof(WIFI_SCAN_RESULT) * (routeCount - 1), 
                                    &wifiScanResult, sizeof(wifiScanResult) );    
            } // if( ptr = strstr( wifiLine[0], WIFI_MARK_ESSID	        
        }
        *pWifiScanResult = (WIFI_SCAN_RESULT *)pResult;
    	close( fd );
    } // if( -1 != (fd == open( pScanResultFile, O_RDONLY))

	return routeCount;
    
}

/*
*	fn : ����wifi�������
*	pWifiScanResult : out, ��ŷ��ؽ���Ľṹ��
*	pScanSize	    : out, pWifiScanResult��ָ���ڴ�ĳ���
* 	����	        : ��������·�����ĸ���,��������򷵻�-1.
*/
int WifiScanResult( WIFI_SCAN_RESULT **pWifiScanResult, int *pScanSize )
{
	int i;
	static int baseTime = -100;
	int curTime;
	int routeCount;
    
	if( NULL == pWifiScanResult || NULL == pScanSize )
    {
    	SVPrint( "error:NULL == pWifiScanResult || NULL == pScanSize!\r\n" );
    	return -1;
    }
    
	curTime = SysRunTimeGet();

	if( curTime - baseTime > WIFI_SCAN_INTERVAL ) 
    {
    	WifiFifoCmd( WIFI_FIFO_CMD_SCAN );
    	baseTime = curTime;
    	for( i = 0; i < 5; i++ )
        {
        	if( 0 == access( WIFI_SCAN_FINISH_FLAG, F_OK) )
            {
            	unlink( WIFI_SCAN_FINISH_FLAG );
            	break;
            }
        	else
            {
            	sleep( 1 );
            }        
        }
    }

	routeCount = GetWifiScanInfo( (char *)WIFI_SCAN_RESULT_FILENAME, pWifiScanResult );
    *pScanSize = routeCount * sizeof( WIFI_SCAN_RESULT );  

	return routeCount;    
}

// ��ʼ��wifi����
int WifiInitNetwork()
{
	int 	ret;
	PARAM_CONFIG_THREEG_T threeg;
	PARAM_CONFIG_NETWORK network;    
	PARAM_CONFIG_WIFI_CONNECT_T wifiConnect;

	memset( &threeg, 0x00, sizeof(threeg) );            
	ParamGetThreeg( &threeg );
	ret = ParamGetNetwork( &network );    
	if( FI_SUCCESSFUL == ret )
    {
    	ret = WifiSetNetworkInfoToFile( NULL, NULL, network.wifi.gateway );    
    	if( 0 == (ret = ParamGetWifiConnect(&wifiConnect)) )
        {
        	WifiSetConncetInfoToFile( wifiConnect.essid, wifiConnect.key );
        	sync();
        }
        
    	if( 1 == network.wifi.enableFlag )
        {            
        	if( 0 == network.wifi.dhcpEnable ) // ��̬ IP
            {            
            	ret = NetSetIpAddr( (char *)NET_WIFI_NAME, network.wifi.ip );
            	if( ret == 0 ) ret = NetSetMask( (char *)NET_WIFI_NAME, network.wifi.netmask );

                //if( 1 == network.wifi.beDefaultGateway && FI_TRUE != threeg.enableFlag ) 
                //{
                //	NetRouteAddDefaultGateway( (char *)NET_WIFI_NAME, network.wifi.gateway );
                //}

            	WifiFifoCmd( WIFI_FIFO_CMD_START );
            }
        	else if( 1 == network.wifi.dhcpEnable ) // ��̬ IP
            {                
                //if( 1 == network.wifi.beDefaultGateway ) // ɾ��������Ĭ�ϵ�����,ʹ��Ĭ������
                //{
                //	NetRouteDelDefaultGateway();
                //}
            	WifiFifoCmd( WIFI_FIFO_CMD_START_DHCP );
            }
        }
    }
	return ret;
}



