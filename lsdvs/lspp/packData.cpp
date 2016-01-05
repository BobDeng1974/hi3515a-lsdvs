/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ��ͷ�ļ�ʵ���˶���ϢЭ��İ����ݽ��д���ͽ�������ĺ���
**  �ο��ĵ�: <<DVS����Э��.doc>> V1.0
**  date           :  2013.12.07
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "debug.h"
#include "netSocket.h"
#include "packData.h"
#include "fitLspp.h"

//
// ��ȡ����������е�ƫ��λ��
//
int GetFlagOffset( unsigned char *data, int len, unsigned int flag )
{
	len -= ( sizeof(flag) - 1 );
	int offset = 0;
	for ( ; offset < len; ++offset )
    {
    	if ( !memcmp(data+offset, &flag, sizeof(flag)) )
        	break;
    }
	return offset;
}

//
// ��ȡ���ݰ�ͷ
//
void FirsGetDataHead( FIRS_PACK_HEAD &head )
{
	head.msgFlag	= ntohl( head.msgFlag );
	head.packSn	    = ntohs( head.packSn );
	head.packType	= ntohl( head.packType );
	head.len	    = ntohs( head.len );
}

//
// ��ȡ���ݰ�����: ��ͷ����+�����ݳ���+У�鳤��
//
int FirsGetPackLen( FIRS_PACK_DATA *pPackData )
{
	unsigned short check = 0;
	return sizeof(pPackData->head) + ntohs(pPackData->head.len) + sizeof(check);
}

//
// �������ݰ�ͷ
//
void FirsPackDataHead(	FIRS_PACK_HEAD &head,
                    	unsigned int	msgFlag,
                    	unsigned char	msgType,
                    	unsigned short	packSn,
                    	unsigned int	packType,
                    	unsigned char	subType,
                    	unsigned short	len )
{
	head.msgFlag	= htonl( msgFlag );
	head.msgType	= msgType;
	head.packSn	    = htons( packSn );
	head.packType	= htonl( packType );
	head.subType	= subType;
	head.len	    = htons( len );
}

//
// �������ݰ�
//
void FirsPackDataPack(	unsigned int	msgFlag,
                    	unsigned char	msgType,
                    	unsigned short	packSn,
                    	unsigned int	packType, 
                    	unsigned char	subType,
                    	unsigned char *	dataBuf,
                    	unsigned short	dataLen,
                    	unsigned char *	packBuf,
                    	int &        	packLen	)
{
	if ( packBuf != NULL )
    {
    	FIRS_PACK_DATA *pFirsPackData = ( FIRS_PACK_DATA * )packBuf;
    	FirsPackDataHead( pFirsPackData->head, msgFlag, msgType,
                        	packSn, packType, subType, dataLen );

    	packLen = sizeof( pFirsPackData->head );
    	if ( dataBuf != NULL && dataLen > 0 )
        {
        	memcpy( (char *)packBuf + packLen, dataBuf, dataLen );
        	packLen += dataLen;
        }
    	unsigned short check = htons( GetCheckSum( packBuf, packLen ) );
    	memcpy( (char *)packBuf + packLen, (char *)&check, sizeof(check) );
    	packLen += sizeof(check);
    }
}

