/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ��ȡwifi��״̬
**  date           :  2011.11.10
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/

#ifndef __WIFISTATE_H__
#define __WIFISTATE_H__

#define WIFI_STATE_FILE "/tmp/wifi.state"
#define WIFI_STATE_MARK_FLAG "state "
#define WIFI_STATE_MARK_SIGNAL "signal "

int WifiStateGet( unsigned char *pConnectState, unsigned char *pSignalLevel );

#endif // __WIFISTATE_H__


