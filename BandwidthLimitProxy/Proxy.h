#pragma once
#pragma comment(lib,"Advapi32.lib")
#pragma comment(lib,"Wininet.lib")
#include "TransferLayer.h"
#include "CacheManager.h"
#include "PortMappingManager.h"
#include "BandwidthManager.h"
#include "winreg.h"
#include "wininet.h"


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
	//int switchWindowsProxyMode(int mode, WINHTTP_PROXY_INFO *proxyInfo);
	
};