#pragma once
#include "DllDefine.h"
class AbControl;
typedef  list<AbControl*> ControlList;
typedef AbControl* (*FunCrtControl)();
class CE_CONTROL_API AbControl 
{
public:
	AbControl(HWND hwnd);
	AbControl( );
	~AbControl( );
	
	virtual BOOL	AddCtrl(AbControl* control);
	//所有控件都必须实现的绘画与事件回答函数
	virtual void Draw( HDC hdcDst ) = 0;
    virtual BOOL Response( HDC hdc, UINT nMsg, WPARAM wParam, LPARAM lParam ){return FALSE;}
	BOOL DealCtrlMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);//**
	void Paint(HDC hdcDst);//**
    BOOL AdjustRect(int xleft, int ytop);
	static HWND m_hCtrlWnd;
protected:
	RECT        m_ActRect;
    
    HWND  m_hWnd;
private:
	AbControl	*m_ParentCtrl;    
	ControlList  *m_pCtrlVet;
};

