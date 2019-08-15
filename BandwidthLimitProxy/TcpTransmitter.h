#pragma once
#include "CacheManager.h"

class TcpTransmitter {
public:
	TcpTransmitter(CacheManager* cacheManager,int portNum);
	~TcpTransmitter();
	int start();
	int stop();
private:
	bool m_started;
	CacheManager* m_cache_manager;
};