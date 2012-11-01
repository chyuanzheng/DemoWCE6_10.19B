#include "../common/StdAfx.h"
#include "../common/StrHelp.h"
#include "../common/AfxFuc.h"
AFX_MODULE_STATE* AFX_MODULE_STATE::m_s_pInstance= NULL;
AFX_MODULE_STATE* AfxGetModuleState()
{
    if(AFX_MODULE_STATE::m_s_pInstance == NULL)
    {
        AFX_MODULE_STATE::m_s_pInstance = new AFX_MODULE_STATE;
    }
    return AFX_MODULE_STATE::m_s_pInstance;
}


CWinApp* AfxGetApp()
{
    return AFX_MODULE_STATE::m_s_pInstance->m_pCurrentWinApp;
}

BOOL  AfxWinInit(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	 LPTSTR lpCmdLine, int nCmdShow)
{
	_ASSERT(hPrevInstance == NULL);
	// set resource handles
	AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
	pModuleState->m_hCurrentInstanceHandle = hInstance;
	CWinApp* pApp = AfxGetApp();
	if (pApp != NULL)
	{
		// Windows specific initialization (not done if no CWinApp)
		pApp->m_hInstance = hInstance;
		hPrevInstance; // Obsolete.
		pApp->m_lpCmdLine = lpCmdLine;
		pApp->m_nCmdShow = nCmdShow;
	}
    else
    {
        return FALSE;
    }

	return TRUE;
}

HINSTANCE AfxGetInstanceHandle( )
{
    AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
	return pModuleState->m_hCurrentInstanceHandle ;
}



CE_CONTROL_API BOOL  AfxGetWorkPath(wstring &path)
{
	AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
	if (pModuleState->m_sWorkPath.length()>0)
	{
		path = pModuleState->m_sWorkPath;
		return TRUE;
	}

	WCHAR tWorkPath[MAX_PATH];
	if(::GetModuleFileName(   NULL,   tWorkPath,   MAX_PATH   ) == 0)
	{
		return FALSE;
	}
	WCHAR   *p   =   wcsrchr(   tWorkPath,   '\\'   );     
	*(p+1)   =   0;  
	path = tWorkPath;
	return TRUE;
}

CE_CONTROL_API BOOL AfxShowTaskBar( BOOL Show /*= TRUE*/ )
{
#ifdef  CH_CE_DEBUG 
	//Òþ²ØÈÎÎñÀ¸
	HWND hTaskBar;
	hTaskBar = ::FindWindow(TEXT("HHTaskBar"), NULL);  //ËÑÑ°ÈÎÎñÀ¸¾ä±ú
	if (NULL == hTaskBar)
	{
		hTaskBar = ::FindWindow(_T("Tray"), NULL);
	}
	if(NULL != hTaskBar)
	{
		if (Show)
		{
			::ShowWindow(hTaskBar, SW_SHOW); //Òþ²Ø
		}
		else
		{
			::ShowWindow(hTaskBar, SW_HIDE); //Òþ²Ø
		}
	}
#endif
	return TRUE;
}



CE_CONTROL_API BOOL AfxValidateRect( LPCRECT rc )
{

	InvalidateRect(AFX_MODULE_STATE::m_s_pInstance->m_wnd,rc,FALSE);
	return TRUE;
}

CE_CONTROL_API void AfxSetActiviy( Activity* act )
{
	AFX_MODULE_STATE::m_s_pInstance->pActiviy = act;
}

CE_CONTROL_API Activity* AfxGetActiviy()
{
	return AFX_MODULE_STATE::m_s_pInstance->pActiviy;
}

CE_CONTROL_API void AfxSetHWND( HWND hwnd )
{
	AFX_MODULE_STATE::m_s_pInstance->m_wnd = hwnd;
}

CE_CONTROL_API HWND AfxGetHWND()
{
	return AFX_MODULE_STATE::m_s_pInstance->m_wnd ;
}

CE_CONTROL_API BOOL AfxPostMessage( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	return PostMessage(AFX_MODULE_STATE::m_s_pInstance->m_wnd, nMsg, wParam, lParam);
}
