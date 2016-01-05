#ifndef _DEV_SEARCH_H
#define _DEV_SEARCH_H

enum MsgDevSearchPackType
{
	MSG_DEV_SEARCH_COM	                = 0xFF00,
};

enum MsgDevSearchSubType
{
	MSG_DEV_SEARCH_REQUEST	            = 0x01,        // ����
	MSG_DEV_SEARCH_RESPONSE	            = 0x02,        // Ӧ��
	MSG_DEV_SEARCH_ERROR	            = 0x03,        // ����
};

#define PACK_ALIGN	__attribute__((packed))

//
// �豸�������ݸ�ʽ
//
typedef struct MessageDevSearch
{
	int		devType;            // �豸����
	char	devTypeName[32];    // �豸��������
	char	devName[32];        // �豸����
	int		channelNum;            // ͨ������
	char	ip[80];                // IP��ַ
	char	netmask[16];        // ��������
	char	gateway[16];        // ����
	char	dns[16];            // ��DNS
	char	dns2[16];            // ����DNS
	char	mac[24];            // �����ַ	
	unsigned short	protocolPort;    // ��ϢЭ��˿�
	unsigned short	httpPort;        // http�˿�
} PACK_ALIGN MESSAGE_DEV_SEARCH;

#undef PACK_ALIGN

int DealDevSearchProcess( unsigned char *dataBuf, int &dataLen, const int bufSize );
int CheckDevSearchProcess( unsigned char *dataBuf, int dataLen, int bufSize, int &offset );

#endif  // _DEV_SEARCH_H

