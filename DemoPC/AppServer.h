#pragma once
#include <winsock2.h>
#include "AppClient.h"
#include <list>
using namespace std;
class AppServer 
{
public:
	static AppServer* GetInstance();
	virtual ~AppServer();
	BOOL StartService(void);
private:
	AppServer();
	void ExitServer(void);
	void	AddClient(AppClient *pClient);//
	AppClient*GetClient(SOCKET s);		 
	SOCKET GetSocket(void)				
	{
		return m_sServer;
	}
	BOOL  IsConnenting(void)										//判断服务器的连接状态
	{
		return m_bConning;
	}
	BOOL	m_bConning;					//服务器连接状态
	list<AppClient*> m_listClient;		//管理客户端的链表
	static AppServer *m_pInstance;
	CRITICAL_SECTION m_cs;				 
	SOCKET	m_sServer;							//监听套接字
	static DWORD WINAPI ServerThread(LPVOID lpParameter);
	void DeleteClient(SOCKET s);
	void DeleteAllClient(void);
};