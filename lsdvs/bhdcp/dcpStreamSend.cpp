/********************************************************************************
**	Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**	author        :  sven
**	version       :  v1.0
**	date           :  2013.04.22
**	description  : ������, ��Ҫ�����ǲ��������
********************************************************************************/

#include "proconH264.h"
#include "dcpStream.h"
#include "dcpTypes.h"
#include "linuxFile.h"
#include "debug.h"
#include "netSocket.h"
#include "dcpCom.h"

static void PacketStreamHead( ushort len, uchar mark, STREAM_PACK_HEAD_T *pSph )
{    
	pSph->len     = len;
	pSph->seq++;
	pSph->mark     = mark;
}

int DssSendStream( int socket, PROCON_NODE_T *pSend )
{
	int ret = 0;
	uchar seqType;
	uint leftSize, thisDataSize, thisSendSize;
	uint dataHadSentSize, dataHadSendCount;
	char *pSendData = (char *)pSend->data;
	STREAM_PACK_HEAD_T sph;

	sph.seq = 0;

	leftSize = pSend->proconHead.len;
	dataHadSendCount     = 0;
	dataHadSentSize     = 0;

	while( leftSize > 0 )
    {        
    	thisDataSize = leftSize;
    	if( thisDataSize > MAX_SEND_DATA_SIZE ) // �������һ��
        {
        	thisDataSize = MAX_SEND_DATA_SIZE;
        	if( 0 == dataHadSendCount )
            {
            	seqType = SEQ_TYPE_START;
            }
        	else
            {
            	seqType = SEQ_TYPE_MID;
            }
        }
    	else // �����һ��
        {
        	if( 0 == dataHadSendCount )
            {
            	seqType = SEQ_TYPE_ONE_PACK;
            }
        	else
            {
            	seqType = SEQ_TYPE_STOP;
            }
        }
        
    	thisSendSize = thisDataSize;
    	PacketStreamHead( thisSendSize, seqType, &sph ); // ���Ͱ�ͷ
    	ret = Sendn( socket, &sph, sizeof(sph) );
    	if( ret != 0 )
        {
        	ERRORPRINT( "ret(%d) = Sendn( socket(%d), &sph, error:%s!\r\n", 
        	ret,socket, STRERROR_ERRNO );
        	ret = -1;
        	break;
        }
        //SVPrint("send:%d LEN:%d...\n",socket,sizeof(sph));

    	ret = Sendn( socket, pSendData + dataHadSentSize, thisSendSize ); // ���Ͱ���
    	if( ret != 0 )
        {
        	ERRORPRINT( "ret(%d) = ret = Sendn( socket, pSendData, error:%s!\r\n", ret, STRERROR_ERRNO );
        	ret = -1;
        	break;
        }
        //SVPrint("send:%d LEN:%d...\n",socket,thisSendSize);
            
    	leftSize         -= thisSendSize;
    	dataHadSentSize += thisSendSize;
    	dataHadSendCount++;        
    } 

	return ret;
}

