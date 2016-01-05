#ifndef __DCPSIGNAL_H__
#define __DCPSIGNAL_H__

#include "const.h"
#include "dcpErr.h"
#include "dcpCom.h"

typedef struct _SelectClientData_
{
	ushort num;        // ��⵽���ٸ��ͻ���
	ushort index[MAX_CLIENT_SOCKET_NUM]; // �����ݸ����ͻ����±��ֵ
} SELECT_CLIENT_DATA_T;

typedef struct _ClientCommunicate_
{
	int 	socket;                // ͨ��socket
	int		socketState;        // socket״̬,CLIENT_SOCKET_STATE_***
	char     *readBuf;            // ���ջ�����	
	uint 	readBufSize;        // ���ջ������Ĵ�С
	uint 	readBufDataSize;    // ���ջ��������浱ǰ�����ݴ�С
	char     *writeBuf;            // ���ͻ�����
	uint	writeBufSize;        // ���ͻ������Ĵ�С
	uint	writeBufDataSize;    // ��������buffer��������ݴ�С
	uint	timestamp;            // ʱ���,�����ж��û�����ʱ��
	uint	threadId;            // ��ÿ����¼�Ŀͻ�����һ���߳�,������������, ��dcpss.cpp �����������������Ƶsocket ���Ǹ��߳�������
	ushort	index;                // �ÿͻ��˶�Ӧ���������������е�����,����ڱ����̼߳�ͨ�Ż��õ�
} CLIENT_COMMUNICATE_T;

typedef struct _ClientConnect_
{
	ushort num;                                            // Ŀǰ�ж��ٸ�����
	CLIENT_COMMUNICATE_T client[MAX_CLIENT_SOCKET_NUM];    // ���֧��16���û�ͬʱ����
} CLIENT_CONNECT_T;


void StartDcpSignalThread();
void StopDcpSignalThread();
ushort DcpSignalConnectedUserNum(); 

#endif 

