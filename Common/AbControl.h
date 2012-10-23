#pragma once
#include "DllDefine.h"
#include "ImagesManager.h"
class AbControl;
typedef  list<AbControl*> ControlList;
typedef AbControl* (*FunCrtControl)();
class CE_CONTROL_API AbControl 
{
public:

	AbControl( );
	~AbControl( );
	
	//控件根据 ele中的参数设置自己的属性
	virtual void setCtrLayout( TiXmlElement * ele){};//
    

	//控件的消息函数入口
	BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);

	//控件的绘制函数入口
	void Paint(HDC hdcDst);//**
    BOOL AdjustRect(int xleft, int ytop);
	void setCtrRect(TiXmlElement * ele);
protected:
    //本控件的消息处理
	virtual BOOL Response(  UINT nMsg, WPARAM wParam, LPARAM lParam ){return FALSE;}
	//本控件的绘制
	virtual void Draw( HDC hdcDst ){};
	BOOL	AddCtrl(AbControl* control);
	RECT        m_ActRect;
    CImagesManager *pImageManager;
private:
	AbControl	*m_ParentCtrl;    
	ControlList  *m_pCtrlVet;
};

