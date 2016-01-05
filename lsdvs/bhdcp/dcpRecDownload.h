#ifndef __DCPRECDOWNLOAD_H__
#define __DCPRECDOWNLOAD_H__

#include "dcpTypes.h"

#define MAX_RECORD_DATA_SEND_PACKET_SIZE (8*1024) //ÿ�η���8 k

typedef struct _RecSendPacket_
{
	STREAM_PACK_HEAD_T packHead;
	char dataBuf[MAX_RECORD_DATA_SEND_PACKET_SIZE]; // ��Ŵ��ļ�������¼������
} REC_SEND_PACKET_T;

typedef struct _RecDownload_
{
	int socket;    // ���͵�socket
	int fd;        // ¼���ļ��ľ��
	int len;     // ���͵ĳ���
	REC_SEND_PACKET_T sendPack;
} REC_DOWNLOAD_T;

int DcpStartRecDownload( int socket, int fd );

#endif 

