#ifndef __EMAIL_H__
#define __EMAIL_H__

#define EMAIL_SEND_TYPE_IO_TEST     	1	// �����ʼ�����
#define EMAIL_SEND_TYPE_IO_PROBER     	2	// IO̽ͷ��������
#define EMAIL_SEND_TYPE_VIDEO_LOSE     	3	// ��Ƶ��ʧ��������
#define EMAIL_SEND_TYPE_MOTION         	4	// ��Ƶ�ƶ����������ʼ�
#define EMAIL_SEND_TYPE_TIMER_CAPTURE 	5	// ��ʱץ�·����ʼ�

typedef struct __send_mail_info_t_ 
{
	int ch;
	int emailSendType;
} send_mail_info_t;

#ifdef __cplusplus
extern "C" {
#endif

int hh_mail_startSendMail(int ch, int emailSendType);
int hh_mail_sendMail(send_mail_info_t *send_mail_info,char *param);

#ifdef __cplusplus
}
#endif 

#endif 

