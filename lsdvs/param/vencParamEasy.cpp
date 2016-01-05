/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.09.16
**  description  : ����Ľӿ���Ҫ��mpi ��Ƶ����ȡ��Ƶ֡��ʱ�����֡ͷʹ�õ�
        	��Щ�ӿ���ʵ������ paramManage.h ����Ľӿ�ʵ��,��������ʹ��
        	Ƶ�ʷǳ���,ÿ��ͨ����ÿһ֡���õ�,paramManage.h ����Ľӿڶ�
        	�漰��������������,Ч���е��,����ר��ʹ�ñ��ĵ��Ľӿ�
********************************************************************************/

#include "paramManage.h"
#include "vencParamEasy.h"

/* ===== video ===== */
static VIDEO_HEAD_LOCAL_T g_videoHeadLocal;

uchar VencParamEasyGetVideoStandard()
{
	return g_videoHeadLocal.videoStandard;
}

uchar VencParamEasyGetResolution( int channel )
{
	return g_videoHeadLocal.resolution[channel];
}

uchar VencParamEasyGetFramerate( int channel )
{
	return g_videoHeadLocal.frameRate[channel];
}

void VencParamEasySetVideoStandard( uchar val )
{
	g_videoHeadLocal.videoStandard = val;
}

void VencParamEasySetResolution( int channel, uchar val )
{
	g_videoHeadLocal.resolution[channel] = val;
}

void VencParamEasySetFramerate( int channel, uchar val )
{
	g_videoHeadLocal.frameRate[channel] = val;
}

static void VencParamEasyInit()
{
	int ret, i;
	PARAM_CONFIG_VIDEO_ENCODE_PUBLIC vepp;
	PARAM_CONFIG_VIDEO_ENCODE vep;
    
	ret = ParamGetVideoEncodePublic( &vepp );
	if( 0 == ret )
    {
    	g_videoHeadLocal.videoStandard = vepp.videoStandard;
    }
	for( i = 0; i < REAL_CHANNEL_NUM; ++i )
    {
    	ret = ParamGetVideoEncode( i, &vep );
    	if( 0 == ret )
        {
        	g_videoHeadLocal.resolution[i]    = vep.resolution;        
        	g_videoHeadLocal.frameRate[i]     = vep.frameRate;
        }
    }
}

/* ===== audio ===== */

static AUDIO_HEAD_LOCAL_T g_audioHeadLocal;

uchar VencParamEasyGetAudioSampleRate()
{
	return g_audioHeadLocal.sampleRate;
}

uchar VencParamEasyGetAudioBitWidth()
{
	return g_audioHeadLocal.bitWidth;
}

uchar VencParamEasyGetAudioEncodeType()
{
	return g_audioHeadLocal.encodeType;
}

uchar VencParamEasyGetAudioChMode()
{
	return g_audioHeadLocal.chMode;
}

void VencParamEasySetAudioSampleRate( uchar val )
{
	g_audioHeadLocal.sampleRate = val;
}

void VencParamEasySetAudioBitWidth( uchar val )
{
	g_audioHeadLocal.bitWidth = val;
}

void VencParamEasySetAudioEncodeType( uchar val )
{
	g_audioHeadLocal.encodeType = val;
}

void VencParamEasySetAudioChMode( uchar val )
{
	g_audioHeadLocal.chMode = val;
}

static void AudioParamEasyInit()
{
	int ret;
	PARAM_CONFIG_AUDIO_ENCODE param;
	ret = ParamGetAudio( &param );
	if( 0 == ret )
    {
    	VencParamEasySetAudioSampleRate( param.sampleRate );
    	VencParamEasySetAudioBitWidth( param.bitWidth );
    	VencParamEasySetAudioEncodeType( param.encodeType );
    	VencParamEasySetAudioChMode( param.chMode );
    }
}

void ParamEasyInit()
{
	VencParamEasyInit();
	AudioParamEasyInit();
}

