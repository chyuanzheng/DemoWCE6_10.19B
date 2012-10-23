#pragma once
#pragma warning(disable:4244) //仅显示一个
#include "DllDefine.h"
#include "stdAfx.h"
class CE_CONTROL_API StrHelp 
{
public:
	static	wstring StringToWString(const string &str);

	//只拷贝低字节至string中
	static string WStringToString(const wstring &wstr);
};


