/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : �շ����Žӿ�
**  date           :  2014.9.25
**
**  version       :  1.0
**  author        :  sven
********************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#include "debug.h"
#include "const.h"
#include "atCom.h"
#include "atMsg.h"

/*******************************************************************************
*	function :���ö��ŵ�CNMI
********************************************************************************/
static int AtSmsSetCnmi( int mode, int mt, int bm, int ds, int bfr )
{
	int ret = -1;    
	AT_CMD_ST *pCmd; 

	pCmd = &g_atCmd;
    
	pthread_mutex_lock( &pCmd->lock );    
    
	sprintf( pCmd->req, "%s%s=%d,%d,%d,%d,%d\r", ATCMD_PRE, ATCMD_MSG_CNMI,\
                         mode,  mt,  bm,  ds,  bfr );    
    
	pCmd->reqSize = strlen( pCmd->req );
    
	ret = AtCmdSend( pCmd );
	if( ret >= 0 ) ret = AtCmdSendSync( pCmd, (char *)AT_CHARS_OK );
    
	pthread_mutex_unlock( &(pCmd->lock) );
    
	return ret;
}


/***********************************************************************
* function :��ʼ����Ϣ����
************************************************************************/
int FiAtSmsInit()
{
	int ret;
    
	ret = AtSmsSetCnmi( 1, 1, 0, 1, 0 );

	return ret;
}

static AT_MSG_FORMAT g_atMsgFormat = AT_MSG_FORMAT_PDU;
static AT_MSG_FORMAT AtSmsGetFormat()
{
	return g_atMsgFormat;
}

static void AtSmsSetFormat( AT_MSG_FORMAT format )
{
	g_atMsgFormat = format;
}

/*************************************************************************
*	function: ���ö��ŵ�CMGF,PDU or TEXT
***********************************************************************/
int FiAtSetSmsFormat( AT_MSG_FORMAT format )
{
	int ret = -1;        
	AT_CMD_ST *pCmd; 

	if( AtSmsGetFormat() == format )
    {
    	return 0;
    }    

	pCmd = &g_atCmd; 
	pthread_mutex_lock( &pCmd->lock );    
    
	sprintf( pCmd->req, "%s%s=%d\r", ATCMD_PRE, ATCMD_MSG_CMGF, format );    
    
	pCmd->reqSize = strlen( pCmd->req );    
	ret = AtCmdSend( pCmd );

	if( ret >= 0 ) ret = AtCmdSendSync( pCmd, (char *)AT_CHARS_OK );
    
	pthread_mutex_unlock( &(pCmd->lock) );

	SVPrint( "FiAtSetSmsFormat: ret = %d!\r\n", ret );

	if( 0 == ret ) AtSmsSetFormat( format );
    
	return ret;
}


/**********************************************************************************************
* function   : �Ѷ��ź�����˹���ʽ(15818757328),תΪPDU���Ÿ�ʽ(5118787523F8)
***********************************************************************************************/
static int PhoneHuman2Pdu( char *pHuman, char *pPdu )
{
	unsigned int i;
	char tmpChar;

	if( NULL == pHuman || NULL == pPdu )
    {
    	SVPrint( "error:NULL == pHuman || NULL == pPdu!\r\n" );
    	return -1;
    }

	if( *pHuman == '+' )
    {
        strcpy( pPdu, pHuman+1 );
    }
	else
    {
        strcpy( pPdu, pHuman );
    }
        
	if( strlen(pPdu)%2 != 0 )	
    {
        strcat( pPdu, "F" );
    }
        
	for( i = 0; i < strlen(pPdu); i += 2 )
    {
    	tmpChar     = pPdu[i];
    	pPdu[i]     = pPdu[i+1];
    	pPdu[i+1]     = tmpChar;
    }

	return 0;
}

static int AtSendPduSizeSync( AT_CMD_ST *pAtCmd )
{
	int ret = -1;
	if( NULL == pAtCmd )
    {
    	SVPrint( "error:NULL == pAtCmd!\r\n" );
    	return -1;
    }

	if( AtCmdSendSync( pAtCmd ) < 0 ) //timeout
    {
    	ret = -2;
    }
	else
    {
    	if( (strstr( pAtCmd->rsp, "OK" ) != NULL) && (strstr( pAtCmd->rsp, ">" ) == NULL) )
        {
        	if( AtCmdSendSync( pAtCmd ) < 0)
            {
            	ret = -2;                
            }
        }
    	if( strstr(pAtCmd->rsp, ">") != NULL )
        {
        	ret = 0;            
        }
    }

	return ret;
}

/**********************************************************************************
*	function:���Ͷ���
*	pPhone:��õ绰���뷢�Ͷ���
*	pMsgConnect:Ҫ���͵�����
************************************************************************************/
int FiAtSendSms( char *pPhone, char *pMsgConnect )
{
	int ret = 0, len = 0, pduContentSize = 0;
	char unicodeMsg[256] = { 0 };
	char pduContentBuf[512] = { 0 };
	char pduPhone[32] = { 0 };    
	AT_CMD_ST *pCmd;
    
	if( NULL == pPhone || NULL == pMsgConnect )
    {
    	SVPrint( "error:NULL == pPhone || NULL == pMsgConnect!\r\n" );
    	return -1;
    }

	if( 0 != FiAtSetSmsFormat( AT_MSG_FORMAT_PDU ) ) // ���͵�ʱ��ʹ��pduģʽ
    {
    	SVPrint( "FiAtSetSmsFormat( AT_MSG_FORMAT_PDU ) failed!\r\n" );
    	return -1;
    }    

	pCmd = &g_atCmd;
	pthread_mutex_lock( &(pCmd->lock) );    
    
	PhoneHuman2Pdu( pPhone, pduPhone );
    
	len = FiAtStrToUnicodeStr( unicodeMsg, pMsgConnect );
	sprintf( pduContentBuf, "%s%s%s%02x%s", "11000B81", pduPhone, "0008FF", len, unicodeMsg );    

    // PDU���ŷ��͵�һ�׶�, ����PDU���ݵĳ���
	pduContentSize = strlen( pduContentBuf )/2;
	memset( pCmd->req, 0x00, sizeof(pCmd->req) );    
	sprintf( pCmd->req, "AT+CMGS=%d\r", pduContentSize );
	pCmd->reqSize = strlen(pCmd->req);
	AtCmdSend( pCmd );
	ret = AtSendPduSizeSync( pCmd );    

    // PDU���ŷ��͵ڶ��׶�, ����PDU����
	if( ret >= 0 )
    {
    	sprintf( pCmd->req, "%s\x1A", pduContentBuf );
    	pCmd->reqSize = strlen( pCmd->req );
    	AtCmdSend( pCmd );
        
    	if( (ret = AtCmdSendSync( pCmd, (char *)AT_CHARS_OK )) < 0)
        {
        	SVPrint( "Send pdu content failed, please check pdu format!\r\n" );
        }
    }
	pthread_mutex_unlock( &(pCmd->lock) );

	FiAtSetSmsFormat( AT_MSG_FORMAT_TEXT );
    
	return ret;
}

/***********************************************************************************************
*	function	: ��SM���¶���֪ͨ��ʱ����ñ�����֪ͨ3Gģ��Ѷ��Ŷ�����
*	smsIndex : �¶��ŵ�����
* 	����	: 0-�ɹ�; -1-ʧ��
***********************************************************************************************/
int FiAtSendReadSmsCmd( int smsIndex )
{
	int ret = -1;        
	AT_CMD_ST *pCmd;     
    
	pCmd = &g_atCmd; 
	pthread_mutex_lock( &pCmd->lock );    
    
	sprintf( pCmd->req, "%s%s=%d\r", ATCMD_PRE, ATCMD_MSG_CMGR, smsIndex );    
    
	pCmd->reqSize = strlen( pCmd->req );    
	ret = AtCmdSend( pCmd );
	pthread_mutex_unlock( &(pCmd->lock) );

	ret = (ret > 0)? 0 : -1;
	return ret;
}

/*********************************************************************************************
*   function : ɾ������
*   index : ɾ��ָ����ĳ������
*   allFlag: �Ƿ�ɾ�����еĶ���
**********************************************************************************************/
int FiAtDelSms( int index, int allFlag )
{
	int ret = -1;        
	AT_CMD_ST *pCmd;     

	pCmd = &g_atCmd; 
	pthread_mutex_lock( &pCmd->lock );    
	if( FI_TRUE == allFlag )
    {
    	sprintf( pCmd->req, "%s%s=0,4\r", ATCMD_PRE, ATCMD_MSG_CMGD );    
    }
	else
    {        
    	sprintf( pCmd->req, "%s%s=%d\r", ATCMD_PRE, ATCMD_MSG_CMGD, index );    
    }
	pCmd->reqSize = strlen( pCmd->req );    
	ret = AtCmdSend( pCmd );
    
	pthread_mutex_unlock( &(pCmd->lock) );

	ret = (ret > 0)? 0 : -1;
	return ret;
}


