/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ��ͷ�ļ��ṩ�����ù�����صĺ����Ľӿڡ�
**  date           :  2013.11.24
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef _CONFIG_MANAGE_H
#define _CONFIG_MANAGE_H

#include "sysConfig.h"
#include "configProtocol.h"


#ifdef __cplusplus
extern "C" {
#endif

//
// ϵͳ��������
//
int CfgManageGetDevName( char *devName );
int CfgManageGetDevId( char *devId );
int CfgManageSetTalkbackVoice( int voiceInLevel, int voiceOutLevel );
int CfgManageGetVideoStandard( int *standard );
int CfgManageGetNtpParam( unsigned char *ntpType, unsigned short *ntpPort, char *ntpAddr );
int CfgManageSetNtpParam( unsigned char ntpType, unsigned short ntpPort, char *ntpAddr );

//
// �������
//
int CfgManageGetMacAddr( char *mac );
int CfgManageGetNetwork( char *ip, char *netmask, char *dns, char *dns2, char *gateway );
int CfgManageSetNetwork( char *ip, char *netmask, char *dns, char *dns2, char *gateway );
int CfgManageSetNetworkReboot( char *ip, char *netmask, char *dns, char *dns2, char *gateway );

//
// ��̨���Ʋ���
//
int CfgManageGetPtzControl( int channel, SYS_CONFIG_PTZ_CONTROL *ptzControl );
int CfgManageSetPtzControl( int channel, SYS_CONFIG_PTZ_CONTROL *ptzControl );

//
// ��̨����Э�� 
//
int CfgManageGetPtzProtocol( char *ptzName, SYS_CONFIG_PTZ_PROTOCOL *ptzProtocol );
int CfgManageSetPtzProtocol( SYS_CONFIG_PTZ_PROTOCOL *ptzProtocol );

//
// ��Ƶ����
//
int CfgManageGetVideoParam( int channel, SYS_CONFIG_VIDEO_BASE_PARAM *video );
int CfgManageSetVideoParam( int channel, SYS_CONFIG_VIDEO_BASE_PARAM *video );

int CfgManageGetBrightness( int channel, int *brightness );
int CfgManageSetBrightness( int channel, int brightness );
int CfgManageGetContrast( int channel, int *contrast );
int CfgManageSetContrast( int channel, int contrast );
int CfgManageGetHue( int channel, int *hue );
int CfgManageSetHue( int channel, int hue );
int CfgManageGetSaturation( int channel, int *saturation );
int CfgManageSetSaturation( int channel, int saturation );
int CfgManageGetExposure( int channel, int *exposure );
int CfgManageSetExposure( int channel, int exposure );

//
// OSD����
//
int CfgManageGetOsdLogo( int channel, CONFIG_OSD_LOGO *osdLogo );
int CfgManageSetOsdLogo( int channel, CONFIG_OSD_LOGO *osdLogo );
int CfgManageGetOsdTime( int channel, CONFIG_OSD_TIME *osdTime );
int CfgManageSetOsdTime( int channel, CONFIG_OSD_TIME *osdTime );

//
// ��Ƶ����
//
int CfgManageGetVideoEncodeParam( int channel, SYS_CONFIG_VIDEO_ENCODE *videoEncode, int chType = 0 );
int CfgManageSetVideoEncodeParam( int channel, SYS_CONFIG_VIDEO_ENCODE *videoEncode, int chType = 0 );

int CfgManageGetBitStreamRate( int channel, int chType, int *bitRate );
int CfgManageSetBitStreamRate( int channel, int chType, int bitRate );
int CfgManageGetFrameRate( int channel, int chType, int *frameRate );
int CfgManageSetFrameRate( int channel, int chType, int frameRate );
int CfgManageGetIFrameInterval( int channel, int chType, int *interval );
int CfgManageSetIFrameInterval( int channel, int chType, int interval );

//
// ¼�����
//
int CfgManageGetRecordTimerPolicy( int channel, int weekDay, CONFIG_TIMER_WEEK *recTimerPolicy );
int CfgManageSetRecordTimerPolicy( int channel, int weekDay, CONFIG_TIMER_WEEK *recTimerPolicy );
int CfgManageGetRecordHand( int channel, CONFIG_RECORD_HAND *getVal );
int CfgManageSetRecordHand( int channel, CONFIG_RECORD_HAND *setVal );
int CfgManageGetLoopRecordFlag( int *flag );
int CfgManageSetLoopRecordFlag( int flag );

#ifdef __cplusplus
}
#endif

//
// �Զ�ά��
//
int CfgManageAutoMaintainReboot( unsigned char flag, unsigned int date, unsigned int time );
int CfgManageAutoMaintainReboot();

//
// ����Email
//
int CfgManageSendEmail( char *message );
int CfgManageGetSdExistFlag( int *flag );
int CfgManageGetUsbExistFlag( int *flag );

//
// �����ϴ�Э������
//
int CfgManageGetDataUploadMode( int *mode );
int CfgManageGetDataUploadLastTime( time_t *lastTime );
int CfgManageSetDataUploadLastTime( time_t lastTime );
int CfgManageGetDataUploadParam( SYS_CONFIG_DATA_UPLOAD *dataUpload );
int CfgManageGetDataUploadOK();

//
// PC������
//
int CfgManageGetPcDirection( int channel, int *oriVertical, int *oriEnter );
int CfgManageSetPcDirection( int channel, int oriVertical, int oriEnter );
int CfgManageGetPcDetectArea( int channel, int *left, int *top, int *right, int *bottom );
int CfgManageSetPcDetectArea( int channel, int left, int top, int right, int bottom );
int CfgManageIsOpenPcDetect( int channel );
int CfgManageOpenPcDetect( int channel );
int CfgManageClosePcDetect( int channel );
int CfgManageGetVideoMode( int channel );
int CfgManageSetVideoMode( int channel, int videoMode );

//
//�м������
//
int CfgManageGetMidUserParam( SYS_CONFIG_MIDWARE midParam[] );
int CfgManageSetMidUserParam( SYS_CONFIG_MIDWARE midParam[] );

//
// PC�Ź������
//
int CfgManageGetPcDoorRule( int *pcType, int *doorType, int *doorRule );
int CfgManageSetPcDoorRule( int pcType, int doorType, int doorRule );

//
// PC����
//
int CfgManageSetSaveHistoryData( int bSaveHistoryData );
int CfgManageIsSaveHistoryData();

//
// AB�ż��
//
int CfgManageGetABDoorDirection( int channel, int *oriVertical, int *oriEnter );
int CfgManageSetABDoorDirection( int channel, int oriVertical, int oriEnter );
int CfgManageGetABDoorDetectArea( int channel, int *left, int *top, int *right, int *bottom );
int CfgManageSetABDoorDetectArea( int channel, int left, int top, int right, int bottom );
int CfgManageIsOpenABDoorDetect( int channel );
int CfgManageOpenABDoorDetect( int channel );
int CfgManageCloseABDoorDetect( int channel );
int CfgManageGetABDoorSensitivity( int channel );
int CfgManageGetABDoorStayerMax( int channel );

//
// FIV�˶�Ŀ����
//
int CfgManageOpenFivDetect( int channel );
int CfgManageCloseFivDetect( int channel );

//
// �����㷨���
//
int CfgManageIsOpenSmartDetect( int channel );
int CfgManageOpenSmartDetect( int channel );
int CfgManageCloseSmartDetect( int channel );

// 
// RF433M����
//
int CfgManageGetRf433mConfig( SYS_CONFIG_RF433M_PARAM *rf433mParam );
int CfgManageSetRf433mConfig( SYS_CONFIG_RF433M_PARAM *rf433mParam );
int CfgManageIsSupportRf433m();    //��licence��RF433M�İ汾��,������DVS�ͻ���ѡ���Ƿ�֧��RF433M����

//
// u-boot����������ʶ
// flag: = UBOOT_ENV_ERASE_FLAG, ��˵��u-boot����������; = ����ֵ,��û�в���
//
int CfgManageSetUbootEnvEraseFlag( unsigned int flag );
int CfgManageGetUbootEnvEraseFlag( unsigned int *flag );

//
// u-boot�������MAC��ַ����
// flag: = UBOOT_ENV_ERASE_FLAG, ��˵��u-boot����������; = ����ֵ,��û�в���
//
int CfgManageSetUbootEnvBackupMac( char *mac );
int CfgManageGetUbootEnvBackupMac( char *mac );
//
// LED����
//
int CfgManagerGetLedShowSetting( SYS_CONFIG_LEDSHOW_SETTING  *pLedShowSetting );
int CfgManagerGetLedBoardSetting( SYS_CONFIG_LEDBOARD_SETTING *pLedBoardSetting );
int CfgManagerLedIsDispDatetime();
int CfgManagerLedIsDispDayTotalIn();
int CfgManagerLedIsDispHourTotalIn();
int CfgManagerLedIsDispInnerCount();
int CfgManagerLedIsDispCustom();

//
// ������
//
int CfgManagerGetGroupSetting( SYS_CONFIG_GROUP_SETTING *pGroupSetting );
int CfgManagerGetEverydayConf( int *pHour, int *pMinute );
int CfgManagerGetGroupPeopleInfo( int *pLimitPeople, int *pAlarmPeople );
int CfgManagerIsSupportGroup();    // ��֧�������Ļ����÷���������Ϣ
int CfgManagerIsMasterDev();    // �Ƿ����豸
int	CfgManagerGetMasterServerIp( char *pIP ); // ��ȡ���豸IP
int CfgManagerGetSyncInterval( int *pSyncInterval ); // ͬ�����

// 
// ��ȡ��³ľ������
//
int CfgManageGetWlPlateform( char *pIpAddr, unsigned short *pPort );

//
// ʹ��3G��������
//
int CfgManageGetThreegEnableFlag();
int CfgManageGetSmsAuthPasswd(char *smsAuthPasswd);
int CfgManageSetSmsAuthPasswd(char *smsAuthPasswd);

//
// ������ƣ�ͼ��������
//
char CfgManageGetBslEyeSensitivity( int channel );
int CfgManageSetBslEyeSensitivity( int channel, char bslSensitivity );

//
// pc����ʱ���
//
int CfgManageSetPcCountTime( char pTime[2][12] );
int CfgManageGetPcCountTime( char pTime[2][12] );
int CfgManageGetPcCarMod( SYS_CONFIG_PC_CONFIG *carMod );
int CfgManageSetPcCarMod( SYS_CONFIG_PC_CONFIG *carMod );
int CfgManageGetPcLimitedNum( int *limitedNumber );
int CfgManageSetPcLimitedNum( int limitedNumber );

//
// ��ȡwifi��������
//
int CfgManageGetWifiConnectParam( char *pEssid, char *pPasswd );
int CfgManageGetWifiNetType( unsigned char *pNetType );
int CfgManageGetNetworkWifi( char *ip, char *netmask, char *gateway, char *useWifiGateway );
int CfgManageGetPcClsCountTime(CONFIG_CLEAR_PC_PERIOD *clsPeriod);

int CfgManageGetsynovateIpPort( char *pIp, unsigned short *pPort);
int CfgManageAutoMaintainDaylight(char *pFDaylight,char *pStart,char *pEnd);
int CfgManageAutoDaylight(char *pftypedaylight,
                          int *pstartMonth,int *pstartWhichDis,int *pstartWhichDay,int *pstartHour,
                          int *pendMonth,int *pendWhichDis,int *pendWhichDay,int *pendHour);
int CfgManageSaveDaylight(int *psetdaylight);
int CfgManageGetMountDevFlag();
int GetFtpRecFlag();
int GetFtpNetParam(SYS_CONFIG_FTP_REC *sysFtpRec);

/* Ftp�ϴ�������Ϣ���� */
int CfgManageGetFtpUploadConfig( SYS_CONFIG_FTP_UPLOAD *sysFtpUpload );
int CfgManageSetFtpUploadConfig( SYS_CONFIG_FTP_UPLOAD *sysFtpUpload );

/* ��õ��̺� */
int CfgManageGetShopID( int &nShopID );
int CfgManageGetSerialNum( char *pSerialNum );

#endif  // _CONFIG_MANAGE_H

