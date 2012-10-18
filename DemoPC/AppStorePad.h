#pragma once
#include "../common/Button.h"
#include "../common/Edit.h"
#include "../common/Activity.h"


class AppStorePad : public Activity
{
public:
    AppStorePad(HWND hwnd, Activity* pParentBoard = NULL);
	AppStorePad(){}
	virtual ~AppStorePad ();
	virtual public void onCreate();
    virtual void   Draw( HDC hdcDst ) ;
	virtual BOOL   Response( HDC hdc, UINT nMsg, WPARAM wParam, LPARAM lParam );
	static Activity* CreateControl();


private:
	Button      m_b_flash;
	Button      m_b_movie;
	Button      m_b_readpaper;
    Button      m_b_exit;
	Button      m_b_web;
	Button      m_b_speed;
	Button      m_b_wifi;

	Edit        m_e_date;
	Edit        m_e_time;
	Edit        m_e_waitweb;

	HANDLE		m_hProcess;

    void  OnGoBack();
	void  OnPlayFlash();
	void  OnPlayMovie();
	void  OnPlayPaper();
	void  OnPlayWeb();
	void  OnPlaySpeed();
	void  OnPlayWifi();

	void  OnPlayShut(WPARAM wparam,LPARAM lparam);
	BOOL  OnTimer(UINT id);
	void  OnStartAWeb(const WCHAR * web);

	BOOL  CreatePlay(const WCHAR *path);


};
