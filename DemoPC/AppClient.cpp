#include "AppClient.h"


AppClient::AppClient( const SOCKET sClient,const sockaddr_in &addrClient )
{
	m_socket=sClient;
	m_addr=addrClient;
}

AppClient::~AppClient()
{

}


BOOL AppClient::StartRuning( void )
{
	m_bConning = TRUE; 

	unsigned long ulThreadId;
	HANDLE hThread = CreateThread(NULL, 0, RecvDataThread, this, 0, &ulThreadId);
	if(NULL == hThread)
	{
		return FALSE;
	}else{
		CloseHandle(hThread);
	}
	return TRUE;
}

DWORD WINAPI AppClient::RecvDataThread( LPVOID lpParameter )
{
	AppClient *ac = (AppClient *)lpParameter;
	return 0;

}


