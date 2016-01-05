/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ���Ͷ��Žӿ�
**  date           :  2014.9.25
**
**  version       :  1.0
**  author        :  sven
********************************************************************************/

#ifndef __ATMSG_H__
#define __ATMSG_H__

typedef enum _AtMsgFormat_
{
	AT_MSG_FORMAT_PDU = 0,    // PDU ��ʽ�շ�����
	AT_MSG_FORMAT_TEXT	    // TEST ��ʽ�շ�����
} AT_MSG_FORMAT;


#define ATCMD_MSG_CMGF	    "+CMGF"    // ���ö��ŵ��շ�ģʽ,pdu or text
#define ATCMD_MSG_CNMI	    "+CNMI"    // ���ý��ն��ŵ�����
#define ATCMD_MSG_CMGR	    "+CMGR"    // ��ȡĳ����������
#define ATCMD_MSG_CMGD	    "+CMGD"    // ɾ����������

int FiAtSetSmsFormat( AT_MSG_FORMAT format );
int FiAtSendSms( char *pPhone, char *pMsgConnect );
int FiAtSmsInit();
int FiAtSendReadSmsCmd( int smsIndex );
int FiAtDelSms( int index, int allFlag );

#endif

