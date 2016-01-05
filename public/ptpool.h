#ifndef __PTPOOL_H__
#define __PTPOOL_H__

#include "threadPool.h"

#define MAX_PTPOOL_SIZE		4 // ���֧��4 ���߳�

void PtpoolInit();
int PtpoolAdd( THREAD_FUN fun, void *args, int argsSize );
int PtpoolDestroy();

#endif 

