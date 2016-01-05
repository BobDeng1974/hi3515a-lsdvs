#ifndef __DCPSTREAM_H__
#define __DCPSTREAM_H__

#include "const.h"
typedef enum _DcpStreamErr_
{
	DCP_STREAM_ERR_QUIT = 100,            // �Ƴ��߳�
	DCP_STREAM_ERR_CHANNEL_IS_EXIST,    // ͨ���Ѿ�����, ��Ӧ�ͻ��˶�ͬһ��ͨ��������
} DCP_STREAM_ERR_EN;

typedef struct _StreamCh_
{
	int         	ch;        // ͨ����
	int         	socket;    // ������socket
	unsigned int 	fd;        // ȡ����fd
} STREAM_CH_T;

typedef struct _DcpStream_
{
	int         	csnum;                        // ��ǰ���͵�ͨ����
	STREAM_CH_T 	streamCh[MAX_CHANNEL_NUM];  // ͨ������,���
} DCP_STREAM_T;

int DcpCreateStreamThread( uint *threadId );
void DcpDestoryStreamThread( uint threadId );
int DcpStartChannelStream( uint threadId, int channel, int socket );
int DcpStopChannelStream( uint threadId, int channel );

#endif 

