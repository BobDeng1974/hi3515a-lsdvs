/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ��ͷ�ļ��ṩ�˶�RTP/RTCPЭ����ص���Ľӿڡ�
**  date           :  2013.11.12
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef _RTP_SERVICE_H
#define _RTP_SERVICE_H

#include "const.h"

const int RTP_PACK_MAX_SIZE	= 1348;//8 * 1024;

#define PACK_ALIGN	__attribute__((packed))

typedef struct rtpHead  /* С���ֽ����ͷ�ṹ	*/
{
	unsigned int	cc	    : 4;    /* CSRC����	*/
	unsigned int	ext	    : 1;    /* ��չ	    */
	unsigned int	pad	    : 1;    /* ���	    */
	unsigned int	ver	    : 2;    /* �汾	    */
	unsigned int	payLoad	: 7;    /* ��������	*/
	unsigned int	mark	: 1;    /* ��־	    */
	unsigned short	seq;            /* ���к�	*/
	unsigned int	time;            /* ʱ���	*/
	unsigned int	ssrc;            /* ͬ��Դ	*/
	unsigned int	end	    : 1;    /* ֡����λ	*/
	unsigned int	begin	: 1;    /* ֡��ʼλ	*/
	unsigned int	sFormat	: 3;    /* ���ĸ�ʽ	*/
	unsigned int	sType	: 3;    /* ��������	*/
	unsigned int	channel	: 4;    /* ͨ����	*/
	unsigned int	fType	: 4;    /* ֡������	*/
	unsigned short	len;            /* ������	*/
    
} PACK_ALIGN RTP_HEAD;

#undef	PACK_ALIGN

typedef struct rtpPack
{
	RTP_HEAD		rtpHead;
	unsigned char	rtpData[1];
    
} RTP_PACK;

typedef struct rtpSocket
{
	int socket;
	int state;                    // д���ݻ��������Ƿ�������
	time_t timeStamp;            // ʱ���

	unsigned char *dataBuf;        // ���ݽ��ջ�����
	int dataLen;                // ��ǰ���������ݳ���
	int bufSize;                // ���ݻ�������С
    
	int flag[MAX_CHANNEL_NUM];    // �Ƿ���RTP���ݵı��
	unsigned short seq[MAX_CHANNEL_NUM];
	struct sockaddr_in addr;
    
} RTP_SOCKET;

class CRtpService
{
public:
	CRtpService();
	CRtpService( int clientMax );
    ~CRtpService();
    
	int InitRtp( int rtpPort );
	int InitTcp( int tcpPort );
	int RtpSend( int channel, void *data, int len,
                	int type, unsigned int time );
	int RtpRecv( void *data, int len, struct sockaddr_in *fromAddr );
	int TcpSend( void *data, int len );
	int TcpRecv( void *data, int len );  // �������ݻ������Ľ��պ���

    // �����ջ�������TcpRecv()
    // ����GetData�ӻ������л�ȡlen�ֽڵ�����
    // ����DelData�ӻ�������ɾ��len�ֽڵ�����	
	int TcpRecv();
	int GetData( void *data, int len );
	int DelData( int len );    
	int Accept();
	int Select();
	int GetSocket();
	int CloseAll();
	int Close( int socket );
	void HeartBeat();
	int SetFlag( int channel );
	int ClearFlag( int channel );
	int SetPort( unsigned short port );    
	int SetAddr( void *ptrAddr );
	int ClientNum();    
	int GetChannelRequestFlag( int channel );    
	int GetCurChannelNum();    
    
private:
	void InitSocket( int clientMax );
	void InitRtpHead( RTP_HEAD *pRtpHead, int seq, unsigned int time,
            	int begin, int end,	int fType, int channel, int len );
	void GetRtpHead( RTP_HEAD *pRtpHead );
	int AddSocket( int socket, struct sockaddr_in &addr );
	int DelSocket( int socket );
	int Select( int socket, int maxMsec );
    
private:
	int m_RtpSocket;
	unsigned short m_RtpPort;
	int m_TcpSocket;
	unsigned short m_TcpPort;
	RTP_SOCKET *m_ClientSocket;    
	int m_ClientNum;
	int m_ClientMax;
	int m_CurSocket;
	int m_channelRequestFlag[REAL_CHANNEL_NUM]; // ��ͨ��Ŀǰ�Ƿ�������
	int m_curChannelNum;
};

#endif  // _RTP_SERVICE_H

