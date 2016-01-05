#ifndef __DCPSEARCHRECORD_H__
#define __DCPSEARCHRECORD_H__

#include "const.h"
#include "dcpTypes.h"

#define SEARCH_RESULT_PACK_SIZE (5*1024)

typedef struct _DcpSearchRecordArgs_
{
	DCP_HEAD_T msgHead;                // ��Ϣͷ
	DCP_SEARCH_RECORD_COND_T searchCond; // ��Ϣ��
	ushort index;                    // ����ָ�����ĸ��û��Ĳ���
} DCP_SEARCH_RECORD_ARGS_T;

void *DcpSearchRecordThread( void *args );

#endif 

