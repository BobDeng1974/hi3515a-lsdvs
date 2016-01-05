/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : AT��绰�ӿ�
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
#include "atCom.h"

/*
* pPhone:     	�绰����
* networkType:	��ͬ��3Gģ��,������ܲ�һ��,��ʱ��0��
* ����:     	����0,ʧ��; ����ֵ,�ɹ�
*/
int FiAtSendCall( char *pPhone )
{
	int ret = -1;    
	AT_CMD_ST *pCmd = &g_atCmd;

	if( NULL == pPhone )
    {
    	SVPrint( "error:NULL == pPhone!\r\n" );
    	return -1;
    }

	pthread_mutex_lock( &pCmd->lock );
    
	sprintf(pCmd->req, "%s%s%sI;%s", ATCMD_PRE, "D", pPhone, ATCMD_CR_LF);    
	pCmd->reqSize = strlen( pCmd->req );
    
	ret = AtCmdSend( pCmd );

	if( ret >= 0 ) ret = AtCmdSendSync( pCmd, (char *)AT_CHARS_OK );
    
	pthread_mutex_unlock(&(pCmd->lock));
    
	return ret;
}

