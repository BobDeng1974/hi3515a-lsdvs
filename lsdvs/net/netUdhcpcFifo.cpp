/********************************************************************************
**	Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**	author        :  sven
**	version       :  v1.0
**	date           :  2013.10.10
**	description  : �����udhcpc ���̽�����fifo
********************************************************************************/

#include "linuxFile.h"
#include "debug.h"
#include "mutex.h"
#include "netUdhcpcFifo.h"

static ClMutexLock g_udhcpcMutex;
/*************************************************************
*  func: 	��ppp.shͬ��, ���Ʋ��ŵĿ���
*  cmd:    	�μ� UDHCPC_FIFO_CMD
*  ����:	0,�ɹ�; ����,ʧ��
**************************************************************/
int UdhcpcForkCtrl( UDHCPC_FIFO_CMD cmd )
{
	int ret, fd = -1;
	int writeLen;
	char writeBuf[4] = { 0 };    

	g_udhcpcMutex.Lock();
    
	fd = Open( UDHCPC_FIFO, O_RDWR );
	if( fd != -1 )
    {
    	sprintf( writeBuf, "%d", cmd);    
    	writeLen = Strlen(writeBuf);    
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
    	Close(fd);
    }
	else
    {
    	SVPrint( "open(%s) error:%s!\r\n", UDHCPC_FIFO, STRERROR_ERRNO );
    	ret = -1;
    }
    
	g_udhcpcMutex.Unlock();
    
	return ret;
}

