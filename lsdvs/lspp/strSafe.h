/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**    
**  description  : ��ͷ�ļ��ṩ����ȫ���ַ�����������strlcpy��strlcat�Ľӿڣ�
**            ��Ҫ�����滻strcpy,strncpy��strcat,strncat������
**            ���ṩ���Ӱ�ȫ���ַ���������
**  date           :  2013.11.11
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef _STR_SAFE_H
#define _STR_SAFE_H

size_t strlcpy( char * dst, const char * src, size_t siz );
size_t strlcat( char * dst, const char * src, size_t siz );

#endif  // _STR_SAFE_H

