/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.10.10
**  description  : ��key������,������������ʱ��ʹ�ø�hash ����
********************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "debug.h" 
#include "malloc.h" 
#include "hashLinear.h" 

/**************************************************************************
* fn: �ַ���ʽ��hash�㷨��װ, H = H(key)
* key: ��������hash ֵ�Ĺؼ���
* max: hash�ĳ�Ա����,index�ĸ���
* ����: ��key �����㷨������hashֵ,
****************************************************************************/
unsigned int LinearHash( unsigned int key, unsigned int max )
{
	return key % max; 
}

CHashLinear::CHashLinear( int n )
{
	int tableSize;
    
	m_maxNode      = n;
	tableSize	= sizeof(m_ppTable) * m_maxNode;
	m_ppTable     = (HASH_LINEAR_T **)malloc( tableSize );    
	if( NULL != m_ppTable )
    {
    	memset( m_ppTable, 0x00, tableSize );
    }
	else
    {
    	m_maxNode = 0;
    }
}

CHashLinear::~CHashLinear()
{
	int index;
	HASH_LINEAR_T *pTable, *pNext;
    
	if ( m_ppTable != NULL )
    {
    	for( index = 0; index < m_maxNode; index++ )
        {            
        	pTable = m_ppTable[index];
        	while( pTable != NULL )
            {
            	pNext = pTable->next;
            	FreeNode( pTable );                
            	pTable = pNext;
            }
        	m_ppTable[index] = NULL;
        }

    	Free( m_ppTable );
    }    
}

void CHashLinear::FreeNode( HASH_LINEAR_T *pNode )
{
	if( NULL != pNode )
    {        
    	FreeVal( pNode->pVal );
    	Free( pNode );
    }
}

/********************************************************************
* fn: ��linear hash ����һ���ڵ�
* key: �ؼ���
* pVal: ����ṹ��ĵ�ַ
* valSize: ����Ĵ�С
*********************************************************************/
int CHashLinear::insert( unsigned int key, void *pVal, int valSize )
{
	int ret = -1, index;
	HASH_LINEAR_T *pTable;
    
	mutex.WriteLock();
	if ( NULL != m_ppTable && NULL != pVal )
    {
    	index = LinearHash( key, m_maxNode );
    	for( pTable = m_ppTable[index]; pTable != NULL; pTable = pTable->next ) //�鿴�Ƿ��Ѿ����ڸ�key
        {
        	if( pTable->key == key )
            {
            	ShareFree( pTable->pVal );  // �ͷžɵ�val
            	pTable->pVal = pVal;        // ���µ��µ�val
            	ret = 0;
            	break;
            }
        }
    	if( -1 == ret ) // ��ϣ�����治���ڸ�key,�����
        {
        	pTable = (HASH_LINEAR_T *)malloc( sizeof(HASH_LINEAR_T) );
        	if( NULL != pTable )
            {
            	pTable->key  = key;                
            	pTable->pVal = pVal;        
            	pTable->next = m_ppTable[index]; // �����ͻ
            	m_ppTable[index] = pTable;
            	ret = 0;                            
            } // if( NULL != pTable
        }
    } // if ( NULL != m_ppTable && NULL != key 
    
	mutex.Unlock();

	return ret;
}

/************************************************************************
* fn: ��ȡָ��key �Ľڵ��ֵ��ָ��ĵ�ַ
* ����: ���key ����,�򷵻�ֵ�ĵ�ַ; ���򷵻� NULL
* ˵��: �ú������صĽ��Ҫ�ñ���� FreeVal �ͷ�
************************************************************************/
void *CHashLinear::GetVal( unsigned int key )
{
	HASH_LINEAR_T *pTable;
	int index;
	void *pRet;

    //FiPrint2( "%s, key(%u)!\r\n", __FUNCTION__, key );

	mutex.ReadLock();    
	pRet = NULL;
	if ( m_ppTable != NULL )
    {
    	index = LinearHash( key, m_maxNode );        
        
    	for ( pTable = m_ppTable[index]; pTable != NULL; pTable = pTable->next )
        {
            //FiPrint2( "%s, key(%u), pTable->key(%u)!\r\n", __FUNCTION__, key, pTable->key );
        	if ( pTable->key == key )
            {
            	pRet = ShareCopy( pTable->pVal );
            }
        }
    }
	mutex.Unlock();
    
	return pRet;
}

/*******************************************************************
* fn: �Ƴ�ָ��key �Ľڵ�
*********************************************************************/
int CHashLinear::remove( unsigned int key )
{
	int ret = -1, index;
	HASH_LINEAR_T *pPreTable, *pCurTable;
    
	mutex.WriteLock();
	if ( m_ppTable != NULL )
    {
    	index = LinearHash( key, m_maxNode );    
    	if( NULL != m_ppTable[index] )
        {
        	pPreTable = m_ppTable[index];
        	pCurTable = pPreTable->next;
            
        	if ( m_ppTable[index]->key == key ) // ͷ�ڵ��key�͵���Ҫɾ���ڵ��key
            {
            	pCurTable = m_ppTable[index];
            	m_ppTable[index] = m_ppTable[index]->next;
            	FreeNode( pCurTable );            
            	ret = 0;
            }        
        	else
            {
            	pPreTable = m_ppTable[index];
            	pCurTable = pPreTable->next;
            	while ( pCurTable != NULL )
                {
                	if ( pCurTable->key == key )
                    {
                    	pPreTable->next = pCurTable->next;
                    	FreeNode( pCurTable );
                    	ret = 0;
                    	break;
                    }

                	pPreTable = pCurTable;
                	pCurTable = pCurTable->next;
                }
            }
        } // if( NULL != m_ppTable[index] 
    } // if ( m_ppTable != NULL && key != NULL
    
	mutex.Unlock();
    
	return ret;    
}

void CHashLinear::FreeVal( void *pVal )
{
	ShareFree( pVal );
}

