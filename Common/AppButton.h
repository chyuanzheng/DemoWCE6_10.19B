#pragma once

#include "AbControl.h"
class CE_CONTROL_API AppButton : public AbControl
{
protected:
	//�¼�
	UINT     m_nEventUp;
    UINT     m_nEventDown;
	HANDLE     m_handleUp;
	HANDLE     m_handleDown;
	//��ťͼƬ
	//�ж��Ƿ񱻰���
	TCHAR     m_isButtonDown;
protected:

	//�滭
	virtual void Draw( HDC hdcDst );
	//��Ӧ�����¼�
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
	BOOL InMyArea( int x, int y );
    

public:
	AppButton();
	virtual ~AppButton();

};
