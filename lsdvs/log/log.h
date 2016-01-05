#ifndef __LOG_H__
#define __LOG_H__

#include <time.h>

#define LOG_SIGNATURE	        "FirsLogEvt"
#define MAX_LOG_NUM	        	1000
// #define LOG_DESCRIPT_LEN		15
#define LOG_INFORMATION_LEN		108
#define LOG_TYPE_ALL	        '0'
#define LOG_TYPE_SYSTEM	        '1'      /* ϵͳ�¼�*/
#define LOG_TYPE_DATABASE	    '2'      /* ��¼�¼�*/
#define LOG_TYPE_STORAGE	    '3'   /* FLASH ��SD���ȴ��������¼� */
#define LOG_TYPE_MODULEx	    '4'   /* ����ģ����չ*/

#define LOG_LEVEL_ALL	        '0'
#define LOG_LEVEL_DEBUG         '1'
#define LOG_LEVEL_INFO	        '2'
#define LOG_LEVEL_WARN	        '3'
#define LOG_LEVEL_ERROR	        '4'
#define LOG_LEVEL_CRITICAL	    '5'
#define TIME_STR_LEN            14

#ifdef WIN32
#pragma pack(1)
#define PACK_ALIGN
#else
#define PACK_ALIGN __attribute__((packed))
#endif

// ��־ͷ
typedef struct _LOG_HEAD_
{
	char signature[8];  // ��־ǩ��
	int totalItemNum;   // ����־����
    int writeItemIndex; // ��ǰд��־ƫ��
    int itemSize;       // ��־���С
    unsigned long crc;
} PACK_ALIGN LOG_HEAD_T, *LP_LOG_HEAD;

// ��־����, ��: "1 20131212121212 1 1��Ƶ��ʧ��
typedef struct _LOG_ITEM_
{
	unsigned char channel[2];                    /* �¼�ͨ�� 1 */
 	char time[14];                                /* �¼�ʱ�� 20131212121212 */
	unsigned char type[2];                        /* �¼�����  1*/
 	unsigned char level[2];                        /* �¼�����  1*/
	char information[LOG_INFORMATION_LEN];        /* �¼����� */
} PACK_ALIGN LOG_ITEM_T, *LP_LOG_ITEM;

// ��־
typedef struct _LOG_
{
	LOG_HEAD_T head;
	LOG_ITEM_T itemArray[MAX_LOG_NUM];
} LOG_T, *LP_LOG;

#ifdef WIN32
#pragma pack()
#endif

#undef PACK_ALIGN
#ifdef __cplusplus
extern "C" {
#endif

void SysLogAddTimer();
int LogInit(void);
int LogAdd( unsigned char channel, unsigned char logType, unsigned char logLevel, char *pLogFmt, ...);
int LogAddAndWriteFlash( unsigned char channel, unsigned char logType, unsigned char logLevel, char *pLogFmt, ... );
int LogGet( unsigned char logType, unsigned char logLevel, LP_LOG pLog);
int LogPrint( unsigned char logType, unsigned char logLevel);
int LogClean(void);

#ifdef __cplusplus
}
#endif

#endif 

