#include "../common/stdAfx.h"
#include "../common/ControlHelp.h"

#include "AppStorePad.h"
#include "resource.h"
#include "Event.h"
#include "Position.h"
#include "ShowBox.h"
#include "WifiBoard.h"
#include "wifi.h"

#define MAX_LOADSTRING 100
//#include "SecondBoard.h"

/////////////////////////////////////////////////////////////////////////
// OpenBoard message map and member functions

const TCHAR* backimage = L"res\\back1.png";
const TCHAR* flashdown = L"res\\home1.png";
const TCHAR* flashup = L"res\\home2.png";

const TCHAR* moviedown = L"res\\home1.png";
const TCHAR* movieup = L"res\\home2.png";

const TCHAR* readdown = L"res\\home1.png";
const TCHAR* readup = L"res\\home2.png";

const TCHAR* exitdown = L"res\\home1.png";
const TCHAR* exitup = L"res\\home2.png";

const TCHAR* webdown = L"res\\home1.png";
const TCHAR* webup = L"res\\webup.png";

const TCHAR* speeddown = L"res\\home1.png";
const TCHAR* speedup = L"res\\home2.png";

const TCHAR* wifidown = L"res\\home1.png";
const TCHAR* wifiup = L"res\\home2.png";

const RECT  BUTTON_READPAPER = { 0, 40 ,200+0,200+40 };
const RECT  BUTTON_FLASH = { 200, 40 ,200+200,200+40 };
const RECT  BUTTON_MOVIE = { 400, 40 ,200+400,200+40 };
const RECT  BUTTON_WEB = { 600, 40 ,200+600,200+40 };
const RECT  BUTTON_SPEED = { 0, 240 ,200+0,200+240 };
const RECT  BUTTON_WIFI = { 200, 240 ,200+200,200+240 };

const RECT  BUTTON_EXIT = { 751, 0 ,751+40,40 };

const RECT  DATA_E = { 0, 0 ,0+260,40 };
const RECT  TIME_E = { 655, 9 ,655+70,9+22 };
const RECT  WAIT_E = { 200, 200 ,600,280 };

#define  TIME_ID   100
AppStorePad::AppStorePad (HWND hwnd,Activity* pParentBoard)
    :Activity(hwnd,pParentBoard)
{
// Init 函数将控件的主要属性设定好，其他属性可通过函数来设定。

	InitBoard(backimage);


	m_b_flash.Init(flashup, flashdown,  BUTTON_FLASH, CHM_PLAY_FLASH );
	AddCtrl(&m_b_flash);//按键 

	m_b_movie.Init(movieup, moviedown, BUTTON_MOVIE, CHM_PLAY_MOVIE );
	AddCtrl(&m_b_movie);//按键 

	m_b_readpaper.Init(readup, readdown, BUTTON_READPAPER, CHM_PLAY_PAPER );
	AddCtrl(&m_b_readpaper);//按键 

	m_b_web.Init(webup, webdown, BUTTON_WEB, CHM_PLAY_WEB );
	AddCtrl(&m_b_web);//按键 网页

	m_b_speed.Init(speedup, speeddown, BUTTON_SPEED, CHM_PLAY_SPEED );
	AddCtrl(&m_b_speed);//按键 网速

	m_b_wifi.Init(wifiup, wifidown, BUTTON_WIFI, CHM_PLAY_WIFI );
	AddCtrl(&m_b_wifi);//按键 关机

	m_b_exit.Init(exitup, exitdown, BUTTON_EXIT, WM_EXIT_GAME );
	AddCtrl(&m_b_exit);//按键

	m_e_date.SetFont(22,600,L"微软雅黑");
	m_e_date.SetArea(DATA_E);
	m_e_date.SetTextColor(RGB(250,250,250));
	AddCtrl(&m_e_date);//日期

	m_e_time.SetFont(16,600,L"微软雅黑");
	m_e_time.SetArea(TIME_E);
	m_e_time.SetTextColor(RGB(250,250,250));
	AddCtrl(&m_e_time);//时间

	m_e_waitweb.SetFont(24,600,L"微软雅黑");
	m_e_waitweb.SetArea(WAIT_E);
	m_e_waitweb.SetTextColor(RGB(250,100,50));
	AddCtrl(&m_e_waitweb);//时间

	

	::SetTimer(hwnd, TIME_ID,1000, NULL);

	m_hProcess = NULL;

}
AppStorePad::~AppStorePad ()
{
	
}

void   AppStorePad::Draw( HDC hdcDst ) 
{
    Activity::Draw( hdcDst );
}
BOOL   AppStorePad::Response( HDC hdc, UINT nMsg, WPARAM wParam, LPARAM lParam )
{
    switch( nMsg )
    {
	case WM_TIMER:  
		if (OnTimer(UINT(wParam)))
			return TRUE;
		return FALSE;
    case WM_EXIT_GAME:  
        OnGoBack();
        return TRUE;
	case CHM_PLAY_FLASH:
		//OnPlayFlash();
		return TRUE;
	case CHM_PLAY_MOVIE:
		//OnPlayMovie();
		return TRUE;
    case CHM_PLAY_PAPER:
        //OnPlayPaper();
        return TRUE;
	case CHM_PLAY_WEB://
		//OnPlayWeb();
		return TRUE;
	case CHM_PLAY_SPEED:
		//OnPlaySpeed();
		return TRUE;
	case CHM_PLAY_WIFI:
		//OnPlayWifi();
		return TRUE;
	case WM_APP+778:
		//OnPlayShut( wParam, lParam);
		return TRUE;
    default:
        break;
    }
    return FALSE;
}
void  AppStorePad::OnGoBack()
{
	//if (GetEVDOStatus()== IDS_RAS_CONNECTED)
	//{
	//	if (EVDO_Hangup())
	//	{
	//		CloseEVDODevice();
	//	}
	//	
	//}
	//::KillTimer(m_hWnd,TIME_ID);
    DestroyBoard();
}

void AppStorePad::OnPlayFlash()
{
	CreatePlay(L"\\NandFlash\\demo3\\flash");
}

void AppStorePad::OnPlayMovie()
{
	CreatePlay(L"\\NandFlash\\demo3\\movie");
}

void AppStorePad::OnPlayPaper()
{
	CreatePlay(L"\\NandFlash\\TabletSoft\\TabletSoft");
}
void AppStorePad::OnPlayWeb()
{

	OnStartAWeb(_T("http://www.hao123.com"));

}

void AppStorePad::OnPlaySpeed()
{
	//OnStartAWeb(_T("http://news.sxrtv.com/speedtest.htm"));
	OnStartAWeb(_T("http://www.bjnet.net.cn/dkcs/BarTest.html"));
}

BOOL AppStorePad::CreatePlay( const WCHAR *path )
{
	if (m_hProcess != NULL)
	{
		if (WAIT_OBJECT_0 != ::WaitForSingleObject(m_hProcess, 0))
		{
			return FALSE;
		}
		CloseHandle(m_hProcess);
		m_hProcess = NULL;
	}
	PROCESS_INFORMATION processInfo; //进程相关信息
	if (!CreateProcess(path, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &processInfo))
	{
		return FALSE;
	}
	CloseHandle(processInfo.hThread);
	m_hProcess = processInfo.hProcess;
	return TRUE;
}

BOOL AppStorePad::OnTimer( UINT id )
{
	if (id != TIME_ID)
	{
		return FALSE;
	}
	SYSTEMTIME sy;
	WCHAR sdtime[50];
	::GetLocalTime(&sy);
	swprintf(sdtime,L"%02d:%02d",sy.wHour,sy.wMinute);
	if (sy.wHour<12)
	{
		wcscat(sdtime,L"AM");
	}
	else
	{
		wcscat(sdtime,L"PM");
	}
	m_e_time.SetText(sdtime);
	//ULARGE_INTEGER f1,f2,f3;
	//::GetDiskFreeSpaceEx(L"\\NandFlash", &f1,&f2,&f3);
	swprintf(sdtime,L"%04d 年 %02d 月 %02d 日",sy.wYear,sy.wMonth,sy.wDay);
	m_e_date.SetText(sdtime);
	return TRUE;
}

void AppStorePad::OnPlayShut(WPARAM wparam,LPARAM lparam)
{
	if(UINT(lparam) == 0x300)
	{
		//new ShowBox(m_hWnd, this);
	}
}

void AppStorePad::OnStartAWeb( const WCHAR * web )//
{
	if (m_hProcess != NULL)
	{
		if (WAIT_OBJECT_0 != ::WaitForSingleObject(m_hProcess, 0))
		{
			return;
		}
		CloseHandle(m_hProcess);
		m_hProcess = NULL;
	}

	BOOL IsWebLink = FALSE;
	const WCHAR * webPath;
	m_e_waitweb.SetText(L"正在连接网络，请等待……",Edit::FreInstant);
	//if (OpenEVDODevice())
	//{
	//	IsWebLink = EVDO_Dial(L"skd");
	//}
	
	if (IsWebLink)
	{
		m_e_waitweb.SetText(L"连接成功",Edit::FreInstant);
		Sleep(300);
		webPath = web;
	}
	else
	{
		m_e_waitweb.SetText(L"连接失败",Edit::FreInstant);
		Sleep(300);
		webPath = NULL;
	}
	m_e_waitweb.SetText(L"",Edit::DoNull);


	SHELLEXECUTEINFO   ExecuteInfo;
	ExecuteInfo.cbSize   =   sizeof( ExecuteInfo);
	ExecuteInfo.fMask   =   SEE_MASK_NOCLOSEPROCESS |  SEE_MASK_FLAG_NO_UI;  
	ExecuteInfo.hwnd   =   NULL;
	ExecuteInfo.lpVerb   =   NULL;   
	ExecuteInfo.lpFile   =   webPath;
	ExecuteInfo.lpParameters   =   NULL;
	ExecuteInfo.lpDirectory   =   NULL;
	ExecuteInfo.nShow   =   SW_HIDE; 
	BOOL   bResult   =   ShellExecuteEx(&ExecuteInfo); 
	if( !bResult && (int)ExecuteInfo.hInstApp <= 32 )
	{  
		return;
	}   
	AfxShowTaskBar();
	if (WaitForSingleObject(ExecuteInfo.hProcess,INFINITE)== WAIT_OBJECT_0)
	{
		AfxShowTaskBar(FALSE);
		CloseHandle(ExecuteInfo.hProcess);
	}
}

void AppStorePad::OnPlayWifi()
{
	//WifiBoard *pWifi = new WifiBoard(m_hWnd,this);
	//pWifi->DoModal();
}

Activity* AppStorePad::CreateControl()
{
	return new AppStorePad;
}

void AppStorePad::onCreate()
{
	InitBoard(backimage);


	m_b_flash.Init(flashup, flashdown,  BUTTON_FLASH, CHM_PLAY_FLASH );
	AddCtrl(&m_b_flash);//按键 

	m_b_movie.Init(movieup, moviedown, BUTTON_MOVIE, CHM_PLAY_MOVIE );
	AddCtrl(&m_b_movie);//按键 

	m_b_readpaper.Init(readup, readdown, BUTTON_READPAPER, CHM_PLAY_PAPER );
	AddCtrl(&m_b_readpaper);//按键 

	m_b_web.Init(webup, webdown, BUTTON_WEB, CHM_PLAY_WEB );
	AddCtrl(&m_b_web);//按键 网页

	m_b_speed.Init(speedup, speeddown, BUTTON_SPEED, CHM_PLAY_SPEED );
	AddCtrl(&m_b_speed);//按键 网速

	m_b_wifi.Init(wifiup, wifidown, BUTTON_WIFI, CHM_PLAY_WIFI );
	AddCtrl(&m_b_wifi);//按键 关机

	m_b_exit.Init(exitup, exitdown, BUTTON_EXIT, WM_EXIT_GAME );
	AddCtrl(&m_b_exit);//按键

	m_e_date.SetFont(22,600,L"微软雅黑");
	m_e_date.SetArea(DATA_E);
	m_e_date.SetTextColor(RGB(250,250,250));
	AddCtrl(&m_e_date);//日期

	m_e_time.SetFont(16,600,L"微软雅黑");
	m_e_time.SetArea(TIME_E);
	m_e_time.SetTextColor(RGB(250,250,250));
	AddCtrl(&m_e_time);//时间

	m_e_waitweb.SetFont(24,600,L"微软雅黑");
	m_e_waitweb.SetArea(WAIT_E);
	m_e_waitweb.SetTextColor(RGB(250,100,50));
	AddCtrl(&m_e_waitweb);//时间



	//::SetTimer(hwnd, TIME_ID,1000, NULL);

	m_hProcess = NULL;
}

static RegisterHelp help("AppStorePad", AppStorePad::CreateControl);