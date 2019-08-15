#include "BandwidthLimitProxy.h"


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
	CacheManager *myCache = new CacheManager(new BandwidthManager());
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0) {
		return TRANSFERLAYER_ERROR_WSASTARTUP_FAIL;
	}

	TcpReceiver *receiver2 = new TcpReceiver(myCache, 1080, CACHEMANAGER_TYPE_UPLOAD);
	
	int iResult = receiver2->start();
	return 0;
}