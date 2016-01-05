#ifndef __DCPERR_H__
#define __DCPERR_H__

#define DCP_RET_ERR_TIMEOUT	    (-2)

//Э��ȫ�ִ���
typedef enum _ErrorTypeEn_ 
{ 
   ERROR_TYPE_SUCCESSFUL             = 0,       // �ɹ� 
   ERROR_TYPE_OTHER                  = 9,       // �������� 
   ERROR_TYPE_USER_WRONG             = 10,      // �û������� 
   ERROR_TYPE_PASSWD_WRONG,                     // ���������� 
   ERROR_TYPE_OVER_MAX_USER,                    // ���������û��� 

   ERROR_TYPE_GET_PARAM_FAILED       = 13,      // ��ȡ����ʧ�� 
   ERROR_TYPE_SET_PARAM_FAILED,                 // ���ò���ʧ�� 
   ERROR_TYPE_CHANNEL,                          // �����ͨ���� 
   ERROR_TYPE_PARAM_OUTOF_RANGE,                // ����������Χ 
   ERROR_TYPE_UPDATE_FILE_WRONG_MD5,            // �����ļ�MD5 У����� 
    
   ERROR_TYPE_UPDATE_FILE_WRONG_TYPE = 18,      // �����ļ����ʹ��� 
   ERROR_TYPE_UPDATE_FILE_SIZE,                 // �����ļ��Ĵ�С���� 
   ERROR_TYPE_DEV_MEMORY_NOT_ENOUGH,            // �豸�ڴ治��    
   ERROR_TYPE_UPDATE_PARAM_INVAL,               // ������������Ƿ�    
   ERROR_TYPE_upDATE_OTHER_UPDATE,              // �����û�������    

   ERROR_TYPE_UPDATE_THREAD_FAIL	= 23,       // ���������߳�ʧ��    
   ERROR_TYPE_UPDATE_WRITE_FLASH,               // �����ļ�дflashʧ��    
} ERROR_TYPE_EN;


// �ͻ���sdk ��������
typedef enum _CErrorTypeEn_
{
	CERROR_TYPE_CONNECT = 512,       // ���Ӵ���	
	CERROR_TYPE_TIMEOUT,             // ��ʱ
	CERROR_TYPE_ISNOT_LOGIN,         // �û�û��½
	CERROR_TYPE_NOT_PERMISSION,      // Ȩ�޲���     
} CERROR_TYPE_EN;

#endif 

