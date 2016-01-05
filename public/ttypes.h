/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.09.16
**  description  : ����һЩ�����Ľṹ��
********************************************************************************/

#ifndef __TTYPES_H__
#define __TTYPES_H__

#include "const.h"
#include <pthread.h>

typedef enum _PackType_
{
	PACK_TYPE_VIDEO = 0,
	PACK_TYPE_AUDIO,    
	PACK_TYPE_SMART,
} PACK_TYPE_E;

#ifndef PACK_ALIGN
#define PACK_ALIGN	__attribute__((packed))
#endif

typedef struct _PackHead_
{
	uchar 	packType;    // ������, 0:��Ƶ��; 1:��Ƶ��; 2:���ܰ�, �� PACK_TYPE_E
	uchar	frameHeadLen;    // ֡ͷ����,�ó��ȸ���packType ��ֵ�仯��ȡ sizeof(��ͬ�Ľṹ��)    
	char	reserved[2];
}PACK_ALIGN PACK_HEAD_T;

// ����Ƶ֡ͷ����
typedef struct _FrameHead_
{
    uint  frameLen;            // ֡��������
    uint  frameNo;            // ֡��,��������
    uchar videoStandard;    // ��Ƶ:��׼ 0,PAL; 1,NTSC. // ��Ƶ:ͨ��ģʽ, 0:��ͨ��, 1:������, Ĭ��ֵ 0
    uchar videoResolution;    // ��Ƶ:�ֱ��� 0,qcif; 1,cif; 2,hd1; 3,d1. // ��Ƶ:������, 0:8k, 1:16k, Ĭ��ֵ 0
    uchar frameRate;          // ��Ƶ:֡��. // ��Ƶ:λ��,0:8bits, 1:16bits, Ĭ��ֵ 1
    uchar frameType;         // ��Ƶ:֡���� 5,I֡; 1,P֡ . // ��Ƶ::���뷽ʽ,0:adpcm, 1:g711, 2:g726, Ĭ��ֵ 0
    uint  sec;                // �ӱ��ػ�ȡ��ʱ��,��
    uint  usec;                // �ӱ��ػ�ȡ��ʱ��,΢��
    uint64_t  pts;                // �Ӻ�˼�ײ��ȡ��ʱ���,(΢��)
}PACK_ALIGN FRAME_HEAD_ST;

typedef struct _StreamHead_
{
	PACK_HEAD_T 	packHead;
	FRAME_HEAD_ST	frameHead;
}PACK_ALIGN STREAM_HEAD_T;

#undef PACK_ALIGN

/* ======================= end ����� ======================= */

/* ======================= ���� ======================= */
// ��������
typedef enum _DataType_
{
	DATA_TYPE_NOMAL = 0,    // ��������
	DATA_TYPE_VIDEO_H264,    // ��ƵH264 ����
	DATA_TYPE_VIDEO_YUV,    // ��ƵYUV ����
	DATA_TYPE_AUDIO,        // ��Ƶ
	DATA_TYPE_H264_I,        // H264 �����е�I ֡	
	DATA_TYPE_H264_P,        // H264 �����е�P ֡
	DATA_TYPE_REC_STOP,        // ¼��Ľ�����ʶ
} DATA_TYPE_EN;    

#define MAX_NAL_IN_ONE_FRAME	16 // һ֡���������8 ��nal
typedef struct _NalInfo_
{
	uint	 nalNum;    // һ֡�����ж��ٸ�nal
	uint nalSize[MAX_NAL_IN_ONE_FRAME]; // ÿ��nal �ĳ���
	uint nalStartOff;        // nal ��ʼƫ�Ƶ�λ��
} NAL_INFO_T;

// ͨ�õ��������
#define MAX_DATA_PIECE_SIZE 16
typedef struct _DataPiece_
{
	int         	count; // ע��, count ����<= MAX_DATA_PIECE_SIZE
	char	        *buf[MAX_DATA_PIECE_SIZE];    // �ڼ�������ָ��ĵ�ַ
	unsigned int 	len[MAX_DATA_PIECE_SIZE];    // �ڼ������ݵĳ���
	NAL_INFO_T		nalInfo;    // ��֡��nal ����Ϣ
} DATA_PIECE_T;

#define	MAX_PROCON_DATA_NODE		64	// һ��ͨ����໺��64 ���ڵ�
#define MAX_PROCON_DATA_NODE_SIZE	(256*1024) // һ�������һ���ڵ����֧��128K

typedef struct _ProconHead_
{
	int type;    // ��������,DATA_TYPE_EN �е�����һ��
	int len;    // �ڵ����ݵĴ�С
	NAL_INFO_T nalInfo;    // ��Ƶ֡��ʱ����������nal ����Ϣ
} PROCON_HEAD_T;

typedef struct _ProConNode_
{
	PROCON_HEAD_T 	proconHead;
	char         	data[1];
} PROCON_NODE_T;

typedef struct _ProconSt_
{
	int	            	writePos;
	pthread_mutex_t		dataMutex;
	PROCON_NODE_T	    *dataPool[MAX_PROCON_DATA_NODE];
} PROCON_T;

typedef struct _ProconRead_
{
	int flag;
	int channel;
	int readBegin;
	int readEnd;
} PROCON_READ_T;

typedef struct _ProconWrite_
{
	int flag;
	int channel;
} PROCON_WRITE_T;

// producer consumer open flag
// ���� ProconH264Open() �Ⱥ�����flag ����
typedef enum _OpenEn_
{
	OPEN_RDONLY = 0,
	OPEN_WRONLY
} OPEN_EN;

typedef enum _BlockEn_
{
	BLOCK_NO = 0,    // �Է������ķ�ʽ
	BLOCK_YES	    // �������ķ�ʽ
} BLOCK_EN;

#define FI_FRAME_TYPE_VIDEO_I		5	// I֡
#define FI_FRAME_TYPE_VIDEO_P		1	// P֡
#define FI_FRAME_TYPE_SEI	    	6     // ����֡
#define FI_FRAME_TYPE_SPS	    	7     // ���в�������֡
#define FI_FRAME_TYPE_PPS	    	8     // ͼ���������֡

// wifi�������
typedef struct _WifiScanResult_
{
	char	essid[32];        // ���֧��32���ֽ�
	char	encType;        // 0-�޼���;1-wep;2-wpa/wpa2(802.1x);3-wpa-psk/wpa2-psk.Ŀǰ�ն�֧��0��1��3����������
	char	signalLevel;    // �ź�ǿ��(��λ ��)1-5
	char	reserved[2];            
} WIFI_SCAN_RESULT;

// 
// wifi��������
//
typedef struct _ConfigWifiConnect_
{
	char	essid[32];        // ���֧��32���ֽ�,֧���ֶ�����ʹ������л�ȡ
	char	key[64];        // ����
	unsigned char connectFlag;    // ֻ��, 0-û�����ӵ�����·��;1-�Ѿ����ӵ�����·��
	unsigned char signalLevel;    // ֻ��, �ź�ǿ��, 1~5��
	char	reserved[14];
} CONFIG_WIFI_CONNECT;


typedef struct talkbackNode
{
	unsigned int	timeStamp;        // ʱ���
	unsigned int	frameSeq;        // ֡����
	unsigned int	frameLen;        // ֡����
	unsigned char *	frameData;        // ֡����
} TALKBACK_NODE;

//
// OSD��������
//
typedef struct ConfigOsdLogo
{
	unsigned char	enable;                // �Ƿ���ʾOSD 1: enable, 0: disable
	unsigned char	colorRed;            // ��ɫ
	unsigned char	colorGreen;            // ��ɫ
	unsigned char	colorBlue;            // ��ɫ
	unsigned short	xPos;                // ����
	unsigned short	yPos;                // ����
	char	    	logo[64];            // ���֧��64Bytes��logo
	unsigned char	bgTransparence;        // ����͸���� 0~100,��ʾ0%~100%
	char	reserved[7];
}  CONFIG_OSD_LOGO;

typedef struct ConfigOsdTime
{
	unsigned char	enable;
	unsigned char	colorRed;    
	unsigned char	colorGreen;    
	unsigned char	colorBlue;    
	unsigned short	xPos;
	unsigned short	yPos;
	unsigned char	bgTransparence;        // ����͸���� 0~100,��ʾ0%~100%
	char	    	reserved[7];
}  CONFIG_OSD_TIME;

typedef struct _JpgInfo_
{
	unsigned int  type;      // ץ�ĵ�����
	unsigned int  num;        // �ڼ���
	char 	datel[DATE_LEN]; // ץ�ĵ�����ʱ��
	char	timel[TIME_LEN]; //
	int 	len;    // ͼƬ�ĳ���
} JPG_INFO_T;

//
// ��Ƶ����
//
#define FRAME_HEAD_ID	"FhIeRaSdDvV1S0"        

typedef enum
{
	FRAME_TYPE_NULL = 0,
	FRAME_TYPE_VIDEO,        // ��Ƶ֡����
	FRAME_TYPE_AUDIO,        // ��Ƶ֡����
	FRMAE_TYPE_SMART,        // ����֡����
} FRAME_TYPE_EN;

typedef enum
{
	VIDEO_FORMAT_NULL = 0,
	VIDEO_FORMAT_H264,
	VIDEO_FORMAT_MPEG,
} VIDEO_FORMAT_EN;

typedef struct _SnapMsg_
{
	int 	channel;
	uint 	snapType;
} SNAP_MSG_T;

typedef struct _SnapHead_
{
	int		channel;    // ͨ��
	uint	snapType;    // ץ������
	int 	sec;        // ʱ���
	int 	jpgLen;        // jpg len
} SNAP_HEAD_T;

//DVS�ϴ��ͻ��˱������Ͷ���
//#define RES_ALARM_TYPE_IO	        	0     //IO����
//#define RES_ALARM_TYPE_VLOSS	    	1     //��Ƶ��ʧ����
//#define RES_ALARM_TYPE_SHELTER	    	2     //��Ƶ�ڵ�
//#define RES_ALARM_TYPE_IO_CANCEL	    3     //IO����ȡ��
//#define RES_ALARM_TYPE_VLOSS_CANCEL		4     //��Ƶ��ʧ����ȡ��
//#define RES_ALARM_TYPE_SHELTER_CANCEL	5     //��Ƶ�ڵ�ȡ��

typedef enum
{
    RES_ALARM_TYPE_IO = 0,
    RES_ALARM_TYPE_VLOSS,
    RES_ALARM_TYPE_SHELTER,
    RES_ALARM_TYPE_IO_CANCEL,
    RES_ALARM_TYPE_VLOSS_CANCEL,
    RES_ALARM_TYPE_SHELTER_CANCEL
}ALARM_TYPE_E;

#endif

