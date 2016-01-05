/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.10.10
**  description  : ���� network�ӿ�
********************************************************************************/

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <net/if.h>

#include "const.h"
#include "debug.h"
    
#include "network.h"

/***************************************************************************
* func: ��ȡĳ��������ip��ַ
* pIf: ����������
* ipaddr: out, ��ȡ����ip��ַ
* len: ipAddr �ĳ���
******************************************************************************/
int NetworkGetIpAddr( char *pIf, char *ipAddr, int len )
{
	int 	fd;
	char 	buffer[20];
	struct 	ifreq ifr;
	struct 	sockaddr_in *addr;

	if( NULL == ipAddr || NULL == pIf )
    {
    	SVPrint("error:NULL==ipAddr\r\n");
    	return FI_FAIL;
    }
    
	if( (fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0 )
    {
    	strncpy( ifr.ifr_name, pIf, IFNAMSIZ );
    	ifr.ifr_name[IFNAMSIZ - 1] = '\0';
    	if( ioctl(fd, SIOCGIFADDR, &ifr) == 0 )
        {
        	addr = (struct sockaddr_in *)&(ifr.ifr_addr);
        	inet_ntop( AF_INET, &addr->sin_addr, buffer, sizeof(buffer) );
        }
    	else
        {
        	close(fd);            
        	return FI_FAIL;
        }
    }
	else
    {
    	SVPrint( "socket() error:%s!\r\n", STRERROR_ERRNO );
    	return FI_FAIL;
    }
    
	if( strlen(buffer) > (unsigned int)(len-1) )
    {            
    	close(fd);
    	SVPrint( "error:strlen(buffer) > len-1!\r\n" );    
    	return FI_FAIL;
    }
    
	strncpy( ipAddr, buffer, len );
	close( fd );
    
	return FI_SUCCESS;
}

/**********************************************************************
* func: ��ȡĳ��������ip��ַ
* pIf: ����������,��eth0
* macAddr: out, ��ȡ����mac ��ַ
* len: macAddr �ĳ���
****************************************************************************/
int NetworkGetMacAddr( char *pIf, char *macAddr, int len )
{
    int 	fd;
    char 	buffer[NET_ADDRSIZE];
    struct ifreq ifr;

	if( NULL == pIf || NULL == macAddr )
    {
    	SVPrint( "error: NULL == pIf || NULL == macAddr!\r\n" );
    	return FI_FAIL;
    }

    if( (fd = socket( AF_INET, SOCK_DGRAM, 0)) >= 0 )
    {
        strncpy(ifr.ifr_name, pIf, IFNAMSIZ);
        ifr.ifr_name[IFNAMSIZ - 1] = '\0';
        if( 0 == ioctl(fd, SIOCGIFHWADDR, &ifr) )
        {
            snprintf(buffer, NET_ADDRSIZE, "%02x:%02x:%02x:%02x:%02x:%02x",
                    (unsigned char)ifr.ifr_hwaddr.sa_data[0],
                    (unsigned char)ifr.ifr_hwaddr.sa_data[1],
                    (unsigned char)ifr.ifr_hwaddr.sa_data[2],
                    (unsigned char)ifr.ifr_hwaddr.sa_data[3],
                    (unsigned char)ifr.ifr_hwaddr.sa_data[4],
                    (unsigned char)ifr.ifr_hwaddr.sa_data[5]);
        }
    	else
        {
        	close( fd );
        	SVPrint( "ioctl() error:%s!\r\n", STRERROR_ERRNO );
        	return FI_FAIL;
        }
    }
	else
    {        
    	SVPrint( "socket() error:%s!\r\n", STRERROR_ERRNO );        
    	return FI_FAIL;
    }
    
	if( strlen(buffer) > (unsigned int)(len-1) )
    {        
    	close(fd);
    	SVPrint( "error:strlen(buffer) > len-1!\r\n" );
    	return FI_FAIL;
    }
	strncpy( macAddr, buffer, len );
    
	close(fd);
	return FI_SUCCESS;
}

