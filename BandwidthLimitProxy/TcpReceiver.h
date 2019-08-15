#pragma once
#pragma comment(lib,"ws2_32.lib")
#include "CacheManager.h"
#include "Codes.hpp"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

#define BUFFERLEN 512


class TcpReceiver {
public:
	TcpReceiver(CacheManager *cacheManager,int portNum,int mode);
	~TcpReceiver();
	int start();
	int stop();
private:
	SOCKET m_sock;
	SOCKET m_client_sock;
	bool m_started;
	char m_port_num[6];
	int m_socket_fd;
	CacheManager* m_cache_manager;
	char m_recv_buffer[BUFFERLEN];
	int m_mode;
};

