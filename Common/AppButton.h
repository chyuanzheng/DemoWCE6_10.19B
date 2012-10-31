#pragma once

#include "AbControl.h"
class CE_CONTROL_API AppButton : public AbControl
{
public:
	void setAppRect(const RECT &rt);
	void getAppRect(RECT &rt);
	void slideApp( int xslide ); 
	virtual void setCtrLayout( TiXmlElement * ele);
	AppButton();
	virtual ~AppButton();
	static AppButton* MoveApp;
	static AppButton* backApp;
protected:
	//�¼�
	UINT     m_nEventUp;
	HANDLE     m_handleUp;
	int m_xpos;//�ƶ���x����
	int m_ypos;//y
	int m_xmove;//�ƶ���x���� ����
	int m_ymove;//y
	RECT  m_appRect;//�����ƶ���rect
	//��ťͼƬ
	//�ж��Ƿ񱻰���
	TCHAR     m_isButtonDown;
protected:

	//�滭
	void exchangeApp(AppButton *pApp);
	virtual void Draw( HDC hdcDst );
	//��Ӧ�����¼�
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	
	BOOL InMyArea( int x, int y );
    



};
