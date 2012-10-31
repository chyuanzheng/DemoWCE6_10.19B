#pragma once

#include "AbControl.h"
class CE_CONTROL_API AppButton : public AbControl
{
public:
	void setAppRect(const RECT &rt);
	void getAppRect(RECT &rt);
	void slideApp( int xslide ); 
	virtual void setCtrLayout( TiXmlElement * ele);
	AppButton();
	virtual ~AppButton();
	static AppButton* MoveApp;
	static AppButton* backApp;
protected:
	//事件
	UINT     m_nEventUp;
	HANDLE     m_handleUp;
	int m_xpos;//移动的x坐标
	int m_ypos;//y
	int m_xmove;//移动的x坐标 距离
	int m_ymove;//y
	RECT  m_appRect;//正在移动的rect
	//按钮图片
	//判断是否被按下
	TCHAR     m_isButtonDown;
protected:

	//绘画
	void exchangeApp(AppButton *pApp);
	virtual void Draw( HDC hdcDst );
	//响应自身事件
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	
	BOOL InMyArea( int x, int y );
    



};
