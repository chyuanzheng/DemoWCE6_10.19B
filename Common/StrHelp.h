#pragma once
#include "DllDefine.h"
#include "stdAfx.h"
class CE_CONTROL_API StrHelp 
{
public:
	static	wstring StringToWString(const string &str);

	//ֻ�������ֽ���string��
	static string WStringToString(const wstring &wstr);
};


