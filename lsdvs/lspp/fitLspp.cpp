/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.01.17
**  description  : ϵͳ����������
*******************************************************************************
*/

#include <string.h>
#include <arpa/inet.h>
#include "debug.h"
#include "malloc.h"
#include "network.h"
#include "netMac.h"
#include "hton.h"
#include "fitLspp.h"

unsigned short GetCheckSum( unsigned char *data, int len )
{    
	unsigned short checkSum = 0x00;
	for ( int i = 0; i < len; ++i ) checkSum += data[i];
	return checkSum;
}

bool IsCheckSumOK( unsigned char *data, int len, unsigned short check )
{
	return ( GetCheckSum(data, len) == check );
}

bool IsCheckSumOK( unsigned char *data, int len )
{
	unsigned short check = 0;
	memcpy( &check, data+len-2, sizeof(check) );
	check = ntohs( check );
	return IsCheckSumOK( data, len-2, check );
}

void PassData( char * pData, int nLen )
{
	char * pwd = (char *)"FirsDvs";
	if ( pData != NULL && nLen > 0 )
    {
    	char * pPwd = pwd;
    	while ( nLen-- > 0 )
        {
            *pData++ ^= *pPwd++;
        	if ( *pPwd == '\0' ) pPwd = pwd;
        }
    }
}

static int gUpdateFlag;
int GetUpdateFlag()
{
	FiPrint("GetUpdate Flag = %d\n", gUpdateFlag);
	return gUpdateFlag;
}

int SetUpdateFlag(int flag)
{
	FiPrint("SetUpdate Flag = %d\n", flag);
	gUpdateFlag = flag;

	return 0;
}

void *GetUpgradeMemory( int size )
{
	return Malloc( size );
}

void ReleaseUpgradeMemory( void *addr )
{
	Free( addr );
}

int FiNetGetMacAddr( char *macAddr, int len )
{    
	return NetworkGetMacAddr( (char *)"eth0", macAddr, len );
}

int FiNetGetPppIpAddr( char *ipAddr, int len )
{
	return NetworkGetIpAddr( (char *)"ppp0", ipAddr, len );
}

int GetWeekdaySeconds( int cTime )
{
	return (cTime + 86400*4) % (86400*7);
}

int GetTimeZone()
{
	return 8;
}

void FiNetGenRandMac( char *pMac )
{
	NetGenRandMac( pMac );
}

void RebootSystem()
{
	return;
}

/*
* fn: �Ѵ�ProconH264Read() ��ȡ����Ƶת����rtp ���ͽӿ���Ҫ�Ľڵ�
* proconNode: ��ProconH264Read() ��ȡ����Ƶ
* pVideoNode: ���ͽӿ���Ҫ�õ��Ľڵ�����
*/
void ProconH264ToVideoSendNode( PROCON_NODE_T *proconNode, VIDEO_SEND_NODE *pVideoSendNode )
{
	STREAM_HEAD_T *pFraemHead;         // �� ProconH264Read()��ȡ����ͷ

	if( NULL == proconNode || NULL == pVideoSendNode )
    {
    	FiPrint( "error:NULL == proconNode || NULL == pVideoNode!\r\n" );
    }
	pFraemHead                     = (STREAM_HEAD_T *)proconNode->data;    
	pVideoSendNode->frameData     = (unsigned char *)proconNode->data;;
                        
    //pVideoSendNode->frameLen     = sizeof(*pFraemHead) + Ntohl(pFraemHead->videoHead.videoSize);    
	pVideoSendNode->frameLen     = proconNode->proconHead.len;    
	pVideoSendNode->frameType	= pFraemHead->frameHead.frameType;
	pVideoSendNode->timeStamp	= Ntohl( pFraemHead->frameHead.sec );
}

