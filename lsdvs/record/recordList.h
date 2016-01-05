/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**	�ļ���: recordList.h
**  description  : for recordList.cpp
**  date           :  2013.10.18
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/

#ifndef __RECORD_LIST_H__
#define __RECORD_LIST_H__

#include "ttypes.h"

#define	FRAME_TYPE_I_FIRSCOM 	FI_FRAME_TYPE_VIDEO_I	//I֡
#define	FRAME_TYPE_P_FIRSCOM 	FI_FRAME_TYPE_VIDEO_P	//P֡

#define	MAX_FRAME_NODE	20	    //���¼������֡�ڵ���Ŀ
#define MAX_FRAME_SIZE	(128*1024)

#define	MIN_FREE_MB		4	

#define	FIRSCOM_FRAME_IDENTIFY_V10	0x1FDF0201
#define	FIRSCOM_FRAME_IDENTIFY	FIRSCOM_FRAME_IDENTIFY_V10

/*do not change*/
typedef struct _RecordFrameHead
{
    unsigned long	frameIdentify;    //֡��ʶ,0x1FDF0201,�ĸ��ֽڵ����� | 31 | 255-31ȡ������� | 2 | 1 | //ǰ�����ֽ��ǹ̶���,�������ֽ��ǿ���չ��
    unsigned long	FrameHeadSize;    //��֡ͷ��С
    unsigned long	frameSize;        //֡��С
    unsigned long	frameNo;        //������reset���������֡��
	unsigned char	videoResolution;//��Ƶʱ��ֱ���,CIF,QCIF,D1,��ƵʱΪAMR����ģʽ(bit7~2)��AMR�����ʽ(bit1~0)    
    unsigned char	frameRate;      //��Ϊ��Ƶ֡ʱ��֡�� ��Ϊ��Ƶ֡ʱ�������(bit7~2)�Ͳ���λ��(bit1~0)
	unsigned char	videoStandard;    //��Ϊ��Ƶ֡ʱ��N/P, Ϊ��Ƶ֡ʱ����뷽ʽ
	unsigned char	frameType;        //video frame: i, P and audio frame
    unsigned long	sec;            //����ֵ,ϵͳʱ���,�����������
    unsigned long	usec;
	unsigned long long	pts;            //���ֵ,��Ƶ����ʱ���,��������ͬ��
}RECORD_FRAME_HEAD;

typedef struct _RecordFrame
{
	RECORD_FRAME_HEAD frameHead;
	unsigned char *frameData;
}RECORD_FRAME;

typedef	struct	_RecordMem
{
	RECORD_FRAME fb;
	struct	_RecordMem	*next;
}RECORD_MEM;

typedef	struct	_RecordList
{
	RECORD_MEM	*freememHead;
	RECORD_MEM	*freememTail;
	RECORD_MEM	*usedmemHead;
	RECORD_MEM	*usedmemTail;
    
	unsigned int	usedListFrameCount;    //usedlist ������ĸ���,qljt����Ԥ¼
    
	pthread_mutex_t	freeListMutex;
	pthread_mutex_t	usedListMutex;
	pthread_cond_t 	condVar;
}RECORD_LIST;     

typedef struct _RecordListFrame
{
	unsigned char	frameType;        //֡����,video frame: i, P and audio frame
    unsigned char	frameRate;      //��Ϊ��Ƶ֡ʱ��֡�� ��Ϊ��Ƶ֡ʱ�������(bit7~2)�Ͳ���λ��(bit1~0)
	unsigned char	videoStandard;    //��Ϊ��Ƶ֡ʱ��N/P, Ϊ��Ƶ֡ʱ����뷽ʽ
	unsigned char 	videoResolution;//��Ƶʱ��ֱ���,CIF,QCIF,D1,��ƵʱΪAMR����ģʽ(bit7~2)��AMR�����ʽ(bit1~0)    
	unsigned long long	pts;        //���ֵ,��Ƶ����ʱ���,��������ͬ��
	unsigned long     	headLen;
	unsigned char         *frameHead;
	unsigned long     	frameLen;         //֡����	
	unsigned char         *frameData;         //֡����	    
}RECORD_LIST_FRAME;

typedef struct _NeedFrameStatus_
{
	int state;  // 0, ��ǰ��ҪI֡,1 ��ǰ��ҪP֡
} NEED_FRAME_STATUS_T;

// �ڲ�
void FiRecMemListInit(int channel);
void FiRecMemListDestroy(int channel);
RECORD_MEM *FiRecGetMbFromFreeList(int channel, int size);
RECORD_MEM *FiRecGetMbFromUsedList(int channel);
void FiRecInsertMbToUsedList(int channel, RECORD_MEM *mb);
//int FiRecSendFrameToRecordStreamList(int channel, int ch_type, void *t_p_stream, int frameRate);
void FiRecRecordStreamBroadcast(int channel);

// �ⲿ
int FiRecInitRecordStream();
void FiRecDestroyRecordStream(void);
int FiRecSendFrameToRecordStreamListEx(int channel, int ch_type, void *pRecordFrame);
void FiRecRecordStreamWaiting(int channel);
RECORD_MEM* FiRecGetFrameFromRecordStreamList(int channel);
void FiRecInsertMbToFreeList(int channel, RECORD_MEM *mb);

#endif //__RECORD_LIST_H__

