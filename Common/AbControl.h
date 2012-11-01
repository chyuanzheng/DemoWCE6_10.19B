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
	virtual void setCtrLayout( TiXmlElement * ele);//
    

	//控件的消息函数入口
	BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);

	//控件的绘制函数入口
	void Paint(HDC hdcDst);//**
    BOOL AdjustRect(int xleft, int ytop);
	void setLayer(int layer=0);//使得本控件不会被同级的覆盖。最多三层。 目前只支持两层
	int  getLayer(){return m_nlayer;}
	void getCtrRect( RECT & rt );
	void setCtrRect(const RECT & rt );
	string getCtrName(){return m_name;}
	AbControl *findViewByName(const CHAR* name);//根据名字找到子控件
protected:
    //本控件的消息处理
	virtual BOOL Response(  UINT nMsg, WPARAM wParam, LPARAM lParam ){return FALSE;}
	//本控件的绘制
	virtual void Draw( HDC hdcDst ){};
	BOOL	AddCtrl(AbControl* control);
	RECT        m_ActRect;
    CImagesManager *pImageManager;
	AbControl	 *m_ParentCtrl; //父控件  
	ControlList  *m_pCtrlVet;//所有子控件
	string     m_name;
private:
	int           m_nlayer;
	
};

