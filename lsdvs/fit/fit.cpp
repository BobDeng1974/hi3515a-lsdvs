/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.09.16
**  description  : Ϊ������һ�׹��̴�����Ӧ��ͬ��Ӳ��ƽ̨����������ļ�
********************************************************************************/

#include "const.h"
#include "ttypes.h"
#include "mympi.h"
#include "mpiApp.h"
#include "snapMpi.h"
#include "osdApply.h"
#include "mpiViFrame.h"

#include "osdViVo.h"

void FitEncAddTimer()
{
	EncAddTimer();
}

int FitFiOsdInitOsdLib()
{
	return FiOsdInitOsdLib();
}

int FitFiOsdDeinitOsdLib()
{
	return FiOsdDeinitOsdLib();
}

int FitMpiServiceStart()
{
	return MpiServiceStart();
}

int FitMpiServiceStop()
{
	return MpiServiceStop();

}

int FitSnapMpiGetJpgAndToProcon( int snapCh, uint snapType )
{
#if defined MCU_HI3515
	return SnapMpiGetJpgAndToProcon( snapCh, snapType );
#else
	return 0;
#endif
}

int FitMympiForceIframe( int channel )
{
	return MympiForceIframe( channel );
}

/*
* fn: ����ͼ��ȼ�,[0,5],
* val: [0..5]. Valid when CBR/VBR.
 	With different RC mode, it means differ.
 	CBR: scope of bitrate fluctuate. 1-5: 10%-50%. 0: SDK optimized, recommended;
 	VBR: Quality of picture. 0: Best; 5: Worst.
*/
int FitMympiSetLevel( int channel, int val )
{
#if defined MCU_HI3515
	return MympiSetLevel( channel, val );
#else
	return 0;
#endif
}

/*
* fn: ���ñ���������
* val: ���ʿ���ģʽ, 0,�ɱ����� VBR ģʽ; 1,�̶����� CBR ģʽ;
*/
int FitMympiSetBitrateType( int channel, int val )
{
#if defined MCU_HI3515
	return MympiSetBitrateType( channel, val );
#else
	return 0;
#endif
}


/*
* fn: ���ñ�����
* val: ��[1, 20000], bit rate. valid when CBR/VBR/ABR.
      With different RC mode, it means differ.
      CBR/ABR: average bitrate; 
      VBR: Max bitrate;
*/
int FitMympiSetBitrate( int channel, int val )
{
#if defined MCU_HI3515
	return MympiSetBitrate( channel, val );
#else
	return 0;
#endif
}

/*
* fn: ����֡����
* val: Ŀ��֡��,P ��(0, 25],N ��(0, 30]
*/
int FitMympiSetFramerate( int channel, int val )
{
#if defined MCU_HI3515
	return MympiSetFramerate( channel, val );
#else
	return 0;
#endif
}

/*
* fn: ����I ֡���
* val: I ֡���,[0, 1000]
*/
int FitMympiSetIframeInterval( int channel, int val )
{
#if defined MCU_HI3515
	return MympiSetIframeInterval( channel, val );
#else
	return 0;
#endif
}

/*
* fn: ���÷ֱ���
      ��������Ƶ�����漰����Ƶ�ֱ���ʱ����
*/
int FitMympiSetResolution()
{
#if defined MCU_HI3515
	return MympiSetResolution();
#else
	return 0;
#endif
}

int FitMympiSetVideoStandard()
{
#if defined MCU_HI3515A
	return MympiSetVideoStandard();
#else
	return 0;
#endif
}
                    
int FitFiOsdSetLogoOsdConfig( int channel, ConfigOsdLogo *setVal )
{
#if defined MCU_HI3515A
	return FiOsdSetLogoOsdConfig( channel, setVal );
#else
	return 0;
#endif
}

int FitFiOsdSetTimeOsdConfig( int channel, ConfigOsdTime *setVal )
{
#if defined MCU_HI3515A
	return FiOsdSetTimeOsdConfig( channel, setVal );
#else
	return 0;
#endif
}

/*
* fn: ���ð�������
* openFlag: 0,����Ƶ; ����ֵ, ��Ƶ
*/
int FitMympiSetAvencAccompanyingAudio( int channel, int openFlag )
{
#if defined MCU_HI3515
	if( 0 == openFlag )
    {
    	return MympiSetAvencAccompanyingAudio( channel, 1 );
    }
	else
    {
    	return MympiSetAvencAccompanyingAudio( channel, 0 );
    }
#else
	return 0;
#endif
}

/*
* fn: ��ȡ��Ƶ��ʧ״̬
*/
int FitMympiGetShelterDetect( int channel )
{
#if defined MCU_HI3515A
	return VideoGetShelterDetect( channel );
#else
	return 0;
#endif
}

int FitMympiSetAudioEncType()
{
#if defined MCU_HI3515A
	return MympiSetAudioEncType();
#else
	return 0;
#endif
}


