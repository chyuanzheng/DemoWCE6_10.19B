#pragma once
#include "../common/Button.h"
#include "../common/AppButton.h"
#include "../common/Activity.h"


class AppStorePad : public Activity
{
public:
	AppStorePad(){}
	virtual ~AppStorePad (){}
	virtual public void onCreate();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	static Activity* CreateControl();


private:
	AppButton   *m_app1;
	Button      *m_btn1;


    void  OnGoBack();
	
	BOOL  CreatePlay(const WCHAR *path);


};
