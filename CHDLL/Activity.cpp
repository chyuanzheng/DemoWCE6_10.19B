#include "../common/StdAfx.h"
#include "../common/Activity.h"
#include "../common/StrHelp.h"
#include "../common/Button.h"
#include "../common/Launch.h"
#include "../common/XmlDef.h"
//#include "aygshell.h"

/////////////////////////////////////////////////////////////////////////
// BaseBoard message map and member functions

//有两点需要考虑，1，图像字符串的存放，
//2 InitBoard失败怎么办

Activity::Activity()
:m_pParentBoard(NULL)
{
	m_handleBack = 0;
	

}


Activity::~Activity ()
{
	if (m_handleBack!=0)
	{
		pImageManager->RemoveImage(m_handleBack);
	}
}


void  Activity::DestroyBoard()
{
    if(m_pParentBoard)//cyz
    {

    }
	else
	{
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
	pImageManager->DrawAlphaImage(m_handleBack,hdcDst,NULL,&m_ActRect);
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

/**控件根据 ele中的参数设置自己的属性
   并递归设置子控件
*/
void Activity::setCtrLayout( TiXmlElement * ele )
{
	if (strcmp(ele->Value(), ABSOLUTE) != 0)
	{
		return ;
	}

	AbControl::setCtrLayout(ele);

	string strTail = ele->Attribute(BACKGROUD);

	wstring path;
	AfxGetWorkPath(path);
	path =  path + StrHelp::StringToWString(strTail);

	m_handleBack = pImageManager->AddImage(path.c_str());

	if (m_handleBack==0)
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

		if (ctrname == BUTTON)
		{
			ctr = new Button;
		}
        if (ctrname == LAUNCH)
        {
			ctr = new Launch;
        }
		if (ctr)
		{
			AddCtrl(ctr);
			ctr->setCtrLayout(chid);
		}
		chid = chid->NextSiblingElement();

	}
}


