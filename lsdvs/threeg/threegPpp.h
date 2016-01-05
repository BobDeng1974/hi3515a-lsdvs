/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ����3G���ŷ���
**  date           :  2014.9.25
**
**  version       :  1.0
**  author        :  sven
********************************************************************************/
#ifndef __THREEGPPP_H__
#define __THREEGPPP_H__

#include <pthread.h>

#define THREEG_PPPSH_FIFO	"/tmp/ppp.fifo" // �� ppp.sh ͬ����fifo
typedef enum _ThreegPppFifoCmd_
{
	THREEG_PPP_FIFO_CMD_START = 1,
	THREEG_PPP_FIFO_CMD_STOP,
	THREEG_PPP_FIFO_CMD_RESTART
} THREEG_PPP_FIFO_CMD;

typedef struct _ThreegPppSt_
{
	pthread_mutex_t lock;
	int	        	fifoFd;    // �� ppp.sh ͬ����fifo���	
} THREEG_PPP_ST;

int ThreegPppInit();
int ThreegPppDeInit();
int ThreegPppControl( THREEG_PPP_FIFO_CMD cmd );

#endif

