#pragma once

#include "AbControl.h"
class CE_CONTROL_API Launch : public AbControl
{
public:
	Launch();
	virtual ~Launch();
	
protected:

	//��Ӧ�����¼�
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
	BOOL InMyArea( int x, int y );
    
};
