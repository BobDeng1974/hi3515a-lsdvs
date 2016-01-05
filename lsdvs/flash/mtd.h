/*
*******************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾
**  All rights reserved.
**	�ļ���: norflash.h
**  description  : ��תnorflsh MTD�ӿ�
**  date           :  2013.12.03
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef __NORFLASH_H__
#define __NORFLASH_H__

////////////////////////////////////////////////////////////
//HI3515A use spi flash block:64kB,size:16MB
//0x82000000-0x820fffff    MTD0:UBOOT,1M
//0x82100000-0x824fffff    MTD1:KENERL,4M
//0x82500000-0x82efffff    MTD2:FS,10M
//0x82f00000-0x82ffffff     MTD3:conf,1M
#define 	MTD_PARTITION_UBOOT	                "/dev/mtd0"    // uboot - 1M
#define 	MTD_PARTITION_KERNEL	            "/dev/mtd1"    // �ں� - 4M
#define 	MTD_PARTITION_ROOTFS	            "/dev/mtd2"    // �ļ�ϵͳ - 10M
#define 	MTD_PARTITION_CONFIG	            "/dev/mtd3"    // ϵͳ���� - 1M
//no use follow
#define 	MTD_PARTITION_OTHER	                "/dev/mtd4"    // ���� - 13M

///////////////////////////////////////////////////////////
/*
** ���溯��ע��:
** 1.���̰߳�ȫ;
** 2.��������flashһ�������Ĵ�СΪ64KBytes,
**     ��д��������ʼ��ַҪ����������,������ʱ��Ҫ������������
** 3.mtdname������Ӧ MTD_PARTITION_*�ĺ�
*/
int mtd_erase(const char *mtdname, unsigned int start, unsigned int size);
int mtd_write(const char *mtdname, unsigned int start, unsigned int size, char *buffer);
int mtd_read(const char *mtdname, unsigned int start, unsigned int size, char *buffer);

#endif //__NORFLASH_H__

