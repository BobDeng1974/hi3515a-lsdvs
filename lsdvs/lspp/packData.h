/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ��ͷ�ļ��ṩ�˶���ϢЭ��İ����ݽ��д���ͽ�������ĺ����ӿ�
**  �ο��ĵ�: <<DVS����Э��.doc>> V1.0
**  date           :  2013.12.07
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef _PACK_DATA_H
#define _PACK_DATA_H

#define PACK_ALIGN	__attribute__((packed))

//
// ����ͷ��ʽ,����14
//
typedef struct FirsPackHead
{
	unsigned int	msgFlag;    // ��Ϣ��ʶ
	unsigned char	msgType;    // ��Ϣ����
	unsigned short	packSn;        // �����
	unsigned int	packType;    // ������
	unsigned char	subType;    // ������
	unsigned short	len;        // ���ݳ���
} PACK_ALIGN FIRS_PACK_HEAD;

//
// ���ݰ���ʽ
//
typedef struct FirsPackData
{
	FIRS_PACK_HEAD	head;        // ��ͷ����
	unsigned char	data[1];    // �������ݲ��ֺ�2�ֽ�У���
} PACK_ALIGN FIRS_PACK_DATA;

#undef PACK_ALIGN

//
// ��ȡ����������е�ƫ��λ��
//
int GetFlagOffset( unsigned char *data, int len, unsigned int flag );

//
// ��ȡ���ݰ�ͷ
//
void FirsGetDataHead( FIRS_PACK_HEAD &head );

//
// ��ȡ���ݰ�����: ��ͷ����+�����ݳ���+У�鳤��
//
int FirsGetPackLen( FIRS_PACK_DATA *pPackData );

//
// �������ݰ�ͷ
//
void FirsPackDataHead(	FIRS_PACK_HEAD &head,
                    	unsigned int	msgFlag,
                    	unsigned char	msgType,
                    	unsigned short	packSn,
                    	unsigned int	packType,
                    	unsigned char	subType,
                    	unsigned short	len );

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
                    	int &        	packLen	);

#endif  // _PACK_DATA_H

