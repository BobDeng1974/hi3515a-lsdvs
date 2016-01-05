/*
*******************************************************************************
**  Copyright (c) 2014, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : wifi��һЩ������
**  date           :  2013.10.21
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef __WIFICOM_H__
#define __WIFICOM_H__

typedef enum _WifiEncTypeEn_
{
	WIFI_ENC_NONE = 0,
	WIFI_ENC_WEP,
	WIFI_ENC_WPA,
	WIFI_ENC_WPAPSK
} WIFI_ENC_TYPE_EN;

typedef enum _WifiSignalLevel_
{
	WIFI_SIGNAL_LEVEL_0 = 0,
	WIFI_SIGNAL_LEVEL_1,
	WIFI_SIGNAL_LEVEL_2,
	WIFI_SIGNAL_LEVEL_3,
	WIFI_SIGNAL_LEVEL_4,    
	WIFI_SIGNAL_LEVEL_5,    
} WIFI_SIGNAL_LEVEL;

typedef enum _WifiFifoCmdEn_
{
	WIFI_FIFO_CMD_SCAN = 11,    // ����
	WIFI_FIFO_CMD_START,        // ��ʼwifi
	WIFI_FIFO_CMD_STOP,            // ֹͣwifi
	WIFI_FIFO_CMD_RESTART,        // ����wifi
	WIFI_FIFO_CMD_START_DHCP,    // ��DHCP�ķ�ʽ������wifi
	WIFI_FIFO_CMD_RESTART_DHCP	// ��DHCP�ķ�ʽ������wifi
} WIFI_FIFO_CMD_EN;


typedef struct _WifiSignalLevelMap_
{
	int signalVal;    // ��λ (dBm)
	int level;        // ��λ (��)
} WIFI_SIGNAL_LEVEL_MAP;

int WifiSignalDbmToLevel( int dbm );

#endif // __WIFICOM_H__

