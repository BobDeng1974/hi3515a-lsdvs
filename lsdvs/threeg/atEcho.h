/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ����3Gģ��Ļ���
**  date           :  2014.9.25
**
**  version       :  1.0
**  author        :  sven
********************************************************************************/


#ifndef __ATECHO_H__
#define __ATECHO_H__

typedef enum _AtEcho_
{
	AT_ECHO_OFF = 0,    // �رջ���
	AT_ECHO_ON	        // �򿪻���
} AT_ECHO_EN;

int FiAtEchoCtl( AT_ECHO_EN flag );    
    
#endif

