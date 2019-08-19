#include "BandwidthLimitProxy.h"
#include "Proxy.h";

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

	int iResult = 0;
	Proxy *myProxy = new Proxy();
	myProxy->start();
	TcpReceiver *tcpReceiver = new TcpReceiver(1080);
	tcpReceiver->start();

	return 0;
}