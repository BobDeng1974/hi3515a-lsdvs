/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.10.10
**  description  : ptpool: public thread pool ȫ���̳߳�
********************************************************************************/

#include "debug.h"
#include "ptpool.h"

static ClThreadPool g_ptpool;

static int PtpoolCreate( int threadNum )
{
	return g_ptpool.Create( threadNum );
}

int PtpoolAdd( THREAD_FUN fun, void *args, int argsSize )
{    
	int ret;
	ret = g_ptpool.Add( fun, args, argsSize );
	return ret;
}

int PtpoolDestroy()
{
	return g_ptpool.Destroy();
}

void PtpoolInit()
{
	PtpoolCreate( MAX_PTPOOL_SIZE );
}

