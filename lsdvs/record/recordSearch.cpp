#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "const.h"
#include "debug.h"
#include "malloc.h"
#include "timeExchange.h"
#include "hdd.h"
#include "public.h"
#include "linuxFile.h"
#include "recordSearch.h"
#include "hddrw.h"

/*
* �Ӹ����Ĳ������ɲ�ѯ·��
* partition:����;year,month,day:��-��-��;channel:ͨ��
* inquire_path:out,��ѯ·��
* ����:FI_FAIL-ʧ��,FI_SUCCESS-�ɹ�
*/
static int GetRecInquirePath(char *partition,int year,int month,int day,int channel,char *inquire_path)
{
	if(NULL == inquire_path || NULL == partition)
    {
    	SVPrint("error:NULL == date_path || NULL == partition!\r\n");
    	return FI_FAIL;
    }
	sprintf(inquire_path,"%s/%04d-%02d-%02d/ch%02d",partition,year,month,day,channel);
	FiPrint2("getInquireDatePath=%s\r\n",inquire_path);
	return FI_SUCCESS;
}

/*
* �ж��ļ��Ƿ��������ļ�,������ʱ��ֻ�������ļ����� 
* ����:FI_TRUE-�������ļ�,FI_FALSE-�������ļ�
*/
static int IsIndexFile(char *filename)
{
	char *token;
	if(NULL == filename)
    {
    	SVPrint("error:NULL == filename!\r\n");
    	return FI_FALSE;
    }
	token = strstr(filename,".index");
	if(NULL != token && Strcmp(token,".index")==0)
    {
    	return FI_TRUE;
    }
	else
    {
    	return FI_FALSE;
    }    
}

/*
* �������ļ����жϸ�¼���ļ��Ƿ�����Ҫ�ҵ��ļ�
* index_name:�������ļ���; recType:Ҫ�ҵ�¼������; startTime:Ҫ����ҵ�¼��Ŀ�ʼʱ��; stopTime:Ҫ����ҵ�¼���ֹͣʱ��
* r_start_time:out,��¼�����ʼʱ��; r_stop_time:out,��¼���ֹͣʱ��; size:out,��¼��Ĵ�С
* ����:FI_TRUE-�ɹ�,FI_FALSE-ʧ��
*/
static int IsMatchRecordFile(char *index_name,uint *recType,time_t startTime,time_t stopTime,
                            	time_t *r_start_time,time_t *r_stop_time,uint *size)
{
	int handle = -1;
	RECORD_INDEX rec_index;
	if(NULL == index_name || NULL == r_start_time 
    || NULL == r_stop_time || NULL == size || NULL == recType)
    {
    	SVPrint("error:NULL == index_name || NULL == r_start_time || NULL == r_stop_time || NULL == size!\r\n");
    	return FI_FALSE;
    }
	if(-1 == (handle=HddrwOpen(index_name,O_RDONLY)))
    {
    	SVPrint("HddrwOpen(%s) error:%s!\r\n",index_name,STRERROR_ERRNO);        
    	return FI_FALSE;
    }
	if(HddrwRead(handle,(char *)&rec_index,sizeof(rec_index)) != sizeof(rec_index))
    {
    	SVPrint("read() error:%s!\r\n",STRERROR_ERRNO);    
    	HddrwClose(handle);
    	return FI_FALSE;
    }
	HddrwClose(handle);    
    
	if(!(rec_index.recordType & *recType))
    {
    	return FI_FALSE;
    }    
	if(rec_index.firstFrameTimestamp > stopTime || rec_index.lastFrameTimestamp < startTime)
    {
    	return FI_FALSE;
    }
    
    *recType         = rec_index.recordType;
    *r_start_time     = rec_index.firstFrameTimestamp;
    *r_stop_time     = rec_index.lastFrameTimestamp;
    *size             = rec_index.fileLen;
    
	return FI_TRUE;    
}

/*
* ��¼��������ļ�����ȡ¼���ļ���,�������ļ��Ƿ���ʹ��
* index_name:�����ļ���
* record_name:out,¼���ļ���
* ����:FI_SUCCESS or FI_FAIL
*/
static int IndexNameToRecordName(char *index_name,char *record_name)
{
	int 	ret         = FI_SUCCESS;
	char     *token         = NULL;
    
	if(NULL == index_name || NULL == record_name)
    {
    	SVPrint("error:NULL == index_name || NULL == record_name!\r\n");
    	return FI_FAIL;
    }
    
	if(NULL == (token=strsep(&index_name,".")))
    {
    	SVPrint("strsep error:%s!\r\n",STRERROR_ERRNO);
    	ret = FI_FAIL;
    }
    
	if(FI_SUCCESS == ret)
    {
    	sprintf(record_name,"%s.dat",token);
    	if(FI_TRUE == IsRecordingFile(record_name))
        	ret = FI_FAIL;
    }
    
	return ret;    
}

/*
* �������ļ���ȡ����¼���ļ�����¼���ѯ������
* index_name:�����ļ���;startTime:���ļ��Ŀ�ʼʱ��;
* stopTime:���ļ��Ľ���ʱ��;recLen:��¼���ļ��ĳ���;
* inquire_list:out,��ѯ����¼�������б�
* ����:FI_SUCCESS or FI_FAIL
*/
static int InsertRecorFileToInquireList(char *index_name,time_t startTime,time_t stopTime,
                                    	uint recLen,RECORD_INQUIRE_LIST *inquire_list,uint recType)
{
	RECORD_INQUIRE *inquire_node = NULL;
	if(NULL == (inquire_node = (RECORD_INQUIRE *)Calloc(1,sizeof(RECORD_INQUIRE))))
    {
    	SVPrint("malloc() error:%s!\r\n",STRERROR_ERRNO);
    	return FI_FAIL;
    }    
	inquire_node->next = NULL;
	inquire_node->prev = NULL;
    
	if(FI_FAIL == IndexNameToRecordName(index_name,inquire_node->recFilename))
    {
    	Free(inquire_node);
    	return FI_FAIL;
    }
    
	inquire_node->startTime = startTime;
	inquire_node->stopTime     = stopTime;
	inquire_node->recLen     = recLen;    
	inquire_node->recType	= recType;

    //start insert
	if(NULL == inquire_list->head)
    {
    	inquire_list->head = inquire_node;
    	inquire_list->cur = inquire_node;
    	inquire_list->tail = inquire_node;
    	return FI_SUCCESS;
    }
	inquire_list->cur = inquire_list->head;
	while(1)
    {
    	if(NULL == inquire_list->cur)
        {
        	inquire_list->tail->next= inquire_node;
        	inquire_node->prev = inquire_list->tail;
        	inquire_list->tail = inquire_node;
        	break;
        }
    	if(inquire_node->startTime < inquire_list->cur->startTime)
        {
        	if(inquire_list->cur == inquire_list->head)
            {
            	inquire_node->next = inquire_list->head;
            	inquire_list->head->prev = inquire_node;
            	inquire_list->head = inquire_node;
            }
        	else
            {
            	inquire_node->next = inquire_list->cur;
            	inquire_node->prev = inquire_list->cur->prev;
            	inquire_node->prev->next = inquire_node;
            	inquire_node->next->prev = inquire_node;
            }
        	break;
        }
    	inquire_list->cur = inquire_list->cur->next;
    }
	return FI_SUCCESS;
}

/*
* �ҳ�ĳ��·�������з��ϲ���Ҫ���¼��
* path:�ļ��ľ���·��;recType:¼������
* startTime:Ҫ���ҵĿ�ʼʱ��;stopTime:Ҫ���ҵĽ���ʱ��
* inquire_list:out,��ѯ����¼�������б�
* ����:FI_TRUE-�ɹ�,FI_FAIL-ʧ��
*/
static int FindRecordFileInPath(char *path,uint recType,
    	time_t startTime,time_t stopTime,RECORD_INQUIRE_LIST *inquire_list)
{
	DIR             *handle_dir     = NULL;
	struct  dirent  *pdir             = NULL;
	time_t         	r_start_time     = 0,r_stop_time = 0;
	uint 	r_rec_len	    = 0;    
	uint 	localRecType     = recType;
	char         	full_index_name[128]     = {0};
    
	if(NULL == path)
    {
    	SVPrint("error:NULL == path!\r\n");
    	return FI_FAIL;
    }
	if(NULL == (handle_dir=HddrwOpendir(path))) 
    {
    	SVPrint("find record,HddrwOpendir(%s) error:%s\r\n",path,STRERROR_ERRNO);
    	return FI_FAIL;
    }
	while(NULL != (pdir=HddrwReaddir(handle_dir)))
    {
    	if(0 == Strcmp(pdir->d_name,".") || 0 == Strcmp(pdir->d_name,".."))
        {
        	continue;
        }
    	if(!IsIndexFile(pdir->d_name))
        {            
        	continue;
        }    
    	localRecType = recType;
    	snprintf(full_index_name,sizeof(full_index_name)-1,"%s/%s",path,pdir->d_name);        
    	if(FI_FALSE == IsMatchRecordFile(full_index_name,&localRecType,startTime,stopTime,&r_start_time,&r_stop_time,&r_rec_len))
        {
        	continue;
        }
    	InsertRecorFileToInquireList(full_index_name,r_start_time,r_stop_time,r_rec_len,inquire_list,localRecType);
    }
	HddrwClosedir(handle_dir);
    
	return FI_SUCCESS;
}

/*
* ¼���ѯ
* recType:¼������
* startTime:UTC��ʽ�Ŀ�ʼʱ��
* stopTime:UTC��ʽ�Ľ���ʱ��
* ����:���ϲ���Ҫ���¼���ļ��б�
* ע��:������ú�����Ҫ�ͷ�һ��ָ��(���ص�ָ��)��һ������(����ָ���head������ָ�������)
*/
/* /record/hd00 /10-10-28 /ch00 /FI_DVS2_000_11h45m50s.h264 */
RECORD_INQUIRE_LIST *FiRecInquireRecordFile( int channel, uint recType, 
                            	time_t startTime, time_t stopTime )
{
	char inquire_partition[32] = {0};
	char inquire_path[RECORD_FILENAME_LEN] = {0};    
    
	int partition_num;
	int i,i_p;
	int year,month,day;
	int startSecond,stopSecond;
	RECORD_INQUIRE_LIST *inquire_list;    

	SVPrint("record search:recType(0x%X),startTime(%d),stopTime(%d)\r\n",recType,startTime,stopTime);
    
	if(startTime > stopTime 
        || channel < 0 || channel >= REAL_CHANNEL_NUM
        || (recType & RECORD_TYPE_ALL)==0 )
    {
    	SVPrint("record find failed:please check your find condition!\r\n");
    	return NULL;
    }

	if(NULL == (inquire_list = (RECORD_INQUIRE_LIST *)Calloc(1,sizeof(RECORD_INQUIRE_LIST))))
    {
    	SVPrint("malloc error:%s!\r\n",STRERROR_ERRNO);
    	return NULL;
    }    
	inquire_list->head = NULL;
	inquire_list->cur = NULL;
	inquire_list->tail = NULL;

	partition_num = FiHddGetMaxPartitionNum();
	for( i_p = 0; i_p<partition_num; i_p++ )
    {
    	if( FI_FAIL == FiHddGetHddPartitionPath(i_p, inquire_partition) )        
        	continue;
        
    	startSecond = startTime;
    	stopSecond = stopTime + ONE_DAY_SECOND - stopTime%ONE_DAY_SECOND;
    	for( i = startSecond; i < stopSecond; i += ONE_DAY_SECOND ) 
        {
        	FiTimeUtcToHuman( i, &year, &month, &day, NULL, NULL, NULL );                    
        	if(FI_FAIL == GetRecInquirePath(inquire_partition,year,month,day,channel,inquire_path))
            {
            	continue;
            }                    
        	FindRecordFileInPath(inquire_path,recType,startTime,stopTime,inquire_list);            
        }
    }
	return inquire_list;    
}

void FiRecFreeInquireRecord(RECORD_INQUIRE_LIST *recInquireRet)
{
	RECORD_INQUIRE *del = NULL;
    
	if(NULL == recInquireRet)
    {
    	return;
    }
	recInquireRet->cur = recInquireRet->head;
	while(NULL != recInquireRet->cur)
    {
    	del = recInquireRet->cur;
    	recInquireRet->cur = recInquireRet->cur->next;
    	Free(del);
    }
	Free( recInquireRet );
    
	return;    
}

