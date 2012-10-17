#include "../common/stdAfx.h"
#include "WifiBoard.h"
#include "resource.h"
#include "Event.h"
#include "Position.h"
#include <pm.h>
#define MAX_LOADSTRING 100
//#include "SecondBoard.h"

/////////////////////////////////////////////////////////////////////////
// WifiBoard message map and member functions


const TCHAR* wifibackshut = L"res\\back1.png";
const RECT  WIFI_RC = { 100, 60 ,100+600,60+360 };

const TCHAR* okdown = L"res\\home1.png";
const TCHAR* okup = L"res\\home2.png";
const TCHAR* returnDown = L"res\\home1.png";
const TCHAR* returnUp = L"res\\home2.png";



const RECT  WIFI_OK = { 200, 310 ,200+92,310+31 };
const RECT  WIFI_CANCEL = { 308, 310 ,308+92,310+31 };

const RECT  WIFI_AP_E   = {20,0,20+180,0+60};


#define  TIME_ID   100
WifiBoard::WifiBoard (HWND hwnd,BaseBoard* pParentBoard)
    :BaseBoard(hwnd,pParentBoard)
{
// Init 函数将控件的主要属性设定好，其他属性可通过函数来设定。

	InitBoard(wifibackshut,&WIFI_RC);

	m_b_ok.Init(okup, okdown, WIFI_OK, CHM_WIFI_OK );
	AddCtrl(&m_b_ok);//按键
	
	m_b_cancel.Init(returnUp, returnDown, WIFI_CANCEL, CHM_WIFI_CANCEL );
	AddCtrl(&m_b_cancel);//按键

	m_e_ap.SetFont(22,600,L"微软雅黑");
	m_e_ap.SetArea(WIFI_AP_E);
	m_e_ap.SetTextColor(RGB(20,20,250));
	m_e_ap.SetText(L"网路站点信息：");
	AddCtrl(&m_e_ap);//日期



}
WifiBoard::~WifiBoard ()
{
	
}

void   WifiBoard::Draw( HDC hdcDst ) 
{
    BaseBoard::Draw( hdcDst );
}
BOOL   WifiBoard::Response( HDC hdc, UINT nMsg, WPARAM wParam, LPARAM lParam )
{
    switch( nMsg )
    {
	case CHM_WIFI_CANCEL:  
		OnCancel();
		return TRUE;
	case CHM_WIFI_OK:  
        OnOk();
        return TRUE;

    default:
        break;
    }
    return FALSE;
}
void  WifiBoard::OnOk()
{
    DestroyBoard();
}

void WifiBoard::OnCancel()
{
	DestroyBoard();
}

