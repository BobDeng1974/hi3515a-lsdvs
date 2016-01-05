/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ���ļ�ʵ�ָ���ȫ���ַ�����������strlcpy��strlcat����Ҫ�����滻
**            strcpy,strncpy��strcat,strncat���������ṩ���Ӱ�ȫ���ַ���������
**  date           :  2013.11.11
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#include <stdio.h>
#include <string.h>
#include "debug.h"
#include "strSafe.h"

size_t strlcpy( char * dst, const char * src, size_t siz )
{
	char *        	d = dst;
	const char *	s = src;
	size_t	    	n = siz;

	if( NULL == dst || NULL == src )
    {
    	FiPrint( "error: NULL == dst || NULL == src!\r\n" );
    	return 0;
    }

	if ( n != 0 )
    {
        while ( --n != 0 )
        {
            if ( (*d++ = *s++) == '\0' )
            	break;
        }
    }

	if ( n == 0 )
    {
        if ( siz != 0 ) *d = '\0'; 
        while ( *s++ )
        {
            ;  // do nothing !
        }
    }

	return ( s - src - 1 ); 
}

size_t strlcat( char * dst, const char * src, size_t siz )
{
	char *        	d = dst;
	const char *	s = src;
	size_t	    	n = siz;
	size_t	    	dlen = 0;

	if( NULL == dst || NULL == src )
    {
    	FiPrint( "error: NULL == dst || NULL == src!\r\n" );
    	return 0;
    }

	while ( n-- != 0 && *d != '\0' )
    {
        ++d;
    }
	dlen = d - dst;
	n = siz - dlen;

	if ( n == 0 )
    {
    	return ( dlen + strlen(s) );
    }
    
	while ( *s != '\0' )
    {
    	if ( n != 1 )
        {
            *d++ = *s;
            --n;
        }
        ++s;
    }
    *d = '\0';

	return ( dlen + (s - src) );
}

