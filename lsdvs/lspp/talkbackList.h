/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ���ļ��ṩ�˶ԶԽ����ͻ��������в�������صĽӿں���
**  date           :  2013.12.20
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef _TALKBACK_LIST_H
#define _TALKBACK_LIST_H

#include "ttypes.h"
//
// �Խ���Ƶ����
//
void WaitTalkbackSendList();
void SignalTalkbackSendList();
int PopTalkbackSendList( TALKBACK_NODE *tFrame );
int PutTalkbackSendList( TALKBACK_NODE *tFrame );
void ClearTalkbackSendList();

//
// �Խ���Ƶ��ȡ
//
void WaitTalkbackRecvList();
void SignalTalkbackRecvList();
int PopTalkbackRecvList( TALKBACK_NODE *tFrame );
int PutTalkbackRecvList( TALKBACK_NODE *tFrame );
void ClearTalkbackRecvList();

//
// ���ô˺�����ʹ�߳̽�������״̬��ֱ���пͻ������ӳɹ���
//
void WaitTalkbackClient();
void BoardcastTalkbackClient();

#endif  // _TALKBACK_LIST_H

