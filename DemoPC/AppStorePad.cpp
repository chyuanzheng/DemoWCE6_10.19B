#include "../common/stdAfx.h"
#include "../common/ControlHelp.h"
#include "../common/MesDef.h"
#include "AppServer.h"
#include "AppStorePad.h"




Activity* AppStorePad::CreateControl()
{
	return new AppStorePad;
}

void AppStorePad::onCreate()
{
	Activity::onCreate();
	setContentView(L"layout\\AppManege.xml");

	m_app1 = (AppButton*)findViewByName("app_btn1");
	m_btn1 =  (Button*)findViewByName("test_btn");
	ASSERT(NULL!=m_app1);
	ASSERT(NULL!=m_btn1);
}


BOOL AppStorePad::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case CTR_MESSAGE:
		if(m_btn1== (Button*)wParam)
		{	
			AppServer *as=AppServer::GetInstance();
			as->StartService();
			
			return TRUE;
		}
		return FALSE;
	default:
		return FALSE;
	}
}


static RegisterHelp help("AppStorePad", AppStorePad::CreateControl);