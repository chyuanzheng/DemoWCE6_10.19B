#pragma once

#include "AbControl.h"
#include "ImagesManager.h"
class CE_CONTROL_API Button : public AbControl
{
protected:
	//事件
	UINT     m_nEventUp;
    UINT     m_nEventDown;
	UINT     m_nIDUp;
	UINT     m_nIDDown;
	//按钮图片
	//判断是否被按下
	TCHAR     m_isButtonDown;
	CImagesManager *pImageManager;
protected:

	//绘画
	virtual void Draw( HDC hdcDst );
	//响应自身事件
	virtual BOOL Response( HDC hdc,	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
	BOOL InMyArea( int x, int y );
    

public:
	Button();
	virtual ~Button();
	BOOL  Init(UINT wMapUp, UINT wMapDown, const RECT& rt, UINT nEventUp, UINT nEventDown = 0);//这个函数必须最先调用 
	BOOL  Init(const TCHAR* pfileUp,const TCHAR* pfileDown, const RECT& rt, UINT nEventUp, UINT nEventDown = 0);

};
