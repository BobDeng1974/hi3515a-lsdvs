#ifndef __DCPSTREAMMESSAGE_H__
#define __DCPSTREAMMESSAGE_H__

#include "message.h"

typedef enum _DsmCmd_
{
	DSM_CMD_START_STREAM = 1000,     // ��ʼĳ��ͨ������
	DSM_CMD_STOP_STREAM,            // ֹͣĳ��ͨ������
	DSM_CMD_QUIT_STREAM,            // �˳����߳�
} DSM_CMD_EN;

typedef struct _ChannelStartStream_
{
	int channel;
	int socket;
} CHANNEL_START_STREAM_T;
int DsmMessageSend( int nMsgId, char* pMsgBuf, int nMsgLen );
int DsmMessageRecv( int nMsgId, char* pMsgBuf, int nMsgLen );
bool DsmMessageFind( int nMsgId );

#endif 

