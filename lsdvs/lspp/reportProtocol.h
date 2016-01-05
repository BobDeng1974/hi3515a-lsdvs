/*
*******************************************************************************
**  Copyright (c) 2011, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**	�ļ���: 
**  description  : 
**  ����:    	������DVSClientͨѶ���ر�������
**  date           :  2011.08.18
**
**  version       :  1.0
**  author        :  ronat
*******************************************************************************
*/

#ifndef _REPORT_PROTOCOL_H_2011_0818_
#define _REPORT_PROTOCOL_H_2011_0818_

enum MsgReportDataPackType
{
	MSG_REPORT_PC_GETDAILYDATA_REQUEST	= 0x0100,        // ȡ�����ձ���ͳ������
	MSG_REPORT_PC_GETMONTHDATA_REQUEST	= 0x0200,        // ȡ�����±���ͳ������
};

enum MsgReportDataSubType
{
	MSG_REPORT_REQUEST	                = 0x01,        // ����
	MSG_REPORT_RESPONSE	                = 0x02,        // Ӧ��
	MSG_REPORT_ERROR	                = 0x03,        // ����
};

#ifdef WIN32
#define PACK_ALIGN
#pragma pack(push,1)
#else
#define PACK_ALIGN	__attribute__((packed))
#endif //~

typedef struct ReportPcDataRequest
{
	unsigned char 	channel;                // ͨ����
	unsigned char 	startTime[20];            // ��ʼʱ�� ����2011-08-18 00:00:00
	unsigned char 	endTime[20];            // ����ʱ��
	unsigned int  	interval;                // ʱ��������
	char	    	reserved[32];            // ����
    
} PACK_ALIGN REPORT_PC_DATA_REQUEST;




#ifdef WIN32
#pragma pack(pop,1)
#else
#undef PACK_ALIGN
#endif //~


int DealReportDataProcess( unsigned char *dataBuf, int &dataLen, const int bufSize );
int CheckReportDataProcess( unsigned char *dataBuf, int dataLen, int bufSize, int &offset );

#endif  //~_REPORT_PROTOCOL_H_2011_0818_

