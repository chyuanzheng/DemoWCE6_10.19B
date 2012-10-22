#pragma once
#include "CWinApp.h"
#include "CWnd.h"
#include "Activity.h"
#include "AbControl.h"
#include <string>
using namespace std;

class AFX_MODULE_STATE 
{
public:
    CE_CONTROL_API friend AFX_MODULE_STATE*  AfxGetModuleState();
    CWinApp* m_pCurrentWinApp;
    HINSTANCE m_hCurrentInstanceHandle;
    static AFX_MODULE_STATE* m_s_pInstance;
	wstring m_sWorkPath;
    Activity *m_actBoard;
	HWND       m_wnd;
	Activity*  pActiviy;
private:
	
    AFX_MODULE_STATE()
    {
        m_pCurrentWinApp=NULL;
		m_sWorkPath.clear();
    }

};



CE_CONTROL_API CWinApp*  AfxGetApp();

CE_CONTROL_API HINSTANCE AfxGetInstanceHandle( );

CE_CONTROL_API BOOL  AfxWinInit(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                 LPTSTR lpCmdLine, int nCmdShow);


CE_CONTROL_API BOOL AfxValidateRect(LPCRECT  rc);

CE_CONTROL_API BOOL  AfxGetWorkPath(wstring &path);
CE_CONTROL_API BOOL  AfxShowTaskBar(BOOL Show = TRUE);

CE_CONTROL_API void AfxSetActiviy(Activity* act);
CE_CONTROL_API Activity* AfxGetActiviy();


CE_CONTROL_API void  AfxSetHWND(HWND  hwnd);
CE_CONTROL_API HWND  AfxGetHWND();
