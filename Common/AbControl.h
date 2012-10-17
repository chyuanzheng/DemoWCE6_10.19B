#pragma once
#include "DllDefine.h"
class AbControl;
typedef  list<AbControl*> ControlList;
class CE_CONTROL_API AbControl 
{
public:
	AbControl(HWND hwnd);
	AbControl( );
	~AbControl( );
	
	virtual BOOL	AddCtrl(AbControl* control);
	//���пؼ�������ʵ�ֵĻ滭���¼��ش���
	virtual void Draw( HDC hdcDst ) = 0;
    virtual BOOL Response( HDC hdc, UINT nMsg, WPARAM wParam, LPARAM lParam ){return FALSE;}
	BOOL DealCtrlMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);//**
	void Paint(HDC hdcDst);//**
    BOOL AdjustRect(int xleft, int ytop);
protected:
	RECT        m_ActRect;
    static HWND m_hCtrlWnd;
    HWND  m_hWnd;
private:
	AbControl	*m_ParentCtrl;    
	ControlList  *m_pCtrlVet;
};
