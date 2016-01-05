#ifndef __ALARMLINKAGE_H__
#define	__ALARMLINKAGE_H__

typedef struct _AlarmLinkageOutput_
{
	unsigned int	linkageAlarmOut;    // �����������,ÿ1bit��ʶһ���������
	unsigned char	alarmOutNum;        // �ܹ��ж��ٸ��������
	unsigned char	alarmOutDuration;    // �������ʱ��, ��λ��
	char	    	reserved[2];
} ALARM_LINKAGE_OUTPUT;

typedef struct _AlarmLinkageBuzzer_
{
	unsigned char   linkageBuzzer;        // ���������� 0: no linkage; 1: linkage;
	unsigned char	buzzerDuration;        // buzzer�����ʱ��, ��λ��
	char	    	reserved[2];
} ALARM_LINKAGE_BUZZER;

typedef struct _AlarmLinkageRecord_
{
	unsigned int	linkageRecord;        // ����¼��,ÿ1bit��ʶһ��ͨ��	    
	unsigned int 	recordType;            // ¼������
	unsigned char	recordDuration;        // ����¼��ʱ��, ��λ��	
	char	    	reserved[3];
} ALARM_LINKAGE_RECORD;

typedef struct _AlarmLinkageCapture_
{
	unsigned int   	linkageCapture;        // ����ץ��,ÿ1bit��ʶһ��ͨ��
	unsigned int 	captureType;        // ץ������
	unsigned char	captureNum;            // ץ������
	char	    	reserved[3];
} ALARM_LINKAGE_CAPTURE;

typedef struct _AlarmLinkageEmail
{
	unsigned char   linkageEmail;        //����eamil. 0: not send; 1: send;
	char	    	reserved[3];
} ALARM_LINKAGE_EMAIL;

void *AlarmLinkageOutput( void *args );
void *AlarmLinkageCapture( void *args );
void *AlarmLinkageRecord( void *args );
void *AlarmLinkageBuzzer( void *args );
void *AlarmLinkageEmail( void *args );

#endif 

