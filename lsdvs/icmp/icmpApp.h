#ifndef __ICMPAPP_H__
#define __ICMPAPP_H__

#include "const.h"

typedef struct _IcmpWorkParam_
{
	int 	enable;                    // �Ƿ�ʹ��icmp
	char	ipAddr[NET_ADDRSIZE];    // ��ping ��ip ��ַ
	int		interval;                // ���������ÿ���೤ʱ�䷢��һ�������� 5��100s
	int		timeOut;                // ����ping ����ȴ����յĳ�ʱʱ�� 5��100s
	int		fcount;                    // failed count, ping��ͨ�������ping ���ٴ�Ҳ����ping ��-c ������ 5��100 ��
	int		finterval;                // ��������·ʱ������ICMP���ļ��ʱ�� 10��100s
} ICMP_WORK_PARAM_T;

typedef enum _IcmpCurState_
{
	ICMP_CUR_STATE_UNKNOW = 0,        // ״̬δ֪
	ICMP_CUR_STATE_PING_SUCCESS,    // ping �ɹ�
	ICMP_CUR_STATE_PING_FAILED,        // ping ʧ��
	ICMP_CUR_STATE_PING_N_FAILED,    // ������ n ��ping ��ʧ��
} ICMP_CUR_STATE_EN;

typedef struct _IcmpWorkMaintain_
{
	int	pts;        // ʱ���,��Ե�
	int curState;    // �� ICMP_CUR_STATE_EN
	int	fcount;        // failed count ping ʧ�ܵĴ���	
} ICMP_WORK_MAINTAIN_T;

void StartIcmpAppThread();
void StopIcmpAppThread();
void IcmpSendParamChangeMessage();
int IcmpGetNetworkState();

#endif 

