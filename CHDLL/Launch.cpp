#include "../common/StdAfx.h"
#include "../common/Launch.h"
#include "../common/AppButton.h"
#include "../common/StrHelp.h"
#include "../common/XmlDef.h"
//#include "aygshell.h"

Launch::Launch()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值

}

Launch::~Launch()
{

	
}


BOOL Launch::InMyArea( int x, int y )
{
	//判断区域
	POINT pt = {x,y};
	return ::PtInRect(&m_ActRect, pt);
}

BOOL Launch::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{

	return FALSE;
}

void Launch::setCtrLayout( TiXmlElement * ele )
{

	setCtrRect(ele);

	TiXmlElement * chid = ele->FirstChildElement();
	string ctrname;
	AbControl *ctr;
	while(chid)
	{

		ctrname = chid->Value();

		if (ctrname == APP_BUTTON)
		{
			ctr = new AppButton;
		}
		if (ctr)
		{
			AddCtrl(ctr);
			ctr->setCtrLayout(chid);
		}
		chid = chid->NextSiblingElement();

	}

}

