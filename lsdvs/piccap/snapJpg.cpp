/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.11.06
**  description  : ץ�ĳ�jpg ͼƬ
********************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include "const.h"
#include "debug.h"
#include "thread.h"
#include "proconJpg.h"
#include "linuxFile.h"
#include "ttypes.h"
#include "public.h"
#include "hdd.h"
#include "pcpIpcSnap.h"

static void AnalysisSnapType( int snapType,char *snapTypeName )
{
	switch( snapType )
    {
    	case SNAP_TYPE_HAND:
        	sprintf( snapTypeName,"hand" );
        	break;
    	case SNAP_TYPE_ALARM_IO:
        	sprintf( snapTypeName, "alarmio" );
        	break;
    	case SNAP_TYPE_ALARM_MD:
        	sprintf( snapTypeName, "alarmmd" );
        	break;
    	case SNAP_TYPE_ALARM_LOST:
        	sprintf( snapTypeName, "alarmlo" );
        	break;
    	case SNAP_TYPE_TIMER:
        	sprintf( snapTypeName, "timer" );
        	break;
    	case SNAP_TYPE_ALARM_SHELTER:
        	sprintf( snapTypeName, "alarmshelter" );
        	break;            
    	default:
        	sprintf( snapTypeName, "hand" );
        	break;            
    }
}

/*********************************************************************
* fn: ���ݸ�������Ϣ����ץ��ͼƬ������
* channel: ͨ��
* jpgInfo: ��ͼƬץ��ʱ����Ϣ
* filename: out, ���ɺ���ļ���
*********************************************************************/
static int GenSnapFilename( int channel, JPG_INFO_T *jpgInfo, char *filename )
{
	int 	ret;
	char 	hddPath[32];
	char	snapTypeName[32];

	if( NULL == jpgInfo || NULL == filename )
    {
    	SVPrint( "error:NULL == jpgInfo || NULL == filename!\r\n" );
    	return FI_FAILED;
    }
    
	if( FI_FAILED == FiHddGetUsingPartition(hddPath) )
    {
        //FiPrint2( "FI_FAILED == FiHddGetUsingPartition() !\r\n" );
    	return FI_FAILED;
    }
	sprintf( filename, "%s/jpg/%s/ch%02d", hddPath, jpgInfo->datel, channel );
    
    
	ret = MakePath( filename, 0777 );
	if( 0 == ret )
    {
    	AnalysisSnapType( jpgInfo->type, snapTypeName );
        
        /* /sdax/jpg/2013-10-28/ch00/11h45m50s_0001_timer.jpg */
    	sprintf( filename, "%s/%s_%04d_%s.jpg",
                	filename, jpgInfo->timel, jpgInfo->num, snapTypeName );         
    }
	return ret;
}

static int WriteJpegToFile( char *filename, char *buffer, unsigned int len )
{
	int fd;
	if( NULL == filename || NULL == buffer )
    {
    	SVPrint( "error:NULL == filename || NULL == buffer!\r\n" );
    	return -1;
    }
	fd = open( filename, O_WRONLY|O_CREAT, 0644 );
	if( fd < 0 )
    {
    	SVPrint( "error: Open(%s):%s!\r\n", filename, STRERROR_ERRNO );
    	return -1;
    }    
	Writen( fd, buffer, len );
	Close( fd );
    
	return 0;
}

static int SnapJpgWrite( int channel, JPG_INFO_T *jpgInfo )
{
	int ret;
	char filename[MAX_SNAP_JPG_PATH_LEN];

	ret = GenSnapFilename( channel, jpgInfo, filename );
	if( 0 == ret )
    {
    	ret = WriteJpegToFile( filename, (char *)jpgInfo + sizeof(JPG_INFO_T), jpgInfo->len );
    }
	return ret;
}

static THREAD_MAINTAIN_T g_snapJpgTm;
static void *SnapJpgThread( void *arg )
{
	int i, ret;
	static uint nullCount;
	uint proconJpgFd[MAX_JPG_CHN_NUM];
	PROCON_NODE_T *pProconJpg;
	PCP_NODE_T *pPcpJpg;
	JPG_INFO_T *jpgInfo;

	for( i = 0; i < MAX_JPG_CHN_NUM; ++i )
    {
    	if( i == (MAX_JPG_CHN_NUM-1) )
        {
        	proconJpgFd[i] = PcpIpcSnapOpen( 0, OPEN_RDONLY );
        }
    	else
        {
        	proconJpgFd[i] = ProconJpgOpen( i, OPEN_RDONLY );
        }
    	if( 0 == proconJpgFd[i] )
        {
        	SVPrint( "failed:ProconJpgOpen( %d, OPEN_RDONLY )!\r\n", i );
        }
    }
	SVPrint( "SnapJpgThread start!\r\n" );
	while( g_snapJpgTm.runFlag )
    {        
    	for( i = 0; i < MAX_JPG_CHN_NUM; ++i )
        {
        	if( i == (MAX_JPG_CHN_NUM-1) )
            {
            	pPcpJpg = PcpIpcSnapRead( proconJpgFd[i] );
            	if( NULL == pPcpJpg )
                {
                	nullCount++;
                }
            	else
                {
                	nullCount = 0;
                	jpgInfo = (JPG_INFO_T *)pPcpJpg->data;
                	ret = SnapJpgWrite( i, jpgInfo );
                    
                	PcpIpcSnapFree( pPcpJpg );
                }
            }
        	else
            {
            	pProconJpg = ProconJpgRead( proconJpgFd[i] );
            	if( NULL == pProconJpg )
                {
                	nullCount++;
                }
            	else
                {
                	nullCount = 0;
                	jpgInfo = (JPG_INFO_T *)pProconJpg->data;
                	ret = SnapJpgWrite( i, jpgInfo );
                    
                	ProconJpgFree( pProconJpg );
                }
            }
        }
    	if( nullCount >= MAX_JPG_CHN_NUM )
        {
        	sleep( 2 );
        }
    }
 
	for( i = 0; i < MAX_JPG_CHN_NUM; ++i )
    {
    	if( 0 != proconJpgFd[i] )
        {
        	if( i == (MAX_JPG_CHN_NUM-1) )
            {
            	PcpIpcSnapClose( proconJpgFd[i] );
            }
        	else
            {
            	ProconJpgClose( proconJpgFd[i] );
            }
        }
    }
	SVPrint( "SnapJpgThread stop!\r\n");
	return NULL;
}

void StartSnapJpgThread()
{
	int ret;
	g_snapJpgTm.runFlag = 1;
	ret = ThreadCreate( &g_snapJpgTm.id, SnapJpgThread, NULL );
	if( 0!= ret )
    {        
    	g_snapJpgTm.runFlag = 0;
    	SVPrint( "error:ThreadCreate:%s\r\n", STRERROR_ERRNO );
    }
}

void StopSnapJpgThread()
{
	int ret;
	g_snapJpgTm.runFlag = 0;
	ret = ThreadJoin( g_snapJpgTm.id, NULL );
	if( 0 != ret )
    {
    	SVPrint( "error:ThreadJoin:%s\r\n", STRERROR_ERRNO );
    }
}

