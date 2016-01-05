/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ����3G��ATҵ��
**  date           :  2014.9.25
**
**  version       :  1.0
**  author        :  sven
********************************************************************************/
#ifndef __THREEGAT_H__
#define __THREEGAT_H__

typedef struct _ThreegAtCommunicate_
{
	int         	socket;            //ͨ��socket
	char             *sockBuf;        //socket buffer	
	unsigned int 	sockDataSize;    //���ջ��������浱ǰ�����ݴ�С
	char             *anaBuf;        //��������buffer
	unsigned int	anaDataSize;    //��������buffer��������ݴ�С
}THREEG_AT_COMMUNICATE;

typedef int (*THREEG_AT_FUNC)( THREEG_AT_COMMUNICATE *pThreegAt, char *pLine );

typedef struct _ThreegAtMsgFunc_
{
	char         	msgKey[32];    // ��Ϣ�ؼ���
	THREEG_AT_FUNC	func;        // ��Ӧ����Ϣ����ĺ���	
} THREEG_AT_MSG_FUNC;

int ThreegAtStartService();
int ThreegAtStopService();
int ThreegAtInit();

#endif 

