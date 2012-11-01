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
}
AppServer::~AppServer()
{

}



void   AppServer::ExitServer(void)
{
	if (m_sServer!=INVALID_SOCKET)
	{
		closesocket(m_sServer);
	}									
	WSACleanup();							//卸载Windows Sockets DLL
}



BOOL	AppServer::StartService(void)
{
	//返回值
	int reVal;

	//初始化Windows Sockets DLL
	WSADATA  wsData;
	reVal = WSAStartup(MAKEWORD(2,2),&wsData);

	if ( LOBYTE( wsData.wVersion ) != 2 ||
		HIBYTE( wsData.wVersion ) != 2 ) {
			ExitServer();
			return FALSE; 
	}

	//创建套接字
	m_sServer = socket(AF_INET, SOCK_STREAM, 0);
	if(INVALID_SOCKET== m_sServer)
	{
		ExitServer();
		return FALSE;
	}

	//设置套接字非阻塞模式
	unsigned long ul = 1;
	reVal = ioctlsocket(m_sServer, FIONBIO, (unsigned long*)&ul);
	if(SOCKET_ERROR == reVal )
	{
		ExitServer();
		return FALSE;
	}

	//绑定套接字
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


	//监听
	reVal = listen(m_sServer, SOMAXCONN);
	if(SOCKET_ERROR == reVal )
	{
		ExitServer();
		return FALSE;
	}

	unsigned long ulThreadId;
	HANDLE hThreadAccept = CreateThread(NULL, 0, AcceptThread, NULL, 0, &ulThreadId);
	if( NULL == hThreadAccept)
	{
		ExitServer();
		return FALSE;
	}else{
		CloseHandle(hThreadAccept);
	}

	return TRUE;	
}

DWORD WINAPI AppServer::AcceptThread( LPVOID lpParameter )
{
	SOCKET  sAccept;							 
	sockaddr_in addrClient;						
	AppServer *as = AppServer::GetInstance();
	for (;;)//这里要考虑退出，待定
	{
		memset(&addrClient, 0, sizeof(sockaddr_in));					
		int			lenClient = sizeof(sockaddr_in);					 
		sAccept = accept(as->m_sServer, (sockaddr*)&addrClient, &lenClient);

		if(INVALID_SOCKET == sAccept )
		{ 
			int nErrCode = WSAGetLastError();
			if(nErrCode == WSAEWOULDBLOCK)	//
			{
				Sleep(100);
				continue;
			}else {
				return 0;// 这里需要特别的考虑，暂时返回0
			}

		}
		else//
		{
			
		}	
	}
	

	return 0;
}
