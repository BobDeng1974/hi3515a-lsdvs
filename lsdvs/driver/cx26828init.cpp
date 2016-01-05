/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.09.16
**  description  : ��ʼ��AD
*******************************************************************************
*/

#include "paramManage.h"
#include "driver.h"
#include "vencParamEasy.h"
#include "cx26828.h"
#include "hicomm.h"

int cx2866_init_videobaseparam()
{
	int i, ret;
	PARAM_CONFIG_VIDEO_BASE_PARAM vpparam;

	for( i = 0; i < REAL_CHANNEL_NUM; ++i )
    {
    	ret = ParamGetVideoBaseParam( i, &vpparam );
    	if( 0 == ret )
        {
        	DriverSetAdVideoCapParam( i, vpparam.brightness, vpparam.contrast,
                                	vpparam.hue, vpparam.saturation );
        }
    }

	return 0;
}


int cx2866_Init_videomode()
{
#if 1
	int ret;
	PARAM_CONFIG_VIDEO_ENCODE_PUBLIC param;
	uchar standard;

	standard = CX26828_MODE_PAL;
	ret = ParamGetVideoEncodePublic( &param );
	if ( FI_SUCCESS == ret ) 
    {
    	if ( VIDEO_ENCODING_MODE_PAL == param.videoStandard ) standard = CX26828_MODE_PAL;
    	else if ( VIDEO_ENCODING_MODE_NTSC == param.videoStandard ) standard = CX26828_MODE_NTSC;
    	else if ( VIDEO_ENCODING_MODE_AUTO == param.videoStandard ) standard = CX26828_MODE_AUTO;        
    	DriverSetAdVideoMode( 0, standard );
    	standard = (VIDEO_ENCODING_MODE_NTSC == param.videoStandard) ? (VIDEO_ENCODING_MODE_NTSC) : (VIDEO_ENCODING_MODE_PAL);
    	VencParamEasySetVideoStandard( standard );
    }

	return 0;
#endif	
}



