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
	BOOL  IsConnenting(void)										//�жϷ�����������״̬
	{
		return m_bConning;
	}
	BOOL	m_bConning;					//����������״̬
	list<AppClient*> m_listClient;		//����ͻ��˵�����
	static AppServer *m_pInstance;
	CRITICAL_SECTION m_cs;				 
	SOCKET	m_sServer;							//�����׽���
	static DWORD WINAPI ServerThread(LPVOID lpParameter);
	void DeleteClient(SOCKET s);
	void DeleteAllClient(void);
};