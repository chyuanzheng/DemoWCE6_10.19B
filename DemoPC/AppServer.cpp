#include "AppServer.h"
#define SERVERPORT			5556			//服务器TCP端口


AppServer *AppServer::m_pInstance = NULL;

AppServer* AppServer::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new AppServer;
	}
	return m_pInstance;
}

AppServer::AppServer()
{
	m_sServer=INVALID_SOCKET;
	InitializeCriticalSection(&m_cs);
}
AppServer::~AppServer()
{
	DeleteCriticalSection(&m_cs);					
}



void   AppServer::ExitServer(void)
{
	if (m_sServer!=INVALID_SOCKET)
	{
		closesocket(m_sServer);
	}									
	WSACleanup();							
}



BOOL	AppServer::StartService(void)
{
	int reVal;

	WSADATA  wsData;
	reVal = WSAStartup(MAKEWORD(2,2),&wsData);

	if ( LOBYTE( wsData.wVersion ) != 2 ||
		HIBYTE( wsData.wVersion ) != 2 ) {
			ExitServer();
			return FALSE; 
	}


	m_sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(INVALID_SOCKET== m_sServer)
	{
		ExitServer();
		return FALSE;
	}

	//设置套接字非阻塞模式
	//unsigned long ul = 1;
	//reVal = ioctlsocket(m_sServer, FIONBIO, (unsigned long*)&ul);
	//if(SOCKET_ERROR == reVal )
	//{
	//	ExitServer();
	//	return FALSE;
	//}


	sockaddr_in serAddr;	
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(SERVERPORT);
	serAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	reVal = bind(m_sServer, (struct sockaddr*)&serAddr, sizeof(serAddr));
	if(SOCKET_ERROR == reVal )
	{
		ExitServer();
		return FALSE;
	}

	reVal = listen(m_sServer, SOMAXCONN);
	if(SOCKET_ERROR == reVal )
	{
		ExitServer();
		return FALSE;
	}

	unsigned long ulThreadId;
	HANDLE hThreadAccept = CreateThread(NULL, 0, ServerThread, NULL, 0, &ulThreadId);
	if( NULL == hThreadAccept)
	{
		ExitServer();
		return FALSE;
	}else{
		CloseHandle(hThreadAccept);
	}

	return TRUE;	
}

DWORD WINAPI AppServer::ServerThread( LPVOID lpParameter )
{						 
	AppServer *pServer = AppServer::GetInstance();

	SOCKET sListen = pServer->GetSocket();

	FD_SET	allSockfd;				
	FD_ZERO(&allSockfd);			
	FD_SET(sListen, &allSockfd);	

	FD_SET readfd;		
	FD_SET	execeptfd;				
	while (pServer->IsConnenting())
	{
		FD_ZERO(&readfd);
		FD_ZERO(&execeptfd);
		readfd = allSockfd;		
		execeptfd = allSockfd;

		int nRet = select(0, &readfd, NULL, &execeptfd, NULL);	
		if (nRet == 0)
		{
			continue;
		}
		if (SOCKET_ERROR==nRet)
		{
			ASSERT(0);
			break;//
		}
		for (int i = 0; i < allSockfd.fd_count; i++)		
		{

			if (FD_ISSET(allSockfd.fd_array[i], &readfd))//
			{
				if (allSockfd.fd_array[i] == sListen)		
				{
					SOCKADDR_IN	addrClient;
					int			nAddrLen = sizeof(addrClient);
					SOCKET	sClient = accept(sListen, (sockaddr*)&addrClient, &nAddrLen);
					AppClient *pClient = new AppClient(sClient, addrClient);	
					pServer->AddClient(pClient);			
					FD_SET(sClient, &allSockfd);		

				}else 
				{	
					AppClient* pClient = pServer->GetClient(allSockfd.fd_array[i]);
					if (pClient != NULL)
					{
						BOOL bRet = pClient->RecvData();				
						if (FALSE == bRet)							
						{
							SOCKET sTemp = allSockfd.fd_array[i];
							FD_CLR(allSockfd.fd_array[i], &allSockfd);
							pServer->DeleteClient(sTemp);
						}			 
					}						 
				}//else					 
			}//if

			if (FD_ISSET(allSockfd.fd_array[i], &execeptfd))
			{
				AppClient* pClient = pServer->GetClient(allSockfd.fd_array[i]);
				if (pClient != NULL)
				{

					SOCKET sDelete = allSockfd.fd_array[i];
					FD_CLR(allSockfd.fd_array[i], &allSockfd);
					pServer->DeleteClient(sDelete);		
				}							 

			}

		}//for 每一个select中的socket
		Sleep(50);
	}//while
	
	pServer->DeleteAllClient();
	return 0;
}


 void AppServer::AddClient(AppClient *pClient)
 {
	 EnterCriticalSection(&m_cs);
	 m_listClient.push_back(pClient);
	 LeaveCriticalSection(&m_cs);
 } 


 AppClient* AppServer::GetClient(SOCKET s)
 {
	 AppClient* pClient = NULL;
	 EnterCriticalSection(&m_cs);
	 list<AppClient*>::iterator it = m_listClient.begin();
	 for (it; it != m_listClient.end(); ++it)
	 {
		 pClient = *it;
		 if (s == pClient->GetSocket())//找到
		 {
			 break;
		 }
	 }

	 LeaveCriticalSection(&m_cs);
	 return pClient;
 }



 /************************************************************************/
 /* 删除客户端      */
 /************************************************************************/
 void AppServer::DeleteClient(SOCKET s)
 {
	 EnterCriticalSection(&m_cs);

	 list<AppClient*>::iterator it = m_listClient.begin();
	 for (it; it != m_listClient.end();)
	 {
		 AppClient *pClient = (AppClient*)*it;
		 if (pClient->GetSocket() == s)
		 {
			 m_listClient.erase(it++);
			 delete pClient;			
			 pClient = NULL;
			 break;
		 }else
		 {
			 it++;
		 }
	 }
	 
	 LeaveCriticalSection(&m_cs);
 }

 /************************************************************************/
 /* 删除所有的客户端      */
 /************************************************************************/
 void AppServer::DeleteAllClient(void)
 {
	 EnterCriticalSection(&m_cs);

	 list<AppClient*>::iterator it = m_listClient.begin();
	 for (it; it != m_listClient.end();)
	 {
		 AppClient *pClient = (AppClient*)*it;
		 m_listClient.erase(it++);

		 delete pClient;
		 pClient = NULL;		
	 }

	 m_listClient.clear();
	 LeaveCriticalSection(&m_cs); 
 }