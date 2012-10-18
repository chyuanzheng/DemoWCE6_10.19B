#pragma once
#include "StdAfx.h"
#include "AbControl.h"
#include "Activity.h"
/*
	这个类用来注册 AbControl 
*/

class CE_CONTROL_API GXCreateControl
{
	map<string, FunCrtControl>mapControlFactory;
	map<string, FunCrtActivity>mapActivityFactory;
	list<Activity*> listActiviy;
	static GXCreateControl *pInstance;
public:
	static GXCreateControl* Instance();
	static AbControl * CreateControlByType(const CHAR * type);
	static Activity * CreateAcitviyByType(const CHAR * type);
	static void RegisterControlCreate(const CHAR * controlname, FunCrtControl funCreate);
	static void RegisterControlCreate(const CHAR * controlname, FunCrtActivity funCreate);
};

