#pragma once

#include "AbControl.h"
class CE_CONTROL_API Launch : public AbControl
{
public:
	Launch();
	virtual ~Launch();
	BOOL checkRect( const RECT & rect );
protected:

	//��Ӧ�����¼�
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
	BOOL InMyArea( int x, int y );
	BOOL inSlideArea( int x, int y );
	int  m_vmar;
	int m_xpos;//�ƶ���x����
	TCHAR     m_isButtonDown;
	
    
};
