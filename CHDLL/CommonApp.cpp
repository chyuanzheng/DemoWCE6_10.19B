#include "../common/stdAfx.h"
#include "../common/StrHelp.h"
#include "../common/GXCreateControls.h"
#include "../common/CommonApp.h"
#include "../common/CommonWnd.h"


CCommonApp myApp;

/////////////////////////////////////////////////////////////////////////
// CCommonApp member functions

BOOL CCommonApp::InitInstance ()
{
	//AfxShowTaskBar(FALSE);
    m_pMainWnd = new CCommonWnd;
	if (!InitActivity(L"layout\\WinceManifest.xml"))// concrete code ,adjusts later
	{
		ASSERT(0);
		return FALSE;
	}
	
    m_pMainWnd->ShowWindow (m_nCmdShow);
    m_pMainWnd->UpdateWindow();
    return TRUE;
}

BOOL CCommonApp::DeInitInstance()
{
	AfxShowTaskBar();
	return TRUE;
}

BOOL CCommonApp::InitActivity( LPCWSTR param1 )
{
	//throw std::exception("The method or operation is not implemented.");
	BOOL ret = FALSE;
	wstring path;
	AfxGetWorkPath(path);
	path += param1;

	TiXmlDocument	xmlDoc;
	ret = xmlDoc.LoadFile(StrHelp::WStringToString(path).c_str());
	if (!ret)
	{
		OutputDebugString(L"LoadFile error! \r\n");
		return FALSE;
	}

	TiXmlElement *root = xmlDoc.RootElement();
	if (strcmp(root->Value(), "manifest") != 0)
	{
		return FALSE;
	}
	
	TiXmlElement * element = root->FirstChildElement();
   
	string startAction;
	string startActiviy;
	while(element)
	{
		if (strcmp(element->Value(), "activity") != 0)
		{
			return FALSE;
		}
		TiXmlElement * action = element->FirstChildElement();
		if (action)
		{
			startAction = action->Attribute("name");
			startActiviy = element->Attribute("name");
			break;
		}
		element = element->NextSiblingElement();

	}
	if (startAction == "MAIN")
	{
		Activity * pAct = GXCreateControl::CreateAcitviyByType(startActiviy.c_str());
		AfxSetActiviy(pAct);
		pAct->onCreate();
		return TRUE;
	}
	
	return ret=FALSE;
}
