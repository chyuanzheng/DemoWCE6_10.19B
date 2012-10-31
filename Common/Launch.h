#pragma once

#include "AbControl.h"
class CE_CONTROL_API Launch : public AbControl
{
public:
	Launch();
	virtual ~Launch();
	BOOL checkRect( const RECT & rect );
protected:

	//响应自身事件
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
	BOOL InMyArea( int x, int y );
	BOOL inSlideArea( int x, int y );
	int  m_vmar;
	int m_xpos;//移动的x坐标
	TCHAR     m_isButtonDown;
	
    
};
