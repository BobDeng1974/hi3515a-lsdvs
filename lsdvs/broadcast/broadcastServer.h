#ifndef __BROADCASTSERVER_H__
#define __BROADCASTSERVER_H__

void StartBroadcastServerThread();
void StopBroadcastServerThread();


typedef   struct   _DevFind_ 
{ 
    int             realChannelNum;            //���豸����ͨ����
    int             serverType;                //�豸���� 
    int             portNo;                    //�����˿� 
    int             netType;                   //�������� 
    char            hostName[32];              //�豸�� 
    char            macAddr[NET_ADDRSIZE];     //MAC��ַ 
    char            ipAddr[NET_ADDRSIZE];      //IP��ַ 
    char            netMask[NET_ADDRSIZE];     //�������� 
    char            gwAddr[NET_ADDRSIZE];      //���ص�ַ 
    char            versionNo[32];             //�汾�� 
    unsigned int    portOffset;                //�˿�ƫ�� 
    char            firstDns[NET_ADDRSIZE];    //��DNS 
    char            secondDns[NET_ADDRSIZE];   //����DNS 
    unsigned short  dnsGetFlag;                //dns �Զ���ñ�־,0: �Զ����, 1: �ֶ���� 
    unsigned short  webPort;                   //web �˿����� 
    char            dhcpFlag;
    char            unused[3];
    char            deviceType[32];            //��Ʒ�ͺ� 
}DEV_FIND_T;

#endif

