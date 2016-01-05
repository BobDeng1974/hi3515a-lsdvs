#ifndef __RECORDPOOL_H__
#define __RECORDPOOL_H__

#include "pcpRecord.h"    // �õ���ͷ�ļ��Ľṹ��
#include "procon.h"    // �õ���ͷ�ļ��Ľṹ��

typedef enum _RecordPoolState_
{
	RECORD_POOL_STATE_INIT = 0, // ��ʼ״̬
	RECORD_POOL_STATE_NORMAL,    // ��̬
	RECORD_POOL_STATE_WAIT_I,    // �ȴ�I ֡
} RECORD_POOL_STATE_EN;

typedef struct _RecordPool_
{
	int	        	state;    
	PCP_NODE_T         *pcpNode;
} RECORD_POOL_T;

void InitRecordPool();
void DeinitRecordPool();
int RecordPoolWrite( int channel, PROCON_NODE_T *pStream );
void RecordPoolSignal( int channel );
void RecordPoolWait( int channel );
PCP_NODE_T *RecordPoolRead( int channel );
void RecordPoolFree( PCP_NODE_T *pcpNode );

#endif // __RECORDPOOL_H__

