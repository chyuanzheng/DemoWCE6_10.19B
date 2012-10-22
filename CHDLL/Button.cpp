#include "../common/StdAfx.h"
#include "../common/Button.h"
#include "../common/StrHelp.h"
#include "../common/XmlDef.h"
//#include "aygshell.h"

Button::Button()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值

	pImageManager= CImagesManager::GetInstance();
}

Button::~Button()
{

	if (m_nIDUp!=0)
	{
		pImageManager->RemoveImage(m_nIDUp);
	}
	if (m_nIDDown!=0)
	{
		pImageManager->RemoveImage(m_nIDDown);
	}
}

BOOL Button::Init(UINT wMapUp, UINT wMapDown, const RECT& rt, UINT nEventUp, UINT nEventDown)
{
	wstring uppath,downpath;
	AfxGetWorkPath(uppath);
	downpath= uppath;

	WCHAR szTitle[100];				
	LoadString(AfxGetInstanceHandle(), wMapUp, szTitle, 100);
	uppath = uppath + szTitle;
	LoadString(AfxGetInstanceHandle(), wMapDown, szTitle, 100);
	downpath = downpath + szTitle;

	return Init(uppath.c_str(),downpath.c_str(),rt,nEventUp,nEventDown);

}
BOOL  Button::Init(const TCHAR* pfileUp,const TCHAR* pfileDown, const RECT& rt, UINT nEventUp, UINT nEventDown )
{
	wstring Path;
	AfxGetWorkPath(Path);

	wstring upstr,downstr;
	upstr = Path + pfileUp;
	downstr = Path + pfileDown;
	

	m_isButtonDown = FALSE;
	m_nEventUp = nEventUp;
	m_nEventDown =  nEventDown;
	m_ActRect = rt;

	m_nIDUp = pImageManager->AddImage(upstr.c_str());
	m_nIDDown = pImageManager->AddImage(downstr.c_str());
	//m_map_up = SHLoadImageFile (pfileUp);
	//m_map_down = SHLoadImageFile (pfileDown);
	if (m_nIDUp == 0 || m_nIDDown == 0)
	{
		return false;
	}
	return true;
}


void Button::Draw( HDC hdcDst )
{



	//被按下为真

	if( m_isButtonDown == TRUE )
	{
		//贴按下图片
		pImageManager->DrawAlphaImage(m_nIDDown,hdcDst,NULL,&m_ActRect);
	}
	//被按下为假 
	else 
	{
		//贴原始图片
		pImageManager->DrawAlphaImage(m_nIDUp,hdcDst,NULL,&m_ActRect);

	}

}

BOOL Button::InMyArea( int x, int y )
{
	//判断区域
	POINT pt = {x,y};
	return ::PtInRect(&m_ActRect, pt);
}

BOOL Button::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if( InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
		{	
			//::SetCapture( m_hWnd );
			m_isButtonDown = TRUE;
			AfxValidateRect(&m_ActRect);
			
			if(m_nEventDown != 0)
			{
				::PostMessage( m_hWnd, m_nEventDown, (WPARAM)this, 0 );
			}
			return TRUE;
		}
		return FALSE;

	case WM_LBUTTONUP:
		//若本按钮曾经被按下
		if( m_isButtonDown == TRUE )
		{
			//::ReleaseCapture();
			m_isButtonDown = FALSE;
			AfxValidateRect(&m_ActRect);
			if( (m_nEventUp!=0) && InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
			{
				::PostMessage( m_hWnd, m_nEventUp, (WPARAM)this, 0 );
			}
			return TRUE;

		}
		return FALSE;
	default:
		return FALSE;
	}
}

void Button::setCtrLayout( TiXmlElement * ele )
{

	setCtrRect(ele);

	wstring path;
	AfxGetWorkPath(path);

	string strTail = ele->Attribute(BTN_UP);
	m_nIDUp = pImageManager->AddImage((path + StrHelp::StringToWString(strTail)).c_str());

    strTail = ele->Attribute(BTN_DOWN);
	m_nIDDown =  pImageManager->AddImage((path + StrHelp::StringToWString(strTail)).c_str());

}

