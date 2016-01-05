/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.09.16
**  description  : ����ץ�ĵ��� jpg ͼƬ
********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "const.h"
#include "debug.h"
#include "public.h"
#include "malloc.h"
#include "timeExchange.h"
#include "linuxFile.h"
#include "snapSearch.h"
#include "hdd.h"

/*****************************************************************
* ץ�����͵��ַ��͵�unsigned longת��
* snapName:����·����ץ���ļ���;
* snapType:out
******************************************************************/
static int snapTypeFromCharToInt( char *snapName, uint *snapType )
{
	if( NULL == snapName || NULL == snapType )
    {
    	SVPrint( "error:NULL == snapTypeName || NULL == snapType!\r\n" );
    	return FI_FAILED;
    }
    
	if( NULL != strstr(snapName,"hand") )
    {
        *snapType = SNAP_TYPE_HAND;
    }
	else if( NULL != strstr(snapName,"timer") )
    {
        *snapType = SNAP_TYPE_TIMER;
    }
	else if( NULL != strstr(snapName,"alarmio") )
    {
        *snapType = SNAP_TYPE_ALARM_IO;
    }
	else if( NULL != strstr(snapName,"alarmlo") )
    {
        *snapType = SNAP_TYPE_ALARM_LOST;
    }
	else if( NULL != strstr(snapName,"alarmmd") )
    {
        *snapType = SNAP_TYPE_ALARM_MD;
    }
	else if( NULL != strstr(snapName,"alarmpc") )
    {
        *snapType = SNAP_TYPE_ALARM_PIC_COMPARE;
    }
	else if( NULL != strstr(snapName,"alarmshelter") )
    {
        *snapType = SNAP_TYPE_ALARM_SHELTER;
    }
    
	return FI_SUCCESSFUL;
}

/*
* ����ץ���ļ���
* snapName:����·����ץ���ļ���;
* snapType:out,ץ������;
* snapTime:out,ץ��ʱ��
*/
static int analysisSnapName( char *snapName, uint *snapType, int *hh, int *mm, int *ss )
{
	int  ret;
    
	if( NULL == snapName || NULL == snapType || NULL == hh || NULL == mm || NULL ==ss )
    {
    	SVPrint( "error:NULL == snapName || NULL == snapType || NULL == hh || NULL == mm || NULL ==ss!\r\n" );
    	return FI_FAILED;
    }

	ret = sscanf( snapName, "%02dh%02dm%02ds", hh, mm, ss );
	if( ret == 3 )
    {        
    	snapTypeFromCharToInt( snapName, snapType );
    	ret = 0;
    }
	else
    {
    	ret = -1;
    }
    
	return ret;    
}

/*
* �ٲ�jpeg�ļ�
* snapName:�ļ���, ������·��; 
* snapType: in, ���ҵ�ץ������; out, ץ���ļ�������; 
* snapTime:���ҿ�ʼʱ��; 
* stopTime:����ֹͣʱ��;
* hh, mm, ss:out,ץ��ʱ��;
* ����:FI_TRUE-�ɹ�,FI_FALSE-ʧ��
*/
static int IsMatchSnapFile( char *snapName, uint *snapType,
                        	int startTime, int stopTime, 
                        	int *hh, int *mm, int *ss )
{
	uint snapJpgType = 0;
	int	 snapJpgTime = 0;
	int  ret;
    
	if( NULL == snapName )
    {
    	SVPrint( "error:NULL == snapName || NULL == snapTime!\r\n" );
    	return FI_FALSE;
    }
    
	ret = analysisSnapName( snapName, &snapJpgType, hh, mm, ss );
	if( 0 == ret )
    {
    	if( !(snapJpgType & *snapType) )
        {
        	FiPrint2( "failed: snapJpgType(%X) - *snapType(%X)!\r\n", snapJpgType, *snapType );
        	return FI_FALSE;
        }
    	snapJpgTime = 3600 * (*hh) + 60 * (*mm) + (*ss);
    	if( snapJpgTime >= (startTime % 86400) && snapJpgTime <= (stopTime % 86400) )
        {
            *snapType = snapJpgType;
        	return FI_TRUE;
        }    
    }
	if( 0 != ret )
    {        
    	return FI_FALSE;
    }
	else
    {
    	return FI_FALSE;    
    }
}

static uint GetSnapFileSize(char *fileName)
{
	int     	ret = 0;  
	struct stat buf = {0};
    
	if(fileName)
    {
    	stat( fileName, &buf );
    	ret = buf.st_size;
    }
    
	return (uint)ret;
}

/*
* �������ļ���ȡ����ץ���ļ�����ץ�²�ѯ������
* snapName: �����ļ���;
* snapTime: ��ͼƬ��ץ��ʱ��;
* inquireList:out,��ѯ����ץ�������б�
*/
static int InsertSnapFileToInquireList( char *snapName, int snapTime,
                                    	SNAP_INQUIRE_LIST *inquireList,uint snapType )
{
	SNAP_INQUIRE *inquireNode = NULL;

	if(NULL == snapName || NULL == inquireList)
    {
    	SVPrint("error:NULL == snapName || NULL == inquireList!\r\n");
    	return FI_FAILED;
    }
    
	if(NULL == (inquireNode = (SNAP_INQUIRE *)calloc(1,sizeof(SNAP_INQUIRE))))
    {
    	SVPrint("malloc() error:%s!\r\n",STRERROR_ERRNO);
    	return FI_FAILED;
    }    
	inquireNode->next = NULL;
	inquireNode->prev = NULL;
    
	snprintf( inquireNode->snapName, MAX_SNAP_JPG_PATH_LEN, "%s", snapName);
	inquireNode->snapTime	= snapTime; 
	inquireNode->snapLen	= GetSnapFileSize( inquireNode->snapName );
	inquireNode->snapType	= snapType;
    //start insert
	if(NULL == inquireList->head)
    {
    	inquireList->head     = inquireNode;
    	inquireList->cur     = inquireNode;
    	inquireList->tail     = inquireNode;
    	return FI_SUCCESSFUL;
    }
	inquireList->cur = inquireList->head;
	while(1)
    {
    	if( NULL == inquireList->cur )
        {
        	inquireList->tail->next	= inquireNode;
        	inquireNode->prev         = inquireList->tail;
        	inquireList->tail         = inquireNode;
        	break;
        }
    	if( inquireNode->snapTime < inquireList->cur->snapTime )
        {
        	if( inquireList->cur == inquireList->head )
            {
            	inquireNode->next         = inquireList->head;
            	inquireList->head->prev = inquireNode;
            	inquireList->head         = inquireNode;
            }
        	else
            {
            	inquireNode->next = inquireList->cur;
            	inquireNode->prev = inquireList->cur->prev;
            	inquireNode->prev->next = inquireNode;
            	inquireNode->next->prev = inquireNode;
            }
        	break;
        }
    	inquireList->cur = inquireList->cur->next;
    }
	return FI_SUCCESSFUL;
}

/*
* �ҳ�ĳ��·�������з��ϲ���Ҫ���ץ��
* path:�ļ��ľ���·��;snapType:ץ������
* snapTime:Ҫ���ҵĿ�ʼʱ��;stopTime:Ҫ���ҵĽ���ʱ��
* inquireList:out,��ѯ����ץ�������б�
*/
static int FindSnapFileInPath( char *path, uint snapType, int startTime, int stopTime, 
                            	int YY, int MM, int DD, SNAP_INQUIRE_LIST *inquireList )
{
	DIR     *handleDir;
	struct	dirent	*pdir;
	int		snapTime;    
	uint	localSnapType = snapType;
	char	fullSnapName[MAX_SNAP_JPG_PATH_LEN];
	int 	hh, mm, ss;
	int 	ret;
    
	if( NULL == path )
    {
    	SVPrint("error:NULL == path!\r\n");
    	return FI_FAILED;
    }
	if( NULL == (handleDir=opendir(path)) ) 
    {
    	SVPrint( "opendir(%s) error:%s\r\n", path, STRERROR_ERRNO );
    	return FI_FAILED;
    }
	while( NULL != (pdir=readdir(handleDir)) )
    {
    	if(0 == strcmp(pdir->d_name,".") || 0 == strcmp(pdir->d_name,".."))
        {
        	continue;
        }    
    	if( NULL == strstr(pdir->d_name,".jpg") )
        {
        	continue;
        }

    	ret = IsMatchSnapFile( pdir->d_name, &localSnapType, startTime, 
                            	stopTime, &hh, &mm, &ss );
    	if( FI_FALSE == ret )
        {
        	continue;
        }
    	snapTime = FiTimeHumanToUtc( YY, MM, DD, hh, mm, ss );
    	snprintf( fullSnapName, sizeof(fullSnapName)-1, "%s/%s", path, pdir->d_name );
        
    	InsertSnapFileToInquireList( fullSnapName, snapTime, inquireList, localSnapType );
    }
	return FI_SUCCESS;
}

/*
* �Ӹ����Ĳ������ɲ�ѯ·��
* partition:����;year,month,day:��-��-��;channel:ͨ��
* inquirePath:out,��ѯ·��
* ����:FI_FAILED-ʧ��,FI_SUCCESSFUL-�ɹ�
*/
static int GetSnapInquirePath( char *partition, int year, int month, 
                        	int day, int channel, char *inquirePath )
{
	sprintf( inquirePath, "%s/jpg/%04d-%02d-%02d/ch%02d",
                    	partition, year, month, day, channel );

	return FI_SUCCESSFUL;
}

/*
* fn: ץ�²�ѯ
* channel: ͨ��
* snapType:	ץ������
* startTime: ��ʼʱ��
* stopTime: ����ʱ��
* ����:���ϲ���Ҫ���ץ���ļ��б�
* ע��:������ú�����Ҫ�ͷ�һ��ָ��(���ص�ָ��)��һ������(����ָ���head������ָ�������)
	ʹ�� FiSnapFreeInquireSnap() �ͷ�
*/
SNAP_INQUIRE_LIST *FiSnapInquireSnapFile( int channel, uint snapType, 
                                    	int startTime, int stopTime )
{
	char inquirePartition[32] = {0};
	char inquirePath[MAX_SNAP_JPG_PATH_LEN] = {0};     
	int partitionNum;
	int i,j;
	int YY, MM, DD;
	int startSecond,stopSecond;
	SNAP_INQUIRE_LIST *inquireList;    
    
	if(	startTime > stopTime 
        || channel < 0 || channel >= REAL_CHANNEL_NUM
        || (snapType & SNAP_TYPE_ALL) == 0 )
    {
    	SVPrint( "snap find failed:please check your find condition!\r\n" );
    	return NULL;
    }

	if(NULL == (inquireList = (SNAP_INQUIRE_LIST *)Malloc(sizeof(SNAP_INQUIRE_LIST))))
    {
    	SVPrint( "malloc error:%s!\r\n", STRERROR_ERRNO );
    	return NULL;
    }    
	inquireList->head     = NULL;
	inquireList->cur     = NULL;
	inquireList->tail     = NULL;

	partitionNum = FiHddGetMaxPartitionNum();
	for( j = 0; j < partitionNum; j++ )
    {
    	if( FI_FAILED == FiHddGetHddPartitionPath( j, inquirePartition) )
        {
        	continue;
        }
    	startSecond = startTime;
    	stopSecond     = stopTime + ONE_DAY_SECOND - stopTime%ONE_DAY_SECOND;
        
    	for( i = startSecond; i < stopSecond; i += ONE_DAY_SECOND ) 
        {
        	FiTimeUtcToHuman( i, &YY, &MM, &DD, NULL, NULL, NULL );                 
        	if(FI_FAILED == GetSnapInquirePath( inquirePartition, YY, MM, DD, channel, inquirePath) )
            {
            	continue;
            }        
        	FindSnapFileInPath( inquirePath, snapType, startTime, stopTime, YY, MM, DD, inquireList );            
        }
    }
    
	return inquireList;    
}

/**********************************************************
* fn: �ͷ�FiSnapInquireSnapFile() �ķ��ؽ��
************************************************************/
void FiSnapFreeInquireSnap( SNAP_INQUIRE_LIST *snapInquireResult )
{
	SNAP_INQUIRE *del;
	if( NULL == snapInquireResult )
    {
    	return;
    }
	snapInquireResult->cur = snapInquireResult->head;
	while( NULL != snapInquireResult->cur )
    {
    	del = snapInquireResult->cur;
    	snapInquireResult->cur = snapInquireResult->cur->next;
    	Free( del );
    }
    
	Free(snapInquireResult);
    
	return; 
}

