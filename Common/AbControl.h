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
	virtual void setCtrLayout( TiXmlElement * ele);//
    

	//�ؼ�����Ϣ�������
	BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);

	//�ؼ��Ļ��ƺ������
	void Paint(HDC hdcDst);//**
    BOOL AdjustRect(int xleft, int ytop);
	void setLayer(int layer=0);//ʹ�ñ��ؼ����ᱻͬ���ĸ��ǡ�������㡣 Ŀǰֻ֧������
	int  getLayer(){return m_nlayer;}
	void getCtrRect( RECT & rt );
	void setCtrRect(const RECT & rt );
	string getCtrName(){return m_name;}
	AbControl *findViewByName(const CHAR* name);//���������ҵ��ӿؼ�
protected:
    //���ؼ�����Ϣ����
	virtual BOOL Response(  UINT nMsg, WPARAM wParam, LPARAM lParam ){return FALSE;}
	//���ؼ��Ļ���
	virtual void Draw( HDC hdcDst ){};
	BOOL	AddCtrl(AbControl* control);
	RECT        m_ActRect;
    CImagesManager *pImageManager;
	AbControl	 *m_ParentCtrl; //���ؼ�  
	ControlList  *m_pCtrlVet;//�����ӿؼ�
	string     m_name;
private:
	int           m_nlayer;
	
};

