/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.10.10
**  description  : Ӧ��dtu ʵ�ָ���Ӧ��
*******************************************************************************
*/
#include <unistd.h>
#include <stdlib.h>
#include "debug.h"
#include "thread.h"
#include "message.h"
#include "condition.h"
#include "dtu.h"
#include "paramManage.h"
#include "dtuApp.h"
#include "sysRunTime.h"
#include "linuxFile.h"
#include "netSocket.h"
#include "public.h"

static ClCondition g_dtuWorkCondition;  

static void GetDtuWork( DTU_WORK_PARAM_T *dtuWorkParam )
{
	int ret;
	PARAM_CONFIG_DTU dtuConf;

	dtuWorkParam->enable = 0;
	ret = ParamGetDtu( &dtuConf );
	if( 0 == ret )
    {
    	strcpy( dtuWorkParam->severIp, dtuConf.severIp );        
    	strcpy( dtuWorkParam->heartbeatContent, dtuConf.heartbeatContent );
    	dtuWorkParam->enable         = dtuConf.enable;        
    	dtuWorkParam->interval	    = dtuConf.interval;
    	dtuWorkParam->transProtocol	= dtuConf.transProtocol;
    	dtuWorkParam->serverPort	= dtuConf.serverPort;
    }
}

static void ResetDtuWorkMaintain( DTU_WORK_MAINTAIN_T *dtuWorkMaintain )
{
	dtuWorkMaintain->pts         = -1000;
	dtuWorkMaintain->tcpMode     = 0;         // 0,������; 1,������
	if( dtuWorkMaintain->socket > 0 )
    {
    	Close( dtuWorkMaintain->socket );
    	dtuWorkMaintain->socket = -1;
    }
}

#if 0
/*
* fn: ˢ��ά������
*/
static void ReFreshDtuWorkMaintain( DTU_WORK_MAINTAIN_T *dtuWorkMaintain )
{
	dtuWorkMaintain->pts = -1000;
}
#endif

/*
* fn: ���������ж��Ƿ���Ҫִ��ping
* ����: 0, ��Ҫִ��ping, ������Ҫִ��
*/
static int ParseDtuWorkParamAndMaintain( DTU_WORK_MAINTAIN_T *dtuWorkMaintain,
                                            	DTU_WORK_PARAM_T dtuWorkParam )
{
	int ret         = -1;
	int curPts         = SysRunTimeGet();
	int interval     = curPts - dtuWorkMaintain->pts;    
    
	if( interval >= dtuWorkParam.interval )
    {        
    	dtuWorkMaintain->pts = curPts;
    	ret = 0;
    }    

	return ret;
}

/*
* fn: ����dtu ������,udpЭ�鷽ʽ
*/
static int SendDtuHeartbeatOrHyalineUdp( DTU_WORK_PARAM_T dtuWorkParam, 
                            	DTU_WORK_MAINTAIN_T *dtuWorkMaintain )
{
	int ret;
	uint len;

	len = strlen( dtuWorkParam.heartbeatContent );
	len = len <= sizeof(dtuWorkParam.heartbeatContent)? len : sizeof(dtuWorkParam.heartbeatContent);
	if( dtuWorkMaintain->socket < 0 )
    {
    	ret = SocketUdpClient( &dtuWorkMaintain->socket );
    }
	else
    {
    	ret = 0;
    }
	if( 0 == ret )
    {
    	if( dtuWorkMaintain->hyalineLen > 0 )
        {
        	ret = UdpSendto( dtuWorkMaintain->socket, dtuWorkParam.severIp, dtuWorkParam.serverPort,
                        (unsigned char *)dtuWorkMaintain->hyalineBuf, dtuWorkMaintain->hyalineLen );
        	dtuWorkMaintain->hyalineLen = 0;
        }
    	else
        {
    	ret = UdpSendto( dtuWorkMaintain->socket, dtuWorkParam.severIp, dtuWorkParam.serverPort,
                                            (unsigned char *)dtuWorkParam.heartbeatContent, len );
        }
    	if( 0 != ret )
        {
        	Close( dtuWorkMaintain->socket );
        	dtuWorkMaintain->socket = -1;
        }
    }

	return ret;
}

/*
* fn: ����dtu ������,tcpЭ������ӷ�ʽ
*/
static int SendDtuHeartbeatTcpOrHyalineShort( DTU_WORK_PARAM_T dtuWorkParam, 
                            	DTU_WORK_MAINTAIN_T *dtuWorkMaintain )
{
	int ret;
	uint len;

	len = strlen( dtuWorkParam.heartbeatContent );
	len = len <= sizeof(dtuWorkParam.heartbeatContent)? len : sizeof(dtuWorkParam.heartbeatContent);
	if( dtuWorkMaintain->socket < 0 )
    {
    	ret = SocketTcpConnectTimtout( &dtuWorkMaintain->socket, dtuWorkParam.severIp,
                                                	dtuWorkParam.serverPort, 8000 );
    }
	else
    {
    	ret = 0;
    }
	if( 0 == ret )
    {
    	if( dtuWorkMaintain->hyalineLen > 0 )
        {
        	ret = Writen( dtuWorkMaintain->socket, dtuWorkMaintain->hyalineBuf, dtuWorkMaintain->hyalineLen );
        	ret = (unsigned int)ret == dtuWorkMaintain->hyalineLen ? 0 : -1;
        	dtuWorkMaintain->hyalineLen = 0;
        }
    	else
        {
        	ret = Writen( dtuWorkMaintain->socket, dtuWorkParam.heartbeatContent, len );
        	ret = (unsigned int)ret == len ? 0 : -1;
        }
    	Close( dtuWorkMaintain->socket );
    	dtuWorkMaintain->socket = -1;        
    }

	return ret;
}

/*
* fn: ����dtu ������,tcpЭ�鳤���ӷ�ʽ
*/
static int SendDtuHeartbeatOrHyalineTcpLong( DTU_WORK_PARAM_T dtuWorkParam, 
                            	DTU_WORK_MAINTAIN_T *dtuWorkMaintain )
{
	int ret;
	uint len;

	len = strlen( dtuWorkParam.heartbeatContent );
	len = len <= sizeof(dtuWorkParam.heartbeatContent)? len : sizeof(dtuWorkParam.heartbeatContent);

	if( dtuWorkMaintain->socket < 0 )
    {
    	ret = SocketTcpConnectTimtout( &dtuWorkMaintain->socket, dtuWorkParam.severIp,
                                                	dtuWorkParam.serverPort, 8000 );
    }
	else
    {
    	ret = 0;
    }
	if( 0 == ret )
    {
    	if( dtuWorkMaintain->hyalineLen > 0 )
        {
        	ret = Writen( dtuWorkMaintain->socket, dtuWorkMaintain->hyalineBuf, dtuWorkMaintain->hyalineLen );
        	ret = (unsigned int)ret == dtuWorkMaintain->hyalineLen ? 0 : -1;
        	dtuWorkMaintain->hyalineLen = 0;
        }
    	else
        {
        	ret = Writen( dtuWorkMaintain->socket, dtuWorkParam.heartbeatContent, len );
        	ret = (unsigned int)ret == len ? 0 : -1;
        }
    	if( 0 != ret )
        {
        	Close( dtuWorkMaintain->socket );
        	dtuWorkMaintain->socket = -1;    
        }
    }

	return ret;
}


/*
* fn: ����dtu ������
*/
static int SendDtuHeartbeatOrHyaline( DTU_WORK_PARAM_T dtuWorkParam, 
                            	DTU_WORK_MAINTAIN_T *dtuWorkMaintain )
{
	int ret;
	if( 1 == dtuWorkParam.transProtocol ) // udp
    {
    	ret = SendDtuHeartbeatOrHyalineUdp( dtuWorkParam, dtuWorkMaintain );
    }
	else // tcp
    {
    	if( 1 == dtuWorkMaintain->tcpMode ) // ������
        {
        	ret = SendDtuHeartbeatTcpOrHyalineShort( dtuWorkParam, dtuWorkMaintain );
        }
    	else  // ������
        {
        	ret = SendDtuHeartbeatOrHyalineTcpLong( dtuWorkParam, dtuWorkMaintain );
        }
    }

	return ret;
}

static THREAD_MAINTAIN_T g_dtuAppTm;
static void *DtuAppThread( void *arg )
{
	int ret;
    
	DTU_WORK_PARAM_T dtuWorkParam;
	DTU_WORK_MAINTAIN_T dtuWorkMaintain;
    
	dtuWorkMaintain.socket = -1;
	ResetDtuWorkMaintain( &dtuWorkMaintain );
	GetDtuWork( &dtuWorkParam );
	SVPrint( "%s start!\r\n", __FUNCTION__ );
	while( g_dtuAppTm.runFlag )
    {
    	if( 0 == dtuWorkParam.enable )
        {
        	g_dtuWorkCondition.Wait();
        	GetDtuWork( &dtuWorkParam );
        	ResetDtuWorkMaintain( &dtuWorkMaintain );
        	continue;
        }
    	else
        {
        	if( MessageRecv(MSG_ID_DTU_APP) >= 0 )
            {
            	GetDtuWork( &dtuWorkParam );
            	ResetDtuWorkMaintain( &dtuWorkMaintain );                
            	continue;
            }
        	if( (ret = MessageRecv(MSG_ID_DTU_HYALINE, dtuWorkMaintain.hyalineBuf, sizeof(dtuWorkMaintain.hyalineBuf))) > 0 )
            {
            	dtuWorkMaintain.hyalineLen     = ret;
            	dtuWorkMaintain.pts	        = -1000;
            }
        	ret = ParseDtuWorkParamAndMaintain( &dtuWorkMaintain, dtuWorkParam ); // ����Ƿ����㷢����������
        	if( ret == 0 )
            {
            	ret = SendDtuHeartbeatOrHyaline( dtuWorkParam, &dtuWorkMaintain );
            }

        	usleep( 500000 );
        }
    }
    
	SVPrint( "%s stop!\r\n", __FUNCTION__ );
	return NULL;
}

void StartDtuAppThread()
{
	int ret;
	g_dtuAppTm.runFlag = 1;
	ret = ThreadCreate( &g_dtuAppTm.id, DtuAppThread, NULL );
	if( 0!= ret )
    {        
    	g_dtuAppTm.runFlag = 0;
    	SVPrint( "error:ThreadCreate:%s\r\n", STRERROR_ERRNO );
    }
}

void StopDtuAppThread()
{
	int ret;
	g_dtuAppTm.runFlag = 0;
	g_dtuWorkCondition.Signal();
	ret = ThreadJoin( g_dtuAppTm.id, NULL );
	if( 0 != ret )
    {
    	SVPrint( "error:ThreadJoin:%s\r\n", STRERROR_ERRNO );
    }
}

/*
* fn: ��dtu �������޸ĺ�,ͨ���˺���֪ͨ
*/
void DtuSendParamChangeMessage()
{
	g_dtuWorkCondition.Signal();
	MessageSend( MSG_ID_DTU_APP );
}

