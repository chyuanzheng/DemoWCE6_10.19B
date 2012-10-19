// WinDll.cpp : 定义 DLL 应用程序的入口点。
//

#include "../common/stdAfx.h"
#include "../common/WinDll.h"

int WINAPI _tWinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
	return WinMainDll( hInstance,
		 hPrevInstance,
		    lpCmdLine,
		       nCmdShow);
}

