#pragma once
 
#include "CWnd.h"
//����Ӧ��
class CE_CONTROL_API CWinApp
{
public:
	CWinApp( );
	virtual int Run();
    virtual BOOL InitApplication();
    virtual BOOL InitInstance() = 0;
	virtual BOOL DeInitInstance() = 0;
    CWnd* m_pMainWnd;

	//ʵ�����
	HINSTANCE m_hInstance;
	LPTSTR m_lpCmdLine;
	int    m_nCmdShow;
	LPCTSTR m_pszAppName;
};
