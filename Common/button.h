#pragma once

#include "AbControl.h"
#include "ImagesManager.h"
class CE_CONTROL_API Button : public AbControl
{
protected:
	//�¼�
	UINT     m_nEventUp;
    UINT     m_nEventDown;
	UINT     m_nIDUp;
	UINT     m_nIDDown;
	//��ťͼƬ
	//�ж��Ƿ񱻰���
	TCHAR     m_isButtonDown;
	CImagesManager *pImageManager;
protected:

	//�滭
	virtual void Draw( HDC hdcDst );
	//��Ӧ�����¼�
	virtual BOOL Response( HDC hdc,	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
	BOOL InMyArea( int x, int y );
    

public:
	Button();
	virtual ~Button();
	BOOL  Init(UINT wMapUp, UINT wMapDown, const RECT& rt, UINT nEventUp, UINT nEventDown = 0);//��������������ȵ��� 
	BOOL  Init(const TCHAR* pfileUp,const TCHAR* pfileDown, const RECT& rt, UINT nEventUp, UINT nEventDown = 0);

};
