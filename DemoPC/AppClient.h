#pragma once
#include <winsock2.h>
class AppClient
{
public:
	AppClient(const SOCKET sClient,const sockaddr_in &addrClient);
	virtual ~AppClient();
	BOOL		StartRuning(void);

private:
	SOCKET m_socket;
	sockaddr_in   m_addr;
	BOOL		m_bConning;			//客户端连接状态
	static DWORD WINAPI RecvDataThread(LPVOID lpParameter);
};