/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.09.16
**  description  : ��װ���������Ľӿ�
*******************************************************************************
*/
#include <unistd.h>
#include "const.h"
#include "linuxFile.h"
#include "driver.h"
#include "debug.h"
#include "tw2866Init.h"
#include "mpiApp.h"
#include "ptypes.h"
#include "vencParamEasy.h"
#include "tw2865.h"
#include "hicomm.h"
#include "timer.h"
#include "fit.h"

#include "cx26828.h"
#include "cx26828setting.h"
#include "nvp1914.h"



// ע��: ����������,ֻ����������������ĺ���(��������),��������extern
extern int set_image_parameter( int video_fd, int chn, uchar brightness, 
                            	uchar contrast, uchar hue, uchar saturation );

extern int get_video_loss(int video_fd, int chn);
extern int get_video_norm(int video_fd, int chn);
extern int get_image_parameter(int video_fd, int chn, uchar *brightness, uchar *contrast, uchar *hue, uchar *saturation);
extern int set_video_norm(int video_fd, int chn, int mode);

static uchar FitValue( uchar val )
{
	int lval;

	if( val < 128 )
    {
    	lval = val + 128;
    }
	else
    {
    	lval = val - 128;
    }

	return lval;
}

/*
* fn: ����Ad�ɼ�оƬ�Ĳɼ�����
* channel: ͨ��      0---3
* brightness: ����   0---255
* contrast: �Աȶ�   0---255
* hue: �Ҷ�          0---255
* saturation: ���Ͷ� 0---255
*/
int DriverSetAdVideoCapParam( int channel, uint brightness, 
                    	uint contrast, short hue, uint saturation )
{
	int fd = -1, ret = -1;
	uchar lbri, lcont, lhue, lsatu;
    
	//fd = Open( AD_DRVFILE, O_RDWR );
	//fd = Open( GPIOI2C, 0 );//yfchanged
	if( fd < 0 )
    {
    	ERRORPRINT( "Open(%s) fail!\r\n", AD_DRVFILE );
    	return -1;
    }
    else
    {
        //CORRECTPRINT("Open(%s) SUCCESS!\r\n", AD_DRVFILE );
    }

	lbri = brightness;
	lbri = FitValue(lbri);
	lcont = contrast;
	lhue = (uchar)hue;    
	lsatu = saturation;

	//ret = set_image_parameter( fd, channel, lbri, lcont, lhue, lsatu );
	ret = set_image_parameter_cx26828(fd, channel, lbri, lcont, lhue, lsatu);

    //ret = set_image_parameter_nvp1914(channel,lbri, lcont, lhue, lsatu);
	Close( fd );
    
    //ColorPrint(COLORPURPLE,"Setting Video ch(%d) Parameter ...ret = %d!\r\n", channel,ret );
	return ret;
}

int DriverGetAdVideoCapParam( int channel, uint *brightness, 
                    	uint *contrast, uint *hue, uint *saturation )
{
	int fd, ret;
	uchar lbri, lcont, lhue, lsatu;
    
	fd = Open( AD_DRVFILE, O_RDWR );
	if( fd < 0 )
    {
    	SVPrint( "Open(%s) fail!\r\n", AD_DRVFILE );
    	return -1;
    }
    
	ret = get_image_parameter_cx26828( fd, channel, &lbri, &lcont, &lhue, &lsatu );
    *brightness = (uint)lbri;
    *contrast = (uint)lcont;
    *hue = (uint)lhue;
    *saturation = (uint)lsatu;

	SVPrint( "Vedio param ch:%d, brightness:%d, contrast:%d, hue:%d, saturation:%d\n", \
                 channel, lbri, lcont, lhue, lsatu );

	Close( fd );
    
    //SVPrint( "Setting Video Parameter ...ret = %d!\r\n", ret );
	return ret;
}



/**************************************************************
*  fn:  �����Ƶ��ʧ��Ϣ
*   channel: ͨ����  0---3
*  return: 0:����   1:��ʧ   -1:����
***************************************************************/
int DriverGetAdVideoLoss( int channel )
{
	int fd, ret;
    
	fd = Open( AD_DRVFILE, O_RDWR );
	if( fd < 0 )
    {
    	SVPrint( "Get Video Loss Open(%s) fail!\r\n", TW2865_FILE );
    	return -1;
    }

	if ( (channel<0) || (channel>3) ) 
    {
    	SVPrint( "channel error!\r\n", AD_DRVFILE );
    	return -1;
    }
    
	ret = get_video_loss_cx26828( fd, channel );

	Close( fd );
    
    //SVPrint( "Setting Video Parameter ...ret = %d!\r\n", ret );
	return ret;    
}


/*************************************************************
*  fn:  �����Ƶģʽ
*   channel: ͨ����  0---3
*  return:  -1:fail    2:TW2865_PAL   1:TW2865_NTSC
**************************************************************/
int DriverGetAdVideoMode( int channel )
{
	int fd, ret;
    
	fd = Open( AD_DRVFILE, O_RDWR );
	if( fd < 0 )
    {
    	SVPrint( "Get Video Mode Open(%s) fail!\r\n", AD_DRVFILE );
    	return -1;
    }

	if ( (channel<0) || (channel>3) ) 
    {
    	SVPrint( "channel error!\r\n", AD_DRVFILE );
    	return -1;
    }
    
    
	ret = get_video_norm_cx26828( fd, channel );

	Close( fd );
    
    //SVPrint( "Setting Video Parameter ...ret = %d!\r\n", ret );
	return ret;    
}

/*
*  fn:  ������Ƶģʽ
*   channel: ͨ����  0---3
*  return:  -1:fail    2:TW2865_PAL   1:TW2865_NTSC  3:TW2865_AUTO
*/
int DriverSetAdVideoMode( int channel, int mode )
{
	int fd, ret;
    
	fd = Open( AD_DRVFILE, O_RDWR );
	if( fd < 0 )
    {
    	SVPrint( "Set Video Mode Open(%s) fail!\r\n", AD_DRVFILE );
    	return -1;
    }

	if ( (channel<0) || (channel>3) ) 
    {
    	SVPrint( "channel error!\r\n", AD_DRVFILE );
    	return -1;
    }        
    
	ret = set_video_norm_cx26828( fd, channel, mode );
	if (0 != ret)
    {
    	SVPrint( "set video mode error!\r\n" );
    }

	Close( fd );
    
    //SVPrint( "Setting Video Parameter ...ret = %d!\r\n", ret );
	return ret;    
}



/*
* fn: ��ʱ��� N��  P�� �л�
*/
static void *DriverVideoStandardDetect( void *args )
{
	int mode;
	uchar standard;

	standard = VencParamEasyGetVideoStandard();
	mode = DriverGetAdVideoMode( 0 );
	if ( CX26828_MODE_PAL == mode ) mode = VIDEO_ENCODING_MODE_PAL;
	else if ( CX26828_MODE_NTSC == mode ) mode = VIDEO_ENCODING_MODE_NTSC;

	if (mode == standard) return NULL;
	SVPrint( "detect video standard changed:%d\n", standard );
    
	VencParamEasySetVideoStandard( mode );
	FitMympiSetVideoStandard();

	return NULL;
}

void DriverVideoStandardDetectAddTimer(void)
{
	AddRTimer( DriverVideoStandardDetect, NULL, 5 );
}




void DriverInit()
{
    
}



