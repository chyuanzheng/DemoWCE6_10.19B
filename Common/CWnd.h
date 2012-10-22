#pragma once
//#include "Control.h"

#include <ddraw.h>
#include "AbControl.h"
#define WM_EXIT_PROSS                 WM_USER + 100
typedef enum
{
    B_NULL,
	B_NORMAL,
	B_SMALLTOBIG,
	B_BIGTOSMALL,
    B_LEFTTORIGHT,
    B_RIGHTTOLEFT
} BOARD_EFFECT;

class CE_CONTROL_API CWnd
{
public:
    CWnd();
    ~CWnd();
    HWND  GetSafeHwnd();
    BOOL ShowWindow(int nCmdShow);
    void Invalidate(BOOL bErase = TRUE);
    void UpdateWindow();
    virtual void  PostNcDestroy();
    static CWnd* PASCAL FromHandlePermanent(HWND hWnd);
    //virtual void OnCreate();

    virtual BOOL Create(LPCTSTR lpszClassName,LPCTSTR lpszWindowName,DWORD dwStyle,const RECT& rect,HWND hWndParent=NULL,UINT nID = 0);
    
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    void  SetShowEffect(BOARD_EFFECT effect);

public:
    HWND	 m_hWnd;
    RECT     m_rect;
    CWnd     * m_pParent;
    INT      m_nExitCode;      
private:
    static CWnd *m_pWindow;

    void  OnPaint();
    BOOL RegisterWindow(LPCTSTR lpClassName);
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	HDC   m_hdcDest;
	HBITMAP  m_hmpDest;
	HBITMAP  m_hmpOldDest;

	//LPDIRECTDRAWCLIPPER DDraw_Attach_Clipper(LPDIRECTDRAWSURFACE7 lpdds,int num_rects,LPRECT clip_list)
    
};
