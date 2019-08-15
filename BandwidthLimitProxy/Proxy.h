#pragma once
#include "TransferLayer.h"
#include "CacheManager.h"
#include "PortMappingManager.h"
#include "BandwidthManager.h"

#define PROXY_MODE_PROXY 0
#define PROXY_MODE_DIRECT 1

class Proxy {
public:
	Proxy();
	~Proxy();
	int start();
	int stop();
private:
	bool m_started;
	TransferLayer *m_transfer_layer;
	CacheManager *m_cache_manager;
	BandwidthManager *m_bandwidth_manager;
	PortMappingManager *m_port_mapping_manager;
	int switchWindowsProxyMode(int mode);
};