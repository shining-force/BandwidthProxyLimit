#pragma once
#include "BandwidthManager.h"
#include "Codes.hpp"
#include <queue>

class CacheManager {
public:
	CacheManager(BandwidthManager *bandwidthManager);
	~CacheManager();

	void TcpStore(char* info,int type);
	void TcpRetrieve(char* info, int type);
	void UdpStore(char* info, int type);
	void UdpRetrieve(char* info, int type);
private:
	bool started;
	BandwidthManager *m_bandwidth_manager;
	std::queue<char*> *m_download_queue;
	std::queue<char*> *m_upload_queue;
	
};