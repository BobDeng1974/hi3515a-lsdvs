/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ���ļ�ΪDVSϵͳ���ļ�����������������ģ��ĳ�ʼ�������á�
**  date           :  2011.11.8
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/

#ifndef __WIFICONF_H__
#define __WIFICONF_H__

#define WIFI_CONF_CONNECT_FILE	    "/tmp/wifi.conf"
#define WIFI_CONF_NETWORK_FILE	    "/tmp/wifi.network"
#define WIFI_CONF_ESSID     "essid"
#define WIFI_CONF_PASSWD     "passwd"

#define WIFI_CONF_IP         "ip"
#define WIFI_CONF_NETMASK     "netmask"
#define WIFI_CONF_GATEWAY     "gateway"

int WifiSetConncetInfoToFile( char *pEssid, char *pPasswd );
int WifiSetNetworkInfoToFile( char *pIp, char *pNetmask, char *pGateway );

#endif // __WIFICONF_H__

