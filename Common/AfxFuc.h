#pragma once
#include "CWinApp.h"
#include "CWnd.h"
#include "Activity.h"
#include "AbControl.h"
#include <string>
using namespace std;
typedef struct HwndInfo
{
    HwndInfo():curWnd(NULL),actBd(NULL){};
    CWnd  *curWnd;
    Activity* actBd;//
	BOOL     IsNewBoard;
}HWND_INFO;
typedef map<HWND,HWND_INFO> WND_BOARD;
class AFX_MODULE_STATE 
{
public:
    CE_CONTROL_API friend AFX_MODULE_STATE*  AfxGetModuleState();
    CWinApp* m_pCurrentWinApp;
    HINSTANCE m_hCurrentInstanceHandle;
    static AFX_MODULE_STATE* m_s_pInstance;
	wstring m_sWorkPath;
    CWnd *m_mainWnd;
    Activity *m_actBoard;
    WND_BOARD  m_wbMap;
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

CE_CONTROL_API void AfxSetBoard(HWND wnd, Activity* bbd);
CE_CONTROL_API Activity* AfxGetBoard(HWND wnd);
CE_CONTROL_API void AfxAddHWnd(HWND wnd, CWnd* cwd);//在CWnd的构造函数中
CE_CONTROL_API BOOL AfxTestNewBoard(HWND wnd);
CE_CONTROL_API void AfxDelHWnd(HWND wnd);//在CWnd的析构函数中
CE_CONTROL_API CWnd* AfxGetCWnd(HWND wnd);
CE_CONTROL_API BOOL AfxValidateRect(HWND wnd, const RECT & rc);

CE_CONTROL_API BOOL  AfxGetWorkPath(wstring &path);
CE_CONTROL_API BOOL  AfxShowTaskBar(BOOL Show = TRUE);
