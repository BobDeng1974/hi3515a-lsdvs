/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ����
**  date           :  2011.11.8
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/

#include <pthread.h>
#include <stdio.h>
#include "debug.h"
#include "wifiConf.h"

pthread_mutex_t g_wifiConfLock = PTHREAD_MUTEX_INITIALIZER;

/*
*	fn	: ��wifi���ӵĵ������Ϣд�뵽 WIFI_CONF_FILE �����ļ�,�ͽű�����
*	pEssid : essid
*	pPasswd : ����
*/
int WifiSetConncetInfoToFile( char *pEssid, char *pPasswd )
{
	FILE *fp;
	int ret = -1;
    
	if( NULL == pEssid || NULL == pPasswd )
    {
    	SVPrint( "NULL == pEssid || NULL == pPasswd!\r\n" );
    	return -1;
    }
	FiPrint2( "WifiSetConncetInfoToFile!\r\n" );
    
	pthread_mutex_lock( &g_wifiConfLock );
    
	fp = fopen( WIFI_CONF_CONNECT_FILE, "w" );
	if( NULL != fp )
    {
    	fprintf( fp, "%s %s\n", WIFI_CONF_ESSID, pEssid );
    	fprintf( fp, "%s %s\n", WIFI_CONF_PASSWD, pPasswd );
        
    	fclose(fp);
    	ret = 0;
    }
    
	pthread_mutex_unlock( &g_wifiConfLock );

	return ret;    
}

/*
*	fn: ��wifi����������д�뵽�ļ���
*
*/
int WifiSetNetworkInfoToFile( char *pIp, char *pNetmask, char *pGateway )
{
	FILE *fp;
	int ret = -1;

	if( NULL == pIp && NULL == pNetmask && NULL == pGateway )
    {
    	return -1;
    }
    
	pthread_mutex_lock( &g_wifiConfLock );
    
	fp = fopen( WIFI_CONF_NETWORK_FILE, "w" );
	if( NULL != fp )
    {
    	if( NULL != pIp ) fprintf( fp, "%s %s\n", WIFI_CONF_IP, pIp );
    	if( NULL != pNetmask ) fprintf( fp, "%s %s\n", WIFI_CONF_NETMASK, pNetmask );        
    	if( NULL != pGateway ) fprintf( fp, "%s %s\n", WIFI_CONF_GATEWAY, pGateway );
        
    	fclose(fp);
    	ret = 0;
    }
    
	pthread_mutex_unlock( &g_wifiConfLock );

	return ret; 
}



