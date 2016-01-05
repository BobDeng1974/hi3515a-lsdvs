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
#ifndef __WIFI_H__
#define __WIFI_H__

#include "ttypes.h"

#define WIFI_SCAN_LINE_SIZE		128  // ÿ�����֧��128���ַ�
#define WIFI_SCAN_MAX_LINE		4      // 4�оͿ���ȷ��һ��wifi·�ɵ���Ϣ
#define WIFI_SCAN_INTERVAL		5  // ���ٸ�5���Ӳ���һ��

#define WIFI_SCAN_RESULT_FILENAME     "/tmp/wifiscanused.txt"
#define WIFI_SCAN_FINISH_FLAG         "/tmp/wifiscanfinish.txt"

#define WIFI_MARK_ESSID             "ESSID:"
#define WIFI_MARK_WIFI_ENC_WPA      "802.1x"
#define WIFI_MARK_WIFI_ENC_WPAPSK   "PSK"
#define WIFI_MARK_SIGNAL	        "Signal level:"
#define WIFI_MARK_KEY_ON	        ":on"
 
int WifiScanResult( WIFI_SCAN_RESULT **pWifiScanResult, int *pScanSize );
int WifiInitNetwork();

#endif // __WIFI_H__

