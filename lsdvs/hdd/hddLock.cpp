/*
*******************************************************************************
**	Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**	author        :  sven
**	version       :  v1.0
**	date           :  2013.10.10
**	description  : ��һ��ʹ��hdd ��ȫ�ֻ������ӿ�
*******************************************************************************
*/

#include "mutex.h"

static CMutexLockRecursive g_hddMutex;

void HddMutexLock()
{
	g_hddMutex.Lock();
}

void HddMutexUnlock()
{
	g_hddMutex.Unlock();
}



