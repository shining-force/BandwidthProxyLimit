#pragma once
#include "CacheManager.h"
#include "BandwidthManager.h"
#include "PortMappingManager.h"
#include "TcpReceiver.h"
#include "TcpTransmitter.h"
#include "UdpTransmitter.h"
#include "UdpReceiver.h"
#include "Codes.hpp"

class TransferLayer
{
public:
	TransferLayer(CacheManager* cacheManager, BandwidthManager* bandwidthManager, PortMappingManager* portMappingManager);
	~TransferLayer();
	int start();
	int stop();
private:
	bool started;

	TcpReceiver *m_tcp_forward_receiver;
	TcpTransmitter *m_tcp_forward_transmitter;
	UdpReceiver *m_udp_forward_receiver;
	UdpTransmitter *m_udp_forward_transmitter;

	TcpReceiver *m_tcp_clientside_receiver;
	TcpTransmitter *m_tcp_clientside_transmitter;
	UdpReceiver *m_udp_clientside_receiver;
	UdpTransmitter *m_udp_clientside_transmitter;

	CacheManager *m_cache_manager;
	BandwidthManager *m_bandwidth_manager;
	PortMappingManager *m_port_mapping_manager;


};