/*********************************************************************
*filename: httpclient.c
*purpose: HTTPЭ��ͻ��˳��򣬿�������������ҳ
*wrote by: zhoulifa(zhoulifa@163.com) ������(http://zhoulifa.bokee.com)
           Linux������ Linux֪ʶ������ SOHO�� ������ ���ó�C����
*date time:2006-03-11 21:49:00
*Note: �κ��˿������⸴�ƴ��벢������Щ���룬��Ȼ���������ҵ��;
*                         ������ѭGPL
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <limits.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <time.h>

#include "ipcHttpSnap.h"
#include "netSocket.h"
#include "debug.h"

/**************************************************************
���ܣ����ַ���src�з�������վ��ַ�Ͷ˿ڣ����õ��û�Ҫ���ص��ļ�
***************************************************************/
void GetHost(char * src, char * web, char * file, int * port)  
{
  char * pA;
  char * pB;
  memset(web, 0, sizeof(web));
  memset(file, 0, sizeof(file));
  *port = 0;
  if(!(*src))  return;
  pA = src;
  if(!strncmp(pA, "http://", strlen("http://")))  pA = src+strlen("http://");
  else if(!strncmp(pA, "https://", strlen("https://")))  pA = src+strlen("https://");
  pB = strchr(pA, '/');
  if(pB)  {
    memcpy(web, pA, strlen(pA) - strlen(pB));
    if(pB+1)  {
      memcpy(file, pB + 1, strlen(pB) - 1);
      file[strlen(pB) - 1] = 0;
    }
  }
  else  memcpy(web, pA, strlen(pA));
  if(pB)  web[strlen(pA) - strlen(pB)] = 0;
  else  web[strlen(pA)] = 0;
  pA = strchr(web, ':');
  if(pA)  *port = atoi(pA + 1);
  else *port = 80;
}

/*
* fn: ͨ��HTTP Э����ץ��ͼƬ
    < Syntax >
	http://<serverIP>/cgi-bin/anv/snapshot.jpg?<parameter>=<value>[&<parameter>=<value>
	http://192.168.1.176/cgi-bin/anv/snapshot.jpg?chnanel=0
    <Response data>
	HTTP/1.0 200 OK\r\n   
	Content-Type: image/jpeg\r\n 
	Content-Length: <image size>\r\n
    \r\n
    <binary JPEG image data>

* pBuf: out, ��Ż�ȡ����ͼƬ
* len: buf �ĳ���
*/
int HttpSnap( char *pBuf, int len ) 
{
  int sockfd = -1;
  char buffer[1024];
  int portnumber,nbytes;
  char host_addr[256];
  char host_file[1024];
  char request[1024];
  int send, totalsend;
  int i, ret, hadReadLen = -1;
  char snapAddr[] = "http://192.168.1.100/cgi-bin/anv/snapshot.jpg?chnanel=0";

  if( NULL == pBuf )
  {
	SVPrint( "error:NULL == pBuf!\r\n" );
	return -1;
  }

  GetHost(snapAddr, host_addr, host_file, &portnumber);/*������ַ���˿ڡ��ļ�����*/
  ret = SocketTcpConnectBlock( &sockfd, host_addr, portnumber );  
  if( ret == -1 )
  {
      SVPrint( "SocketTcpConnectTimtout(%s), error:%s\r\n", snapAddr, STRERROR_ERRNO );
      return -1;
  }
  /*�ر�ע��,�������"sprintf()" ��Ҫ���ᶯ, ����ᵼ�»�ȡ����IPC ͼƬ */
  sprintf(request, "GET /%s HTTP/1.1\r\nAccept: */*\r\nAccept-Language: zh-cn\r\n\
User-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)\r\n\
Host: %s:%d\r\nConnection: Close\r\n\r\n", host_file, host_addr, portnumber);

  /*����http����request*/
  send         = 0;
  totalsend = 0;
  nbytes     = strlen(request);
  while(totalsend < nbytes) 
  {
    send = write(sockfd, request + totalsend, nbytes - totalsend);
    if( send == -1 )  
    {
    	printf("send error!%s\n", strerror(errno));
    	return -1;
    }
    totalsend += send;
    /*���͵��ֽ���Ϊ197 bytes Ϊ��ȷ!*/
    SVPrint("%d bytes send OK!\n", totalsend);
  }
  
  i=0;
  /* ���ӳɹ��ˣ�����http��Ӧ��response */
  while( (nbytes=read(sockfd,buffer,1)) == 1 )
  {
    if( i < 4 )  
    {
      if(buffer[0] == '\r' || buffer[0] == '\n')  i++;
      else i = 0;
    }
    else  
    {
      hadReadLen = 0;
      memcpy( pBuf, buffer, 1 );
      hadReadLen += 1;
      while( (nbytes=read(sockfd,pBuf+hadReadLen,len - hadReadLen)) > 0 )
      {
      	hadReadLen += nbytes;
      }
      break;      
    }
  } // while( (nbytes=read(sockfd,buffer,1)) == 1
  /* ����ͨѶ */
  close(sockfd);

  return hadReadLen;
}

