/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ��ͷ�ļ��ṩ��DVS����Э��İ�ͷ���ݽṹ����
**  �ο��ĵ�: <<DVS����Э��.doc>> V1.0
**  date           :  2013.11.11
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef _MESSAGE_PROTOCOL_H
#define _MESSAGE_PROTOCOL_H

const unsigned int	MSG_DATA_FLAG	    = 0xABBA3AA3;    // Э���ʶ
const int	    	MSG_CFG_DATA_PORT	= 6010;            // �˿ں�
const int	    	MSG_CFG_DATA_BAUD	= 9600;            // ������

enum MsgDataType
{
	MSG_CFG_DATA_TYPE	        = 0x01,        // ����Э����Ϣ����
	MSG_AVS_DATA_TYPE	        = 0x02,        // ��ý���������
	MSG_CTL_DATA_TYPE	        = 0x03,        // ��������
	MSG_UPL_DATA_TYPE	        = 0x04,        // �¼��ϱ�
	MSG_DEV_SEARCH_TYPE	        = 0x05,        // �豸����
	MSG_DATA_TRANSMIT_TYPE	    = 0x06,        // ����Э��
	MSG_DATA_REPORT_TYPE	    = 0x07,        // ����Э��
};

#define PACK_ALIGN	__attribute__((packed))

typedef struct messageData
{
	unsigned int	msgFlag;        // ��Ϣ��ʶ
	unsigned char	msgType;        // ��Ϣ����
	unsigned char 	msgData[1];        // ��Ϣ����
    
} PACK_ALIGN MESSAGE_DATA;

#undef PACK_ALIGN

const int MAX_DATA_BUF_SIZE = 16 * 1024;

#endif  // _MESSAGE_PROTOCOL_H

