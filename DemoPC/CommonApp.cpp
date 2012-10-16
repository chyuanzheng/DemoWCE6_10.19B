#include "stdAfx.h"
#include "CommonApp.h"
#include "CommonWnd.h"


CCommonApp myApp;

/////////////////////////////////////////////////////////////////////////
// CCommonApp member functions

BOOL CCommonApp::InitInstance ()
{
	AfxShowTaskBar(FALSE);
    m_pMainWnd = new CCommonWnd;
    m_pMainWnd->ShowWindow (m_nCmdShow);
    m_pMainWnd->UpdateWindow();
    return TRUE;
}

BOOL CCommonApp::DeInitInstance()
{
	AfxShowTaskBar();
	return TRUE;
}
