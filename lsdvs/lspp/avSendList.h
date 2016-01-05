/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ��ͷ�ļ��ṩ�˶�����Ƶ���ͻ��������в�������غ����Ľӿ�
**  date           :  2013.11.11
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef _AV_SEND_LIST_H
#define _AV_SEND_LIST_H

typedef struct videoSendNode
{
	unsigned int	timeStamp;        // ʱ���
	unsigned char	frameType;        // ֡����
	unsigned int	frameLen;        // ֡����
	unsigned char *	frameData;        // ֡����
} VIDEO_SEND_NODE;

void WaitVideoSendList();
void SignalVideoSendList();
int PopVideoSendList( int channel, VIDEO_SEND_NODE *vFrame );
int PutVideoSendList( int channel, VIDEO_SEND_NODE *vFrame );
void ClearVideoSendList();

#endif  // _AV_SEND_LIST_H

