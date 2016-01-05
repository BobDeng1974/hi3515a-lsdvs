#ifndef __DCPINS_H__
#define __DCPINS_H__

#define  SV_MSG_REQ_BASE		0x6000
#define  SV_MSG_RES_BASE		0x8000

//1.��֤, �൱��login ����, ��logout ���Ӧ
#define SV_MSG_REQ_VARIFY               (SV_MSG_REQ_BASE + 0x1)    
#define SV_MSG_RES_VARIFY	            (SV_MSG_RES_BASE + 0x1)    

//2.����
#define SV_MSG_REQ_HEARTBEAT	        (SV_MSG_REQ_BASE + 0x2)
#define SV_MSG_RES_HEARTBEAT	        (SV_MSG_RES_BASE + 0x2)

//3.��ͨ��sessionID��֤ 
#define SV_MSG_REQ_STREAM_SESSIONID	    (SV_MSG_REQ_BASE + 0x3)
#define SV_MSG_RES_STREAM_SESSIONID	    (SV_MSG_RES_BASE + 0x3)

//4.ʵʱ������
#define SV_MSG_REQ_STREAM_START	        (SV_MSG_REQ_BASE + 0x4)
#define SV_MSG_RES_STREAM_START	        (SV_MSG_RES_BASE + 0x4)

//5.��ȡ��������
#define SV_MSG_REQ_GET_BASE_INFO	    (SV_MSG_REQ_BASE + 0x5)
#define SV_MSG_RES_GET_BASE_INFO	    (SV_MSG_RES_BASE + 0x5)

//6.��ȡ��������
#define SV_MSG_REQ_GET_NETWORK	        (SV_MSG_REQ_BASE + 0x6)
#define SV_MSG_RES_GET_NETWORK	        (SV_MSG_RES_BASE + 0x6)

//7.������������
#define SV_MSG_REQ_SET_NETWORK	        (SV_MSG_REQ_BASE + 0x7)
#define SV_MSG_RES_SET_NETWORK	        (SV_MSG_RES_BASE + 0x7)

//8.��ȡ�û�����(ȫ���û�)
#define SV_MSG_REQ_GET_CLIENT_USER	    (SV_MSG_REQ_BASE + 0x8)
#define SV_MSG_RES_GET_CLIENT_USER	    (SV_MSG_RES_BASE + 0x8)

//9.�����û�����
#define SV_MSG_REQ_SET_CLIENT_USER	    (SV_MSG_REQ_BASE + 0x9)
#define SV_MSG_RES_SET_CLIENT_USER	    (SV_MSG_RES_BASE + 0x9)

//10.��ȡ��Ƶ��������
#define SV_MSG_REQ_GET_VIDEO_BASE_PARAM	(SV_MSG_REQ_BASE + 0xA)
#define SV_MSG_RES_GET_VIDEO_BASE_PARAM	(SV_MSG_RES_BASE + 0xA)

//11.������Ƶ��������
#define SV_MSG_REQ_SET_VIDEO_BASE_PARAM	(SV_MSG_REQ_BASE + 0xB)
#define SV_MSG_RES_SET_VIDEO_BASE_PARAM	(SV_MSG_RES_BASE + 0xB)

//12.��ȡOSD logo
#define SV_MSG_REQ_GET_OSD_LOGO         (SV_MSG_REQ_BASE + 0xC)
#define SV_MSG_RES_GET_OSD_LOGO	        (SV_MSG_RES_BASE + 0xC)

//13.����OSD logo
#define SV_MSG_REQ_SET_OSD_LOGO         (SV_MSG_REQ_BASE + 0xD)
#define SV_MSG_RES_SET_OSD_LOGO         (SV_MSG_RES_BASE + 0xD)

//14.��ȡOSD time
#define SV_MSG_REQ_GET_OSD_TIME         (SV_MSG_REQ_BASE + 0xE)
#define SV_MSG_RES_GET_OSD_TIME	        (SV_MSG_RES_BASE + 0xE)

//15.����OSD time
#define SV_MSG_REQ_SET_OSD_TIME         (SV_MSG_REQ_BASE + 0xF)
#define SV_MSG_RES_SET_OSD_TIME	        (SV_MSG_RES_BASE + 0xF)

//16.��ȡ��Ƶ���빫������
#define SV_MSG_REQ_GET_VIDEO_ENCODE_PUBLIC	    (SV_MSG_REQ_BASE + 0x10)
#define SV_MSG_RES_GET_VIDEO_ENCODE_PUBLIC	    (SV_MSG_RES_BASE + 0x10)

//17.������Ƶ���빫������
#define SV_MSG_REQ_SET_VIDEO_ENCODE_PUBLIC      (SV_MSG_REQ_BASE + 0x11)
#define SV_MSG_RES_SET_VIDEO_ENCODE_PUBLIC	    (SV_MSG_RES_BASE + 0x11)

//18.��ȡ��Ƶ��������
#define SV_MSG_REQ_GET_AUDIO	                (SV_MSG_REQ_BASE + 0x12)
#define SV_MSG_RES_GET_AUDIO	                (SV_MSG_RES_BASE + 0x12)

//19.������Ƶ��������
#define SV_MSG_REQ_SET_AUDIO	            (SV_MSG_REQ_BASE + 0x13)
#define SV_MSG_RES_SET_AUDIO	            (SV_MSG_RES_BASE + 0x13)

//20.��ȡ�Զ�ά������
#define SV_MSG_REQ_GET_AUTO_MAINTAIN	    (SV_MSG_REQ_BASE + 0x14)
#define SV_MSG_RES_GET_AUTO_MAINTAIN	    (SV_MSG_RES_BASE + 0x14)

//21.�����Զ�ά������
#define SV_MSG_REQ_SET_AUTO_MAINTAIN	    (SV_MSG_REQ_BASE + 0x15)
#define SV_MSG_RES_SET_AUTO_MAINTAIN	    (SV_MSG_RES_BASE + 0x15)

//22.��ȡ¼�񹫹�����
#define SV_MSG_REQ_GET_RECORD_PUBLIC	    (SV_MSG_REQ_BASE + 0x16)
#define SV_MSG_RES_GET_RECORD_PUBLIC	    (SV_MSG_RES_BASE + 0x16)

//23.����¼�񹫹�����
#define SV_MSG_REQ_SET_RECORD_PUBLIC	    (SV_MSG_REQ_BASE + 0x17)
#define SV_MSG_RES_SET_RECORD_PUBLIC	    (SV_MSG_RES_BASE + 0x17)

//24.��ȡ����ͨ��¼�����
#define SV_MSG_REQ_GET_RECORD_PARAM	    (SV_MSG_REQ_BASE + 0x18)
#define SV_MSG_RES_GET_RECORD_PARAM	    (SV_MSG_RES_BASE + 0x18)

//25.���ø���ͨ��¼�����
#define SV_MSG_REQ_SET_RECORD_PARAM	    (SV_MSG_REQ_BASE + 0x19)
#define SV_MSG_RES_SET_RECORD_PARAM	    (SV_MSG_RES_BASE + 0x19)

//26.��ȡIO��������
#define SV_MSG_REQ_GET_ALARM_IO	    (SV_MSG_REQ_BASE + 0x1A)
#define SV_MSG_RES_GET_ALARM_IO	    (SV_MSG_RES_BASE + 0x1A)

//27.����IO��������
#define SV_MSG_REQ_SET_ALARM_IO	    (SV_MSG_REQ_BASE + 0x1B)
#define SV_MSG_RES_SET_ALARM_IO	    (SV_MSG_RES_BASE + 0x1B)

//28.��ȡNTP�������
#define SV_MSG_REQ_GET_NTP	            (SV_MSG_REQ_BASE + 0x1C)
#define SV_MSG_RES_GET_NTP	            (SV_MSG_RES_BASE + 0x1C)

//29.����NTP�������
#define SV_MSG_REQ_SET_NTP	            (SV_MSG_REQ_BASE + 0x1D)
#define SV_MSG_RES_SET_NTP	            (SV_MSG_RES_BASE + 0x1D)

//30.��ȡEMAIL�������
#define SV_MSG_REQ_GET_EMAIL	        (SV_MSG_REQ_BASE + 0x1E)
#define SV_MSG_RES_GET_EMAIL	        (SV_MSG_RES_BASE + 0x1E)

//31.����EMAIL�������
#define SV_MSG_REQ_SET_EMAIL	        (SV_MSG_REQ_BASE + 0x1F)
#define SV_MSG_RES_SET_EMAIL	        (SV_MSG_RES_BASE + 0x1F)

//32.��ȡ��Ƶ�������
#define SV_MSG_REQ_GET_VIDEO_ENCODE_PARAM	(SV_MSG_REQ_BASE + 0x20)
#define SV_MSG_RES_GET_VIDEO_ENCODE_PARAM	(SV_MSG_RES_BASE + 0x20)

//33.������Ƶ�������
#define SV_MSG_REQ_SET_VIDEO_ENCODE_PARAM	(SV_MSG_REQ_BASE + 0x21)
#define SV_MSG_RES_SET_VIDEO_ENCODE_PARAM	(SV_MSG_RES_BASE + 0x21)

//32.��ȡ��������Ƶ�������
#define SV_MSG_REQ_GET_VIDEO_ENCODE_PARAM_SLAVE	(SV_MSG_REQ_BASE + 0x22)
#define SV_MSG_RES_GET_VIDEO_ENCODE_PARAM_SLAVE	(SV_MSG_RES_BASE + 0x22)

//33.���ô�������Ƶ�������
#define SV_MSG_REQ_SET_VIDEO_ENCODE_PARAM_SLAVE	(SV_MSG_REQ_BASE + 0x23)
#define SV_MSG_RES_SET_VIDEO_ENCODE_PARAM_SLAVE	(SV_MSG_RES_BASE + 0x23)

//34.һ���Ի�ȡlogo OSD��ʱ��OSD
#define SV_MSG_REQ_GET_OSD	    (SV_MSG_REQ_BASE + 0x24)
#define SV_MSG_RES_GET_OSD	    (SV_MSG_RES_BASE + 0x24)

//35.һ��������logo OSD��ʱ��OSD
#define SV_MSG_REQ_SET_OSD     (SV_MSG_REQ_BASE + 0x25)
#define SV_MSG_RES_SET_OSD     (SV_MSG_RES_BASE + 0x25)

//36.ע����¼
#define SV_MSG_REQ_LOGIN_OUT     (SV_MSG_REQ_BASE + 0x26)

//37. �ָ���������
#define SV_MSG_REQ_RESET_FACTORY	(SV_MSG_REQ_BASE + 0x27)
#define SV_MSG_RES_RESET_FACTORY	(SV_MSG_RES_BASE + 0x27)

//38. �ָ�Ĭ�ϲ�������
#define SV_MSG_REQ_RESET_DEFAULT_PARAM	(SV_MSG_REQ_BASE + 0x28)
#define SV_MSG_RES_RESET_DEFAULT_PARAM	(SV_MSG_RES_BASE + 0x28)

//39. �ָ�Ĭ��ͨ�������������
#define SV_MSG_REQ_RESET_DEFAULT_CHANNEL_ENCODE_PARAM	(SV_MSG_REQ_BASE + 0x29)
#define SV_MSG_RES_RESET_DEFAULT_CHANNEL_ENCODE_PARAM	(SV_MSG_RES_BASE + 0x29)

//40. ��ȡʱ��
#define SV_MSG_REQ_GET_TIME	(SV_MSG_REQ_BASE + 0x2A)
#define SV_MSG_RES_GET_TIME	(SV_MSG_RES_BASE + 0x2A)

//41. ����ʱ��
#define SV_MSG_REQ_SET_TIME	(SV_MSG_REQ_BASE + 0x2B)
#define SV_MSG_RES_SET_TIME	(SV_MSG_RES_BASE + 0x2B)

//42.����¼��
#define SV_MSG_REQ_SEARCH_RECORD     (SV_MSG_REQ_BASE + 0x2C)
#define SV_MSG_RES_SEARCH_RECORD     (SV_MSG_RES_BASE + 0x2C)

//43.��������ϵͳ
#define SV_MSG_REQ_UPDATE	    (SV_MSG_REQ_BASE + 0x2D)
#define SV_MSG_RES_UPDATE	    (SV_MSG_RES_BASE + 0x2D)

//44. ʵʱ��ֹͣ
#define SV_MSG_REQ_STREAM_STOP	    (SV_MSG_REQ_BASE + 0x2E)

//45. ¼����������
#define SV_MSG_REQ_RECORD	    (SV_MSG_REQ_BASE + 0x2F)

//46. �ͻ�����dvs ע��
#define SV_MSG_REQ_LOGOUT	    (SV_MSG_REQ_BASE + 0x30)

//47. �����ļ�����
#define SV_MSG_REQ_TXUPDATEFILE	            (SV_MSG_REQ_BASE + 0x31)

//48. �����ļ�дFLASH����
#define SV_MSG_RES_WRITE_FLASH_PROGRESS	    (SV_MSG_RES_BASE + 0x32)

//49. �������
#define SV_MSG_RES_UPDATE_RESULT	            (SV_MSG_RES_BASE + 0x33)

//50. dvs��ͻ��˷��ͱ�����Ϣ
#define SV_MSG_RES_ALARM	                    (SV_MSG_RES_BASE + 0x34)

//51. ��־����
#define SV_MSG_REQ_GET_LOG                     (SV_MSG_REQ_BASE + 0x35)
#define SV_MSG_RES_GET_LOG                     (SV_MSG_RES_BASE + 0x35)

//52. SD����Ϣ����
#define SV_MSG_REQ_STORAGE_INFO                (SV_MSG_REQ_BASE + 0x36)
#define SV_MSG_RES_STORAGE_INFO                (SV_MSG_RES_BASE + 0x36)

//53.��ȡ��Ƶ��ʧ��������
#define SV_MSG_REQ_GET_ALARM_VLOSS	    (SV_MSG_REQ_BASE + 0x37)
#define SV_MSG_RES_GET_ALARM_VLOSS	    (SV_MSG_RES_BASE + 0x37)

//54.������Ƶ��ʧ��������
#define SV_MSG_REQ_SET_ALARM_VLOSS	    (SV_MSG_REQ_BASE + 0x38)
#define SV_MSG_RES_SET_ALARM_VLOSS	    (SV_MSG_RES_BASE + 0x38)

//55.��ȡ��Ƶ�ڵ���������
#define SV_MSG_REQ_GET_ALARM_SHELTER	    (SV_MSG_REQ_BASE + 0x39)
#define SV_MSG_RES_GET_ALARM_SHELTER	    (SV_MSG_RES_BASE + 0x39)

//56.������Ƶ�ڵ���������
#define SV_MSG_REQ_SET_ALARM_SHELTER	    (SV_MSG_REQ_BASE + 0x3A)
#define SV_MSG_RES_SET_ALARM_SHELTER	    (SV_MSG_RES_BASE + 0x3A)

//57.��ȡ�ƶ���ⱨ������
#define SV_MSG_REQ_GET_ALARM_MD	        (SV_MSG_REQ_BASE + 0x3B)
#define SV_MSG_RES_GET_ALARM_MD	        (SV_MSG_RES_BASE + 0x3B)

//58.�����ƶ���ⱨ������
#define SV_MSG_REQ_SET_ALARM_MD	        (SV_MSG_REQ_BASE + 0x3C)
#define SV_MSG_RES_SET_ALARM_MD	        (SV_MSG_RES_BASE + 0x3C)

//59. dvs��ͻ��˷���Ӳ����,���쳣������Ϣ, �����������ֿ�
#define SV_MSG_RES_HDD_STAT_ERR	        (SV_MSG_RES_BASE + 0x3D)

//60. �ն�ϵͳ����
#define SV_MSG_REQ_SYS_REBOOT	            (SV_MSG_REQ_BASE + 0x3E)
#define SV_MSG_RES_SYS_REBOOT	            (SV_MSG_RES_BASE + 0x3E)

//61. dvs��ͻ��˷���
#define SV_MSG_RES_PARAM_CHANGED	        (SV_MSG_RES_BASE + 0x3F)

//62. �������в���
#define SV_MSG_REQ_GET_ALL_PARAM	           (SV_MSG_REQ_BASE + 0x40)
#define SV_MSG_RES_GET_ALL_PARAM	           (SV_MSG_RES_BASE + 0x40)

//63. ��ȡ���в���
#define SV_MSG_REQ_SET_ALL_PARAM	           (SV_MSG_REQ_BASE + 0x41)
#define SV_MSG_RES_SET_ALL_PARAM	           (SV_MSG_RES_BASE + 0x41)


#endif // __DCPINS_H__

