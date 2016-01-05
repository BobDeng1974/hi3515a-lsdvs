/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : at ָ�
**  date           :  2014.9.25
**  version       :  1.0
**  author        :  sven
********************************************************************************/

#ifndef __ATCMD_H__
#define __ATCMD_H__

#include "sem.h"
#include <sys/times.h>

#define AT_CHARS_OK	    "OK"
#define AT_CALL_PREFIX	"ATD"

#define AT_KEY_SHORT_MSG_ENTRY	        ">"            // ��������ؼ���
#define AT_KEY_RING_NUMBER_DISPLAY	    "+CLIP:"    // ������ʾ�ؼ���
#define AT_KEY_RING	                    "RING"        // �绰����ؼ���	
#define AT_KEY_SIGNAL_VALUE	            "+CSQLVL"    // �źŸ�����ѯ��ظ��ؼ���
#define AT_KEY_RECV_NEW_SMS	            "+CMTI:"    // �յ��¶�������
#define AT_KEY_RECV_SMS_CONTENT	        "+CMGR:"    // �յ���������

// for huawei wcdma
#define AT_KEY_SIGNAL_VALUE_HW	        "+CSQ"    // �źŸ�����ѯ��ظ��ؼ���


#define ATCMD_PRE	"AT"     
#define ATCMD_CR_LF	"\r\n"
#define ATCMD_INPUT	"> "

#define AT_WAIT_SEC		20
#define AT_WAIT_NSEC	0

#define ATCMD_SIZE		1024

typedef enum _AtRecvFlag_
{
	PRE_RECV_FLAG_NO = 0,    // û��Ԥ����
	PRE_RECV_FLAG_SYNC,        // ���յ���Ҫͬ����Ԥ����
	PRE_RECV_FLAG_ASYC,        // ���յ�����Ҫͬ����Ԥ����
	PRE_RECV_FLAG_SMS	    // ���յ����ŵ�Ԥ����
} AT_RECV_FLAG;

typedef struct _AtCmdSt_
{
	pthread_mutex_t		lock;                // ��,��Ҫ�Ƿ�ֹ���ATָ��ͬʱ����
	sem_t	        	sem;                // �߳�ͬ��
	char             	req[ATCMD_SIZE];    // AT�����������
	int	            	reqSize;            // ���յ������ݴ�С
	char             	rsp[ATCMD_SIZE];    // ��3Gģ����յ�����Ϣ
	struct timeval		recvTimeout;        // ͬ����ʱ
	char	        	preRecvFlag;        // �ڽ��ս����ؼ���(�󲿷�Ϊ \r\n"OK"\r\n) ǰ��û�н���������
} AT_CMD_ST;

extern AT_CMD_ST g_atCmd;

int AtCmdInitStruct( AT_CMD_ST *pAtCmd );
int AtCmdDeinitStruct( AT_CMD_ST *pAtCmd );
int AtCmdSend( AT_CMD_ST *pAtCmd );
int AtCmdSendSync( AT_CMD_ST *pAtCmd );
int AtCmdSendSync( AT_CMD_ST *pAtCmd, char *pKey );
int FiAtStrToUnicodeStr( char *pUnicode, char *srcStr );

#endif
 
