#pragma once
#include "../common/Button.h"
#include "../common/Activity.h"


class AppStorePad : public Activity
{
public:
	AppStorePad(){}
	virtual ~AppStorePad (){}
	virtual public void onCreate();

	static Activity* CreateControl();


private:

    Button      m_b_exit;

    void  OnGoBack();

	BOOL  CreatePlay(const WCHAR *path);


};
