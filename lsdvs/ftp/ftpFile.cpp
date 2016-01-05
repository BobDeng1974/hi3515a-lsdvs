/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.09.16
**  description  : ����ftpLib �ӿڷ�װ���ļ��ϴ�����,
            	ftp Э�������������ģ�һ������ָ�����; ����һ�����ڴ�������
*******************************************************************************
*/

#include <stdio.h>
#include "debug.h"
#include "ftpLib.h"
#include "ftpFile.h"
#include "netSocket.h"

/*
* fn: ��ʼ��һ��ftp ����, ��½ftp ������
* host: ��Ҫ��õ�ַ����
* user: ��½ftp ���������û���
* pass: ��½ftp ������������
* nControl: out, �ɹ���½��õ��Ŀ���������
*/
int FtpFileInit( const char *host, const char *user, const char *pass, netbuf **nControl )
{
	if( host == NULL || user == NULL || pass == NULL )
    	return -1;
    
	if( FtpConnect(host, nControl) != 1 )
    {
    	SVPrint("connect host %s fail!\r\n", host);
    	return -1;
    }
	if( FtpLogin(user, pass, *nControl) != 1 )
    {
    	SVPrint( "login fail!\r\n" );
    	return -1;
    }
	return 0;
}

/*
* fn: �˳�ftp ������
* nControl: FtpFileInit() �ɹ����غ�õ��Ŀ���������
*/
int FtpFileQuit( netbuf *nControl )
{
	if( nControl == NULL )
    {
    	return -1;
    }
    
	FtpQuit( nControl );
	return 0;
}

/*
* fn: ��ftp�������´�һ���ļ�
* path: ftp ��������Ҫ�򿪵��ļ���
* typ: FtpAccess() type codes, �ο�ftpLib.h
* nControl: FtpFileInit() �ɹ����غ�õ��Ŀ���������
* nData: out, �ļ��ɹ��󷵻ص����ݴ���������
* dirChangFlag: path �Ƿ�ֻ�����ļ���, 0, �ǵ�,����Ҫ�ı�Ŀ¼; 1,����,��Ҫ�ı�Ŀ¼
*/
int FtpFileOpen( const char *path, int typ, netbuf *nControl, netbuf **nData, int dirChangFlag )
{
	char dir[256] = {0};
	char *pTargetDir = NULL;
	unsigned int i;
	int mode = 'I';

	if( path == NULL || nControl == NULL || nData == NULL )
    {
    	return -1;
    }
	strncpy( dir, path, sizeof(dir)-1 );
	pTargetDir = dir;
	if( dirChangFlag == 1 )    
    {
    	for( i = 0; i < strlen(path); i++ )
        {
        	if( dir[i] == '/' )
            {
            	dir[i] = 0x00;
            	if( FtpChdir(pTargetDir, nControl) != 1 )
                {
                	if( FtpMkdir(pTargetDir, nControl) != 1 )
                    {
                    	SVPrint( "mkdir %s fail \r\n", pTargetDir );
                    	return -1;
                    }
                	if( FtpChdir(pTargetDir, nControl) != 1 )
                    {
                    	SVPrint( "chdir %s fail \r\n", pTargetDir );
                    	return -1;
                    }
                }

            	pTargetDir = &dir[i+1];
            }
        } // for( i = 0; i < strlen(path)                    
    }
	else
    {
    	for(i = strlen(dir)-1; i >= 0; i--)
        {
        	if( dir[i] == '/' )
            {
               pTargetDir = &dir[i+1];
               break;
            }
        }
    }
	if( !FtpAccess(pTargetDir, typ, mode, nControl, nData) )
    {
    	SVPrint("open ftp file fail!\n");
    	return -1;
    }
	return 0;
}

/*
* fn: ��ftp ������д����
* buf: ����buf
* len: ���ݳ���
* nData: FtpFileOpen() �ɹ����غ�õ�������������
*/
int FtpFileWrite( void *buf, int len, netbuf *nData )
{
	int ret;
	if ( buf == NULL || nData == NULL )
    {
    	return -1;
    }
	ret = SelectWrite( nData->handle, 0 );
	if( ret > 0 )
    {    
    	ret = FtpWrite( buf, len, nData );
    }

	return ret;
}

/*
* fn: ��ftp ������������
* buf: ����buf
* len: ���ݳ���
* nData: FtpFileOpen() �ɹ����غ�õ�������������
*/
int FtpFileRead( void *buf, int max, netbuf *nData )
{
	return 0;
}

/*
* fn: �رղ������ļ�
* nControl: FtpFileInit() �ɹ����غ�õ��Ŀ���������
* nData: FtpFileOpen() �ɹ����غ�õ�������������
*/
int FtpFileClose( netbuf *nControl, netbuf *nData )
{
	if( nData == NULL )
    {
    	return -1;
    }
    
	FtpClose( nData );    
	if( readresp('2', nControl) != 1 )
    {
    	return -1;
    }
	return 0;
}

