/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ����wifi fifo,��Ҫ�Ǻ�wifi.sh�ű�ͨ��
**  date           :  2013.10.21
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/

#ifndef __WIFIFIFO_H__
#define __WIFIFIFO_H__

#include "wifiCom.h"

#define WIFI_FIFO_DEVICE "/tmp/wifi.fifo"

int WifiFifoCmd( WIFI_FIFO_CMD_EN cmd );
int WifiFifoReStart();

#endif // __WIFIFIFO_H__



