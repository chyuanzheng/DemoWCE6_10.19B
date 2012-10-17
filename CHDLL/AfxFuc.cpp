#include "../common/StdAfx.h"
//#include "MessageWnd.h"
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

void AfxSetBoard(HWND wnd, Activity* bbd)
{
    _ASSERT(wnd&&AFX_MODULE_STATE::m_s_pInstance->m_wbMap.size()<4);
	HWND_INFO &wnd_info =  AFX_MODULE_STATE::m_s_pInstance->m_wbMap[wnd];
	if (wnd_info.actBd != bbd)
	{
		wnd_info.actBd = bbd;
		wnd_info.IsNewBoard = TRUE;
	}
    //::PostMessage(wnd,WM_PAINT,0,0);
	::InvalidateRect(wnd,NULL,FALSE);//cyz

}
Activity* AfxGetBoard(HWND wnd)
{
    WND_BOARD &wb = AFX_MODULE_STATE::m_s_pInstance->m_wbMap;
    WND_BOARD::iterator pos;
    pos = wb.find(wnd);
    if(pos  != wb.end() )
    {
        return wb[wnd].actBd;
    }
    else
        return NULL;
}

void AfxAddHWnd(HWND wnd, CWnd* cwd)
{

    WND_BOARD &wb = AFX_MODULE_STATE::m_s_pInstance->m_wbMap;
    HWND_INFO hi;
    hi.curWnd = cwd;
    wb[wnd]=hi;
}
void AfxDelHWnd(HWND wnd)
{
    WND_BOARD &wb = AFX_MODULE_STATE::m_s_pInstance->m_wbMap;
    WND_BOARD::iterator pos;
    pos = wb.find(wnd);
    if(pos  != wb.end() )
    {
        wb.erase(pos);
    }
    //_ASSERT(0);
}
CWnd* AfxGetCWnd(HWND wnd)
{
    WND_BOARD &wb = AFX_MODULE_STATE::m_s_pInstance->m_wbMap;
    WND_BOARD::iterator pos;
    pos = wb.find(wnd);
    if(pos  != wb.end() )
    {
        return wb[wnd].curWnd;
    }
    else
        return NULL;
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

CE_CONTROL_API BOOL AfxTestNewBoard( HWND wnd )
{
	WND_BOARD &wb = AFX_MODULE_STATE::m_s_pInstance->m_wbMap;
	WND_BOARD::iterator pos;
	pos = wb.find(wnd);
	if(pos  != wb.end() )
	{
		BOOL isnew = wb[wnd].IsNewBoard;
		wb[wnd].IsNewBoard = FALSE;
		return isnew;
	}
	else
		return FALSE;
}

CE_CONTROL_API BOOL AfxValidateRect( HWND wnd, const RECT & rc )
{
	CWnd *pWnd = AfxGetCWnd(wnd);
	_ASSERT(pWnd != NULL);
	pWnd->AddClipRect(rc);
	InvalidateRect(wnd,NULL,FALSE);
	return TRUE;
}