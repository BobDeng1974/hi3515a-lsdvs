/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ����3G��ATҵ��
**  date           :  2014.9.25
**
**  version       :  1.0
**  author        :  sven
********************************************************************************/
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "const.h"
#include "serial.h"
#include "thread.h"
#include "debug.h"
#include "linuxFile.h"
#include "malloc.h"
#include "atCom.h"
#include "atMsg.h"
#include "threegSerial.h"
#include "threegAt.h"
#include "atEcho.h"

#define THREEG_AT_BUFSIZE	(ATCMD_SIZE + 4)
static int g_threegAtFlag = FI_FALSE;

static int ThreegAtUnknow( THREEG_AT_COMMUNICATE *pThreegAt, char *pLine )
{
	AT_CMD_ST *pCmd = &g_atCmd;

	if( PRE_RECV_FLAG_NO != pCmd->preRecvFlag )
    {
    	if( PRE_RECV_FLAG_SMS == pCmd->preRecvFlag )
        {             
        	strcat( pCmd->rsp, ATCMD_CR_LF ); 
        }
    	strcat( pCmd->rsp, pLine );        
    }
	else
    {
    	SVPrint( "ThreegAtUnknow failed:recv unknow msg(%s)!\r\n", pLine );
    }    
    
	pThreegAt->anaDataSize = 0;
	return 0;
}

static int GetSmsPhoneNum( char *pLine, char *pPhoneNum )
{
	int len, ret = -1;
	const char phoneNumMarkStart[] = "\",\""; //�� +CMGR: "REC UNREAD","15818757328",,"11/11/16,21:53:15+32" ���ҵ绰����
	const char phoneNumMarkStop[] = "\",";
	char *ptrPhoneNumStart, *ptrPhoneNumStop;
    
	ptrPhoneNumStart = strstr( pLine, phoneNumMarkStart );
	if( NULL != ptrPhoneNumStart )
    {
    	ptrPhoneNumStart += strlen( phoneNumMarkStart );
    	ptrPhoneNumStop = strstr( ptrPhoneNumStart, phoneNumMarkStop );
    	if( NULL != ptrPhoneNumStop )
        {
        	len = ptrPhoneNumStop - ptrPhoneNumStart;
        	memcpy( pPhoneNum, ptrPhoneNumStart, len );
        	pPhoneNum[len] = '\0';

        	ret = 0;
        }
    }

	return ret;
}
static int ParseSmsContent( char *pSmsContent )
{
	int ret = -1;
	char phoneNum[16];    // �绰����
	char smsBare[256] = { 0 };    // ����������Ϣ���� 
	char *ptr;
	ptr = Strsep( &pSmsContent, ATCMD_CR_LF );
	if( NULL != ptr )
    {
    	ret = GetSmsPhoneNum( ptr, phoneNum );
    	if( ret == 0 )
        {
        	ptr = Strsep( &pSmsContent, ATCMD_CR_LF );
        	strcpy( smsBare, ptr );
        }
    }
    
	FiPrint2( "%s:%s, %s!\r\n", __FUNCTION__, phoneNum, smsBare );

	return ret;
}

static int ThreegAtAck( THREEG_AT_COMMUNICATE *pThreegAt, char *pLine )
{
	AT_CMD_ST *pCmd = &g_atCmd;

	if( PRE_RECV_FLAG_NO != pCmd->preRecvFlag )
    {
    	if( PRE_RECV_FLAG_SMS == pCmd->preRecvFlag )
        {             
        	strcat( pCmd->rsp, ATCMD_CR_LF ); 
        }
    	strcat( pCmd->rsp, pLine );
    }
	else
    {
    	strcpy( pCmd->rsp, pLine );
    }

	if( PRE_RECV_FLAG_SMS == pCmd->preRecvFlag )
    {
    	ParseSmsContent( pCmd->rsp );
    	FiAtDelSms( 0, FI_TRUE );
    }
	else
    {        
    	SemPost( &pCmd->sem );        
    }    

	if( PRE_RECV_FLAG_NO != pCmd->preRecvFlag )
    {
    	pCmd->preRecvFlag = PRE_RECV_FLAG_NO;
    }
    
	pThreegAt->anaDataSize = 0;
	return 0;
}

/*
*	func	: ����ĳЩ����1�еĻظ�,������������ս����ؼ���(�󲿷�Ϊ \r\n"OK"\r\n) ǰ����
*/
static int ThreegAtAckPreRecv( THREEG_AT_COMMUNICATE *pThreegAt, char *pLine )
{
	AT_CMD_ST *pCmd = &g_atCmd;

	strcpy( pCmd->rsp, pLine );    
	pCmd->preRecvFlag = PRE_RECV_FLAG_SYNC;
    
	pThreegAt->anaDataSize = 0;
	return 0;
}

static int ThreegAtRing( THREEG_AT_COMMUNICATE *pThreegAt, char *pLine )
{
	pThreegAt->anaDataSize = 0;
	return 0;
}

static int ThreegAtRingNum( THREEG_AT_COMMUNICATE *pThreegAt, char *pLine )
{
	pThreegAt->anaDataSize = 0;
	return 0;
}

/*
*	fn : �� +CMTI: "SM",10 ������Ϣ�еõ��½��յ�sms��index
*	������sms��index
*/
static int GetSmsIndex( char *pLine )
{
	int smsIndex = 0;
	char *ptr;

	ptr = strstr( pLine, "," );
	if( NULL != ptr ) 
    {
    	ptr++;
    	smsIndex = atoi( ptr );
    }
    
	return smsIndex;
}
static int ThreegAtRecvNewSms( THREEG_AT_COMMUNICATE *pThreegAt, char *pLine )
{
	int smsIndex;
    //AT_CMD_ST *pCmd = &g_atCmd;
	SVPrint( "note:dvs recv new sms, pLine = %s!\r\n", pLine );
	smsIndex = GetSmsIndex( pLine );    
	SVPrint( "note:dvs recv new sms, index = %d!\r\n", smsIndex );
	FiAtSendReadSmsCmd( smsIndex );

	pThreegAt->anaDataSize = 0;
	return 0;
}

static int ThreegAtRecvSmsContent( THREEG_AT_COMMUNICATE *pThreegAt, char *pLine )
{
    //int smsIndex;
	AT_CMD_ST *pCmd = &g_atCmd;
	strcpy( pCmd->rsp, pLine ); 
	SVPrint( "recv sms, content:%s!\r\n", pCmd->rsp );
	pCmd->preRecvFlag = PRE_RECV_FLAG_SMS; // �������ն�Ϣ����������
    
	pThreegAt->anaDataSize = 0;
	return 0;
}

/*
*  func	        : �����յ�������������Ƿ��кϸ���У����� ATCMD_CR_LF ֮�����Ϊ�ϸ���
*  checkedSize	: out,�Ѿ����������ݴ�С��
*  pLine	    : ���ҵ�����Ч�п����� pLine  
*  ����         : 0,�ҵ��ϸ���; -1,�Ҳ����ϸ���.
*/
static int ThreegAtCheck( THREEG_AT_COMMUNICATE *pThreegAt, char *pLine, int *pCheckedSize )
{        
	int ret = -1;
	int checkedSize = 0, cpySize, secondKeySize, offset;
	int rcLfLen = strlen(ATCMD_CR_LF);
	char *pRcLfFirst, *pRcLfSecond;    
	AT_CMD_ST *pCmd = &g_atCmd;

	if( NULL == pThreegAt || NULL == pLine || NULL == pCheckedSize )
    {
    	SVPrint( "NULL == pThreegAt || NULL == pLine || NULL == pCheckedSize\r\n" );
    	return -1;
    }
    
	if( PRE_RECV_FLAG_SMS == pCmd->preRecvFlag )
    {
    	pRcLfFirst         = pThreegAt->sockBuf;
    }
	else
    {
    	pRcLfFirst      = strstr( pThreegAt->sockBuf, ATCMD_CR_LF );
    }    
	if( NULL == pRcLfFirst )
    {        
    	checkedSize += pThreegAt->sockDataSize;
    }
	else
    {
    	if( PRE_RECV_FLAG_SMS != pCmd->preRecvFlag )
        {
        	do	// ȥ���������� "\r\n"
            {
            	pRcLfFirst += rcLfLen;
            }while( 0 == memcmp( pRcLfFirst, ATCMD_CR_LF, rcLfLen ) );
        }
        
    	offset = pRcLfFirst - pThreegAt->sockBuf;
    	checkedSize += (offset > 0 ? offset : 0);
    	ret = 0;
    }

	if( ret != -1)
    {
    	ret = -1;
    	if( NULL != (pRcLfSecond = strstr( pRcLfFirst, ATCMD_INPUT )) )
        {
        	pRcLfSecond += strlen( ATCMD_INPUT );
        	secondKeySize = 0;
        }
    	else
        {
        	pRcLfSecond = strstr( pRcLfFirst, ATCMD_CR_LF );
        	secondKeySize = strlen( ATCMD_CR_LF );
        }
    	if( NULL != pRcLfSecond )    // �ҵ��ڶ���"\r\n"
        {
        	cpySize = pRcLfSecond - pRcLfFirst;
        	cpySize = (cpySize > (ATCMD_SIZE - 1)) ? (ATCMD_SIZE - 1) : cpySize;
        	memcpy( pLine, pRcLfFirst, cpySize );
        	pLine[cpySize] = '\0';
        	checkedSize += ( cpySize + secondKeySize); 
        	ret = 0;
        }
    	else if( pThreegAt->sockDataSize >= ATCMD_SIZE ) // û���ҵ��ڶ���"\r\n",ͬʱ���ջ����������ˡ�
        {
        	checkedSize = pThreegAt->sockDataSize;
        }
    }
    
    *pCheckedSize = checkedSize;
    
	return ret;
} 

static THREEG_AT_MSG_FUNC g_threegAtMsgFunc[] = 
{
    { AT_CHARS_OK,                	ThreegAtAck	            },    // ͨ�ûظ�
    { AT_KEY_SHORT_MSG_ENTRY,    	ThreegAtAck	            },    // ��������
    { AT_KEY_RING_NUMBER_DISPLAY, 	ThreegAtRingNum         },    // ���������ʾ
    { AT_KEY_RING,                	ThreegAtRing             },    // �е绰�����
    { AT_KEY_SIGNAL_VALUE,        	ThreegAtAckPreRecv	    },    // �鿴�źŸ���
    { AT_KEY_RECV_NEW_SMS,        	ThreegAtRecvNewSms	    },    // �յ��¶���֪ͨ
    { AT_KEY_RECV_SMS_CONTENT,    	ThreegAtRecvSmsContent     },    // ��ʼ���ն�������	
    { AT_KEY_SIGNAL_VALUE_HW,    	ThreegAtAckPreRecv	    },    // �鿴�źŸ���
};
/*
* func	: ����һ����������������
* pLine	: ��3Gģ���л�ȡ����һ������������
*/
static THREEG_AT_FUNC ThreegAtGetFunc( char *pLine)
{
	THREEG_AT_FUNC func = ThreegAtUnknow;
	int loopTimes, i;
	loopTimes = sizeof( g_threegAtMsgFunc ) / sizeof( THREEG_AT_MSG_FUNC ) ;
    
	for( i = 0; i < loopTimes; ++i )
    {
    	if( NULL != strstr( pLine, g_threegAtMsgFunc[i].msgKey ) )
        {
        	func = g_threegAtMsgFunc[i].func;
        	break;
        }
    }

	return func;
}
/*
* func	: ����һ����������������
* pLine	: ��3Gģ���л�ȡ����һ������������
* ����	: ���ݸ������Ҫ�������ĺ���
*/
static THREEG_AT_FUNC ThreegAtParseCmdLine( char *pLine )
{
	THREEG_AT_FUNC func;
	if( NULL == pLine )
    {
    	SVPrint( "NULL == pLine\r\n" );
    	return NULL;
    }

	func = ThreegAtGetFunc( pLine );
    
	return func;
}

/*
*  func	: ������յ������ݡ�
*  phandledSize	: out, ����������ݵĴ�С 
*  ����	: 0,�ɹ�������һ������; -1,û�гɹ���������
*/
static int ThreegAtHandleRecvMsg( THREEG_AT_COMMUNICATE *pThreegAt, int *phandledSize )
{
	int 	ret;
	char   	line[ATCMD_SIZE];
	int		checkedSize = 0;
	THREEG_AT_FUNC	doFunc;
    
	if( NULL == pThreegAt )
    {
    	SVPrint( "NULL == pThreegAt!\r\n" );
    	return -1;
    }

	ret = ThreegAtCheck( pThreegAt, line, &checkedSize);
	if( ret == 0 ) // �ҵ�һ����ɵ���Ϣ
    {
    	doFunc = ThreegAtParseCmdLine( line );
    	if( NULL != doFunc ) ret = doFunc( pThreegAt, line );
    }
    
    *phandledSize = checkedSize;
    
	return ret;
}

void *ThreegAtRecvThread( void *arg )
{
	char *pRecvBuf;
	THREEG_AT_COMMUNICATE threegAt;        
	int ret, recvSize, handedSize;

	threegAt.sockBuf     = (char *)Malloc( THREEG_AT_BUFSIZE );
	threegAt.anaBuf     = (char *)Malloc( THREEG_AT_BUFSIZE );
	if( NULL == threegAt.sockBuf || NULL == threegAt.anaBuf )
    {        
    	Free( threegAt.sockBuf );
    	Free( threegAt.anaBuf );
    	return NULL;
    }
	threegAt.sockBuf[0] = '\0';
	threegAt.sockDataSize = 0;
    
	SVPrint( "start ThreegAtRecvThread(%d)!\r\n", ThreadSelf() );
	while( FI_TRUE == g_threegAtFlag )
    {
    	pRecvBuf = threegAt.sockBuf + threegAt.sockDataSize; // -1 ����Ϊ���е��ַ�����Ҫ�ŵ�'\0'ǰ
    	recvSize = THREEG_AT_BUFSIZE - threegAt.sockDataSize - 1;
    	ret = FiThreegSerialRecvData( SERIAL_TYPE_THREEG_AT, pRecvBuf,  recvSize );
    	if( ret > 0 )
        {    
        	threegAt.sockDataSize += ret;
        	threegAt.sockBuf[threegAt.sockDataSize] = '\0';                    
        	do
            {
            	ret = ThreegAtHandleRecvMsg( &threegAt, &handedSize );
            	if( ret == 0 )
                {                        
                	threegAt.sockDataSize -= handedSize;
                	memmove( threegAt.sockBuf, threegAt.sockBuf + handedSize, threegAt.sockDataSize );
                	threegAt.sockBuf[threegAt.sockDataSize] = '\0';                    
                }                
            	usleep(5);
            }while( ret == 0 );
        }    
    	usleep(100000);
    } // end while( FI_TRUE == g_threegAtFlag )

	Free( threegAt.sockBuf );
	Free( threegAt.anaBuf );
	SVPrint( "stop ThreegAtRecvThread!\r\n" );

	return NULL;
}

static pthread_t	g_threegAtId;
int ThreegAtStartService()
{
	int ret;
    
	ret = AtCmdInitStruct( &g_atCmd );
	if( ret != 0 ) 
    {        
    	SVPrint( "error:AtCmdInitStruct failed,please check dev!\r\n" );
    	return ret;
    }
    
	g_threegAtFlag = FI_TRUE;
	ret = ThreadCreateCommonPriority( &g_threegAtId, ThreegAtRecvThread, NULL );
	if ( ret != 0 )
    {
    	g_threegAtFlag = FI_FALSE;
    	SVPrint( "ThreadCreateCommonPriority() error:%s\r\n", STRERROR_ERRNO );
    }

	return ret;
}

int ThreegAtStopService()
{    
	g_threegAtFlag = FI_FALSE;
	if( 0 != ThreadJoin( g_threegAtId, NULL ) )
    {
    	SVPrint( "ThreadJoin error:%s!\r\n", STRERROR_ERRNO );
    	return FI_FAILED;
    }
	AtCmdDeinitStruct( &g_atCmd );
	return FI_SUCCESSFUL;
}

static void *ThreegAtInitThread( void *arg )
{
	int i, ret;

	for( i = 0; i < 10; i++ )
    {
    	if( 0 == FiAtSmsInit() )
        {
        	break;
        }        
    	usleep(10000);        
    	SVPrint( "FiAtSmsInit usleep(10000);\r\n" );
    }

	for( i = 0; i < 10; i++ )
    {
    	if( 0 == FiAtSetSmsFormat( AT_MSG_FORMAT_TEXT ) )
        {
        	break;
        }
    	usleep(10000);
    	SVPrint( "FiAtSetSmsFormat usleep(10000)!\r\n" );
    }        
	ret = FiAtEchoCtl( AT_ECHO_OFF);
	SVPrint( "FiAtEchoCtl( AT_ECHO_OFF ) = ret(%d)!\r\n", ret );
    
	return NULL;
}

/*
*	fn : ͨ��ATָ���ʼ��3Gģ��Ĳ���,������ŵ�CNMI
*         ������Щ������Ҫ���߳� ThreegAtStartService() ����������ʱ���������ȷ�ķ���ֵ,����
         ����һ���߳�����ʼ��
*/
int ThreegAtInit()
{
	int ret;    
	pthread_t threegAtInitId;
    
	ret = ThreadCreateCommonPriority( &threegAtInitId, ThreegAtInitThread, NULL );
	if ( ret != 0 )
    {
    	SVPrint( "ThreadCreateCommonPriority() error:%s\r\n", STRERROR_ERRNO );
    }

	return ret;
}



