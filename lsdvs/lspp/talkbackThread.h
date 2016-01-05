/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ���ļ��ṩ�˶ԶԽ������߳�ʹ�õ���ؽṹ�嶨��
**  date           :  2013.12.20
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef _TALKBACK_THREAD_H
#define _TALKBACK_THREAD_H

const unsigned int	MSG_TALKBACK_FLAG	    = 0xABBA5CC5;    // Э���ʶ
const unsigned char MSG_TALKBACK_TYPE         = 0x20;            // Э����Ϣ����

//
// ���ݰ�����
//
enum MsgTalkbackPackType
{
	MSG_TALKBACK_HEART_BEAT	        = 0x0000,        // ����
	MSG_TALKBACK_START_AUDIO	    = 0x0010,        // ��ʼ��Ƶ����
	MSG_TALKBACK_STOP_AUDIO	        = 0x0020,        // ֹͣ��Ƶ����
};

//
// ����������
//
enum MsgAvsSubType
{
	MSG_TALKBACK_REQUEST	    = 0x01,        // ����
	MSG_TALKBACK_RESPONSE	    = 0x02,        // Ӧ��
	MSG_TALKBACK_ERROR	        = 0x03,        // ����
};

#define PACK_ALIGN	__attribute__((packed))

//
// ����ͷ��ʽ
//
typedef struct TalkbackPackHead
{
	unsigned int	msgFlag;        // ��Ϣ��ʶ
	unsigned char	msgType;        // ��Ϣ����
	unsigned short	packSn;            // �����
	unsigned int	packType;        // ������
	unsigned char	subType;        // ������
	unsigned short	len;            // ���ݳ���
    
} PACK_ALIGN TALKBACK_PACK_HEAD;

//
// ���ݰ���ʽ
//
typedef struct TalkbackPack
{
	TALKBACK_PACK_HEAD head;        // ��ͷ����
	unsigned char data[1];            // �������ݲ��ֺ�2�ֽ�У���
    
} PACK_ALIGN TALKBACK_PACK;

#undef PACK_ALIGN

void *DealTalkbackThread( void *args );

#endif  // _TALKBACK_THREAD_H

