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
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "debug.h"
#include "const.h"
#include "linuxFile.h"

#include "threegPpp.h"

static THREEG_PPP_ST g_threegPpp;

int ThreegPppInit()
{
	int ret = FI_SUCCESSFUL;
    
	memset( &g_threegPpp, 0, sizeof(g_threegPpp) );    
    
	pthread_mutexattr_t mutexattr;
	pthread_mutexattr_init( &mutexattr );
	pthread_mutexattr_settype( &mutexattr, PTHREAD_MUTEX_RECURSIVE_NP );
	pthread_mutex_init( &g_threegPpp.lock, &mutexattr );
	pthread_mutexattr_destroy( &mutexattr );

	if( -1 == (g_threegPpp.fifoFd = open(THREEG_PPPSH_FIFO, O_RDWR)) )
    {
    	SVPrint( "Error:open(%s) error:%s!\r\n", THREEG_PPPSH_FIFO, STRERROR_ERRNO );
    	ret = FI_FAILED;
    }    
    
	return ret;
}

int ThreegPppDeInit()
{
	pthread_mutex_destroy( &g_threegPpp.lock );        
	close( g_threegPpp.fifoFd );
	return 0;
}

/*******************************************************************
*  function: 	��ppp.shͬ��, ���Ʋ��ŵĿ���
*  cmd     :    	�μ� THREEG_PPP_FIFO_CMD
*  return  :	0,�ɹ�; ����,ʧ��
*********************************************************************/
int ThreegPppControl( THREEG_PPP_FIFO_CMD cmd )
{
	int ret, fd = -1;
	int writeLen;
	char writeBuf[4] = { 0 };
    
	pthread_mutex_lock( &g_threegPpp.lock );
    
	fd = open( THREEG_PPPSH_FIFO, O_RDWR );
	if( fd != -1 )
    {
    	sprintf( writeBuf, "%d", cmd);    
    	writeLen = strlen(writeBuf);    
    	ret = Writen( fd, writeBuf, writeLen );
    	if( ret != writeLen )
        {
        	SVPrint( "Writen error:%s!\r\n", STRERROR_ERRNO );
        	ret = -1;
        }
    	else
        {
        	ret = 0;
        }
    	close(fd);
    }
	else
    {
    	SVPrint( "open(%s) error:%s!\r\n", THREEG_PPPSH_FIFO, STRERROR_ERRNO );
    	ret = -1;
    }
	pthread_mutex_unlock( &g_threegPpp.lock );
    
	return ret;
}

