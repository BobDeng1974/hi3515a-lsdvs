/********************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ��ͷ�ļ��ṩ��DVS�������ݴ���Э��İ�ͷ���ݽṹ����
**
**  version       :  1.0
**  author        :  SVEN
********************************************************************************/

#ifndef __DCPUPDATE_H__
#define __DCPUPDATE_H__

// �����������ļ�������
typedef enum _UpdateFileSubtype_
{
    UPDATE_FILE_DATA_SEGMENT = 0,   // �����ļ����ݰ�
    UPDATE_FILE_LAST_SEGMENT,       // ���һ�����ݰ�
} UPDATE_FILE_SUBTYPE_EN;

// ��������ļ�ʱ���ص�״̬
typedef enum _DcpFileCode_
{
    DCP_FILE_COMPLETE = 0,  // ��ɽ���
    DCP_FILE_RECEIVE,       // ���ڽ���
    DCP_FILE_ERROR,         // ���ճ���
} DCP_FILE_CODE_EN;

// дFLASH���Ƚṹ��
typedef struct _WriteFlashProgress_
{
    int percent;
    char reserved[20];
} WRITE_FLASH_PROGRESS_T;

// ���������߳���Ҫ�Ĳ��� 
typedef struct _UpdateParam_
{
	unsigned int 	fileSize;        // �����ļ���С
	int         	socket;            // ����������socket
} UPDATE_PARAM_T;

// ά����������ͨ�Žṹ
typedef struct _UpdateCom_
{
	int 	socket;                // ͨ��socket
	char     *readBuf;            // ���ջ�����	
	uint 	readBufSize;        // ���ջ������Ĵ�С
	uint 	readBufDataSize;    // ���ջ��������浱ǰ�����ݴ�С
	char     *writeBuf;            // ���ͻ�����
	uint	writeBufSize;        // ���ͻ������Ĵ�С
	uint	writeBufDataSize;    // ��������buffer��������ݴ�С
} UPDATE_COM_T;

int DcpCreateUpdateThread(uint fileSize, int socket );
int IsDcpUpdateThreadRun();

void StartUpdateFlashThread();
void StopUpdateFlashThread();

#endif

