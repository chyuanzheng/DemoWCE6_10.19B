#pragma once
#include "DllDefine.h"
class AbControl;
typedef  list<AbControl*> ControlList;
typedef AbControl* (*FunCrtControl)();
class CE_CONTROL_API AbControl 
{
public:

	AbControl( );
	~AbControl( );
	
	virtual void setCtrLayout( TiXmlElement * ele);//这里应该为纯虚函数
	virtual BOOL	AddCtrl(AbControl* control);
	//所有控件都必须实现的绘画与事件回答函数
	virtual void Draw( HDC hdcDst ) = 0;
	virtual BOOL Response(  UINT nMsg, WPARAM wParam, LPARAM lParam ){return FALSE;}
	BOOL DealCtrlMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);//**
	void Paint(HDC hdcDst);//**
    BOOL AdjustRect(int xleft, int ytop);
	void setCtrRect(TiXmlElement * ele);
	static HWND m_hCtrlWnd;
protected:
	
	RECT        m_ActRect;
    
    HWND  m_hWnd;
private:
	AbControl	*m_ParentCtrl;    
	ControlList  *m_pCtrlVet;
};

