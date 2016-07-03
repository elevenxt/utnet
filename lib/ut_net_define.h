/*
** simple net lib for windows and linux
**
** Copyright (C) 2016 Eleven. See Copyright Notice in ut_def.h
*/



#ifndef _NET_DEFINE_
#define _NET_DEFINE_

#include "ut_net.h"
#include "ut_sock.h"
#include "ut_list.h"

#ifdef UT_PLATFORM_WINDOWS
#include <Winsock2.h>
#endif
#ifdef UT_PLATFORM_LINUX
#include <sys/epoll.h>
#endif

__C_BEGIN_DECLS

// ������������
struct ut_net_config_t
{
	int32_t		st_net_size;
	int32_t		st_channel_size;
	int32_t		num_connection_limit;
};

// ����������Ϣ
struct ut_channel_info_t
{
	// ���ذ�ip
	int32_t		local_ip;
	// �Զ�ip
	int32_t		remote_ip;
	// ���ذ󶨶˿�
	int32_t		local_port;
	// �Զ˶˿�
	int32_t		remote_port;
	int64_t		bytes_recved;		// ������������
	int64_t		bytes_sended;		// ������������
};

#ifdef UT_PLATFORM_WINDOWS
enum IOType 
{
	IO_RECEIVE,		// ���ݽ����¼�
};

typedef struct _IOOverlapped
{
	OVERLAPPED		overlapped;
	enum IOType		io_type;
	WSABUF			wsabuf;
}IOOverlapped;

#define OVERLAPPED_BUF_SIZE		4096
#endif

#ifdef UT_PLATFORM_LINUX
#define MAX_WAIT_EVENT		1024
#define EPOLL_RCV_BUF_SIZE	1024*128
#endif

struct ut_net_t;
struct ut_channel_t
{
	int32_t				index;
	struct ut_net_t*	net;

	ut_list_t			queue_inuse;	// ��������е�ͨ������ʹ����,��queue_free����һ��

	ut_sock_t			sock;			// �����׽���
	struct ut_channel_info_t info;
#ifdef UT_PLATFORM_WINDOWS
	char			rcv_buf[OVERLAPPED_BUF_SIZE];		// ���ջ�����
	IOOverlapped	io_overlapped;		// win32ϵͳ���ص�����
#endif
	void(*connection_data)(struct ut_channel_t* channel, const char* data
		, int32_t datalen, void* netdata, void* channeldata);
	void*	user_data;
};

// ����������
struct ut_net_t
{
	// �û���������
	struct ut_net_config_t			cfg;
#ifdef UT_PLATFORM_LINUX
	// linux ר��
	int32_t				epoll_handle;		// epoll ���
	struct epoll_event	wait_event[MAX_WAIT_EVENT];			// epoll�¼�����
	char	rcv_buf[EPOLL_RCV_BUF_SIZE];
#endif
#ifdef UT_PLATFORM_WINDOWS
	// windosר��
	// ��ɶ˿ھ��
	HANDLE				io_complete_port;	// IOCP�˿�
#endif
	ut_list_t		queue_inuse;		// ����ʹ�õĶ���
	ut_list_t		queue_free;			// ���ж���
	void(*new_func)(struct ut_channel_t* channel, void* netdata, void* channeldata);
	void(*lost_func)(struct ut_channel_t* channel, void* netdata, void* channeldata);
	void*	user_data;
};


__C_END_DECLS

#endif