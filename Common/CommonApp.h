#pragma once
#include "../common/CWinApp.h"
class CCommonApp : public CWinApp
{
public:
    virtual BOOL InitInstance ();
	virtual BOOL DeInitInstance();
	BOOL InitActivity( LPCWSTR param1 );
};

