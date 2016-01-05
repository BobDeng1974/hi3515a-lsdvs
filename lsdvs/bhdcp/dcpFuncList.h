/******************************************************************************
*! ��ͻ��˶Խ����һ��������ȡ�������õĹ�����:
 1. ����ͨ�ŵĽṹ��: CONFIG_xxx .
 2. ����ͨ�ŵ���Ϣ: SV_MSG_REQ_xxx �� SV_MSG_RES_xxx .
 3. ���崦����Ϣ�ĺ��� : SVMsgGetxxx �� SVMsgSetxxx .
 4. �� g_clientMsgFunction ������������������ ��Ϣ�� ������.
 5. ��client�Բ�����������Ӧ���Գ���(��ѡ)
******************************************************************************/

#ifndef __DCPFUNCLIST_H__
#define __DCPFUNCLIST_H__

#include "dcpTypes.h"
#include "dcpSignal.h"
int SVMsgVerifyReq( DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom );
int SVMsgStreamStartReq(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgGetBaseInfo(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgGetNetwork(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);    
int SVMsgSetNetwork(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom); 
int SVMsgGetClientUser(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgSetClientUser(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);

int SVMsgGetVideoBaseParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgSetVideoBaseParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgGetOsdLogo(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgSetOsdLogo(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgGetOsdTime(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);

int SVMsgSetOsdTime(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgGetVideoEncodePublic(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom); 
int SVMsgSetVideoEncodePublic(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgGetAudio(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgSetAudio(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);

int SVMsgGetAutoMaintain(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom); 
int SVMsgSetAutoMaintain(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom); 
int SVMsgGetRecordPublic(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom); 
int SVMsgSetRecordPublic(DCP_HEAD_T *msgHead,CLIENT_COMMUNICATE_T *clientCom);
int SVMsgGetRecordParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);

int SVMsgSetRecordParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
//int SVMsgGetAlarmIo(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
//int SVMsgSetAlarmIo(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgGetNtp(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgSetNtp(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);

int SVMsgGetEmail(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgSetEmail(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgGetVideoEncodeParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgSetVideoEncodeParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgGetVideoEncodeParamSlave(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);

int SVMsgSetVideoEncodeParamSlave(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgGetOsd(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgSetOsd(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgSearchRecord( DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom );
int SVMsgRecordReq( DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom );
int SVMsgUpdateReq(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);

int SVMsgStopStream( DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom );
int SVMsgLogout( DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom );
int SVMsgGetLog(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgGetStorageInfo( DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom );

int SVMsgGetAlarmIoParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgSetAlarmIoParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgGetAlarmVlossParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgSetAlarmVlossParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgGetAlarmVideoShelterParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgSetAlarmVideoShelterParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgGetAlarmMDParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgSetAlarmMDParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);

int SVMsgGetSysTime( DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom );
int SVMsgSetSysTime( DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom );
    
int SVMsgSysReboot( DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom );
int SVMsgResetFactory( DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom );
int SVMsgResetDefaultParam( DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom );

int PacketClientHead( DCP_HEAD_T *msgHead,unsigned short msgType,unsigned short subType,
                        	unsigned int len,unsigned int ackResult );
int SVMsgHeartbeatReq( DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom );
int SVMsgGetAllParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
int SVMsgSetAllParam(DCP_HEAD_T *msgHead, CLIENT_COMMUNICATE_T *clientCom);
    
#endif


