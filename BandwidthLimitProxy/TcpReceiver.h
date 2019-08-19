#pragma once
#pragma comment(lib,"ws2_32.lib")
#include "CacheManager.h"
#include "Codes.hpp"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <iostream>

#define BUFFERLEN 512


class TcpReceiver {
public:
	TcpReceiver(int portnum);
	~TcpReceiver();
	int start();
	int stop();
private:
	char *m_portnum;
	SOCKET m_listen_socket;
	BOOL m_started;
	DWORD WINAPI recieverLoop(LPVOID lpParameter);
	
};

