#include "Proxy.h"

inline void wsa_init() {
	WORD versionRequested;
	WSADATA wsaData;
	int iResult;
	
	versionRequested = MAKEWORD(2, 2);
	WSAStartup(versionRequested, &wsaData);
}

Proxy::Proxy() {
	//TODO Proxy Object Create
	wsa_init();

}

Proxy::~Proxy() {
	//TODO Proxy Object destroy
}

int Proxy::start() {
	//TODO Proxy start

	switchWindowsProxyMode(PROXY_MODE_PROXY);

	return NULL;
}
int Proxy::stop() {
	//TODO Proxy stop

	switchWindowsProxyMode(PROXY_MODE_DIRECT);
	return NULL;
}

inline void InternetSetProxy() {
	HKEY mainKey = HKEY_CURRENT_USER;
	LPCSTR subKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings";
	DWORD valueType = REG_SZ;
	HKEY keyHandle;

	char *proxyServer = "127.0.0.1:1080";
	char *proxyOverride = "localhost;127.*;10.*;172.16.*;172.17.*;172.18.*;172.19.*;172.20.*;172.21.*;172.22.*;172.23.*;172.24.*;172.25.*;172.26.*;172.27.*;172.28.*;172.29.*;172.30.*;172.31.*;172.32.*;192.168.*;<local>";
	long enableProxy = 1;

	RegOpenKeyEx(mainKey, subKey, NULL, KEY_ALL_ACCESS, &keyHandle);
	RegSetValueEx(keyHandle, "MigrateProxy", NULL, REG_DWORD, (BYTE*)&enableProxy, sizeof(long));
	RegSetValueEx(keyHandle, "ProxyEnable", NULL, REG_DWORD, (BYTE*)&enableProxy, sizeof(long));
	RegSetValueEx(keyHandle, "ProxyServer", NULL, REG_SZ, (BYTE*)proxyServer, strlen(proxyServer));
	RegSetValueEx(keyHandle, "ProxyOverride", NULL, REG_SZ, (BYTE*)proxyOverride, strlen(proxyOverride));

	RegCloseKey(keyHandle);
}

inline void InternetSetDirect() {
	HKEY mainKey = HKEY_CURRENT_USER;
	LPCSTR subKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings";
	DWORD valueType = REG_SZ;
	HKEY keyHandle;

	const char *proxyServer = "";
	const char *proxyOverride = "<local>";
	long enableProxy = 0;

	RegOpenKeyEx(mainKey, subKey, NULL, KEY_ALL_ACCESS, &keyHandle);
	RegSetValueEx(keyHandle, "MigrateProxy", NULL, REG_DWORD, (BYTE*)&enableProxy, sizeof(long));
	RegSetValueEx(keyHandle, "ProxyEnable", NULL, REG_DWORD, (BYTE*)&enableProxy, sizeof(long));
	RegSetValueEx(keyHandle, "ProxyServer", NULL, REG_SZ, (BYTE*)proxyServer, strlen(proxyServer));
	RegSetValueEx(keyHandle, "ProxyOverride", NULL, REG_SZ, (BYTE*)proxyOverride, strlen(proxyOverride));

	RegCloseKey(keyHandle);
}



int Proxy::switchWindowsProxyMode(int mode)
{
	switch (mode)
	{
	case PROXY_MODE_DIRECT:
		InternetSetDirect();
		break;
	case PROXY_MODE_PROXY:
		InternetSetProxy();
		break;
	default:
		return PROXY_ERROR_MODE;
	}

	InternetSetOption(NULL, INTERNET_OPTION_PROXY_SETTINGS_CHANGED, NULL, 0);
	InternetSetOption(NULL, INTERNET_OPTION_REFRESH, NULL, 0);
}


