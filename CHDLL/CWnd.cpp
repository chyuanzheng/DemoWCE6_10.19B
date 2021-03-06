#include "../common/StdAfx.h"
#include "../common/CWnd.h"
//#include "resource.h"
#define DDRAW_INIT_STRUCT(ddstruct) { memset(&ddstruct,0,sizeof(ddstruct)); ddstruct.dwSize=sizeof(ddstruct); }
#define  DEF_WNDCLASS    L"CHNiHao"
CWnd *CWnd::m_pWindow=NULL;
CWnd::CWnd()
{
    m_hWnd = NULL;

	m_hdcDest = NULL;
	m_hmpDest = NULL;
	m_hmpOldDest = NULL;
    m_nExitCode = 0;

}
CWnd::~CWnd()
{
	::SelectObject( m_hdcDest, m_hmpOldDest);
	::DeleteObject( m_hmpDest);
	::DeleteDC( m_hdcDest );

	
}
HWND CWnd::GetSafeHwnd()
{
    return m_hWnd;
}


BOOL CWnd::Create(LPCTSTR lpszClassName,LPCTSTR lpszWindowName,DWORD dwStyle,const RECT& rect,HWND hWndParent,UINT nID)
{
	//if( !RegisterWindow( lpszClassName ) )
	//{
	//	MessageBox( NULL, _T("Can not register class"), _T("!"), MB_OK );
	//	return FALSE;
	//}
    static BOOL bReg = 0;
    if(lpszClassName == NULL)
    {
        lpszClassName = DEF_WNDCLASS;
        if(!bReg)//保证只注册一次
        {
            RegisterWindow( lpszClassName );
            bReg = 1;
        }
    }
	if( ::IsWindow( m_hWnd ) )
		return FALSE;


    m_hWnd =::CreateWindowEx(NULL, lpszClassName, lpszWindowName, dwStyle,
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		hWndParent, NULL, AfxGetInstanceHandle(),NULL);
  
	if (m_hWnd)
	{


		HDC hdc = ::GetDC( m_hWnd );
		m_hdcDest = ::CreateCompatibleDC( hdc );
		m_hmpDest =::CreateCompatibleBitmap( hdc, rect.right - rect.left, rect.bottom - rect.top);
		m_hmpOldDest = ( HBITMAP )::SelectObject( m_hdcDest, m_hmpDest);

		::ReleaseDC( m_hWnd, hdc);
		m_rect =  rect;
		::SetBkMode( m_hdcDest, TRANSPARENT );
		AfxSetHWND(m_hWnd);
		m_pWindow = this;
		return TRUE;
	}

	
	return FALSE;
}
BOOL CWnd::ShowWindow(int nCmdShow)
	{ _ASSERT(::IsWindow(m_hWnd)); return ::ShowWindow(m_hWnd, nCmdShow); }
void CWnd::Invalidate(BOOL bErase)
	{ _ASSERT(::IsWindow(m_hWnd)); ::InvalidateRect(m_hWnd, NULL, bErase); }
void CWnd::UpdateWindow()
	{ _ASSERT(::IsWindow(m_hWnd)); ::UpdateWindow(m_hWnd); }
void CWnd::PostNcDestroy()
{
	// default to nothing
}

BOOL CWnd::RegisterWindow(LPCTSTR lpClassName)
{
	//为防止此类已经被注册过，先销毁注册
	//::UnregisterClass( lpClassName, GetModuleHandle(NULL) );

	//设置窗体类属性
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = lpClassName;
	wndclass.lpszMenuName = NULL;
	wndclass.hInstance = GetModuleHandle(NULL);
	wndclass.hbrBackground = NULL;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = NULL;

	return RegisterClass(&wndclass);
}
LRESULT CALLBACK CWnd::WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	//调用窗口类的回调函数
   if(m_pWindow == NULL)
   {
        return ::DefWindowProc(hWnd, nMsg, wParam, lParam);;
   }
   switch( nMsg )
   {
   case WM_EXIT_PROSS:
	   return ::DestroyWindow(m_pWindow->m_hWnd);
   case WM_DESTROY://
	   PostQuitMessage(m_pWindow->m_nExitCode);
	   //#ifndef CH_CE_DEBUG
	   //	   return 0; 
	   //   case WM_NCDESTROY:
	   //#endif
	   m_pWindow->PostNcDestroy();
	   return 0; 
   default:
	   break;
   }

   return m_pWindow->WindowProc( nMsg, wParam, lParam );
}
LRESULT CWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    Activity* db = AfxGetActiviy();
    if (db ==NULL)
    {
		return 0;
    }

	switch( message )
	{
         case WM_PAINT:
             OnPaint();
            return 0;
		default:
			break;
	}
	
    if(db->DealCtrlMsg(message, wParam, lParam))
    {
        return 0;
    }   
    return ::DefWindowProc(m_hWnd, message, wParam, lParam);
};
void  CWnd::SetShowEffect(BOARD_EFFECT effect)
{
}
void  CWnd::OnPaint()
{

    Activity* db = AfxGetActiviy();

    PAINTSTRUCT ps;

	HDC hdc = ::BeginPaint( m_hWnd, &ps );
	//DWORD time =::GetTickCount();
	db->Paint(m_hdcDest);
	//time = ::GetTickCount()-time;
	//WCHAR  show[60];
	//wsprintf(show,L"time is :%d\r\n",time);
	//OutputDebugString(show);
	::BitBlt(hdc, 0,0,m_rect.right -m_rect.left,m_rect.bottom-m_rect.top,m_hdcDest,0,0,SRCCOPY);
	

	::EndPaint( m_hWnd, &ps );
}





