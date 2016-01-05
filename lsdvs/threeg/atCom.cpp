/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ��װat ָ�ʹ�õĹ�������,��ʼ��ATָ�ʹ�õ���Դ
**  date           :  2014.9.25
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "debug.h"
#include "serial.h"
#include "sem.h"
#include "gb2312.h"
#include "atCom.h"

AT_CMD_ST g_atCmd;

/*
*  func:��ʼ��AT���ȫ�ֽṹ��
*/
int AtCmdInitStruct( AT_CMD_ST *pAtCmd )
{
	int ret = -1;
	int serialFd;

	if( NULL == pAtCmd )
    {
    	SVPrint( "error:NULL == pAtCmd!\r\n" );
    	return -1;
    }
    
	pthread_mutexattr_t	mutexattr;
	memset( pAtCmd, 0, sizeof(AT_CMD_ST) );    
	pthread_mutexattr_init( &mutexattr );
	pthread_mutexattr_settype( &mutexattr, PTHREAD_MUTEX_RECURSIVE_NP );
	pthread_mutex_init( &pAtCmd->lock, &mutexattr);
	SemInit( &(pAtCmd->sem), 0, 0 );        
    
	serialFd = FiSerialOpenThreeg();
	if( serialFd != -1 )
    {
    	ret = FiSerialSetParamThreeg( serialFd, SERIAL_BAUDRATE_115200,
                            	SERIAL_DATABITS_8, SERIAL_STOPBITS_1,SERIAL_PARITY_NONE );
    }

	pAtCmd->recvTimeout.tv_sec = 0;
	pAtCmd->recvTimeout.tv_usec = 100*1000;

	pthread_mutexattr_destroy( &mutexattr );
    
	return ret;
}

/*
*  func: ȥ��ʼ��AT���ȫ�ֽṹ��
*/
int AtCmdDeinitStruct( AT_CMD_ST *pAtCmd )
{
	if( NULL == pAtCmd )
    {
    	SVPrint( "error:NULL == pAtCmd!\r\n" );
    	return -1;
    }
    
	pthread_mutex_destroy( &(pAtCmd->lock) );    
	SemDestroy( &pAtCmd->sem );

	FiSerialCloseThreeg();

	return 0;
}

/*
*  func: ����ATָ��
*/
int AtCmdSend( AT_CMD_ST *pAtCmd )
{
	if( NULL == pAtCmd )
    {
    	SVPrint( "error:NULL == pAtCmd!\r\n" );
    	return -1;
    }
    
	return FiSerialWriteThreeg( pAtCmd->req, pAtCmd->reqSize );
}

/*
*  func: ͬ������ָ��
*  ����: == 0: ͬ���ɹ�;����ͬ��ʧ��
*/
int AtCmdSendSync( AT_CMD_ST *pAtCmd )
{
	if( NULL == pAtCmd )
    {
    	SVPrint( "error:NULL == pAtCmd!\r\n" );
    	return -1;
    }

	return SemTimedWait( &pAtCmd->sem, AT_WAIT_SEC, AT_WAIT_NSEC );
}

/*
*  func: ͬ������ָ��, ������ֻ��һ���ؼ��ֵ�ͬ��
*  pKey: ͬ���Ĺؼ���
*  ����: == 0: ͬ���ɹ�;����ͬ��ʧ��
*/
int AtCmdSendSync( AT_CMD_ST *pAtCmd, char *pKey )
{
	int ret;
	if( NULL == pAtCmd || NULL == pKey )
    {
    	SVPrint( "error:NULL == pAtCmd || NULL == pKey!\r\n" );
    	return -1;
    }

	ret = SemTimedWait( &pAtCmd->sem, AT_WAIT_SEC, AT_WAIT_NSEC );
	if( ret == 0 )
    {
    	if( strstr( pAtCmd->rsp, pKey ) == NULL )
        {
        	ret = -1;
        }
    }

	return ret;
}

/*
* func: ��һ���ַ���ת��unicode�봮
* ע��: �ú�����Ҫ���ڶ���, srcStr ���ܳ���512��bytes
*/
int FiAtStrToUnicodeStr( char *pUnicode, char *srcStr )
{
	int i, count;
	char tmpBuf[1024];
	int len = strlen( srcStr );
	unsigned short unicodeWord;    
    
	count = 0;
	memset(tmpBuf,0,sizeof(tmpBuf));
    
	for (i = 0;i < len;)
    {
    	if ( (unsigned char)(*(srcStr + i)) > 0x80 )
        {
        	Gb2312ToUnicode( &unicodeWord, srcStr + i );
        	tmpBuf[count]         = (char)( (unicodeWord >> 8) & 0xff );
        	tmpBuf[count+1]     = (char)( unicodeWord&0xff );
        	i += 2;
        }
    	else
        {
        	tmpBuf[count]     = 0x00;
        	tmpBuf[count+1] = *(srcStr + i);
        	i++;
        }
    	count += 2;
    }
    
	for ( i = 0; i < count; i++)
    {
    	sprintf( pUnicode + strlen(pUnicode), "%02x", tmpBuf[i]);
    }
    
	return count;
}


