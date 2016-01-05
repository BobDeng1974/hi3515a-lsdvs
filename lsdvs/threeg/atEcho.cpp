/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ����3Gģ��Ļ���
**  date           :  2014.9.25
**
**  version       :  1.0
**  author        :  sven
********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "atCom.h"
#include "atEcho.h"


/**************************************************
* function       : ����3Gģ���Ƿ����
***************************************************/

int FiAtEchoCtl( AT_ECHO_EN flag )
{
	int ret = -1;    
	AT_CMD_ST *pCmd;    
    
	pCmd = &g_atCmd;    
	pthread_mutex_lock( &pCmd->lock );

	sprintf(pCmd->req, "%s%s%d\r", ATCMD_PRE, "E", flag );    
	pCmd->reqSize = strlen( pCmd->req );
    
	ret = AtCmdSend( pCmd );

	if( ret >= 0 ) ret = AtCmdSendSync( pCmd, (char *)AT_CHARS_OK );
    
	pthread_mutex_unlock( &(pCmd->lock) );
    
	return ret;
}


