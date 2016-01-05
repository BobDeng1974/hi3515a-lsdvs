/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ��ͷ�ļ��ṩ����ý�����ݷ���ģ��Ľӿڡ�
**  date           :  2013.11.11
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef _AV_SEND_THREAD_H
#define _AV_SEND_THREAD_H

const unsigned int	MSG_AVS_DATA_FLAG	    = 0xABBA5CC5;    // Э���ʶ
const unsigned char MSG_AVS_DATA_TYPE         = 0x10;            // Э����Ϣ����

//
// ���ݰ�����
//
enum MsgAvsPackType
{
	MSG_AVS_HEART_BEAT	        = 0x0000,        // ����
	MSG_AVS_START_VIDEO	        = 0x0010,        // ��ʼ��Ƶ����
	MSG_AVS_STOP_VIDEO	        = 0x0020,        // ֹͣ��Ƶ����
	MSG_AVS_SET_VIDEO_PORT	    = 0x0030,        // ������Ƶ���Ͷ˿�
};

//
// ����������
//
enum MsgAvsSubType
{
	MSG_AVS_DATA_REQUEST	    = 0x01,        // ����
	MSG_AVS_DATA_RESPONSE	    = 0x02,        // Ӧ��
	MSG_AVS_DATA_ERROR	        = 0x03,        // ����
};

#define PACK_ALIGN	__attribute__((packed))

//
// ����ͷ��ʽ
//
typedef struct AvsPackHead
{
	unsigned int	msgFlag;        // ��Ϣ��ʶ
	unsigned char	msgType;        // ��Ϣ����
	unsigned short	packSn;            // �����
	unsigned int	packType;        // ������
	unsigned char	subType;        // ������
	unsigned short	len;            // ���ݳ���
    
} PACK_ALIGN AVS_PACK_HEAD;

//
// ���ݰ���ʽ
//
typedef struct AvsPackData
{
	AVS_PACK_HEAD head;                // ��ͷ����
	unsigned char data[1];            // �������ݲ��ֺ�2�ֽ�У���
    
} PACK_ALIGN AVS_PACK_DATA;

#undef PACK_ALIGN

void *DealAVSendThread( void *args );

#endif  // _AV_SEND_THREAD_H

