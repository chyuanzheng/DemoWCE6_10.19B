#include "StdAfx.h"
#include "CWinApp.h"

//��ʼ����̬��Ա
CWinApp::CWinApp(  )
{
	// initialize CWinThread state
    m_pMainWnd = NULL ;
	AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
	pModuleState->m_pCurrentWinApp = this;
	_ASSERT(AfxGetApp() == this);	
}
BOOL CWinApp::InitApplication()
{
    return TRUE;
}

int CWinApp::Run()
{
	//��Ϣѭ��
    MSG    msg;
	while(GetMessage(&msg, NULL, 0, 0 ))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}