/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ���ļ��ṩ�˲���licence�ļ�����Ҫ����غ����ӿ�
**  date           :  2011.04.06
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef _LICENCE_H
#define _LICENCE_H

#include "const.h"

#define LICENCE_FLAG	    	0x74CECEFA	        // LICENCE ��ʶ

#define	OEM_FIRS	        	0x00	            // 
#define	OEM_STD	            	0x10	            // ��׼�汾
#define	OEM_LTY	            	0x11	            // ��̩Դ
#define OEM_SD	            	0x12	            // ɣ��
#define OEM_PNM	            	0x13	            // ��ŵ��
#define OEM_FT	            	0x14	            // ��ͨ
#define OEM_ZHUNDIAN	    	0x15	            // ׼��
#define	OEM_YW	            	0x16	            // ��Ϊ
#define	OEM_JSYD	        	0x17	            // �����ƶ�
#define	OEM_WKP	            	0x18	            // ������

#define PF_HI3512	        	0	                // HiSi3512ƽ̨
#define PF_TI6446	        	1	                // TI6446ƽ̨
#define PF_LTY	            	2	                // lty ����
#define PF_CIM	            	3	                // �ϰ�һ�������
#define PF_CAR	            	4	                // ����dvs ����
#define PF_NCIM	            	5	                // ��wifi һ�������
#define PF_WKP	            	6	                // �����պ�������

#define OD_TYPE_NULL	    	0x00	            // �����㷨
#define OD_TYPE_PC	        	0x01	            // �����㷨
#define OD_TYPE_FIV	        	0x02	            // �˶�Ŀ�����㷨
#define OD_TYPE_FOV	        	0x04	            // ʧ������㷨
#define OD_TYPE_FACE	    	0x08	            // ��������㷨
#define OD_TYPE_EYE	        	0x10	            // ���ۼ���㷨
#define OD_TYPE_FESMC	    	0x20	            // �����쳣���
#define OD_TYPE_LP	        	0x40	            // ���Ƽ��
#define OD_TYPE_ABDOOR	    	0x80	            // AB��

#define OD_FLAG_CLOSE	    	0	                // �ر��㷨
#define OD_FLAG_OPEN	    	1	                // ���㷨

#define ENCODE_FLAG_CLOSE		0	                // �رձ���
#define ENCODE_FLAG_OPEN		1	                // �򿪱���

#define SERIAL_NORMAL	    	0	                // �������� RS232
#define SERIAL_RS232	    	0	                // �������� RS232
#define SERIAL_RS485	    	1	                // �������� RS485 

#define PROTOCOL_NULL	    	0	                // ��ЧЭ������
#define PROTOCOL_FIRS	    	6	                // ͨѶЭ��V2.1��(RS232)
#define PROTOCOL_LTY	    	1	                // ��̩Դ����ͨѶЭ��(RS232)
#define PROTOCOL_YW_GPS	    	2	                // ��ΪGPSͨѶЭ��(RS232)
#define PROTOCOL_JTX_GPS		3	                // ������GPSͨѶЭ��(RS232)
#define PROTOCOL_FIRS_COM		4	                // ͨѶЭ��V3.0��(RS232)
#define PROTOCOL_FIRS_COUNTER	5	                // ������(TCP/IP RS232 RS485)
#define PROTOCOL_ZHUOYANG	PROTOCOL_FIRS_COUNTER	// ׿�ﴮ��ͨѶЭ��(RS485)
#define PROTOCOL_NORMAL		PROTOCOL_FIRS_COUNTER	// ��׼Э��: ������(TCP/IP RS232 RS485)
#define PROTOCOL_FIRS_XS		7	                // -��ʢͨѶЭ��(RS485)
#define PROTOCOL_FIRS_ERRISSOM 	8	                // ��³ľ�복��ʮ����Ƭ���� RS232
#define PROTOCOL_JSYD_COM_GPS	9	                // �����ƶ�����ͳ�� RS232
#define PROTOCOL_DLHZH         	10                     // ������չ RS485
#define PROTOCOL_JYZT         	11                     // ������Ӣ��ͨ(RS232)
#define PROTOCOL_PCTY         	13                     // IPSOS��Ŀ����ͨ��ƽ̨ͨ��(TCP)

#define PC_TYPE_PC	        	0	                // ����ϵͳ����:�ǳ�������
#define PC_TYPE_PC_BUS	    	1	                // ����ϵͳ����:��������
#define DATA_UPLOAD_NO	    	0	                // ��֧��ʵʱ�����ϴ�
#define DATA_UPLOAD_YES	    	1	                // ֧��ʵʱ�����ϴ�

//0x01��ʾ��һ�����0x02��ʾ��һ�����0x03��ʾ2·LTY DVS��0x04��ʾ2·wkp DVS��0x05��ʾ4·����DVS��0x06��ʾ3512��·D1
#define DVS_TYPE_OLD_WHOLE_ONE_ROAD         	0x01
#define DVS_TYPE_NEW_WHOLE_ONE_ROAD         	0x02
#define DVS_TYPE_LTY_TWO_ROAD                 	0x03
#define DVS_TYPE_WKP_TWO_ROAD                 	0x04
#define DVS_TYPE_CAR_FOUR_ROAD                 	0x05
#define DVS_TYPE_HI3512_D1_ONE_ROAD         	0x06

#ifndef PACK_ALIGN
#define PACK_ALIGN __attribute__((packed))
#endif

typedef struct Licence
{
	unsigned int	flag;                            // �ļ�ͷ���
	unsigned char	oemVersion;                        // OEM�汾
	unsigned char	platform;                        // ƽ̨
	unsigned int	odType[MAX_CHANNEL_NUM];        // �㷨����: ����ͬʱ֧�ֶ����㷨 OD_PC|OD_FIV
	unsigned char	odFlag[MAX_CHANNEL_NUM];        // �Ƿ����㷨
	unsigned char	encodeFlag[MAX_CHANNEL_NUM];    // �Ƿ�������
	unsigned char	serialType;                        // ��������
	unsigned char	protocolType;                    // Э������
	unsigned char	pcType;                            // ����ϵͳ����:��������,�ǳ�������(���Ϊ1���Ǵ��Ŵŵ�)
	unsigned char	dataUploadFlag;                    // �Ƿ�֧��ʵʱ�����ϴ�
	unsigned char	fivRf433mFlag;                    // �Ƿ��������FIV
	unsigned char   led             : 1;            // LED��־ -1
	unsigned char	mainSlave	    : 1;            // ���ӱ�־ - 2
	unsigned char	fivType         : 1;            // fiv��ͬ��Э������ -4	
	unsigned char	threeg	        : 1;            // 3Gģ���־ - 8
	unsigned char	wifi	        : 1;            // wifiģ���־
	unsigned char	wlPlatform	    : 1;            // ��³ľ�복�Ʋ�׽��,���Ϊ0,��ͻ��˲���Ҫ��ʾƽ̨������������
	unsigned char	bsl             : 1;            // ������Э��,(�������Ҫ�ͻ��˹���)
	unsigned char	synovate	    : 1;            // ˼γЭ��
    
	unsigned char	czcf	        : 1;            // ���д�����ץ��
	unsigned char	shelterf	    : 1;            // �ڵ�����ץ��	
    unsigned char 	qirui	        : 1;            // ��������
    unsigned char   jyzht             : 1;            // ��Ӣ��ͨ
    unsigned char   rlweye             : 1;            // �г�ƣ�ͼ��,add at 2013.07.31(��ÿʮ���ӵ������֤)
	unsigned char	bjgq	        : 1;             // ��������(led)&��������
	unsigned char	reserved	    : 2;            // ����
    
	unsigned char	devType;                        // �豸����, 0x01��ʾ��һ�����0x02��ʾ��һ�����0x03��ʾ2·LTY DVS��0x04��ʾ3·wkp DVS��0x05��ʾ4·����DVS��0x06��ʾ3512��·D1

	char	    	unused[2];                        // ��չ	
} PACK_ALIGN LICENCE;

#ifndef PACK_ALIGN
#undef PACK_ALIGN
#endif

int SysGetLicence( LICENCE *pLicence );
int SysIsPcBus();
int SysGetProtocolType();
int SysGetDataUploadFlag();
int SysGetPcType();
int SysGetOdType( int channel );
int SysGetOdFlag( int channel );
int SysGetEncodeFlag( int channel );
int SysGetWifiFlag();
int SysGetThreegFlag();
int SysGetOemType();
int SysGetCzcfFlag();
int SysGetSynovateFlag();
int SysGetBslFlag();
int SysGetShf();

unsigned char SysGetDvsType();

int SysGetQiruiFlag();
int SysGetSerialType();
int SysGetOemVersion();
int SysGetJyzhtFlag();
int SysGetRlweyeFlag();//�г�ƣ�ͼ��,add at 2013.07.31
int SysGetBjgqFlag();

#ifdef __cplusplus
extern "C" {
#endif

int SysGetFivRf433mFlag();
int SysGetLedFlag();
int SysGetMasterSlaverFlag();

#ifdef __cplusplus
}
#endif

#endif  // _LICENCE_H

