#include "AppClient.h"


AppClient::AppClient( const SOCKET sClient,const sockaddr_in &addrClient )
{
	m_sClient=sClient;
	m_addr=addrClient;
}

AppClient::~AppClient()
{

}


BOOL AppClient::RecvData( void )
{
	char			buf[64];	//接收数据缓冲区
	int nReadLen = recv(m_sClient, buf, 64, 0);				//每次接收一个字符
	if (SOCKET_ERROR == nReadLen)
	{
		return FALSE;
	}
	return TRUE;
}


