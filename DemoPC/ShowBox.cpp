#include "../common/stdAfx.h"
#include "ShowBox.h"
#include "resource.h"
#include "Event.h"
#include "Position.h"
#include <pm.h>
#define MAX_LOADSTRING 100
//#include "SecondBoard.h"

/////////////////////////////////////////////////////////////////////////
// ShowBox message map and member functions



const TCHAR* backshut = L"res\\item.png";

const TCHAR* turnoffdown = L"res\\home1.png";
const TCHAR* turnoffup = L"res\\home2.png";
const TCHAR* restartdown = L"res\\home1.png";
const TCHAR* restartup = L"res\\home2.png";
const TCHAR* canceldown = L"res\\home1.png";
const TCHAR* cancelup = L"res\\home2.png";

//const RECT  SHOW_RC = { 40, 40 ,400+40,400+40 };

const RECT  SHOW_TURNOFF = { 258, 155 ,258+283,155+70 };
//const RECT  SHOW_RESTART = { 258, 205 ,258+283,205+70 };
const RECT  SHOW_CANCEL = { 258, 255 ,258+283,255+70 };




#define  TIME_ID   100
ShowBox::ShowBox (HWND hwnd,BaseBoard* pParentBoard)
    :BaseBoard(hwnd,pParentBoard)
{
// Init 函数将控件的主要属性设定好，其他属性可通过函数来设定。

	InitBoard(backshut);

	m_b_turnoff.Init(turnoffup, turnoffdown, SHOW_TURNOFF, CHM_TURNOFF );
	AddCtrl(&m_b_turnoff);//按键
	
	//m_b_restart.Init(restartup, restartdown, SHOW_RESTART, CHM_RESTART );
	//AddCtrl(&m_b_restart);//按键
	
	m_b_exit.Init(cancelup, canceldown, SHOW_CANCEL, WM_EXIT_GAME );
	AddCtrl(&m_b_exit);//按键



}
ShowBox::~ShowBox ()
{
	
}

void   ShowBox::Draw( HDC hdcDst ) 
{
    BaseBoard::Draw( hdcDst );
}
BOOL   ShowBox::Response( HDC hdc, UINT nMsg, WPARAM wParam, LPARAM lParam )
{
    switch( nMsg )
    {
	case CHM_TURNOFF:  
		OnTurnOff();
		return TRUE;
	//case CHM_RESTART:  
	//	OnRestart();
	//	return TRUE;
    case WM_EXIT_GAME:  
        OnGoBack();
        return TRUE;

    default:
        break;
    }
    return FALSE;
}
void  ShowBox::OnGoBack()
{
    DestroyBoard();
}

void ShowBox::OnTurnOff()
{
	DWORD RET = ::SetSystemPowerState(NULL, POWER_STATE_SUSPEND, POWER_FORCE);
	if (ERROR_SUCCESS  != RET)
	{
		RET = GetLastError();
		//MessageBeep(1000);
	}
}

void ShowBox::OnRestart()
{
	//::SetSystemPowerState(NULL, POWER_STATE_BOOT, POWER_FORCE);
}