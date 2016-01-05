/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
    
**  description  : GPSһЩ�����ĺ�,�Լ�һЩ����Ĺ����ӿ�
**  date           :  2014.9.25
**  GPS��Ϣ:
	$GPGSA,A,3,03,11,13,19,23,24,,,,,,,3.5,2.0,2.8*32
	$GPVTG,,T,,M,0.0,N,0.0,K*4E
	$GPGSV,3,1,10,16,22,071,,06,14,043,,03,26,039,33,08,21,323,21*78
	$GPGSV,3,2,10,11,61,170,34,07,49,323,24,24,38,167,38,19,54,018,27*72
	$GPGSV,3,3,10,23,21,199,38,13,33,227,35*73
	$GPGGA,062131.0,2232.039330,N,11401.093446,E,1,07,1.7,57.5,M,,,,*3C
	$GPRMC,062131.0,A,2232.039330,N,11401.093446,E,,,110811,,,A*63
**  version:1.0
**  author :sven
********************************************************************************/

#ifndef __GPSCOM_H__
#define __GPSCOM_H__

#include <pthread.h>

#define GPS_MSG_GPGSV_KEY	"GPGSV"        // �ɼ�������Ϣ�ؼ���
#define GPS_MSG_GPGLL_KEY     "GPGLL"        // ����λ��Ϣ�ؼ���
#define GPS_MSG_GPRMC_KEY     "GPRMC"         // �Ƽ���С��λ��Ϣ�ؼ���
#define GPS_MSG_GPVTG_KEY     "GPVTG"        // �����ٶ���Ϣ�ؼ���
#define GPS_MSG_GPGGA_KEY     "GPGGA"        // GPS��λ��Ϣ�ؼ���
#define GPS_MSG_GPGSA_KEY     "GPGSA"        // ��ǰ������Ϣ�ؼ���

#define GPS_MSG_COMMA	","        // ���ŷָ���
#define GPS_MAX_SYNC_INTERVAL	300 // ��Ч��GPSͬ��ʱ����(��)

typedef struct _GpsMsgSync_
{
	pthread_mutex_t		lock;
	int pts;                    // ʱ���,�����ж���Ϣ����Ч��
	int interval;                // ��Ч��ʱ����,������ʱ����Ч,��λ(��)
} GPS_MSG_SYNC;

// GPS�ٶ�
typedef struct _GpsMsgSpeed_
{
	GPS_MSG_SYNC 	sync;
	float	    	speed;    // ��λ(��)
} GPS_MSG_SPEED;

// GPS����
typedef struct _GpsMsgXyz_
{    
	float	    	latitude;        // γ�� ddmm.mmmm���ȷ֣�
	char	    	latitudeNs;        // γ�Ȱ���, == 'N'Ϊ������, == 'S'Ϊ�ϰ���
	float	    	longitude;        // ���� ddmm.mmmm���ȷ֣�
	char	    	longitudeEw;    // ���Ȱ���, == 'E'Ϊ������, 'W'Ϊ������
} GPS_MSG_XYZ;
typedef struct _GpsMsgXyzSt_
{
	GPS_MSG_SYNC 	sync;
	GPS_MSG_XYZ		xyz;
} GPS_MSG_XYZ_ST;

// GPS��ƫ��
typedef struct _GpsMsgMagneticDeclination_
{
    
	float	    	magneticDeclination;        // 000.0~180.0��
	char	    	magneticDeclinationEw;        // ��ƫ�Ƿ���E��������W������
} GPS_MSG_MAGNETIC_DECLINATION;
typedef struct _GpsMsgMagneticDeclinationSt_
{
	GPS_MSG_SYNC 	sync;
	GPS_MSG_MAGNETIC_DECLINATION magDec;
} GPS_MSG_MAGNETIC_DECLINATION_ST;

int GpsComInit();
int GpsComDeInit();

// set ���ֺ�����ģ���ڲ�ʹ��
int GpsSetSpeed( float speed );
int FiGpsSetXyz( GPS_MSG_XYZ xyz );
int FiGpsSetMagDec( GPS_MSG_MAGNETIC_DECLINATION magDec );

// get ���ֺ���������ģ�����
int FiGpsGetSpeed( float *pSpeed );
int FiGpsGetXyz( GPS_MSG_XYZ *pXyz );
int FiGpsGetMagDec( GPS_MSG_MAGNETIC_DECLINATION *pMagDec );

#endif 

