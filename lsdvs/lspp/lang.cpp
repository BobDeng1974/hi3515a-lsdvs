/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ���ļ�ʵ���˶Զ����Խ���֧�ֵ������
**  date           :  2013.11.11
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "debug.h"
#include "malloc.h"
#include "strSafe.h"
#include "lang.h"

void CLang::ClearCfg( LP_LANGCFG *ppLangCfg )
{
	if ( ppLangCfg ) 
    {
    	for ( int i = 0; i < m_nLangNum; i++ )
        {
        	Free( ppLangCfg[i]->fontLib );
        	Free( ppLangCfg[i]->charSet );
        	Free( ppLangCfg[i]->langFile );
        	Free( ppLangCfg[i]->langSufix );
        	Free( ppLangCfg[i]->langName );
        	Free( ppLangCfg[i] );
        }
    	Free( ppLangCfg );
    }    
}

/*
** ��ȡ���������ļ�
** �����ļ���ʽ: ����ID=�ֿ�����,�ַ�������,���԰�����,���Ժ�׺,��������
*/
int CLang::ReadCfg( char *cfgFile )
{
	int nRet = -1;
	char *pCfgBuf = NULL;
     
	int len = ReadFile( &pCfgBuf, cfgFile );
	if ( len > 0 && pCfgBuf != NULL )
    {
    	int lineCnt = 0;

        // ���������ļ�����
    	for( char *pCfgTmp = pCfgBuf; pCfgTmp != NULL; pCfgTmp++ )
        {
        	pCfgTmp = strchr( pCfgTmp, '\n' );
        	if ( pCfgTmp != NULL ) lineCnt++;
        	else break;
        }

    	if ( lineCnt > 0 )
        {
        	if ( m_ppLangCfg ) ClearCfg( m_ppLangCfg );
        	m_ppLangCfg = ( LP_LANGCFG * )Malloc( lineCnt * sizeof(LP_LANGCFG) );
        	if ( m_ppLangCfg )
            {
            	for ( int i = 0; i < lineCnt; i++ ) m_ppLangCfg[i] = NULL;

            	char *pCfg = pCfgBuf;
            	char *pLine = NULL;
            	int langCnt = 0;
            	while ( (langCnt < lineCnt) && (pLine = GetLine( &pCfg )) )
                {
                	m_ppLangCfg[langCnt] = GetLangCfg( pLine );
                	if ( m_ppLangCfg[langCnt] != NULL ) langCnt++;
                	Free( pLine );
                }
                
            	if ( langCnt > 0 ) // ��ȡ�����ļ��ɹ�
                {
                	m_nLangNum = langCnt;
                	nRet = 0;
                	FiPrint( "Load language config file success !\r\n" );                    
                }
            }
        	else
            {
            	FiPrint( "Load language config file error: Malloc memory failed !\r\n" );                
            }
        }
    }
	else
    {
    	if ( len == 0 )
        	FiPrint( "Load language config file error: Empty file !\r\n" );
    	else if ( len == -1 )
        	FiPrint( "Load language config file error: Read file error !\r\n" );
    	else
        	FiPrint( "Load language config file error: Malloc memory failed !\r\n" );
    }
    
	Free( pCfgBuf );
	return nRet;
}

/*
** �����԰���ȡ����ϣ����
*/
int CLang::LoadLangFile( char *file )
{
	int nRet = -1;
	char *pLangBuf = NULL;

    // �����԰��е����ݱ��浽��������
	int len = ReadFile( &pLangBuf, file );

	if ( len > 0 && pLangBuf != NULL )
    {
    	m_lang.Clear(); // ��չ�ϣ��

    	char *pKey = NULL;
    	char *pVal = NULL;
    	char *pLine = NULL;

    	char *pLang = pLangBuf;

        // �ӻ������з�����ȡһ������
        // ���Ӹ�����������ȡ�ؼ��ֺ�ֵ���浽��ϣ����
    	while ( (pLine = GetLine( &pLang )) != NULL )
        {
        	GetKeyVal( &pKey, &pVal, pLine );
        	if ( pKey != NULL && pVal != NULL ) m_lang.Put( pKey, pVal );
        	Free( pLine );
        }

    	nRet = 0;
    }
	else
    {
    	if ( len == 0 )
        	FiPrint( "Load language file error: Empty file !\r\n" );
    	else if ( len == -1 ) 
        	FiPrint( "Load language file error: Read file error !\r\n" );
    	else
        	FiPrint( "Load language file error: Malloc memory failed !\r\n" );
    }
    
	Free( pLangBuf );
	return nRet;
}

/* �����ļ���ʽ: ����ID=�ֿ�����,�ַ�������,���԰�����,���Ժ�׺,�������� */
LP_LANGCFG CLang::GetLangCfg( char *pCfgBuf )
{
	int flag = 1;
	if ( pCfgBuf == NULL ) return NULL;

	LP_LANGCFG pLangCfg = ( LP_LANGCFG )Malloc( sizeof( LANGCFG ) );
	if ( pLangCfg == NULL ) return NULL;

	pLangCfg->langID = 0;
	pLangCfg->fontLib = NULL;
	pLangCfg->charSet = NULL;
	pLangCfg->langFile = NULL;
	pLangCfg->langSufix = NULL;
	pLangCfg->langName = NULL;        

	int nBufLen = strlen(pCfgBuf) + 1;
    // ����һ�������ļ���Ϣ
	char *pCfgTmp = ( char * )Malloc( sizeof(char) * nBufLen );
	if ( pCfgTmp != NULL )
    {
    	strlcpy( pCfgTmp, pCfgBuf, nBufLen );

    	char *pTmp = pCfgTmp;
    	char *pStr = NULL;
        
        // ��ȡ����ID
    	if ( (flag == 1) && (pStr = strchr( pTmp, '=' )) )
        {
            *pStr = '\0';
            // ����ID������Ϊ��!
        	if ( pTmp[0] != '\0' )
            {
            	pLangCfg->langID = atoi( pTmp );
            	pTmp = ++pStr;
            }
        	else
            {
            	flag = 0;
            }
        }
    	else
        {
        	flag = 0;
        }
        
        // ��ȡ���������
    	if ( (flag == 1) && (pStr = strchr( pTmp, ',' )) )
        {
            *pStr = '\0';
            // �ֿ����Ʋ�����Ϊ��!
        	if( pTmp[0] != '\0' )
            {
            	pLangCfg->fontLib = StrCopy( pTmp );
            	if ( pLangCfg->fontLib ) pTmp = ++pStr;
            	else flag = 0;
            } 
        	else
            {
            	flag = 0;
            }
        }
    	else
        {
        	flag = 0;
        }

        // ��ȡ���������
    	if ( (flag == 1) && (pStr = strchr( pTmp, ',' )) )
        {
            *pStr = '\0';
        	pLangCfg->fontWidth = atoi( pTmp );
            // ���������ֻ����Ϊ1��2
        	if ( 1 <= pLangCfg->fontWidth && pLangCfg->fontWidth <= 2 ) pTmp = ++pStr;
        	else flag = 0;
        }
    	else
        {
        	flag = 0;
        }
        
        // ��ȡ�ַ�������
    	if ( (flag == 1) && (pStr = strchr( pTmp, ',' )) )
        {
            *pStr = '\0';
        	pLangCfg->charSet = StrCopy( pTmp );
        	if ( pLangCfg->charSet ) pTmp = ++pStr;
        	else flag = 0;
        }
    	else
        {
        	flag = 0;
        }
        
        // ��ȡ���԰�����
    	if ( (flag == 1) && (pStr = strchr( pTmp, ',' )) )
        {
            *pStr = '\0';

        	pLangCfg->langFile = StrCopy( pTmp );
        	if ( pLangCfg->langFile ) 
            {
                // ���԰����Ʋ�����Ϊ��
            	if ( pLangCfg->langFile[0] != '\0' ) pTmp = ++pStr;
            	else flag = 0;
            }
        	else
            {
            	flag = 0;
            }
        }
    	else
        {
        	flag = 0;
        }    
        
        // ��ȡ���Ժ�׺��
    	if ( (flag == 1) && (pStr = strchr( pTmp, ',' )) )
        {
            *pStr = '\0';
        	pLangCfg->langSufix= StrCopy( pTmp );
        	if ( pLangCfg->langSufix ) pTmp = ++pStr;
        	else flag = 0;
        }
    	else
        {
        	flag = 0;
        }
        
        // ��ȡ��������
    	if ( (flag == 1) && (pStr = strchr( pTmp, '\0' )) )
        {
            *pStr = '\0';
        	pLangCfg->langName = StrCopy( pTmp );
        	if ( pLangCfg->langName ) pTmp = ++pStr;
        	else flag = 0;
        }
    	else
        {
        	flag = 0;
        }

    	Free( pCfgTmp );
    }

	if ( flag == 0 )
    {
    	Free( pLangCfg->fontLib );
    	Free( pLangCfg->charSet );
    	Free( pLangCfg->langFile );    
    	Free( pLangCfg->langSufix );
    	Free( pLangCfg->langName );        
    	Free( pLangCfg ); 
    }

	return pLangCfg;
}

/* �ַ���������������̬�����ڴ汣�濽�����ַ��� */
char *CFile::StrCopy( const char *pStr ) 
{
	int len = strlen( pStr );
	char *pBuf = ( char * )Malloc( sizeof( char ) * ( len + 1 ) );
	if ( pBuf != NULL ) strlcpy( pBuf, pStr, len + 1 );
	return pBuf;
}

/*
** ���ļ����ݶ�ȡ������������������С������ļ���С�Զ�����ռ�
*/
int CFile::ReadFile( char **ppBuf, char *pFileName )
{
	int nRet = 0;
	struct stat st;

	if ( pFileName != NULL && stat( pFileName, &st ) == 0 ) 
    {
    	int len = st.st_size;
    	if ( len > 0 )
        {
            *ppBuf = ( char * )Malloc( sizeof(char) * (len + 1) );
        	if ( *ppBuf != NULL )
            {    
            	memset( *ppBuf, 0, sizeof(char) * (len + 1) );
            	int fd = open( pFileName,  O_RDONLY );
            	if ( read( fd, *ppBuf, len ) == len )
                {
                	nRet = len;
                }
            	else
                {
                	Free( *ppBuf );
                    *ppBuf = NULL;
                	nRet = -1;
                }
            	close( fd );
            }    
        	else
            {    
            	nRet = -2;                
            }
        }
    }
    
	return nRet;
}

/*
** ���ַ��������ж�ȡһ���ַ���������ռ䱣������ַ�����
** ͬʱ�޸��ַ���������ָ�룬ʹ��ָ����һ���ַ����Ŀ�ͷ��
*/
char *CFile::GetLine( char **ppBuf )
{
	int len = 0;

	if ( ppBuf == NULL || *ppBuf == NULL ) return NULL;

	char *pn = strchr( *ppBuf, '\n' );
	char *pLine = NULL;

	if ( pn == NULL )
    {
    	len = strlen( *ppBuf );
    	if ( len != 0 ) // ���һ������
        {
        	pLine = ( char * )Malloc( sizeof(char) * (len + 1) );
        	if ( pLine != NULL ) strlcpy( pLine, *ppBuf, len + 1 );
        }
        *ppBuf = NULL;
    }
	else
    {
    	len = pn - *ppBuf + 1;
    	pLine = ( char * )Malloc( sizeof(char) * len );
    	if ( pLine != NULL )
        {
        	memcpy( pLine, *ppBuf, sizeof(char) * len );
        	pLine[len-1] = '\0';
        	if ( pLine[len-2] == '\r' ) pLine[len-2] = '\0';
        }

        *ppBuf = pn + 1;  // ָ����һ������
    }

	return pLine;
}

/*
** ��һ���ַ�������ȡ�ؼ��ֺ�ֵ
** ���Թؼ��ֺ�ֵ��ͷ�ͽ�β�Ŀհ׷�
** ����ע��: ���з���"//"���������Ϊע��
*/
void CFile::GetKeyVal( char **ppKey, char **ppVal, char * const pLine )
{
	char *pKey = NULL;
	char *pVal = NULL;

    // ȥ��ע�ͷ�"//"���������
	char *pComment = strstr( pLine, "//" );
	if ( pComment != NULL ) *pComment = '\0';

    // ȥ�����ݽ�β�Ŀհ׷�
	int len = strlen( pLine );
	while ( (len > 0) && (pLine[len-1] == ' ' || pLine[len-1] == '\t') )    
    {
    	pLine[len-1] = '\0';
    	len--;
    }

	char *pe = strchr( pLine, '=' );
	if ( pe != NULL )
    {
        *pe = '\0';

    	pKey = pLine;
        // ���Թؼ��ֿ�ͷ�Ŀհ׷�
    	while( *pKey == ' ' || *pKey == '\t' ) pKey++;  

    	char *pEnd = pe - 1;
        // ȥ���ؼ��ֽ�β�Ŀհ׷�
    	while( pKey <= pEnd && ( *pEnd == ' ' || *pEnd == '\t' ) )
        {
            *pEnd = '\0';
        	pEnd--;
        }
        
    	if ( pKey <= pEnd && *pKey != '\0' ) 
        {            
        	pVal = pe + 1; 
            // �������ݿ�ͷ�Ŀհ׷�
        	while( *pVal == ' ' || *pVal == '\t' ) pVal++;
        	if ( *pVal == '\0' )
            {
            	pKey = NULL;
            	pVal = NULL;
            }
        }
    	else
        {
        	pKey = NULL;
        	pVal = NULL;
        }
    }

    *ppKey = pKey;
    *ppVal = pVal;
}

/* ------------------------------------------------------------------------- */

CLang s_SysLang;

int ReadLangCfg()
{
	char langCfg[256] = { 0 };
	snprintf( langCfg, sizeof(langCfg), "%s/lang.cfg", SYS_CONFIG_LANG_PATH );
	return s_SysLang.ReadCfg( langCfg );
}

char *GetLangText( char *pKey, char *pDefLang )
{    
	return s_SysLang.GetLangText( pKey );
}

char *GetLangText( int nKey, char *pDefLang )
{    
	char keyBuf[100] = { 0 };
	snprintf( keyBuf, sizeof(keyBuf), "%d", nKey );    
	return s_SysLang.GetLangText( keyBuf );
}

int LoadLangText( char *file )
{
	char path[256] = { 0 };
	snprintf( path, sizeof(path), "%s/%s", SYS_CONFIG_LANG_PATH, file );
	return s_SysLang.LoadLangFile( path );    
}

int SetLangID( int langID )
{
	int nRet = 0;
	int curID = s_SysLang.GetLangID();

	if ( curID != langID )
    {
    	nRet = s_SysLang.SetLangID( langID );
    	if ( nRet == 0 )
        {    
        	char path[256];
        	const char *pLangFile = s_SysLang.GetLangFile( langID );
        	snprintf( path, sizeof(path), "%s/%s", SYS_CONFIG_LANG_PATH, pLangFile );
        	nRet = s_SysLang.LoadLangFile( path );
        	if ( nRet != 0 ) s_SysLang.SetLangID( curID );
        }
    }
    
	return nRet;
}

int GetLangID()
{
	return s_SysLang.GetLangID();
}

const char *GetFontLib( int langID )
{
	return s_SysLang.GetFontLib( langID );
}

int GetFontWidth( int langID )
{
	return s_SysLang.GetFontWidth( langID );
}

const char *GetCharSet()
{
    return s_SysLang.GetCharSet( s_SysLang.GetLangID() );
}

const char *GetLangSufix( int langID )
{
	return s_SysLang.GetLangSufix( langID );
}

const char *GetLangName( int langID )
{
	return s_SysLang.GetLangName( langID );
}

int GetIDList( int **ppList )
{
	return s_SysLang.GetIDList( ppList );
}

