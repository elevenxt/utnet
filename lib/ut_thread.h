/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#ifndef _UT_THREAD_H_
#define _UT_THREAD_H_

#include "ut_def.h"

__C_BEGIN_DECLS

typedef struct ut_thread		ut_thread_t;
typedef struct ut_mutex			ut_mutex_t;
typedef struct ut_spinlock		ut_spinlock_t;
typedef long long			thread_id_t;
typedef void* thread_handle;

/**
* �߳�ִ�к�����.
*/
typedef int32_t(*ut_thread_func_t)(void*);

/**
* ����һ���߳�ִ����
*
* @param thread_func	�߳�ִ�к�����
* @param arg			���ݸ��߳�ִ�к������һ������
* @return 				�������̲߳���ָ�룬0��ʾ����ʧ��
*/
ut_thread_t*	ut_thread_new(ut_thread_func_t thread_func, void* arg);

thread_handle	ut_thread_handle(ut_thread_t* thread);
/**
* ɾ��һ���߳�
*
* @param a_thread	�̲߳���ָ��
* @return 			NA
*/
void	ut_thread_delete(ut_thread_t* a_thread);

/**
* ɾ��һ���߳�
*
* @param a_thread	�ȴ�һ���̵߳Ľ���
* @return 			NA
*/
void	ut_thread_join(ut_thread_t* a_thread);

/**
* ��ȡ��ǰ�߳�id
*
* @return 			�߳�id
*/
thread_id_t ut_thread_self(void);

/**
* ��ǰ�߳̽�������״̬
*
* @param milliseconds	���ߵĺ�����
* @return 				NA
*/
void	ut_sleep(int32_t milliseconds);

/**
* ��ǰ�߳��ó�ִ��Ȩ
*
* @return 				NA
*/
void	ut_yield();

/**
* ����һ���߳���
*
* @return 				��
*/
ut_mutex_t*		ut_mutex_new();

/**
* ɾ��һ���߳���
*
* @param a_mutex	��
* @return 			NA
*/
void	ut_mutex_delete(ut_mutex_t*	a_mutex);

/**
* ��ס�ٽ���Դ
*
* @param a_mutex	��
* @return 			NA
*/
void	ut_mutex_lock(ut_mutex_t* a_mutex);

/**
* �ͷ��ٽ���Դ
*
* @param a_mutex	��
* @return 			NA
*/
void	ut_mutex_unlock(ut_mutex_t* a_mutex);

/**
* ��ͼ��ס�ٽ���Դ
*
* @param a_mutex	��
* @return 			�ɹ�����0��ʧ�ܷ���-1
*/
ut_err_code_t		ut_mutex_trylock(ut_mutex_t* a_mutex);

/**
* full memory barrier
*
* @return 			NA
*/
void	ut_sync_synchronize();

/**
* �Ƚϲ�����,���ptrָ���ֵ��oval��ȣ�������Ϊnval��ֵ����������֮ǰ��ֵ
*
* @return 			NA
*/
int16_t ut_cas(int16_t volatile* ptr, int16_t oval, int16_t nval);


/**
* ����һ��������
*
* @return 				��
*/
ut_spinlock_t*		ut_spinlock_new();

/**
* ɾ��һ��������
*
* @param a_lock	��
* @return 			NA
*/
void	ut_spinlock_delete(ut_spinlock_t*	a_lock);

/**
* ��ס�ٽ���Դ
*
* @param a_lock	��
* @return 			NA
*/
void	ut_spinlock_lock(ut_spinlock_t* a_lock);

/**
* �ͷ��ٽ���Դ
*
* @param a_lock	��
* @return 			NA
*/
void	ut_spinlock_unlock(ut_spinlock_t* a_lock);

/**
* ��ͼ��ס�ٽ���Դ
*
* @param a_lock	��
* @return 			�ɹ�����0��ʧ�ܷ���-1
*/
ut_err_code_t		ut_spinlock_trylock(ut_spinlock_t* a_lock);

__C_END_DECLS

#endif
