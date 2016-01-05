/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**	�ļ���: hdd.h
**  description  : for hdd.cpp
**  date           :  2013.10.18
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/

#ifndef __HDD_H__
#define __HDD_H__

#include "const.h"

#define FAT32	"vfat"

#define MIN_PARTITION_SIZE	    	50	//¼����С���÷�����С 50MBytes
#define MIN_PARTITION_SIZE_OTHER	10	//����Ӧ����С���÷�����С 10MBytes

#define MAX_HDD_PARTITION_NUM	32	    //���֧��32������
#define MAX_HDD_PATH_NAMESIZE	64	    //Ӳ��·������ֽ���

#define UEVENT_BUFFER_SIZE 2048

#define MMC_INSERT_MARK	    "add@/block/mmcblk0/mmcblk0p"
#define MMC_REMOVE_MARK	    "remove@/block/mmcblk"

//usb insert mark:add@/devices/platform/hisilicon-ohci.0/usb1/1-1/1-1:1.0/host*/target*:0:0/0:0:0:0
//note:but "/target*" is not used.
#define USB_INSERT_MARK_FIRST	"add@/devices"
#define USB_INSERT_MARK_SECOND	"/host"
#define USB_REMOVE_MARK_FIRST	"remove@/devices"
#define USB_REMOVE_MARK_SECOND	"/host"

//MMC ���豸Ŀ¼
// #define MMC_DEV_PATH	        "/dev/mmc/blk0"
#define MMC_DEV_PATH	        "/dev/"


//USB���豸Ŀ¼
//usb dev path:/dev/scsi/host*/bus0/target0/lun0/part*
#define USB_DEV_PATH_FIRST	    "/dev/scsi"
#define USB_DEV_PATH_SECOND	    "bus0/target0/lun0"


#define MMC_MOUNT_PATH	        "/hdd/mmcp"    //EXAMPLE:hdd/mmcp0
#define USB_MOUNT_PATH	        "/hdd/sda"    //EXAMPLE:/hdd/sda0

//��mount�ķ�����ʶ
#define MMC_MOUNT_PARTITION_MARK	        "mmcp"
#define USB_MOUNT_PARTITION_MARK	        "sda"

// ������ʶ
#define MMC_DEV_PARTITION_MARK	        "mmcblk0p"
#define USB_DEV_PARTITION_MARK	        "part"

//���̻�MMC/SD��mount�ĸ�Ŀ¼
#define HDD_ROOT_DIR	"/hdd"    

typedef enum _HddState_
{
	HDD_STATE_START = 0,    // ��ʼ
	HDD_STATE_NORMAL,    // ����
	HDD_STATE_STOP,            // ֹͣ
	HDD_STATE_SLEEP,        // ����
} HDD_STATE_EN;

typedef enum _HddDevTypeSt
{
	HDD_TYPE_MMC = 0,
	HDD_TYPE_USB
}HDD_DEV_TYPE_ST;

typedef enum _HddStatusSt
{
	HDD_NONE = 0,            //û�м�⵽/�Ƴ�
	HDD_DETECT,                //��⵽
	HDD_MOUNTED,            //�Ѿ�mount��
	HDD_MOUNT_FAILED,        //mountʧ��
	HDD_UMOUNT_FAILED	    //umountʧ��
}HDD_STATUS_ST;

typedef struct _HotPlugManage
{
	int mmcInsertFlag;
	int mmcRemoveFlag;
	int usbInsertFlag;
	int usbRemoveFlag;
}HOTPLUG_MAMAGE;

typedef struct _HddPartitionInfoSt
{
	char	devPath[MAX_HDD_PATH_NAMESIZE];            //�����豸·��
	char 	mountPath[MAX_HDD_PATH_NAMESIZE];        //����mount·��
	int 	mountFlag;                                //�Ƿ��Ѿ�mount�� HDD_STATUS_ST
	int 	type;                                    //�����豸���� HDD_DEV_TYPE_ST
	long 	totalSize;                                //�����ܴ�С ��λMBytes
	long 	freeSize;                                //����ʣ��ռ� ��λMBytes	
}HDD_PARTITION_INFO_ST;

typedef struct _HddManageSt
{
	int totalMounted;                        //�����Ѿ�mount��ȥ�ķ���	
	HDD_PARTITION_INFO_ST	usingPart;        //��ǰ�����б�
	HDD_PARTITION_INFO_ST	partHead[MAX_HDD_PARTITION_NUM];//���з����б�
}HDD_MANAGE_ST;

int FiHddGetMaxPartitionNum(void);
int FiHddGetHddPartitionPath(int partition,char *path);
int FiHddGetUsingPartition(char *hddPath);
int FiHddGetHddExistFlag(int type,int *flag);
int FiHddGetTotalMounted();
int FiHddGetPartitionFreeSize(int partition);

int FiHddStartHotplugService();
int FiHddStopHotplugService();

void HddStateSet( int state );
int HddStateGet();

int FiHddStopHotPlugForDelRecord();
int FiHddRestartHotPlugForDelRecord();

int FiHddGetHddManage(HDD_MANAGE_ST *pHddManageSt);

int FiHddGetHddPartitionFault();
void FiHddSetHddPartitionFault(int hddPartitionFault);
int FiHddHddStatErrReport(int errCode);

#endif //__HDD_H__

