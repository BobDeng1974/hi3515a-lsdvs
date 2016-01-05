/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : AT GPS���ƻ��ӿ�
**  date           :  2014.9.25
**
**  version       :  1.0
**  author        :  sven
********************************************************************************/

#ifndef __ATGPS_H__
#define __ATGPS_H__

#define ATCMD_GSP_START_KEY	    "^GPSSTART"
#define ATCMD_GSP_STOP_KEY	    "^GPSSTOP"


typedef enum _AtGps_
{
	AT_GPS_OFF = 0,        // �ر�GPS
	AT_GPS_ON	        // ����GPS
} AT_GPS_EN;

int FiAtGpsCtl( AT_GPS_EN flag );    
    
#endif

