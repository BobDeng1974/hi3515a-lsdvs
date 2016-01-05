#ifndef __DCPSEARCHLOG_H__
#define __DCPSEARCHLOG_H__

#include "const.h"
#include "dcpTypes.h"

#define SEARCH_LOG_PACK_SIZE (5*1024)

typedef struct _DcpSearchLogArgs_
{
	DCP_HEAD_T msgHead;                // ��Ϣͷ
	DCP_GET_LOG_T getLogCond;       // ��Ϣ��
	ushort index;                    // ����ָ�����ĸ��û��Ĳ���
} DCP_SEARCH_LOG_ARGS_T;

void *DcpSearchLogThread( void *args );

#endif 

