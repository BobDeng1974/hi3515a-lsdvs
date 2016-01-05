/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : �źŸ���
**  date           :  2013.9.25
**  version       :  1.0
**  author        :  sven
********************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "debug.h"
#include "atCom.h"
#include "atEcho.h"
#include "atCsqlvl.h"

#define MIN_SIGNAL_VALUE	0
#define MAX_SIGNAL_VALUE	5

/******************************************************************
*  	func        : ��3Gģ�鷵�ص���Ϣ�л�ȡ�źŸ���
*	pRspStr	: ��3Gģ�鷵�ص���Ϣ
*	pSignalValue	: out,��ȡ�����źŸ���
*	return	: 0-pSignalValue��Ч;��֮-��Ч
********************************************************************/
static int AtGetSignalValue( char *pRspStr, int *pSignalValue )
{
	int ret = -1;
	char *pResult;

	if( NULL != pRspStr && NULL != pSignalValue )
    {
    	pResult = strstr( pRspStr, "," );
    	if( pResult != NULL && pResult != pRspStr )
        {
            *pSignalValue = atoi( pResult - 1 );
            
        	if( *pSignalValue >= MIN_SIGNAL_VALUE && *pSignalValue <= MAX_SIGNAL_VALUE )
            {
            	ret = 0;
            }
        }
    }

	return ret;
}

/********************************************************
*   func	             : ��ȡ��ǰ�źŸ���
*   pSignalValue	: out,�źŸ���
*   return              : 0-pSignalValue ��Ч, ��֮��Ч
*********************************************************/
int FiAtCsqlvlZx( int *pSignalValue )
{
	int ret = -1;    
	AT_CMD_ST *pCmd;    
    
	pCmd = &g_atCmd;    
	pthread_mutex_lock( &pCmd->lock );

	sprintf(pCmd->req, "%s%s\r", ATCMD_PRE, AT_KEY_SIGNAL_VALUE );    
	pCmd->reqSize = strlen( pCmd->req );
    
	ret = AtCmdSend( pCmd );
	FiPrint2( "------1ret(%d)!\r\n", ret );
	if( ret >= 0 ) ret = AtCmdSendSync( pCmd, (char *)AT_KEY_SIGNAL_VALUE );    
    
	FiPrint2( "------1ret(%d)!\r\n", ret );
	if( 0 == ret ) ret = AtGetSignalValue( pCmd->rsp, pSignalValue );
    
	FiPrint2( "------1ret(%d),pCmd->rsp(%s)!\r\n", ret, pCmd->rsp );
	pthread_mutex_unlock( &(pCmd->lock) );
    
	return ret;
}

/* ===== ����Ĵ�������thinkwill��wcdma | ����Ĵ����û�Ϊwcdma===== */

/**************************************************************************************
*  	func     : ��3Gģ�鷵�ص���Ϣ�л�ȡ�źŸ���
*	pRspStr	: ��3Gģ�鷵�ص���Ϣ
*	pSignalValue	: out,��ȡ�����źŸ���
*	����	: 0-pSignalValue��Ч;��֮-��Ч
**************************************************************************************/
static int AtGetSignalValueHw( char *pRspStr, int *pSignalValue )
{
	int ret = -1;
	int rssi = 0, ber = 0;
	char *pResult;
	int sl = 0;

	if( NULL != pRspStr && NULL != pSignalValue )
    {
    	pResult = strstr( pRspStr, AT_KEY_SIGNAL_VALUE_HW );
    	if( pResult != NULL )
        {            
        	sscanf( pResult, "+CSQ: %u,%u", &rssi, &ber);
        	if( (rssi <= 0) || (rssi == 99) )
            {
            	sl = 0;
            }
        	else if( (rssi >= 1) && (rssi < 8) )
            {
            	sl = 1;
            }
        	else if( (rssi >= 8) && (rssi < 16) )
            {
            	sl = 2;
            }
        	else if((rssi >= 16) && (rssi < 24))
            {    
            	sl = 3;
            }
        	else if((rssi >= 24) && (rssi < 31))
            {
            	sl = 4;
            }
        	else if(rssi >= 31)
            {
            	sl = 5;
            }
        	else
            {
            	sl = 0;
            }

        	ret = 0;
        }
        *pSignalValue = sl;
    }    

	return ret;
}

int FiAtCsqlvlHw( int *pSignalValue )
{
	int ret = -1;    
	AT_CMD_ST *pCmd;    
    
	pCmd = &g_atCmd;    
	pthread_mutex_lock( &pCmd->lock );

	sprintf(pCmd->req, "%s%s\r", ATCMD_PRE, AT_KEY_SIGNAL_VALUE_HW );    
	pCmd->reqSize = strlen( pCmd->req );
    
	ret = AtCmdSend( pCmd );
	if( ret >= 0 ) ret = AtCmdSendSync( pCmd, (char *)AT_KEY_SIGNAL_VALUE_HW );    
    
	if( 0 == ret ) ret = AtGetSignalValueHw( pCmd->rsp, pSignalValue );
    
	pthread_mutex_unlock( &(pCmd->lock) );
    
	return ret;
}

int FiAtCsqlvl( int *pSignalValue )
{
	int ret = -1;
    
//#if ( BOARD_TYPE == BOARD_CAR ) // �ſ�ģ��
	ret = FiAtCsqlvlZx(pSignalValue);
//#elif ( BOARD_TYPE == BOARD_NCIM ) // // ��Ϊ�ſ�ģ��
//	ret = FiAtCsqlvlHw(pSignalValue);
//#endif
	return ret;
}



