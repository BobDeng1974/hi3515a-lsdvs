/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.05.03
**  description  : IO�ڿ���
*******************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "debug.h"
#include "const.h"
#include "gpio.h"


#define GPIO_DEVICE_PATH	    "/dev/hi_gpio"

static signed int fd = -1;

void GpioDirInit(void);


/*
* fn: GPIO ��ʼ������GPIO�豸
* return : 0:�ɹ�    -1:ʧ��
*/
int GpioInit(void)
{
	int ret;

	ret = FI_FAIL;
    if(fd <= 0)
    {
    	fd = open( GPIO_DEVICE_PATH, O_RDWR );
    	if(fd <= 0)
        {
        	SVPrint("failed: GpioInit!\r\n");
        	ret = FI_FAIL;
        }
    	else 
        {
        	GpioDirInit();
        	ret = FI_SUCCESS;
        }
    }

    return ret;
}


int  GpioDeinit(void)
{
    if(fd > 0)
    {
        close(fd);
        fd = -1;
    	SVPrint("Gpio Close!\r\n");
    }
    
    return FI_SUCCESS;
}



int  GpioSetDir( GPIO_GROUP_EN gpioGroup, GPIO_BIT_EN gpioBit, GPIO_DIR_EN gpioDir )
{
    int tmp=0;
    GPIO_GROUPBIT_INFO_T groupDirInfo;
	int ret = FI_SUCCESS;

    groupDirInfo.group = gpioGroup;
    groupDirInfo.bit = gpioBit;
    groupDirInfo.value = gpioDir;

    if(fd <= 0)
    {
    	SVPrint("failed: Gpio set dir fd<0 !\r\n");
    	ret = FI_FAIL;
    }
	else 
    {
    	tmp = ioctl( fd, GPIO_SET_DIR, (unsigned long)&groupDirInfo );
    	if(tmp != 0)
        {
        	SVPrint("failed: Gpio set dir ioctl() !\r\n");
        	ret = FI_FAIL;
        }
        
    }

    return ret;
}


int  GpioSetBit(GPIO_GROUP_EN gpioGroup, GPIO_BIT_EN gpioBit, GPIO_BIT_VALUE_EN bitValue)
{
    signed int tmp=0;
    GPIO_GROUPBIT_INFO_T groupDirInfo;
	int ret = FI_SUCCESS;

    groupDirInfo.group = gpioGroup;
    groupDirInfo.bit = gpioBit;
    groupDirInfo.value = bitValue;

    if(fd <= 0)
    {
    	SVPrint("failed: Gpio set bit fd<0 !\r\n");
    	ret = FI_FAIL;
    }
	else 
    {
        tmp = ioctl( fd, GPIO_WRITE_BIT, (unsigned long)&groupDirInfo );
        if(tmp != 0)
        {
        	SVPrint("failed: Gpio set bit ioctl() !\r\n");
        	ret = FI_FAIL;
        }        
    }
    
    return ret;
}


/************************************************************************
* fn: ���IO��״̬
* gpioGroup:
* gpioBit:
* return : -1:ʧ��    0:low  1:high
*************************************************************************/
int  GpioGetBit(GPIO_GROUP_EN gpioGroup, GPIO_BIT_EN gpioBit)
{
    signed int tmp=0;
    GPIO_GROUPBIT_INFO_T groupDirInfo;
    //int ret = FI_SUCCESS;
	int bitValue;

    groupDirInfo.group = gpioGroup;
    groupDirInfo.bit = gpioBit;

    if(fd <= 0)
    {
    	SVPrint("failed: Gpio get bit fd < 0 !\r\n");
    	return FI_FAIL;
    }
	else 
    {
        tmp = ioctl( fd, GPIO_READ_BIT, (unsigned long)&groupDirInfo );
        if(tmp != 0)
        {
        	SVPrint("failed: Gpio get bit ioctl !\r\n");
        	return FI_FAIL;
        }
    }

	bitValue = groupDirInfo.value;
    
    return bitValue;
}



/*===========================================================================================================
*  ����Ϊ GPIO  ͨ�ýӿ�   ����Ϊ�û�GPIO��ʼ��
*============================================================================================================*/


/******************************************************************************
* fn: ��ʼ��ϵͳ�����õ���GPIO
*******************************************************************************/
void GpioDirInit(void)
{
    //������
	GpioSetDir(GPIO_BUZZER_GROUP, GPIO_BUZZER_BIT, GPIO_DIR_OUT);
	GpioSetDir(GPIO_RECORD_LED_GROUP, GPIO_RECORD_LED_BIT, GPIO_DIR_OUT);
	GpioSetDir(GPIO_ALARM0_GROUP, GPIO_ALARM0_BIT, GPIO_DIR_IN);
	GpioSetDir(GPIO_ALARM1_GROUP, GPIO_ALARM1_BIT, GPIO_DIR_IN);

	GpioBuzzerDisable();
	GpioRecordLedDisable();
}

void GpioBuzzerEnable(void)
{
	GpioSetBit(GPIO_BUZZER_GROUP, GPIO_BUZZER_BIT, GPIO_BIT_HIGH);
}

void GpioBuzzerDisable(void)
{
	GpioSetBit(GPIO_BUZZER_GROUP, GPIO_BUZZER_BIT, GPIO_BIT_LOW);
}

void GpioRecordLedEnable(void)
{
	GpioSetBit(GPIO_RECORD_LED_GROUP, GPIO_RECORD_LED_BIT, GPIO_BIT_HIGH);
}

void GpioRecordLedDisable(void)
{
	GpioSetBit(GPIO_RECORD_LED_GROUP, GPIO_RECORD_LED_BIT, GPIO_BIT_LOW);
}




