#pragma once

#include "AbControl.h"
class CE_CONTROL_API Button : public AbControl
{
protected:
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
	Button();
	virtual ~Button();

};
