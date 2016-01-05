#ifndef __DDNSFIFO_H__
#define __DDNSFIFO_H__

#define DDNS_FIFO_DEVICE "/tmp/ddns.fifo"

typedef enum _DdnsFifoCmd_
{
	DDNS_FIFO_CMD_START = 11,    // ����
	DDNS_FIFO_CMD_STOP,            // ֹͣ
	DDNS_FIFO_CMD_RESTART,        // ����	
	DDNS_FIFO_CMD_REFREASH,        // ˢ��,���ǰ�enable ֱ��д��/tmp/ddns.conf,��ddns.sh �Լ������Ƿ�����ddns
} DDNS_FIFO_CMD_EN;

int DdnsFifoCmd( DDNS_FIFO_CMD_EN cmd );
int DdnsWriteConff( char *pathname );

#endif 

