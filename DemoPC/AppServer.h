#pragma once
#include <winsock2.h>

class AppServer 
{
public:
	static AppServer* GetInstance();
	virtual ~AppServer();
	BOOL StartService(void);
private:
	AppServer();
	void ExitServer(void);
	static AppServer *m_pInstance;
	SOCKET	m_sServer;							//¼àÌýÌ×½Ó×Ö
	static DWORD WINAPI AcceptThread(LPVOID lpParameter);

};