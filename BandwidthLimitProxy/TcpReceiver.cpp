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

	m_reciever_threads = new std::list<std::thread*>();
}
TcpReceiver::~TcpReceiver(){

}



int recieverThread(void* lpParameter) {
	int iResult;
	int buflen = 512;
	char* buff = new char[buflen];

	SOCKET clientSocket = (SOCKET)lpParameter;
	std::cout << "current thread id:"<<GetCurrentThreadId() << std::endl;

	
	if (clientSocket == INVALID_SOCKET) {
		std::cout << "TcpReceiver_ERROR_ACCEPT_FAIL" << std::endl;
		return -1;
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

	return 0;
}

void TcpReceiver::recieverLoop() {
	do {
		sockaddr info;
		//CreateThread(NULL, 0, recieverThread, (LPVOID)accept(this->m_listen_socket, &info, NULL), 0, NULL);
		std::thread *t =new  std::thread((recieverThread, (void*)accept(this->m_listen_socket, &info, NULL)));

		m_reciever_threads->push_back(t);
		
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