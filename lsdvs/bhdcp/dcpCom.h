#ifndef __DCPCOM_H__
#define __DCPCOM_H__

#include "dcpIns.h"
#include "dcpTypes.h"

#define CLIENT_MSG_MARK		0x5AA58BB8
#define MAX_MSG_DATA_LEN    (100*1024)
#define MAX_NET_PACK_SIZE 	1400

#define SUPER_USER	    "shenzhenrha"
#define SUPER_PASSWD    "1asdrtyjkl1"


#define LISTEN_CLIENT_MSG_PORT		20000
#define LISTEN_CLIENT_STREAM_PORT	20001

typedef enum _ClientSocketStateEn_
{
	CLIENT_SOCKET_STATE_NONE	= 0,     // ��
	CLIENT_SOCKET_STATE_LISTEN,            // ����
	CLIENT_SOCKET_STATE_ACCEPT,            // �Ѿ���accept��, ��û��ͨ�����û����������½��
	CLIENT_COCKET_STATE_LOAD,            // �û��Ѿ�ͨ�����û����������½��
}CLIENT_SOCKET_STATE_EN;

#define MAX_CLIENT_SIZE	        	44//16(16->44,��λ���кܶ಻�������ӣ���Ҫ��������������)  //���֧�ֵĿͻ�����
#define MAX_CLIENT_SOCKET_NUM	    (MAX_CLIENT_SIZE + 1)    //����һ��socket�������listen��socket

typedef enum _DcpComErr_
{
	DCP_COM_ERR_NEED_CLOSE_SOCKET = -10000,    
	DCP_COM_ERR_NEED_MOVE_SOCKET,
} DCP_COM_ERR_EN;

#define MAX_SEND_DATA_SIZE	(1*1024)
typedef enum _SeqTypeEn_
{
	SEQ_TYPE_ONE_PACK = 0,     // ��ʼ�ͽ�������ͬһ����,Ҳ����ֻ��һ����
	SEQ_TYPE_START,            // ��ʼ��
	SEQ_TYPE_STOP,            // ������
	SEQ_TYPE_MID,            // �м��
} SEQ_TYPE_EN;

typedef struct _SocketErr_
{
	int num;                                // �ܹ��ж��ٸ�socket ������
	int socket[MAX_CLIENT_SOCKET_NUM];         // ������socket ��ֵ
	int moveFlag[MAX_CLIENT_SOCKET_NUM];    // =1,��ʾ��socket ��û�з�������,���Ǳ������߳̽���,����ҪClose; ������ҪClose, ����dcpss.cpp ���õ�
} SOCKET_ERR_T;

#endif 

