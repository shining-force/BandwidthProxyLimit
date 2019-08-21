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



void recieverThread(void* param,sockaddr *addr) {
	int iResult;
	int buflen = 512;
	char* buff = new char[buflen]; memset(buff, 0, 512);

	SOCKET clientSocket = (SOCKET)param;
	
	std::cout << "current thread id:"<<GetCurrentThreadId() << std::endl;
	struct sockaddr_in *s = (struct sockaddr_in *)&addr;
	char* info = new char[256]; memset(info, 0, 256);
	InetNtop(AF_INET, &s->sin_addr, info, 256);
	std::cout << "source addr:" << info << "source port:" << s->sin_port << std::endl;
	
	if (clientSocket == INVALID_SOCKET) {
		std::cout << "TcpReceiver_ERROR_ACCEPT_FAIL" << std::endl;
		return;
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
}

void TcpReceiver::recieverLoop() {

	do {
		sockaddr info;
		//CreateThread(NULL, 0, recieverThread, (LPVOID)accept(this->m_listen_socket, &info, NULL), 0, NULL);

		SOCKET *get = (SOCKET*)accept(this->m_listen_socket, &info, NULL);

		std::thread t(recieverThread, (void*)&get,&info);
		t.detach();
		Sleep(300);
	} while (this->m_started == TRUE);
}


int TcpReceiver::start() {


	this->m_started = TRUE;
	std::thread t(&TcpReceiver::recieverLoop,this);

	t.detach();

	return TRUE;
}
int TcpReceiver::stop() {
	this->m_started = FALSE;

	return TRUE;
}