/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**	�ļ���: recordDel.h
**  description  : for recordDel.h
**  date           :  2013.10.18
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/

#ifndef __RECORD_DEL_H__
#define __RECORD_DEL_H__

#include "record.h"

#define RECORD_DEL_SPACE	100	//ʣ����ٿռ��ɾ��¼��,��λM;ɾ������Ϊ��λ

typedef	struct	_delOldDate
{
	char	dirName[RECORD_FILENAME_LEN];
	struct	_delOldDate	*next;
}DEL_OLD_DATE;

void FiRecStartAutoDelOldFile(void);
int FiRecSetSupportLoopRecordFlag(int flag);
int FiRecGetSupportLoopRecordFlag(void);
int FiRecInitLoopRecordFlag();

int FiRecSetRecordDelSpace(int delSpace);
int FiRecGetRecordDelSpace(void);

#endif //__RECORD_DEL_H__

