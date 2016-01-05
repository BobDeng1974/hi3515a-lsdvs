/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ���ļ�ʵ����DVS����Э��
**  �ο��ĵ�: <<DVS����Э��.doc>> V1.0
**  date           :  2013.11.11
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "debug.h"
#include "malloc.h"
#include "thread.h"
#include "timer.h"
#include "message.h"
#include "table.h"
#include "const.h"
#include "netSocket.h"
#include "dataService.h"
#include "packData.h"
#include "configProtocol.h"
#include "searchProtocol.h"
#include "transmitProtocol.h"
#include "messageProtocol.h"
#include "reportProtocol.h"


int GetMessageFlagOffset( unsigned char *data, int len )
{
	return GetFlagOffset( data, len, htonl( MSG_DATA_FLAG ) );
}

int CheckMessageDataProcess( unsigned char *dataBuf, const int dataLen,
                            	const int bufSize, int &offset )
{
	int nRet = -1;
	if ( dataBuf != NULL && dataLen > 0 )
    {
    	offset = GetMessageFlagOffset( dataBuf, dataLen );
    	unsigned char *	data	= dataBuf + offset;
    	int	        	len	    = dataLen - offset;
    	int	        	size	= bufSize - offset;
    	int	        	off	    = 0;
        
    	MESSAGE_DATA *pMessageData = (MESSAGE_DATA *)( data );
    	switch ( pMessageData->msgType )
        {
    	case MSG_CFG_DATA_TYPE:
        	nRet = CheckConfigDataProcess( data, len, size, off );
        	break;
        
    	case MSG_AVS_DATA_TYPE:
            // TODO
        	break;
        
    	case MSG_CTL_DATA_TYPE:    
            // TODO
        	break;
        
    	case MSG_UPL_DATA_TYPE:
            // TODO
        	break;

    	case MSG_DEV_SEARCH_TYPE:
        	nRet = CheckDevSearchProcess( data, len, size, off );
        	break;

    	case MSG_DATA_TRANSMIT_TYPE:
        	nRet = CheckDataTransmitProcess( data, len, size, off );
        	break;
    	case MSG_DATA_REPORT_TYPE:
        	nRet = CheckReportDataProcess( data, len, size, off );
        	break;
        }

    	offset += off;
    }
	return nRet;
}

int DealMessageDataProcess( unsigned char *dataBuf, int &dataLen, const int bufSize )
{
	int nRet = -1;
	if ( dataBuf != NULL && dataLen > 0 )
    {
    	MESSAGE_DATA *pMessageData = ( MESSAGE_DATA * )dataBuf;
    	switch ( pMessageData->msgType )
        {
    	case MSG_CFG_DATA_TYPE:
        	nRet = DealConfigDataProcess( dataBuf, dataLen, bufSize );
        	break;
        
    	case MSG_AVS_DATA_TYPE:
            // TODO
        	break;
        
    	case MSG_CTL_DATA_TYPE:
            // TODO
        	break;
        
    	case MSG_UPL_DATA_TYPE:
            // TODO
        	break;
            
    	case MSG_DEV_SEARCH_TYPE:
        	nRet = DealDevSearchProcess( dataBuf, dataLen, bufSize );
        	break;

    	case MSG_DATA_TRANSMIT_TYPE:
        	nRet = DealDataTransmitProcess( dataBuf, dataLen, bufSize );
        	break;

    	case MSG_DATA_REPORT_TYPE:
        	nRet = DealReportDataProcess( dataBuf, dataLen, bufSize );
        	break;
        }
    }    
	return nRet;
}

void DealMessageDataInit( CDataService &dataService )
{
	dataService.Init( UDP_SERVICE, MSG_CFG_DATA_PORT );
	dataService.Init( TCP_SERVICE, MSG_CFG_DATA_PORT );
}

void *DealMessageDataThread( void *args )
{
	int	        	nRet	        = -1;
	unsigned char * dataBuf	        = NULL;
	int	        	bufSize	        = 0;
	int	        	dataLen	        = 0;    
	CDataService	dataService;
	unsigned char *	alarmBuf	    = NULL;
	int         	alarmLen         = 0;
	char           	msgBuf[1024] = { 0 };
	int         	msgLen	        = 1024;

	dataBuf = ( unsigned char * )Malloc( sizeof(unsigned char)*MAX_DATA_BUF_SIZE + sizeof(int) );
	if ( dataBuf == NULL ) return NULL;
	else bufSize = MAX_DATA_BUF_SIZE;

	alarmBuf = ( unsigned char * )Malloc( sizeof(unsigned char)*1024  );
	if ( alarmBuf == NULL )
    {    
    	return NULL;
    }
    
	DealMessageDataInit( dataService );
    
	while ( 1 )
    {    
    	if ( MessageRecv( MSG_ID_DEAL_MESSAGE_DATA_THREAD ) >= 0 )
        {
        	FiPrint( "DealMessageDataThread will quit ...\r\n" );
        	break;
        }
    	nRet = dataService.Select();
    	if ( nRet < 0 )
        {
        	FiPrint( "DealMessageDataThread Select Error !\r\n" );
        	break;
        }
    	if ( nRet > 0 )
        {    
        	if ( dataService.Accept() != -1 ) continue;

            // ��������
        	int recvLen = dataService.Recv();    // ���յ����ݷ�����ջ�����	        
        	if ( recvLen <= 0 ) dataService.Close( dataService.GetSocket() );

            // ѭ���ӻ������ж�ȡ���ݽ��д��� !
            // ����������ݴӻ�������ɾ��, û�д�������������ѭ������. 
            // ���ȶ����ݽ���У��, ͨ������У����ٽ������ݴ���; ������Ϻ���з���.
        	while ( recvLen > 0 )
            {
                // ��ȡ����
            	dataLen = dataService.GetData( dataBuf, bufSize );
            	if ( dataLen == -1 ) break;

                // У������
            	int offset = 0;
            	nRet = CheckMessageDataProcess( dataBuf, dataLen, bufSize, offset );        
            	recvLen -= dataService.DelData( offset );
            	if ( nRet == -1 ) break;
            	else recvLen -= dataService.DelData( nRet );

                // ��������
            	unsigned char *	packBuf = dataBuf + offset;
            	int         	packLen = dataLen - offset;
            	nRet = DealMessageDataProcess( packBuf, packLen, bufSize-offset );
            	if ( nRet == -1 ) break;

            	int sndSocket = dataService.GetSocket();
            	memcpy(packBuf+MAX_DATA_BUF_SIZE, &sndSocket, sizeof(int));

                // ��������
            	nRet = dataService.Send( packBuf, packLen );
            	if ( nRet < 0 )
                {
                	dataService.Close( dataService.GetSocket() );
                	break;
                }
            }
        }


    	nRet = MessageRecv( MSG_ID_ALARM_MORE_THAN_LIMIT, msgBuf, msgLen );
    	if( nRet >= 0 )
        {        
        	alarmLen = nRet;
        	memcpy( alarmBuf, msgBuf, alarmLen );
        	nRet = dataService.SendtoAllTCPClient( alarmBuf, alarmLen );
        }
                
    	dataService.HeartBeat();    // ����
        
    	usleep( 10*1000 );
    }
    
	dataService.CloseAll();
	Free( dataBuf );
	Free( alarmBuf );
	return NULL;
}

int QuitMessageDataThread()
{
	int nRet = MessageSend( MSG_ID_DEAL_MESSAGE_DATA_THREAD );
	FiPrint( "Quit Message Data Thread %s !\r\n", (nRet != -1) ? "OK" : "Failed"  );
	return nRet;    
}

