/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ��ͷ�ļ��ṩ�˶Զ����Խ���֧�ֵ������Ľӿ�
**  date           :  2013.11.11
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef _LANG_H
#define _LANG_H

#include "table.h"
#include "malloc.h"

#define SYS_CONFIG_LANG_PATH  "./resource/lang"

typedef struct LangCfg
{
	int		langID;            /* ����ID */
	char *	fontLib;        /* �ֿ����� */
	int		fontWidth;        /* ��������ַ���� */
	char *	charSet;        /* �ַ��� */
	char *	langFile;        /* �����ļ� */
	char *	langSufix;        /* ���Ժ�׺ */
	char *	langName;        /* �������� */
    
} LANGCFG, *LP_LANGCFG;

class CFile
{
public:
	char *StrCopy( const char *pStr );
	int ReadFile( char **ppBuf, char *pFileName );
	char *GetLine( char **ppBuf );
	void GetKeyVal( char **ppKey, char **ppVal, char * const pLine );
};

class CLang : private CFile
{
public:
	CLang()
    {
    	m_ppLangCfg = NULL;
    	m_nLangNum = 0;
    	m_nLangID = 0;
    }
    
    ~CLang() 
    {
    	if ( m_ppLangCfg )
        {
        	ClearCfg( m_ppLangCfg );
        }

    	m_nLangNum = 0;
    	m_nLangID = 0;        
    }
    
public:

	void ClearCfg( LP_LANGCFG *ppLangCfg );
	int ReadCfg( char *cfgFile );
    
	int SetLangID( int langID )
    { 
    	int nRet = -1;
    	for ( int i = 0; i < m_nLangNum; i++ )
        {
            // ���õ�����ID��������Ч��ID
        	if ( m_ppLangCfg[i]->langID == langID )
            {
            	m_nLangID = langID;
            	nRet = 0;
            	break;
            }
        }

    	return nRet;
    }
    
	int GetLangID()
    { 
    	return m_nLangID; 
    }

	int GetIDList( int **ppList )
    {
    	if ( m_nLangNum > 0 )
        {
            *ppList = ( int * )Malloc( sizeof(int) * m_nLangNum );
        	for ( int i = 0; i < m_nLangNum; i++ )
            {            
                (*ppList)[i] = m_ppLangCfg[i]->langID;
            }
        }

    	return m_nLangNum;
    }

    // �������ID��Ч�򷵻ؿ��ַ���
	const char *GetFontLib( int langID )
    {
    	static const char pBuf[1] = { 0 };
    	int index = GetIndex( langID );
    	if ( 0 <= index && index < m_nLangNum )
        {
        	return m_ppLangCfg[index]->fontLib;
        }
    	return pBuf;
    }

	int GetFontWidth( int langID )
    {
    	int index = GetIndex( langID );
    	if ( 0 <= index && index < m_nLangNum )
        {
        	return m_ppLangCfg[index]->fontWidth;
        }
    	return 0;
    }
    
	const char *GetCharSet( int langID )
    {
    	static const char pBuf[1] = { 0 };
    	int index = GetIndex( langID );
    	if ( 0 <= index && index < m_nLangNum )
        {
        	return m_ppLangCfg[index]->charSet;
        }
    	return pBuf;
    }
    
	const char *GetLangFile( int langID )
    {
    	static const char pBuf[1] = { 0 };
    	int index = GetIndex( langID );
    	if ( 0 <= index && index < m_nLangNum )
        {
        	return m_ppLangCfg[index]->langFile;
        }
    	return pBuf;
    }
    
	const char *GetLangSufix( int langID )
    {
    	static const char pBuf[1] = { 0 };
    	int index = GetIndex( langID );
    	if ( 0 <= index && index < m_nLangNum )
        {
        	return m_ppLangCfg[index]->langSufix;
        }
    	return pBuf;
    }
    
	const char *GetLangName( int langID )
    {
    	static const char pBuf[1] = { 0 };
    	int index = GetIndex( langID );
    	if ( 0 <= index && index < m_nLangNum )
        {
        	return m_ppLangCfg[index]->langName;
        }
    	return pBuf;
    }    
    
	int LoadLangFile( char *file );
    
	char *GetLangText( char *pKey )
    {
    	static char pBuf[1] = { 0 };
    	char * pVal = m_lang.Get( pKey ); 
    	return ( pVal == NULL ) ? pBuf : pVal;
    }

public:
	CTable m_lang;
    
private:
	LP_LANGCFG *m_ppLangCfg;
	int m_nLangNum;
	int m_nLangID;

private:    
	LP_LANGCFG GetLangCfg( char *pCfgBuf );
	int GetIndex( int langID )
    {
    	for ( int i = 0; i < m_nLangNum; i++ )
        {
        	if ( m_ppLangCfg[i]->langID == langID ) return i;
        }
    	return -1;
    }
};

/* ------------------------------------------------------------------------- */
//
// ������Խӿں���
//
int ReadLangCfg();
char *GetLangText( int nKey, char *pDefLang );
int LoadLangText( char *file );
int SetLangID( int langID );
int GetLangID();
const char *GetFontLib( int langID );
int GetFontWidth( int langID );
const char *GetCharSet();
const char *GetLangSufix( int langID );
const char *GetLangName( int langID );
int GetIDList( int **ppList );

#endif  // _LANG_H

