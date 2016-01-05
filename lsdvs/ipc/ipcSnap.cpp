/*
*******************************************************************************
**	Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**	author        :  sven
**	version       :  v1.0
**	date           :  2013.10.10
**	description  : ipc ץ��
*******************************************************************************
*/
#include "ipcSnap.h"
#include "debug.h"
#include "public.h"
#include "ttypes.h"
#include "mutex.h"
#include "pcpIpcSnap.h"
#include "ipcHttpSnap.h"
#include "proconApp.h"

#include "timeExchange.h"

static ClMutexLock g_ipcSnapMutex[IPC_JPG_CHN_NUM];

static void GetiPCJpgDatetimeInfo( int sec, char *date, char *time )
{
	int YY, MM, DD, hh, mm, ss;
	FiTimeUtcToHuman( sec, &YY, &MM, &DD, &hh, &mm, &ss );
	sprintf( date, "%04d-%02d-%02d", YY, MM, DD );    
	sprintf( time, "%02dh%02dm%02ds", hh, mm, ss );
}

static uint g_pcpIpcSnapFd[IPC_JPG_CHN_NUM];
static int GetChnIpcSnapPcpFd( int channel )
{
	return g_pcpIpcSnapFd[channel];
}

void InitIpcSnapPcpFd()
{
	int i;
	for( i = 0; i < IPC_JPG_CHN_NUM; ++i )
    {
    	g_pcpIpcSnapFd[i] = PcpIpcSnapOpen( i, OPEN_WRONLY );
    	if( 0 == g_pcpIpcSnapFd[i] )
        {
        	SVPrint( "ch(%d) PcpIpcSnapOpen failed!\r\n", i );
        }
    }
}

void DeinitIpcSnapPcpFd()
{
	int i;
	for( i = 0; i < IPC_JPG_CHN_NUM; ++i )
    {
    	PcpIpcSnapClose( g_pcpIpcSnapFd[i] );
    	g_pcpIpcSnapFd[i] = 0;
    }
}

/*
* fn: ��ipc ץ�ĵ�ͼƬ,Ȼ�����pcp, �˺��������ø�SnapMpiGetJpgAndToProcon() ����
* snapCh: ����ͨ�� 0
* snapType: ץ������, SNAP_TYPE_TIMER ��
*/
int IpcSnapAndToPcp( int snapCh, uint snapType )
{
	int ret = -1;
	int infoLen;
	static uint 	num[IPC_JPG_CHN_NUM];
	JPG_INFO_T		jpgInfo;
	PCP_NODE_T         *pPcpNode;
    
	if( snapCh < 0 || snapCh >= IPC_JPG_CHN_NUM )
    {
    	SVPrint( "error:snapCh < 0 || snapCh >= IPC_JPG_CHN_NUM!\r\n" );
    	return -1;
    }

	g_ipcSnapMutex[snapCh].Lock();
    
	pPcpNode = PcpIpcSnapTalloc( snapCh );
	if(  NULL != pPcpNode )
    {
    	jpgInfo.num     = num[snapCh]++;
    	jpgInfo.type	= snapType;
    	GetiPCJpgDatetimeInfo( time(NULL), jpgInfo.datel, jpgInfo.timel ); 
    	jpgInfo.len     = 0;        

    	infoLen = sizeof(jpgInfo);
    	ret = HttpSnap( pPcpNode->data + infoLen, MAX_IPC_SNAP_DATA_SIZE - infoLen );
    	if( ret > 0 )
        {
        	jpgInfo.len += ret;
        	memcpy( pPcpNode->data, &jpgInfo, infoLen );
        	ret = PcpIpcSnapWrite( GetChnIpcSnapPcpFd(snapCh), pPcpNode );
        }
    	else
        {
        	PcpIpcSnapFree( pPcpNode );
        	ret = -1;
        }
    }
    
	g_ipcSnapMutex[snapCh].Unlock();
    
	return ret;
}


