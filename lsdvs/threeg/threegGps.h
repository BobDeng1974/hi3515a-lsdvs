/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ����3G��GPSҵ��
**  date           :  2014.9.25
**
**  version       :  1.0
**  author        :  sven
********************************************************************************/
#ifndef __THREEGGPS_H__
#define __THREEGGPS_H__

#define GPS_LINE_SIZE 1024
#define GPS_MSG_START	"$"
#define GPS_MSG_STOP	"\r\n"
typedef struct _ThreegGpsCommunicate_
{
	int         	socket;            //ͨ��socket
	char             *sockBuf;        //socket buffer	
	unsigned int 	sockDataSize;    //���ջ��������浱ǰ�����ݴ�С
	char             *anaBuf;        //��������buffer
	unsigned int	anaDataSize;    //��������buffer��������ݴ�С
}THREEG_GPS_COMMUNICATE;

typedef int (*THREEG_GPS_FUNC)( THREEG_GPS_COMMUNICATE *pThreegGps, char *pLine );
typedef struct _ThreegGpsMsgFunc_
{
	char         	msgKey[32];    // ��Ϣ�ؼ���
	THREEG_GPS_FUNC	func;        // ��Ӧ����Ϣ����ĺ���	
} THREEG_GPS_MSG_FUNC;

int ThreegGpsStartService();
int ThreegGpsStopService();

#endif

