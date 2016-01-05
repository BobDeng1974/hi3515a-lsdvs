#ifndef __PUBLIC_H__
#define __PUBLIC_H__

#define MAX_SUPPORT_SNAP_TYPE_NUM		32
#define SNAP_TYPE_HAND	(0x01<<0)        //�ֶ�
#define SNAP_TYPE_TIMER	(0x01<<1)        //��ʱ
#define	SNAP_TYPE_ALARM_IO	(0x01<<2)    //IO(̽ͷ)����
#define SNAP_TYPE_ALARM_MD	(0x01<<3)    //�ƶ���ⱨ��
#define SNAP_TYPE_ALARM_LOST	(0x01<<4)        // ��Ƶ��ʧ����
#define SNAP_TYPE_ALARM_PIC_COMPARE (0x01<<5)     // ͼ��Աȱ���
#define SNAP_TYPE_ALARM_SHELTER (0x01<<5)     // ��Ƶ�ڵ�����
#define SNAP_TYPE_ALARM_ALL	(SNAP_TYPE_ALARM_IO | \
                                 SNAP_TYPE_ALARM_MD | \
                                 SNAP_TYPE_ALARM_LOST | \
                                 SNAP_TYPE_ALARM_PIC_COMPARE | \
                                 SNAP_TYPE_ALARM_SHELTER)
#define SNAP_TYPE_ALL	(SNAP_TYPE_HAND  | \
                    	SNAP_TYPE_TIMER  | \
                         SNAP_TYPE_ALARM_ALL)


/*¼������,Ŀǰ���֧��32�ֱ���,�Ժ����¼������ֻ��������ӣ�ÿ����Ӷ�Ҫ����RECORD_TYPE_ALL*/
#define MAX_SUPPORT_RECORD_TYPE_NUM		32
#define RECORD_TYPE_HAND	            (0x01<<0)    //�ֶ�
#define RECORD_TYPE_TIMER	            (0x01<<1)    //��ʱ
#define	RECORD_TYPE_ALARM_IO	        (0x01<<2)    //IO(̽ͷ)����
#define RECORD_TYPE_ALARM_MD	        (0x01<<3)    //�ƶ���ⱨ��
#define RECORD_TYPE_ALARM_LOST	        (0x01<<4)    //��Ƶ��ʧ����
#define RECORD_TYPE_ALARM_SHELTER	        (0x01<<5)    //��Ƶ�ڵ�����
#define RECORD_TYPE_ALARM_ALL	( RECORD_TYPE_ALARM_IO | \
                                  RECORD_TYPE_ALARM_MD | \
                                  RECORD_TYPE_ALARM_LOST | \
                                  RECORD_TYPE_ALARM_SHELTER)                                      
#define RECORD_TYPE_ALL	        ( RECORD_TYPE_HAND  | \
                                   RECORD_TYPE_TIMER | \
                                   RECORD_TYPE_ALARM_ALL )


#define MAX_JPG_CHN_NUM     	5         // 4 · D1 ��1 ·�����ץ��
#define IPC_JPG_CHN_NUM     	1         // 1 ·�����ץ��

#define D1_WIDTH	        	704
#define D1_HEIGHT	        	576
#define CIF_WIDTH	            (D1_WIDTH/2)
#define CIF_HEIGHT	            (D1_HEIGHT/2)
#define QCIF_WIDTH	            (CIF_WIDTH/2)
#define QCIF_HEIGHT	            (CIF_HEIGHT/2)

#define MAX_SNAP_JPG_PATH_LEN		128
#define MD5_KEY_SIZE		16

#endif 

