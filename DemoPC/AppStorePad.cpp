#include "../common/stdAfx.h"
#include "../common/ControlHelp.h"

#include "AppStorePad.h"




Activity* AppStorePad::CreateControl()
{
	return new AppStorePad;
}

void AppStorePad::onCreate()
{
	Activity::onCreate();
	setContentView(L"layout\\AppManege.xml");
}

static RegisterHelp help("AppStorePad", AppStorePad::CreateControl);