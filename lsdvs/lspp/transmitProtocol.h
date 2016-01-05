/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ��ͷ�ļ��ṩ��DVS���ݴ���Э��İ�ͷ���ݽṹ����
**  �ο��ĵ�: <<DVS����Э��.doc>> V1.0
**  date           :  2013.12.07
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef _TRANSMIT_PROTOCOL_H
#define _TRANSMIT_PROTOCOL_H

enum MsgDataTransmitPackType
{
	MSG_TRANSMIT_UPGRADE_REQUEST	= 0x0100,        // ����ϵͳ����
	MSG_TRANSMIT_UPGRADE_FILE	    = 0x0200,        // ���������ļ�
	MSG_TRANSMIT_GET_SYSCONFIGURE	= 0x0300,        // ����ϵͳ����
};

enum MsgDataTransmitSubType
{
	MSG_TRANSMIT_REQUEST	        = 0x01,        // ����
	MSG_TRANSMIT_RESPONSE	        = 0x02,        // Ӧ��
	MSG_TRANSMIT_ERROR	            = 0x03,        // ����
	MSG_TRANSMIT_DATA_SEGMENT	    = 0x04,        // ���ݷ�Ƭ
	MSG_TRANSMIT_LAST_SEGMENT	    = 0x05,        // ���һ�����ݷ�Ƭ
};

int DealDataTransmitProcess( unsigned char *dataBuf, int &dataLen, const int bufSize );
int CheckDataTransmitProcess( unsigned char *dataBuf, int dataLen, int bufSize, int &offset );

#endif  // _TRANSMIT_PROTOCOL_H

