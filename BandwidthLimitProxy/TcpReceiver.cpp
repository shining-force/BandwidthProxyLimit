#include "TcpReceiver.h"

TcpReceiver::TcpReceiver(int portnum) {
	int iResult;
	m_portnum = new char[10];memset(m_portnum, 0, 10);
	_itoa(portnum, m_portnum, 10);

	

	struct addrinfo listenInfo, *result;
	ZeroMemory(&listenInfo, sizeof(listenInfo));
	listenInfo.ai_family = AF_INET;
	listenInfo.ai_socktype = SOCK_STREAM;
	listenInfo.ai_protocol = IPPROTO_TCP;
	listenInfo.ai_flags = AI_PASSIVE;


	iResult = getaddrinfo(NULL, this->m_portnum, &listenInfo, &result);
	if (iResult != 0) {
		std::cout << "TcpReceiver_ERROR_GETADDRINFO_FAIL" << std::endl;
	}

	m_listen_socket = socket(listenInfo.ai_family, listenInfo.ai_socktype, listenInfo.ai_protocol);
	if (m_listen_socket == INVALID_SOCKET) {
		std::cout << "TcpReceiver_ERROR_CREATESOCKETFAIL_FAIL" << std::endl;
	}

	iResult = bind(this->m_listen_socket, result->ai_addr, result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		std::cout << "TcpReceiver_ERROR_BINDPORT_FAIL" << std::endl;
		closesocket(this->m_listen_socket);
	}

	freeaddrinfo(result);

	iResult = listen(this->m_listen_socket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		std::cout << "TcpReceiver_ERROR_LISTEN_FAIL" << std::endl;
		closesocket(this->m_listen_socket);
	}
}
TcpReceiver::~TcpReceiver(){

}
int TcpReceiver::start() {
	int iResult;

	this->m_started = TRUE;
	int buflen = 512;
	char* buff = new char[buflen];

	do {
		SOCKET clientSocket;
		sockaddr info;

		clientSocket = accept(this->m_listen_socket, &info, NULL);
		if (clientSocket == INVALID_SOCKET) {
			std::cout << "TcpReceiver_ERROR_ACCEPT_FAIL" << std::endl;
			continue;
		}

		do {
			iResult = recv(clientSocket, buff, buflen, 0);
			if (iResult > 0) {
				std::cout << buff;
			}
			else if (iResult == 0)
			{
				std::cout << "Receiver closing" << std::endl;
			}
			else
			{
				std::cout << "TcpReceiver_ERROR_RETRIEVE_FAIL" << std::endl;
				closesocket(clientSocket);
				break;
			}
		} while (iResult > 0);

	} while (this->m_started == TRUE);

	return TRUE;
}
int TcpReceiver::stop() {
	this->m_started = FALSE;

	return TRUE;
}