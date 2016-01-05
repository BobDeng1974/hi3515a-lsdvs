#ifndef __DTUAPP_H__
#define __DTUAPP_H__

typedef struct _DtuWorkParam_
{
	uchar 	enable;                        // 0,��ʹ��; 1,ʹ��
	uchar 	transProtocol;                // ����Э��, 0:tcp; 1,udp
	ushort	serverPort;                    // �������˿�
	char	severIp[NET_ADDRSIZE];        // ������IP ��ַ
	char	heartbeatContent[76];        // ������������,���32 ���ֽ�,�ɰ������֡����֡�Ӣ�Ĵ�Сд��ĸ��
	ushort	interval;                    // �������ķ��ͼ��1��65535s
} DTU_WORK_PARAM_T;

typedef struct _DtuWorkMaintain_
{
	int	pts;            // ʱ���,��Ե�
	int tcpMode;        // 0,������; 1,������
	int socket;            // tcp ͨ�ŵ�socket, -1 ��ʾû������, > 0 ��ʾ������
	char hyalineBuf[1024];  // ͸����������
	uint hyalineLen;        // ͸�����䳤��
} DTU_WORK_MAINTAIN_T;

void StartDtuAppThread();
void StopDtuAppThread();
void DtuSendParamChangeMessage();

#endif //__DTUAPP_H__

