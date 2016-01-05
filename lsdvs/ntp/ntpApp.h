#ifndef __NTPAPP_H__
#define __NTPAPP_H__

typedef enum _NtpMaintain_
{
	NTP_MAINTAIN_WORK = 10,
	NTP_MAINTAIN_RESTART,
	NTP_MAINTAIN_NOT_ENABLE,
} NTP_MAINTAIN_EN;

typedef struct _NtpApp_
{
	unsigned char	enable;        // �Ƿ�ʹ��
	char	    	zone;        // ����ʱ��
	unsigned short	interval;    // ����ö�ʱһ��,��λ��	
	char	    	host[64];    // ֧������
	int	        	count;        // ��count == 0, ���ntpʱ��д��ϵͳ��rtc,�������д��rtc	
} NTP_APP_T;

int NtpAppGetRunFlag();
int NtpAppMaintain();
int NtpAppSaveTime( int second );
int NtpAppGetParam( int *pInterval, char *pHost );

void StartNtpAppService();
void StopNtpAppService();
void NtpAppOutMaintain();

#endif // __NTPAPP_H__

