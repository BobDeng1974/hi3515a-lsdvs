/********************************************************************************
**	Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**	author        :  sven
**	version       :  v1.0
**	date           :  2013.10.10
**	description  : ddns Ӧ�ýӿ�
********************************************************************************/
#include "debug.h"
#include "ddnsFifo.h"
#include "ddnsApp.h"

/*
* fn: ˢ��ddns�Ĺ�������
      �˺������豸��ʼ�����޸���ddns�����󱻵��á�      
*/
int DdnsAppRefresh()
{
	int ret;
    
	ret = DdnsWriteConff( (char *)DDNS_CONF_PATHNAME );
	if( 0 == ret )
    {
    	ret = DdnsFifoCmd( DDNS_FIFO_CMD_REFREASH );
    }
	return ret;
}

