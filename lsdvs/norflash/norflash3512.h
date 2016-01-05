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
#ifndef __NORFLASH3512_H__
#define __NORFLASH3512_H__


#if defined MCU_HI3515
/*
ע��: norflash ��ӳ���ַ�� 0x0200000 ��ʼ
**	0x00000000-0x00080000 : MTD 0	512K
**	0x00080000-0x00280000 : MTD 1	2M
**	0x00280000-0x01280000 : MTD 2	16M
**	0x01280000-0x01300000 : MTD 3	512K
**	0x01300000-0x02000000 : MTD 4	13M
*/
#define 	MTD_PARTITION_UBOOT	                "/dev/mtd0"    // uboot - 512K
#define 	MTD_PARTITION_KERNEL	            "/dev/mtd1"    // �ں� - 1.5
#define 	MTD_PARTITION_ROOTFS	            "/dev/mtd2"    // �ļ�ϵͳ - 16M
#endif
#define 	MTD_PARTITION_CONFIG	            "/dev/mtd3"    // ϵͳ���� - 512K
#define 	MTD_PARTITION_OTHER	                "/dev/mtd4"    // ���� - 13M


#if defined MCU_HI3515A
////////////////////////////////////////////////////////////
//HI3515A use spi flash block:64kB,size:16MB
//0x82000000-0x820fffff    MTD0:UBOOT,1M
//0x82100000-0x824fffff    MTD1:KENERL,4M
//0x82500000-0x82fffffff    MTD2:FS,11M
#define 	MTD_PARTITION_UBOOT	                "/dev/mtd0"    // uboot - 1M
#define 	MTD_PARTITION_KERNEL	            "/dev/mtd1"    // �ں� - 4M
#define 	MTD_PARTITION_ROOTFS	            "/dev/mtd2"    // �ļ�ϵͳ - 11M
#endif


///////////////////////////////////////////////////////////
/*
** ���溯��ע��:
** 1.���̰߳�ȫ;
** 2.��������norflashһ�������Ĵ�СΪ128KBytes,
**     ��д��������ʼ��ַҪ����������,������ʱ��Ҫ������������
** 3.mtdname������Ӧ MTD_PARTITION_*�ĺ�
*/
int mtd_erase(const char *mtdname, unsigned int start, unsigned int size);
int mtd_write(const char *mtdname, unsigned int start, unsigned int size, char *buffer);
int mtd_read(const char *mtdname, unsigned int start, unsigned int size, char *buffer);

#endif //__NORFLASH3512_H__

