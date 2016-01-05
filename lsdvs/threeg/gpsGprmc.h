/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.

**  description  : ���� GPRMC ��Ϣ
**  date           :  2014.9.25

**  version:1.0
**  author :sven
********************************************************************************/
#ifndef __GPSGPRMC_H__
#define __GPSGPRMC_H__

#define TEN_MINUTE (10*60)

typedef enum _GpsGprmcMsgEn_
{
	GPS_GPRMC_MSG_HEAD = 0,            // <0> ��Ϣͷ��"$GPRMC"    
	GPS_GPRMC_MSG_TIME,                // <1> UTCʱ�䣬hhmmss��ʱ���룩��ʽ
	GPS_GPRMC_MSG_STATE,            // <2> ��λ״̬��A=��Ч��λ��V=��Ч��λ
	GPS_GPRMC_MSG_LATITUDE,            // <3> γ��ddmm.mmmm���ȷ֣���ʽ��ǰ���0Ҳ�������䣩
	GPS_GPRMC_MSG_LATITUDE_NS,        // <4> γ�Ȱ���N�������򣩻�S���ϰ���
	GPS_GPRMC_MSG_LONGITUDE,        // <5> ����dddmm.mmmm���ȷ֣���ʽ��ǰ���0Ҳ�������䣩
	GPS_GPRMC_MSG_LONGITUDE_EW,        // <6> ���Ȱ���E����������W��������
	GPS_GPRMC_MSG_SPEED,            // <7> �������ʣ�000.0~999.9�ڣ�ǰ���0Ҳ�������䣩
	GPS_GPRMC_MSG_DIRECTION,        // <8> ���溽��000.0~359.9�ȣ����汱Ϊ�ο���׼��ǰ���0Ҳ�������䣩
	GPS_GPRMC_MSG_DATE,                // <9> UTC���ڣ�ddmmyy�������꣩��ʽ
	GPS_GPRMC_MSG_MAGNETIC_DECLINATION,        // <10> ��ƫ�ǣ�000.0~180.0�ȣ�ǰ���0Ҳ�������䣩
	GPS_GPRMC_MSG_MAGNETIC_DECLINATION_EW,    // <11> ��ƫ�Ƿ���E��������W������
	GPS_GPRMC_MSG_MODE,                        // <12> ģʽָʾ����NMEA0183 3.00�汾�����A=������λ��D=��֣�E=���㣬N=������Ч��
} GPS_GPRMC_MSG_EN;

typedef enum _GpsGprmcMarkEn_
{
	GPS_GPRMC_MARK_HEAD     = (0x01 << 1),            // <0> ��Ϣͷ��"$GPRMC"    
	GPS_GPRMC_MARK_TIME     = (0x01 << 2),            // <1> UTCʱ�䣬hhmmss��ʱ���룩��ʽ
	GPS_GPRMC_MARK_STATE     = (0x01 << 3),            // <2> ��λ״̬��A=��Ч��λ��V=��Ч��λ
	GPS_GPRMC_MARK_LATITUDE = (0x01 << 4),            // <3> γ��ddmm.mmmm���ȷ֣���ʽ��ǰ���0Ҳ�������䣩
	GPS_GPRMC_MARK_LATITUDE_NS	= (0x01 << 5),        // <4> γ�Ȱ���N�������򣩻�S���ϰ���
	GPS_GPRMC_MARK_LONGITUDE     = (0x01 << 6),        // <5> ����dddmm.mmmm���ȷ֣���ʽ��ǰ���0Ҳ�������䣩
	GPS_GPRMC_MARK_LONGITUDE_EW = (0x01 << 7),        // <6> ���Ȱ���E����������W��������
	GPS_GPRMC_MARK_SPEED         = (0x01 << 8),        // <7> �������ʣ�000.0~999.9�ڣ�ǰ���0Ҳ�������䣩
	GPS_GPRMC_MARK_DIRECTION     = (0x01 << 9),        // <8> ���溽��000.0~359.9�ȣ����汱Ϊ�ο���׼��ǰ���0Ҳ�������䣩
	GPS_GPRMC_MARK_DATE         = (0x01 << 10),                // <9> UTC���ڣ�ddmmyy�������꣩��ʽ
	GPS_GPRMC_MARK_MAGNETIC_DECLINATION     = (0x01 << 11),        // <10> ��ƫ�ǣ�000.0~180.0�ȣ�ǰ���0Ҳ�������䣩
	GPS_GPRMC_MARK_MAGNETIC_DECLINATION_EW     = (0x01 << 12),    // <11> ��ƫ�Ƿ���E��������W������
	GPS_GPRMC_MARK_MODE                     = (0x01 << 13),                        // <12> ģʽָʾ����NMEA0183 3.00�汾�����A=������λ��D=��֣�E=���㣬N=������Ч��
} GPS_GPRMC_MARK_EN;
#define GPS_GPRMC_MARK_TIME_MIX	    ( GPS_GPRMC_MARK_TIME | GPS_GPRMC_MARK_STATE | GPS_GPRMC_MARK_DATE )
#define GPS_GPRMC_MARK_SPEED_MIX	( GPS_GPRMC_MARK_STATE | GPS_GPRMC_MARK_SPEED )
#define GPS_GPRMC_MARK_XYZ_MIX	    ( GPS_GPRMC_MARK_STATE \
                                    | GPS_GPRMC_MARK_LATITUDE | GPS_GPRMC_MARK_LATITUDE_NS \
                                    | GPS_GPRMC_MARK_LONGITUDE | GPS_GPRMC_MARK_LONGITUDE_EW )
#define GPS_GPRMC_MARK_MAG_DEC_MIX	( GPS_GPRMC_MARK_STATE \
                                    | GPS_GPRMC_MARK_MAGNETIC_DECLINATION \
                                    | GPS_GPRMC_MARK_MAGNETIC_DECLINATION_EW )

typedef struct _GpsGprmcMsgSt_
{
	char	head[16];
	char 	time[9];
	char 	state;
	float 	latitude;
	char 	latitudeNs;
	float 	longitude;
	char  	longitudeEw;
	float 	speed;
	float 	direction;
	char  	date[9];
	float	magneticDeclination;
	char	magneticDeclinationEw;
	char	mode[16];
	int		mark;        //����, ��ӦGPS_GPRMC_MARK_EN
} GPS_GPRMC_MSG_ST;

int FiGpsParseGprmc( char *pGprmc );

#endif 

