#pragma once

#include "AbControl.h"
class CE_CONTROL_API Button : public AbControl
{
protected:
	HANDLE     m_handleUp;
	HANDLE     m_handleDown;
	//按钮图片
	//判断是否被按下
	TCHAR     m_isButtonDown;
protected:

	//绘画
	virtual void Draw( HDC hdcDst );
	//响应自身事件
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
	BOOL InMyArea( int x, int y );
    

public:
	Button();
	virtual ~Button();

};
