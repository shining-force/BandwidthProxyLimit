#include "TcpReceiver.h"

TcpReceiver::TcpReceiver(CacheManager *cacheManager, int portNum,int mode) {
	_itoa(portNum, this->m_port_num, 10);
	this->m_cache_manager = cacheManager;
	this->m_mode = mode;

}
TcpReceiver::~TcpReceiver() {
}

int TcpReceiver::start() {
	int iResult;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	//Create port info
	iResult = getaddrinfo(NULL,this->m_port_num, &hints, &result);
	if (iResult != 0) {
		return TcpReceiver_ERROR_CREATESOCKETFAIL_FAIL;
	}

	//Create socket
	this->m_sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (this->m_sock == INVALID_SOCKET)
		return TcpReceiver_ERROR_GETADDRINFO_FAIL;

	//Setup listen port
 	iResult = bind(this->m_sock, result->ai_addr, result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		return TcpReceiver_ERROR_BINDPORT_FAIL;
	}
	
	freeaddrinfo(result);

	iResult = listen(this->m_sock, SOMAXCONN);
	if (iResult == SOCKET_ERROR){
		closesocket(this->m_sock);
		return TcpReceiver_ERROR_LISTEN_FAIL;
	}

	m_client_sock = accept(this->m_sock, NULL, NULL);
	
	if (m_client_sock == INVALID_SOCKET) {
		closesocket(this->m_sock);
		return TcpReceiver_ERROR_ACCEPT_FAIL;
	}

	closesocket(this->m_sock);

	//Retrive data
	do {
		iResult = recv(m_client_sock, m_recv_buffer, BUFFERLEN, 0);
		if (iResult > 0)
		{
			switch (m_mode)
			{
			case CACHEMANAGER_TYPE_UPLOAD:
				this->m_cache_manager->TcpStore(m_recv_buffer, CACHEMANAGER_TYPE_UPLOAD);
				break;
			case CACHEMANAGER_TYPE_DOWNLOAD: 
				this->m_cache_manager->TcpStore(m_recv_buffer, CACHEMANAGER_TYPE_DOWNLOAD);
				break;
			}
			std::cout << "Bytes received:" << iResult << std::endl;
		}
		else if (iResult == 0) {
			std::cout << "Connection closing..."<< std::endl;
		}
		else
		{
			closesocket(m_client_sock);
			return TcpReceiver_ERROR_RETRIEVE_FAIL;
		}
	} while (iResult > 0);
	

	//Shudown socket
	iResult = shutdown(this->m_client_sock, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		return TcpReceiver_ERROR_SHUTDOWN_FAIL;
	}

	closesocket(this->m_client_sock);

	this->m_started = true;

	//TODO create listener 
}
int TcpReceiver::stop(){
	this->m_started = false;

	return 0;
}