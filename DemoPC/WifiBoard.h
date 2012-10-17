#pragma once
#include "../common/Button.h"
#include "../common/Edit.h"

#include "../common/BaseBoard.h"


class WifiBoard : public BaseBoard
{
public:
    WifiBoard(HWND hwnd, BaseBoard* pParentBoard = NULL);
	virtual ~WifiBoard ();
    virtual void   Draw( HDC hdcDst ) ;
	virtual BOOL   Response( HDC hdc, UINT nMsg, WPARAM wParam, LPARAM lParam );


private:
	Button      m_b_ok;
    Button      m_b_cancel;

	Edit        m_e_ap;
	Edit        m_e_time;

    void  OnOk();
	void  OnCancel();
	void  OnRestart();

};
