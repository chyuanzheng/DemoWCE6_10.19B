// WinDll.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include "CWinApp.h"
int WINAPI _tWinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
#ifndef CH_CE_DEBUG
    _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF|_CRTDBG_ALLOC_MEM_DF);
#endif
    int nReturnCode = -1;
    CWinApp* pApp = AfxGetApp();
    if (!AfxWinInit(hInstance, hPrevInstance, lpCmdLine, nCmdShow)) 
        goto InitFailure;
	if (pApp != NULL && !pApp->InitApplication())
		goto InitFailure;

    //pApp->InitApplication();


	if (!pApp->InitInstance())
	{
		if (pApp->m_pMainWnd != NULL)
		{
			//TRACE0( _T("Warning: Destroying non-NULL m_pMainWnd\n"));
			//pApp->m_pMainWnd->DestroyWindow();
		}
		nReturnCode = -2;
		goto InitFailure;
	}
    nReturnCode = pApp->Run();
	pApp->DeInitInstance();
InitFailure:
    delete AfxGetModuleState();
    return nReturnCode;
}

