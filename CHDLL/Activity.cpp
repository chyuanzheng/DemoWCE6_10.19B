#include "../common/StdAfx.h"
#include "../common/Activity.h"
#include "../common/StrHelp.h"
#include "../common/Button.h"
//#include "aygshell.h"

/////////////////////////////////////////////////////////////////////////
// BaseBoard message map and member functions

//有两点需要考虑，1，图像字符串的存放，
//2 InitBoard失败怎么办
Activity::Activity (HWND hwnd,Activity* pParent)
    :AbControl(hwnd)
    ,m_pParentBoard(pParent)
{
	m_bIsDomal = FALSE;
	m_resID = 0;
	pImageManager= CImagesManager::GetInstance();
	
}

Activity::Activity()
:m_pParentBoard(NULL)
{
	m_bIsDomal = FALSE;
	m_resID = 0;
	pImageManager= CImagesManager::GetInstance();

}


Activity::~Activity ()
{
	if (m_resID!=0)
	{
		pImageManager->RemoveImage(m_resID);
	}
}


void  Activity::DestroyBoard()
{
    if(m_pParentBoard)//cyz
    {
		if (m_bIsDomal)
		{
			m_bIsDomal = FALSE;
		}
        //AfxSetBoard(m_hWnd,m_pParentBoard);//cyz
    }
	else
	{
		//AfxSetBoard(m_hWnd,NULL);
		//::PostMessage(m_hWnd,WM_EXIT_PROSS,0,0);
	}
	delete this;
	//::DestroyWindow(m_hWnd);
    return;//如果是有父窗口则返回FALSE
}
void  Activity::DestroyAllBoard()
{
    Activity *pBb;
    Activity *pPraBb = this;
    while(pPraBb){
        pBb = pPraBb;
        pPraBb = pBb->m_pParentBoard;
        pBb->DestroyBoard();
    }
}


void Activity::Draw( HDC hdcDst )
{
	pImageManager->DrawAlphaImage(m_resID,hdcDst,NULL,&m_ActRect);
    //::BitBlt(hdcDst, 0, 0, m_nWidth, m_nHeight,m_hBackDC,0,0,SRCCOPY);
}

BOOL Activity::DlClick()
{
    DWORD ncur;
    DWORD npre;
    ncur = ::GetTickCount();
    npre = m_ntime;
    m_ntime = ncur;
    if( ( ncur- npre)>0 &&( ncur- npre) <300 )
        return TRUE;
    return FALSE;
}

INT Activity::DoModal()
{
	_ASSERT(m_bIsDomal==FALSE);
	m_bIsDomal = TRUE;

	MSG    msg;
	while(GetMessage(&msg, NULL, 0, 0 ))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (m_bIsDomal== FALSE)
		{
			break;
		}
	}

	return 1;
}


void Activity::onCreate()
{

}

BOOL Activity::setContentView( const WCHAR* layout )
{
	BOOL ret = FALSE;
	wstring path;
	AfxGetWorkPath(path);
	path += layout;

	TiXmlDocument	xmlDoc;
	ret = xmlDoc.LoadFile(StrHelp::WStringToString(path).c_str());
	if (!ret)
	{
		OutputDebugString(L"setContentView LoadFile error! \r\n");
		return FALSE;
	}
	
	TiXmlElement *root = xmlDoc.RootElement();
	setCtrLayout(root);

	return TRUE;
}

void Activity::setCtrLayout( TiXmlElement * ele )
{
	if (strcmp(ele->Value(), "AbsoluteLayout") != 0)
	{
		return ;
	}

	int data;
	ele->Attribute("layout_x",&data);
	m_ActRect.left = data;

	ele->Attribute("layout_y",&data);
	m_ActRect.top =  data;

	ele->Attribute("layout_width",&data);
	m_ActRect.right =  data + m_ActRect.left;

	ele->Attribute("layout_height",&data);
	m_ActRect.bottom =  data + m_ActRect.top;

	string strTail = ele->Attribute("background");

	wstring path;
	AfxGetWorkPath(path);
	path =  path + StrHelp::StringToWString(strTail);

	m_resID = pImageManager->AddImage(path.c_str());

	if (m_resID==0)
	{
		ASSERT(0);
		return;
	}


	TiXmlElement * chid = ele->FirstChildElement();
	string ctrname;
	AbControl *ctr;
	while(chid)
	{

	    ctrname = chid->Value();

		if (ctrname == "Button")
		{
			ctr = new Button;
		}

		if (ctr)
		{
			AddCtrl(ctr);
			ctr->setCtrLayout(chid);
		}
		chid = chid->NextSiblingElement();

	}
}
