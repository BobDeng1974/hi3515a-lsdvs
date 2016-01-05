/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ���ļ�ʵ�ֶԹ�ϣ����࣬��ϣ�������Ҫ�ṩ�ؼ��ֺ����ݶ����ַ���
**            ���͵����ݽ��в��룬���ң�ɾ���������ϣ��Ȳ�����
**  date           :  2013.11.11
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "malloc.h"
#include "strSafe.h"
#include "table.h"

CTable::CTable()
{
	m_nHash = NHASH;
	m_ppTable = ( LP_TABLE * )Malloc( m_nHash * sizeof( LP_TABLE ) );
	if ( m_ppTable != NULL )
    {
    	for ( int i = 0; i < m_nHash; i++ )
        	m_ppTable[i] = NULL;
    }
	else
    {
    	m_nHash = 0;
    }
}

CTable::CTable( int nHash )
{
	m_nHash = nHash;
	if ( m_nHash < NHASH ) m_nHash = NHASH;

	m_ppTable = ( LP_TABLE * )Malloc( m_nHash * sizeof( LP_TABLE ) );
	if ( m_ppTable != NULL )
    {
    	for ( int i = 0; i < m_nHash; i++ )
        	m_ppTable[i] = NULL;
    }
	else
    {
    	m_nHash = 0;
    }    
}

CTable::~CTable()
{
	if ( m_ppTable != NULL )
    {
    	Clear();
    	Free( m_ppTable );
    	m_nHash = 0;
    }
}

/*
* ���ݹؼ��ֲ��ҹ�ϣ����Ԫ�ص�ֵ������޷��Ϲؼ��ֵ�Ԫ�ط���NULL
*/
char *CTable::Get( char *pKey )
{
	LP_TABLE pTable = NULL;
    
	if ( m_ppTable != NULL && pKey != NULL )
    {
    	int idx = Hash( pKey );
    	for ( pTable = m_ppTable[idx]; pTable != NULL; pTable = pTable->next )
        {
        	if ( strcmp( pTable->key, pKey ) == 0 )
            	return pTable->val;
        }
    }

	return NULL;
}

/*
** ���ؼ��ֺ�ֵ�����ϣ������ؼ����Ѿ�
** ���ڷ���1���������ɹ�����0������ʧ�ܷ���-1��
*/
int CTable::Put( char *pKey, char *pVal )
{
	LP_TABLE pTable = NULL;
	int nRet = -1;

	if ( m_ppTable != NULL && pKey != NULL && pVal != NULL )
    {
    	int idx = Hash( pKey );
    	for ( pTable = m_ppTable[idx]; pTable != NULL; pTable = pTable->next )
        {
            /* �ؼ����Ѿ����� */
        	if ( strcmp( pTable->key, pKey ) == 0 )
            {
            	nRet = 1;
            	break;
            }
        }
        
    	if ( nRet != 1 )
        {
        	LP_TABLE pNew = ( LP_TABLE )Malloc( sizeof( TABLE ) );
        	if ( pNew != NULL )
            {
            	pNew->key = StrCopy( pKey );
            	if ( pNew->key == NULL )
                {
                	Free( pNew );
                }
            	else
                {
                	pNew->val = StrCopy( pVal );
                	if ( pNew->val == NULL )
                    {
                    	Free( pNew->key );
                    	Free( pNew );
                    }
                	else /* ����ɹ� */
                    {
                    	pNew->next = m_ppTable[idx];
                    	m_ppTable[idx] = pNew;
                    	nRet = 0;
                    }
                }
            } // if ( pNew != NULL
        }
    }

	return nRet;
}

int CTable::Delete( char *pKey )
{
	int nRet = -1;
	LP_TABLE pTable = NULL;
    
	if ( m_ppTable != NULL && pKey != NULL )
    {
    	int idx = Hash( pKey );
    	pTable = m_ppTable[idx];
    	if ( pTable != NULL )
        {
        	if ( strcmp( pTable->key, pKey ) == 0 )
            {
            	m_ppTable[idx] = pTable->next;
            	Free( pTable->key );
            	Free( pTable->val );
            	Free( pTable );
            	nRet = 0;
            }        
        }
    	else
        {
        	LP_TABLE pPreTable = m_ppTable[idx];
        	LP_TABLE pCurTable = pPreTable->next;
        	while ( pCurTable != NULL )
            {
            	if ( strcmp( pCurTable->key, pKey ) == 0 )
                {
                	pPreTable->next = pCurTable->next;
                	Free( pCurTable->key );
                	Free( pCurTable->val );
                	Free( pCurTable );
                	nRet = 0;
                	break;
                }

            	pPreTable = pCurTable;
            	pCurTable = pPreTable->next;
            }
        }
    }
	return nRet;    
}

/*
** ��չ�ϣ��
*/
void CTable::Clear()
{
	LP_TABLE pTable = NULL, pNext = NULL;
    
	if ( m_ppTable != NULL )
    {
    	for( int idx = 0; idx < m_nHash; idx++ )
        {
        	pTable = m_ppTable[idx];
        	while( pTable != NULL )
            {
            	pNext = pTable->next;
            	Free( pTable->key );
            	Free( pTable->val );
            	Free( pTable );
            	pTable = pNext;
            }
        	m_ppTable[idx] = NULL;
        }
    }
}

/* �ַ���������������̬�����ڴ汣�濽�����ַ��� */
char *CTable::StrCopy( const char *pStr ) 
{
	int len = strlen( pStr );
	char *pBuf = ( char * )Malloc( sizeof( char ) * ( len + 1 ) );
	if ( pBuf != NULL ) strlcpy( pBuf, pStr, len + 1 );
	return pBuf;
}

/* ����ؼ��ֵĹ�ϣֵ */
int CTable::Hash( char *pKey )
{
	unsigned int h = 0;
	unsigned char *pCh = NULL;

	for ( pCh = (unsigned char *)pKey; *pCh != '\0'; pCh++ )
    	h = MULTIPLTER * h + *pCh;

	return h % (unsigned int)m_nHash;
}

#ifdef _TABLE_DEBUG

/* ������ϣ������Ԫ�ظ��� */    
int CTable::Size()
{
	LP_TABLE pTable = NULL;
	int cnt = -1;
    
	if ( m_ppTable != NULL )
    {
    	cnt = 0;
    	for( int idx = 0; idx < m_nHash; idx++ )
        {
        	pTable = m_ppTable[idx];
        	while ( pTable != NULL )
            {
            	cnt++;        
            	pTable = pTable->next;
            }
        }
    }
    
	return cnt;
}

/* ������ϣ����ӡ������Ԫ�� */
void CTable::Print( FILE *fp )
{
	if ( m_ppTable != NULL && fp != NULL )
    {
    	for ( int idx = 0; idx < m_nHash; idx++ )
        {
        	LP_TABLE pTable = m_ppTable[idx];
        	if ( pTable != NULL )
            {
            	fprintf( fp, "%d:|", idx );
            	for ( ; pTable != NULL; pTable = pTable->next )
                {
                	fprintf( fp, "%s->%s|", pTable->key, pTable->val );    
                }
            	fprintf( fp, "\r\n" );
            }
        }
    }

	fflush( fp );
}

#endif

