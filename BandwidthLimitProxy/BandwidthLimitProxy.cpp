#include "BandwidthLimitProxy.h"
#include "Proxy.h"

int main(int argc, char** argv)
{
	//TODO get command of user
	/*
	loop
	{
		1.Select user mode<proxy,direct>
			if direct switch MS Windows to non-proxy and continue;
			if proxy switch MS Windows to proxy;
		2.Select application
			list all application and open port from A to Z;
		3.Input upload bandwidth limitation<in kbps>
		4.Input download bandwidth limitation<in kbps>
	}
	*/
	char *cmd = new char[256]; memset(cmd, 0, 256);
	std::cout << "please choose :" << std::endl << "1.start proxy server" << std::endl << "2.stop proxy server" << std::endl;
	std::cin >> cmd;
	

	int iResult = 0;
	Proxy *myProxy = new Proxy();
	if (strcmp(cmd, "2") == 0)
	{
		myProxy->stop();
		return 0;
	}
		
	myProxy->start();
	TcpReceiver *tcpReceiver = new TcpReceiver(1080);
	tcpReceiver->start();
	while (true);
	return 0;
}