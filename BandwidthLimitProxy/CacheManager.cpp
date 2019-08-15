#include "CacheManager.h"

CacheManager::CacheManager(BandwidthManager *bandwidthManager) {
	this->m_bandwidth_manager = bandwidthManager;
	this->m_download_queue = new std::queue<char*>();
	this->m_upload_queue = new std::queue<char*>();
}

CacheManager::~CacheManager() {

}

void CacheManager::TcpStore(char* info, int type)
{
	switch (type)
	{
	case CACHEMANAGER_TYPE_UPLOAD:
		m_upload_queue->push(info);
		break;
	case CACHEMANAGER_TYPE_DOWNLOAD:
		m_download_queue->push(info);
		break;
	}
}

void CacheManager::TcpRetrieve(char* info, int type) {
	switch (type)
	{
	case CACHEMANAGER_TYPE_UPLOAD:
		info = m_upload_queue->front();
		m_upload_queue->pop();
		break;
	case CACHEMANAGER_TYPE_DOWNLOAD:
		info = m_download_queue->front();
		m_upload_queue->pop();
		break;
	}
}

void CacheManager::UdpStore(char* info, int type) {
	switch (type)
	{
	case CACHEMANAGER_TYPE_UPLOAD:
		m_upload_queue->push(info);
		break;
	case CACHEMANAGER_TYPE_DOWNLOAD:
		m_download_queue->push(info);
		break;
	}
}

void CacheManager::UdpRetrieve(char* info, int type) {
	switch (type)
	{
	case CACHEMANAGER_TYPE_UPLOAD:
		info = m_upload_queue->front();
		m_upload_queue->pop();
		break;
	case CACHEMANAGER_TYPE_DOWNLOAD:
		info = m_download_queue->front();
		m_upload_queue->pop();
		break;
	}
}