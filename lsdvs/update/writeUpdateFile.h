#ifndef __WRITEUPDATEFILE_H__
#define __WRITEUPDATEFILE_H__

#include "public.h"

#define UPDATE_FILE_ID	    "FD01"
#define UPDATE_HEAD_FLAG	"FdIvRsS01"

#define	MAX_UPGRADE_MEMORY	(16*1024*1024)
typedef enum _UpgradeErrorNo_
{
	UPGRADE_OK	        = 0,
	FILE_SIZE_ERROR	    = 1,
	MD5_CHECK_ERROR	    = 2,
	FILE_ID_ERROR	    = 3,
	FILE_TYPE_ERROR	    = 4,
	FILE_VERSION_ERROR	= 5,
	WRITE_FLASH_FAIL	= 6,
	UPGRADE_SAME_FILE	= 7,
	UPGRADE_OTHER_ERROR	= 0xff,
} UPDATE_ERROR_NO_EN;

typedef enum _UpgradeFileType_
{
	UPGRADE_FILE_TYPE_ROOTFS	= 10,
	UPGRADE_FILE_TYPE_UBOOT,
	UPGRADE_FILE_TYPE_KERNEL
} UPGRADE_FILE_TYPE_EN;


#ifndef PACK_ALIGN
#define PACK_ALIGN __attribute__((packed))
#endif

typedef struct _FileInfo_
{
	unsigned int version;    // �ļ��汾
	unsigned int type;        // �ļ�����: 0-�ļ�ϵͳ��1-UBOOT��2-�ں�
	unsigned int size;        // �ļ���С
} FILE_INFO;

typedef struct _UpgradeHead_
{
	unsigned char	headFlag[16];          // �ļ�ͷ��ʶ��FdIvRsS01
	unsigned int	headSize;              // �ļ�ͷ��С
	unsigned int	upgradeNum;              // �����ļ�������1 ~ 3��
	FILE_INFO		upgradeInfo[1];          // ������Ϣ
} UPGRADE_HEAD;

typedef struct UpgradeFileInfo
{
	unsigned char		id[4];                   // ����id
	unsigned short     	version;                 // �ļ��汾
	unsigned char		type;                    // �ļ�����
	unsigned char		reserve[9];              // ����
 	unsigned char		md5Key[MD5_KEY_SIZE];     // md5У����
} PACK_ALIGN UPGRADE_FILE_INFO;

#undef PACK_ALIGN

unsigned char UpgradeSystem( char *upgradeFile, int upgradeSize );

#endif //

