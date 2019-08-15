#include "TransferLayer.h"

TransferLayer::TransferLayer(CacheManager* cacheManager, BandwidthManager* bandwidthManager, PortMappingManager* portMappingManager) {
	

}

int TransferLayer::start()
{
	//init WSA 
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0) {
		return TRANSFERLAYER_ERROR_WSASTARTUP_FAIL;
	}

	//TODO TransferLayer start
}

int TransferLayer::stop() {
	//uninit WSA
	if (WSACleanup() != 0) {
		return TRANSFERLAYER_ERROR_WSACleanup_FAIL;
	}

	//TODO TransferLayer stop
}