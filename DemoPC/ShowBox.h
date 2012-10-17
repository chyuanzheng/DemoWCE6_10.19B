#pragma once
#include "../common/Button.h"
#include "../common/Edit.h"

#include "../common/BaseBoard.h"


class ShowBox : public BaseBoard
{
public:
    ShowBox(HWND hwnd, BaseBoard* pParentBoard = NULL);
	virtual ~ShowBox ();
    virtual void   Draw( HDC hdcDst ) ;
	virtual BOOL   Response( HDC hdc, UINT nMsg, WPARAM wParam, LPARAM lParam );


private:
	Button      m_b_turnoff;
	Button      m_b_restart;
    Button      m_b_exit;

    void  OnGoBack();
	void  OnTurnOff();
	void  OnRestart();

};
