// WinDll.cpp : ���� DLL Ӧ�ó������ڵ㡣
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

