/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#ifndef _UT_TIME_H_
#define _UT_TIME_H_

#include "ut_def.h"

__C_BEGIN_DECLS

typedef struct _ut_time
{
	int32_t year;
	int32_t month;
	int32_t day;
	int32_t hour;
	int32_t minute;
	int32_t second;
} ut_time_t;

/**
* ��ȡ��ǰϵͳ����ʱ��
*
* @return ��ǰϵͳ����ʱ��
*/
ut_time_t ut_gettime();

/**
* ��ȡ��Ժ������ֵ
*
* @return �������ֵ
*/
int64_t ut_gettickcount();

int64_t	ut_time_seconds();

__C_END_DECLS

#endif