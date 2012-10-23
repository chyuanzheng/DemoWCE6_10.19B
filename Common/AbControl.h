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
	
	//�ؼ����� ele�еĲ��������Լ�������
	virtual void setCtrLayout( TiXmlElement * ele){};//
    

	//�ؼ�����Ϣ�������
	BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);

	//�ؼ��Ļ��ƺ������
	void Paint(HDC hdcDst);//**
    BOOL AdjustRect(int xleft, int ytop);
	void setCtrRect(TiXmlElement * ele);
protected:
    //���ؼ�����Ϣ����
	virtual BOOL Response(  UINT nMsg, WPARAM wParam, LPARAM lParam ){return FALSE;}
	//���ؼ��Ļ���
	virtual void Draw( HDC hdcDst ){};
	BOOL	AddCtrl(AbControl* control);
	RECT        m_ActRect;
    CImagesManager *pImageManager;
private:
	AbControl	*m_ParentCtrl;    
	ControlList  *m_pCtrlVet;
};

