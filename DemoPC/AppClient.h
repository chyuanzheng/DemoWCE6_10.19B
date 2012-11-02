#pragma once
#include <winsock2.h>
class AppClient
{
public:
	AppClient(const SOCKET sClient,const sockaddr_in &addrClient);
	virtual ~AppClient();
	SOCKET	GetSocket(void)							//»ñÈ¡Ì×½Ó×Ö
	{
		return m_sClient;	
	}
	BOOL	RecvData(void);
private:
	SOCKET m_sClient;
	sockaddr_in   m_addr;
};