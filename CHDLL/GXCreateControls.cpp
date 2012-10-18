#include "../common/GXCreateControls.h"
 
//map<UINT, FunCreate> GXCreateControl::mapControlFactory;

AbControl * GXCreateControl::CreateControlByType( const CHAR * type )
{
	AbControl *pControl = NULL;
	string sname=type;

	//if (0 == strcmp(type, "WINDOW"))
	//{
	//	//pControl = new GxxWindow();
	//}

	map<string, FunCrtControl>::iterator iter;

	GXCreateControl *p = GXCreateControl::Instance();
	iter = p->mapControlFactory.find(sname);
	if (iter != p->mapControlFactory.end())
	{
		pControl = iter->second();
	}
	return pControl;
}


Activity * GXCreateControl::CreateAcitviyByType( const CHAR * type )
{
	Activity *pControl = NULL;
	string sname=type;

	map<string, FunCrtActivity>::iterator iter;

	GXCreateControl *p = GXCreateControl::Instance();
	iter = p->mapActivityFactory.find(sname);
	if (iter != p->mapActivityFactory.end())
	{
		pControl = iter->second();
	}
	//p->listActiviy.push_back(pControl);
	return pControl;
}


void GXCreateControl::RegisterControlCreate( const CHAR * controlname, FunCrtControl funCreate )
{
	map<string, FunCrtControl>::iterator iter;
	string sname=controlname;

	GXCreateControl *p = GXCreateControl::Instance();
	iter = p->mapControlFactory.find(sname);

	if (iter == p->mapControlFactory.end())
	{
		p->mapControlFactory.insert(pair<string,FunCrtControl>(sname, funCreate));
	}
}

void GXCreateControl::RegisterControlCreate( const CHAR * controlname, FunCrtActivity funCreate )
{
	map<string, FunCrtActivity>::iterator iter;
	string sname=controlname;

	GXCreateControl *p = GXCreateControl::Instance();
	iter = p->mapActivityFactory.find(sname);

	if (iter == p->mapActivityFactory.end())
	{
		p->mapActivityFactory.insert(pair<string,FunCrtActivity>(sname, funCreate));
	}
}

GXCreateControl* GXCreateControl::pInstance = NULL;

GXCreateControl * GXCreateControl::Instance()
{
	if (!pInstance)
	{
		pInstance = new GXCreateControl;
	}
	return pInstance;
}

