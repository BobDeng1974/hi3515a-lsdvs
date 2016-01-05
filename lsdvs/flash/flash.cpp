/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ���ļ�ʵ���˶�flash���ж�д�����ĺ���
**  date           :  2013.11.11
**
**  version       :  1.0
**  author        :  sven
********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "debug.h"
#include "const.h"
#include "mutex.h"
#include "message.h"
#include "malloc.h"   
#include "crc.h"
#include "linuxFile.h"
#include "flash.h"
#include "confFile.h"

#include "logfile.h"


// ��64KB���� (FLASH�������64KB����)
static const int	SECTOR_SIZE	    = 64*1024;


static CMutexLock 	s_FlashMutex;

/*******************************************************************************
* fn: ��ȡflash ����ͨ�ú���
* mtd: mtd ����, ����FLASH_DEVICE_CONFIG
* offset: �Ӹ÷�����ƫ���Ǹ��ط���ʼ��ȡ
* pData: out, ��Ŷ�ȡ��������
* nLen: Ҫ��ȡ�೤������
********************************************************************************/
int ReadFlash( char *mtd, int offset, char *pData, int nLen )
{
	int nRet = -1;
	s_FlashMutex.Lock();
	nRet = mtd_read( mtd, offset, nLen, pData );
	s_FlashMutex.Unlock();
	return nRet;
}

/********************************************************************************
* fn: д���ݵ�flash ͨ�ú���
* mtd: mtd ����, ����FLASH_DEVICE_CONFIG
* offset: �Ӹ÷�����ƫ���Ǹ��ط���ʼд��
* pData: ָ��Ҫд�������
* nLen: Ҫд��೤������
* ˵��: д���ʱ��һ�β���һ������(���flash������ΪSECTOR_SIZE),
    	д��ǰ�ȶ�����,�������һ��,�򲻲���; �������Ȳ���,Ȼ��д��
* ����: -1,����ʧ��; 0,�����ɹ�,��Ҫд������ݺ�flash �����һ��,û������д��;
    	1,�����ɹ�,����������дflash�Ķ���
*********************************************************************************/
int WriteFlash( char *mtd, int offset, char *pData, int nLen )
{
	int i = 0, j = 0, nRet = -1;    
	int start = offset / SECTOR_SIZE * SECTOR_SIZE;

	char *pWriteData = ( char * )Malloc( SECTOR_SIZE );
	char *pReadData = ( char * )Malloc( SECTOR_SIZE );
	if ( pWriteData == NULL || pReadData == NULL )
    {
    	Free( pWriteData );
    	Free( pReadData );
    	return nRet;
    }
    
	s_FlashMutex.Lock();
	SVPrint( "<WriteFlash: mtd=%s, offset=%X, len=%d>\r\n", mtd, offset, nLen );
	if ( offset >= 0 && nLen > 0 && pData ) 
    {
    	nRet = 0;
    	offset -= start;
    	while ( nLen > 0 )
        {
        	int len = nLen;
        	if ( (offset+len) > SECTOR_SIZE ) len = SECTOR_SIZE-offset;

        	mtd_read( mtd, start, SECTOR_SIZE, pWriteData );
        	if ( memcmp(pWriteData+offset, pData, len) )
            {
            	nRet = 1;
            	memcpy( pWriteData+offset, pData, len );
            	for ( j = 0; j < 10; j++ )
                {        
                	for ( i = 0; i < 10; i++ )
                    {
                    	if ( mtd_erase(mtd, start, SECTOR_SIZE) == 0 ) break;
                    }
                	if ( i == 10 )
                    {
                    	SVPrint( "Erase flash partion %s offset %08X fail\r\n", mtd, start );
                    	nRet = -1;
                    	break;
                    }
                    
                	if ( mtd_write( mtd, start, SECTOR_SIZE, pWriteData ) == 0 ) 
                    {
                    	mtd_read( mtd, start, SECTOR_SIZE, pReadData );
                    	if( memcmp( pWriteData, pReadData, SECTOR_SIZE ) == 0 ) break;
                    }
                }
            	if ( nRet == -1 ) break;
            	if ( j == 10 )
                {
                	SVPrint( "Write flash partion %s offset %08X fail\r\n", mtd, start );
                	nRet = -1;
                	break;
                }
                
            	Print( "." );
            	fflush( stderr );
            	usleep( 20*1000 );
            }
        	else
            {
            	Print( "*" );
            	fflush( stderr );
            	usleep( 20*1000 );
            }
        	start += SECTOR_SIZE;
        	pData += len;
        	nLen -= len;
        	offset = 0;
        }
    	Print( "\r\n" );
    }

	SVPrint( "<WriteFlash: mtd=%s, offset=%X, len=%d>, nRet(%d)!\r\n", 
                                        	mtd, offset, nLen, nRet );
	s_FlashMutex.Unlock();
    
	Free( pWriteData );
	Free( pReadData );
    
	return nRet;
}

/*****************************************************************************************
* fn: ����дflash �����ͽ���,��WriteFlash �������ڴ˺������дflash�Ľ��ȣ�����Ϣ����ʽ���͸��������罻���߳�
* mtd: Ҫд��flash �豸��
* offset: д�����ʼƫ�Ƶ�ַ
* pData: Ҫд�����ݻ�����
* nLen: д�볤��
* totalLen: �ܳ���, д�볤��<= �ܳ���, ����ͳ�ưٷ���.
********************************************************************************/
int WriteFlashSendProgress( char *mtd, int offset, char *pData, int nLen, int totalLen )
{
	int i = 0, j = 0, nRet = -1;    
	int start = offset / SECTOR_SIZE * SECTOR_SIZE;
    int totalPercent = (totalLen + SECTOR_SIZE -1) / SECTOR_SIZE;
    int curPercent = 0;

    // ���͵����������̵߳���Ϣ, ����Ϊ����, ����Ϊ���Ȱٷ���
    WRITE_FLASH_MSG_T wfm;
    wfm.msgType = WRITE_FLASH_MSG_PROGRESS;
    wfm.msgData = 0;

	char *pWriteData = ( char * )Malloc( SECTOR_SIZE );
	char *pReadData = ( char * )Malloc( SECTOR_SIZE );
	if ( pWriteData == NULL || pReadData == NULL )
    {
    	Free( pWriteData );
    	Free( pReadData );
    	return nRet;
    }
    
	s_FlashMutex.Lock();
	SVPrint( "<WriteFlash: mtd=%s, offset=%X, len=%d>\r\n", mtd, offset, nLen );
	if ( offset >= 0 && nLen > 0 && pData ) 
    {
    	nRet = 0;
    	offset -= start;
    	while ( nLen > 0 )
        {
        	int len = nLen;
        	if ( (offset+len) > SECTOR_SIZE ) len = SECTOR_SIZE-offset;

        	mtd_read( mtd, start, SECTOR_SIZE, pWriteData );
        	if ( memcmp(pWriteData+offset, pData, len) )
            {
            	nRet = 1;
            	memcpy( pWriteData+offset, pData, len );
            	for ( j = 0; j < 10; j++ )
                {        
                	for ( i = 0; i < 10; i++ )
                    {
                    	if ( mtd_erase(mtd, start, SECTOR_SIZE) == 0 ) break;
                    }
                	if ( i == 10 )
                    {
                    	SVPrint( "Erase flash partion %s offset %08X fail\r\n", mtd, start );
                    	nRet = -1;
                    	break;
                    }
                    
                	if ( mtd_write( mtd, start, SECTOR_SIZE, pWriteData ) == 0 ) 
                    {
                    	mtd_read( mtd, start, SECTOR_SIZE, pReadData );
                    	if( memcmp( pWriteData, pReadData, SECTOR_SIZE ) == 0 ) break;
                    }
                }
            	if ( nRet == -1 ) break;
            	if ( j == 10 )
                {
                	SVPrint( "Write flash partion %s offset %08X fail\r\n", mtd, start );
                	nRet = -1;
                	break;
                }
                
            	Print( "." );
            	fflush( stderr );
            	usleep( 20*1000 );
            }
        	else
            {
            	Print( "*" );
            	fflush( stderr );
            	usleep( 20*1000 );
            }
        	start += SECTOR_SIZE;
        	pData += len;
        	nLen -= len;
        	offset = 0;
            curPercent += 100;
            wfm.msgData = curPercent / totalPercent;
            MessageSend(MSG_ID_SYS_UPDATE_PRO, (char *)&wfm, sizeof(wfm));
        }
    	Print( "\r\n" );
    }

	SVPrint( "<WriteFlash: mtd=%s, offset=%X, len=%d>, nRet(%d)!\r\n", 
                                        	mtd, offset, nLen, nRet );
	s_FlashMutex.Unlock();
    
	Free( pWriteData );
	Free( pReadData );
    
	return nRet;
}

/*******************************************************************************
* fn: �˺����� WriteFlashImp() ���ʹ��,��ֹ��ǰ�߳�ʹ��WriteFlash() �������ӳ�
* mtd: mtd ����, ����FLASH_DEVICE_CONFIG
* offset: �Ӹ÷�����ƫ���Ǹ��ط���ʼд��
* pData: ָ��Ҫд�������
* nLen: Ҫд��೤������
********************************************************************************/
int WriteFlashMsg( char *mtd, int offset, char *pData, int nLen )
{
	int	    	nRet	= -1;
	FLASH_MSG	flash	= { 0 };

	if ( pData != NULL && nLen > 0 )
    {
    	flash.mtd	    = mtd;
    	flash.offset	= offset;
    	flash.data	    = ( char * )Malloc( sizeof(char) * nLen );
    	flash.len	    = nLen;

    	if ( flash.data != NULL )
        {
        	memcpy( flash.data, pData, nLen );
        	nRet = MessageSend( MSG_ID_WRITE_FLASH, (char *)&flash, sizeof(flash) );
        }
    	else
        {
        	nRet = WriteFlash( mtd, offset, pData, nLen );
        }
    }
	return nRet;
}

void *WriteFlashImp( void *args )
{
	FLASH_MSG flash = { 0 };

	if ( MessageRecv( MSG_ID_WRITE_FLASH, (char *)&flash, sizeof(flash) ) > 0 )
    {
    	if ( flash.data != NULL && flash.len > 0 )
        {
        	WriteFlash( flash.mtd, flash.offset, flash.data, flash.len );
        	Free( flash.data );
        }
    }
	return NULL;
}

#define USEFLASH  //use flash or not
//
// ϵͳ����
//
#ifdef USEFLASH
static int ReadConfigFlash( char* pConfigBuf, int nBufLen )
{
	int nRet = -1;
	if ( pConfigBuf == NULL || nBufLen < 0 || nBufLen > FLASH_SIZE_CONFIG )
    {
    	SVPrint( "ReadConfig parameter error !\r\n" );
    	return nRet;
    }
	SVPrint( "ReadConfig, please wait ...\r\n" );
	nRet = ReadFlash( (char *)FLASH_DEVICE_CONFIG, FLASH_OFFSET_CONFIG, pConfigBuf, nBufLen );
	SVPrint( "ReadConfig %s !\r\n", nRet >= 0 ? "OK" : "FAIL" );    
	return nRet >= 0 ? 0 : -1;
}
#endif

int ReadConfig( char* pConfigBuf, int nBufLen )
{
	int ret;
#ifdef USEFLASH
	ret = ReadConfigFlash( pConfigBuf, nBufLen );
#else
	ret = ConfFileRead( pConfigBuf, nBufLen );
#endif
	return ret;
}

//
// �ӱ��ݷ�����ϵͳ����
//
int ReadConfigBackup( char* pConfigBuf, int nBufLen )
{
	int nRet = -1;
	if ( pConfigBuf == NULL || nBufLen < 0 || nBufLen > FLASH_SIZE_CONFIG )
    {
    	SVPrint( "ReadConfig parameter backup error !\r\n" );
    	return nRet;
    }
	SVPrint( "ReadConfig backup, please wait ...\r\n" );
	nRet = ReadFlash( (char *)FLASH_DEVICE_CONFIG, FLASH_OFFSET_CONFIG_BACKUP, pConfigBuf, nBufLen );
	SVPrint( "ReadConfig backup nRet(%d) !\r\n", nRet );    
    
	return nRet >= 0 ? 0 : -1;
}

#ifdef USEFLASH
static int WriteConfigFlash( char* pConfigBuf, int nBufLen )
{
	int nRet = -1;
	if ( pConfigBuf == NULL || nBufLen < 0 || nBufLen > FLASH_SIZE_CONFIG )
    {
    	SVPrint( "WriteConfig parameter error !\r\n" );
    	return nRet;
    }
	SVPrint( "WriteConfig, please wait ...\r\n" );
	nRet = WriteFlash( (char *)FLASH_DEVICE_CONFIG, FLASH_OFFSET_CONFIG, pConfigBuf, nBufLen );
	SVPrint( "WriteConfig %s !\r\n", nRet >= 0 ? "OK" : "FAIL" );
    
	return nRet >= 0 ? 0 : -1;
}
#endif

int WriteConfig( char* pConfigBuf, int nBufLen )
{
	int ret;
#ifdef USEFLASH
	ret = WriteConfigFlash( pConfigBuf, nBufLen );
#else
	ret = ConfFileWrite( pConfigBuf, nBufLen );
#endif
	return ret;
}


int WriteConfigBackup( char* pConfigBuf, int nBufLen )
{
	int nRet = -1;
	if ( pConfigBuf == NULL || nBufLen < 0 || nBufLen > FLASH_SIZE_CONFIG )
    {
    	ERRORPRINT( "WriteConfig parameter error !\r\n" );
    	return nRet;
    }
	//SVPrint( "WriteConfig, please wait ...\r\n" );
	nRet = WriteFlashMsg( (char *)FLASH_DEVICE_CONFIG, FLASH_OFFSET_CONFIG_BACKUP, 
                                                        	pConfigBuf, nBufLen );
	//SVPrint( "WriteConfig %s !\r\n", nRet >= 0 ? "OK" : "FAIL" );
    
	return nRet >= 0 ? 0 : -1;
}

int WriteConfigMsg( char* pConfigBuf, int nBufLen )
{
	int nRet = -1;
	if ( pConfigBuf == NULL || nBufLen < 0 || nBufLen > FLASH_SIZE_CONFIG )
    {
    	SVPrint( "WriteConfigMsg parameter error !\r\n" );
    	return nRet;
    }
	SVPrint( "WriteConfigMsg, please wait ...\r\n" );
	nRet = WriteFlashMsg( (char *)FLASH_DEVICE_CONFIG, FLASH_OFFSET_CONFIG, pConfigBuf, nBufLen );
	SVPrint( "WriteConfigMsg %s !\r\n", nRet >= 0 ? "OK" : "FAIL" );
	return nRet >= 0 ? 0 : -1;
}

//
//ϵͳ��־
//
#ifdef USEFLASH
static int ReadLogFlash( char* pLogBuf, int nBufLen )
{
	int nRet = -1;
	if ( pLogBuf == NULL || nBufLen < 0 || nBufLen > FLASH_SIZE_LOG )
    {
    	SVPrint( "ReadLog parameter error !\r\n" );
    	return nRet;
    }
	SVPrint( "ReadLog, please wait ...\r\n" );
	nRet = ReadFlash( (char *)FLASH_DEVICE_LOG, FLASH_OFFSET_LOG, pLogBuf, nBufLen );
	SVPrint( "ReadLog %s !\r\n", nRet >= 0 ? "OK" : "FAIL" );    
	return nRet >= 0 ? 0 : -1;
}
#endif

int ReadLog( char* pLogBuf, int nBufLen )
{
	int ret;
#ifdef USEFLASH
	ret = ReadLogFlash( pLogBuf, nBufLen );
#else
    ret = LogFileRead( pLogBuf, nBufLen );
#endif
	return ret;
}

int ReadLogBackup( char* pLogBuf, int nBufLen )
{
	int nRet = -1;
	if ( pLogBuf == NULL || nBufLen < 0 || nBufLen > FLASH_SIZE_LOG )
    {
    	SVPrint( "ReadLogBackup parameter error !\r\n" );
    	return nRet;
    }
	SVPrint( "ReadLogBackup, please wait ...\r\n" );
	nRet = ReadFlash( (char *)FLASH_DEVICE_LOG, FLASH_OFFSET_LOG_BACKUP, pLogBuf, nBufLen );
	SVPrint( "ReadLog %s !\r\n", nRet >= 0 ? "OK" : "FAIL" );    
	return nRet >= 0 ? 0 : -1;
}

#ifdef USEFLASH
static int WriteLogFlash( char* pLogBuf, int nBufLen )
{
	int nRet = -1;
	if ( pLogBuf == NULL || nBufLen < 0 || nBufLen > FLASH_SIZE_LOG )
    {
    	SVPrint( "WriteLog parameter error !\r\n" );
    	return nRet;
    }
	SVPrint( "WriteLog, please wait ...\r\n" );
	nRet = WriteFlash( (char *)FLASH_DEVICE_LOG, FLASH_OFFSET_LOG, pLogBuf, nBufLen );
	SVPrint( "WriteLog %s !\r\n", nRet >= 0 ? "OK" : "FAIL" );
    
	return nRet >= 0 ? 0 : -1;
}
#endif

int WriteLog( char* pLogBuf, int nBufLen )
{
	int ret;
#ifdef USEFLASH
	ret = WriteLogFlash( pLogBuf, nBufLen );
#else
    //ret = ConfFileWrite( pLogBuf, nBufLen );
    ret = LogFileWrite(pLogBuf, nBufLen );
#endif
	return ret;
}

int WriteLogBackup( char* pLogBuf, int nBufLen )
{
#ifdef USEFLASH
	int nRet = -1;
	if ( pLogBuf == NULL || nBufLen < 0 || nBufLen > FLASH_SIZE_LOG )
    {
    	SVPrint( "WriteLogBackup parameter error !\r\n" );
    	return nRet;
    }
	SVPrint( "WriteLogBackup, please wait ...\r\n" );
	nRet = WriteFlash( (char *)FLASH_DEVICE_LOG, FLASH_OFFSET_LOG_BACKUP, pLogBuf, nBufLen );
	SVPrint( "WriteLog %s !\r\n", nRet >= 0 ? "OK" : "FAIL" );
    
	return nRet >= 0 ? 0 : -1;
#else

    return 0;

#endif

}

int WriteLogMsg( char* pLogBuf, int nBufLen )
{
	int nRet = -1;
	if ( pLogBuf == NULL || nBufLen < 0 || nBufLen > FLASH_SIZE_LOG )
    {
    	SVPrint( "WriteLogMsg parameter error !\r\n" );
    	return nRet;
    }
	SVPrint( "WriteLogMsg, please wait ...\r\n" );
	nRet = WriteFlashMsg( (char *)FLASH_DEVICE_LOG, FLASH_OFFSET_LOG, pLogBuf, nBufLen );
	SVPrint( "WriteLogMsg %s !\r\n", nRet >= 0 ? "OK" : "FAIL" );
	return nRet >= 0 ? 0 : -1;
}


/*
* function: ����u-boot������
*/
void EraseUbootEnv()
{
	int i, ret;
    
	s_FlashMutex.Lock();
	for( i = 0; i < 10; i++ )
    {
    	ret = mtd_erase( FLASH_DEVICE_UBOOT, FLASH_OFFSET_UBOOT_ENV, FLASH_SIZE_UBOOT_ENV );        
    	if( ret == 0 )	break;        
    }    
    
	s_FlashMutex.Unlock();
	Print( "\r\nErase Uboot Env %s !\r\n", (ret == 0) ? "OK" : "FAIL" );    
}

int UpgradeUBoot( char *pData, int nLen )
{
	int nRet = -1;
#if 1
    int offset;
    int align;
    int end;
    int totalPercent = (FLASH_SIZE_UBOOT_BIN + SECTOR_SIZE -1) / SECTOR_SIZE;
    int curPercent = 0;

    // ���͵����������̵߳���Ϣ, ����Ϊ����, ����Ϊ���Ȱٷ���
    WRITE_FLASH_MSG_T wfm;
    wfm.msgType = WRITE_FLASH_MSG_PROGRESS;
    wfm.msgData = 0;
#endif
	if ( 0 < nLen && nLen <= FLASH_SIZE_UBOOT_BIN )
    {
    	Print( "Upgrading uboot, please wait ...\r\n" );
    	nRet = WriteFlashSendProgress( (char *)FLASH_DEVICE_UBOOT, FLASH_OFFSET_UBOOT_BIN, pData, nLen, FLASH_SIZE_UBOOT_BIN );
    	Print( "\r\nUpgrading uboot %s !\r\n", (nRet >= 0) ? "OK" : "FAIL" );
    }
    // ���д�벻�� FLASH_SIZE_UBOOT_BIN, û��д��������.
#if 1
    if(nRet != -1)
    {
        offset = FLASH_OFFSET_UBOOT_BIN + nLen;
        align = offset % SECTOR_SIZE;
        end = FLASH_OFFSET_UBOOT_BIN + FLASH_SIZE_UBOOT_BIN;
        if(align != 0)
        {
            offset = offset + SECTOR_SIZE - align;
        }
        curPercent = ((nLen + SECTOR_SIZE - 1) / SECTOR_SIZE) * 100;
        for(; offset < end; offset += SECTOR_SIZE)
        {
            mtd_erase((char *)FLASH_DEVICE_UBOOT, offset, SECTOR_SIZE);
            curPercent += 100;
            wfm.msgData = curPercent / totalPercent;
            MessageSend(MSG_ID_SYS_UPDATE_PRO, (char *)&wfm, sizeof(wfm));
        }
    }
#endif
	return nRet;
}

int UpgradeKernel( char *pData, int nLen )
{
	int nRet = -1;
	if ( 0 < nLen && nLen <= FLASH_SIZE_KERNEL )
    {
    	Print( "Upgrading kernel, please wait ...\r\n" );
    	nRet = WriteFlashSendProgress( (char *)FLASH_DEVICE_KERNEL, FLASH_OFFSET_KERNEL, pData, nLen, nLen );
    	Print( "\r\nUpgrading kernel %s !\r\n", (nRet >= 0) ? "OK" : "FAIL" );
    }
	return nRet;
}

// cramfs ����ȫ��������jffs2��Ҫ
#define ERASEALL 0   //�Ƿ���Ҫ����ȫ��������
int UpgradeRootfs( char *pData, int nLen )
{
	int nRet = -1;
#if ERASEALL
    int offset;
    int align;
    int end;
    int totalPercent = (FLASH_SIZE_ROOTFS + SECTOR_SIZE -1) / SECTOR_SIZE;
    int curPercent = 0;

    // ���͵����������̵߳���Ϣ, ����Ϊ����, ����Ϊ���Ȱٷ���
    WRITE_FLASH_MSG_T wfm;
    wfm.msgType = WRITE_FLASH_MSG_PROGRESS;
    wfm.msgData = 0;
#endif
	if ( 0 < nLen && nLen <= FLASH_SIZE_ROOTFS )
    {
    	Print( "Upgrading file system, please wait ...\r\n" );
#if ERASEALL
    	nRet = WriteFlashSendProgress( (char *)FLASH_DEVICE_ROOTFS, FLASH_OFFSET_ROOTFS, pData, nLen, FLASH_SIZE_ROOTFS );
#else
    	nRet = WriteFlashSendProgress( (char *)FLASH_DEVICE_ROOTFS, FLASH_OFFSET_ROOTFS, pData, nLen, nLen );
#endif
    	Print( "\r\nUpgrading file system %s\r\n", (nRet >= 0) ? "OK" : "FAIL" );
    }
#if ERASEALL
    // ���д�벻�� FLASH_SIZE_ROOTFS, û��д��������.
    if(nRet != -1)
    {
        offset = FLASH_OFFSET_ROOTFS + nLen;
        align = offset % SECTOR_SIZE;
        end = FLASH_OFFSET_ROOTFS + FLASH_SIZE_ROOTFS;
        if(align != 0)
        {
            offset = offset + SECTOR_SIZE - align;
        }
        curPercent = ((nLen + SECTOR_SIZE - 1) / SECTOR_SIZE) * 100;
        for(; offset < end; offset += SECTOR_SIZE)
        {
            mtd_erase((char *)FLASH_DEVICE_ROOTFS, offset, SECTOR_SIZE);
            curPercent += 100;
            wfm.msgData = curPercent / totalPercent;
            MessageSend(MSG_ID_SYS_UPDATE_PRO, (char *)&wfm, sizeof(wfm));
        }
    }
#endif
	return nRet;
}

static CMutexLock s_UbootMutex;
char* GetUbootEnv( char* pEnv )
{
	int ret;
	static char	ubootEnv[FLASH_SIZE_UBOOT_ENV]    = { 0 };
	int	    	ubootLen	                    = 0;
	char *    	p	                            = ubootEnv;
    
	CMutexLockGuard lock( s_UbootMutex );
	memset( ubootEnv, 0, sizeof(ubootEnv) );
	if ( pEnv != NULL )
    {
    	ret = ReadFlash( (char *)FLASH_DEVICE_UBOOT_ENV, FLASH_OFFSET_UBOOT_ENV, ubootEnv, FLASH_SIZE_UBOOT_ENV );
    	if( 0 != ret )
        {
        	return NULL;
        }
    	for ( ubootLen = 0; ubootLen < (FLASH_SIZE_UBOOT_ENV-1); ++ubootLen )
        {
        	if ( ubootEnv[ubootLen]=='\0' && ubootEnv[ubootLen+1]=='\0' ) break;
        }
    	if ( ubootLen ) ubootLen++;
        
    	int len = strlen( pEnv );
    	int i = 4;
    	while ( ubootEnv[i] ) 
        {
        	if ( memcmp(ubootEnv+i, pEnv, len) == 0 && ubootEnv[i+len]=='=' ) break;
        	i += strlen(ubootEnv+i)+1;
        }

    	if( i < ubootLen ) 
        {
        	p = ubootEnv + i + len + 1;
        }
    	else 
        {
        	ubootEnv[0] = '\0';
        	p = NULL;
        }
    }

	return p;
}

int SetUbootEnv( char* pEnv )
{
	int	    	nRet	                = -1;
	char *    	ubootEnv	            = NULL;
	int     	ubootLen	            = 0;
	bool		bChanged	            = false;
	char		name[256]                = { 0 };

	ubootEnv = ( char * )Calloc( 1, FLASH_SIZE_UBOOT_ENV );
	if ( ubootEnv == NULL ) return nRet;
    
	CMutexLockGuard lock( s_UbootMutex );
	nRet = ReadFlash( (char *)FLASH_DEVICE_UBOOT_ENV, FLASH_OFFSET_UBOOT_ENV,
                    	ubootEnv, FLASH_SIZE_UBOOT_ENV );
	if ( nRet == 0 )
    {
    	unsigned long crcOld = 0;
    	unsigned long crcVal = 0;
    	crcVal = CRC32( (unsigned char *)(ubootEnv+4), FLASH_SIZE_UBOOT_ENV-4 );
    	memcpy( &crcOld, ubootEnv, 4 );
    	if ( crcVal != crcOld )
        {
        	SVPrint( "failed: crc failed with u-boot env!\r\n" );
        	return nRet;
        }
    }    
	else
    {
    	SVPrint( "SetUbootEnv failed: ReadFlash return -1\r\n" );
    	Free( ubootEnv );
    	return nRet;
    }
    
	for ( ubootLen = 0; ubootLen < (FLASH_SIZE_UBOOT_ENV-1); ++ubootLen ) 
    {
    	if ( ubootEnv[ubootLen]=='\0' && ubootEnv[ubootLen+1]=='\0' ) 
        	break;
    }
    
	if ( ubootLen ) ubootLen++;
	if ( pEnv != NULL ) 
    {
    	while ( *pEnv != '\0' ) 
        {
        	char *p = strstr( pEnv, "=" );
        	if ( p == NULL || p == pEnv ) break;
        	int len = p - pEnv;
        	if ( len > 255 ) break;
            
        	memcpy( name, pEnv, len );
        	name[len] = 0;

        	int i = 4;
        	while ( ubootEnv[i] ) 
            {
            	if ( memcmp(ubootEnv+i, name, len) == 0 && ubootEnv[i+len]=='=' ) break;
            	i += strlen(ubootEnv+i) + 1;
            }
        	if ( i < ubootLen ) 
            {
            	len = strlen(ubootEnv+i) + 1;
            	if ( strcmp(ubootEnv+i, pEnv) ) 
                { 
                	ubootLen -= len;
                	memmove( ubootEnv+i, ubootEnv+i+len, ubootLen-i );
                	i = ubootLen;
                }
            }
        	len = strlen(pEnv) + 1;
        	if ( i >= ubootLen ) 
            {
            	memcpy( ubootEnv + ubootLen, pEnv, len );
            	ubootLen += len;
            	ubootEnv[ubootLen] = '\0';
            	bChanged = true;
            }
        	pEnv += len;
        }
    }

	if ( bChanged ) 
    {
    	unsigned long crc32 = CRC32( (unsigned char *)(ubootEnv+4), FLASH_SIZE_UBOOT_ENV-4 );
    	memcpy( ubootEnv, &crc32, 4 );
    	nRet = WriteFlash( (char *)FLASH_DEVICE_UBOOT_ENV, FLASH_OFFSET_UBOOT_ENV,
                        	ubootEnv, FLASH_SIZE_UBOOT_ENV );
    }

	Free( ubootEnv );
	return nRet;
}

