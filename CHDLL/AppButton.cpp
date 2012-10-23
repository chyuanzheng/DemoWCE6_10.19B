#include "../common/StdAfx.h"
#include "../common/AppButton.h"
#include "../common/StrHelp.h"
#include "../common/XmlDef.h"
//#include "aygshell.h"

AppButton::AppButton()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值

}

AppButton::~AppButton()
{

	if (m_handleUp!=NULL)
	{
		pImageManager->RemoveImage(m_handleUp);
	}
	if (m_handleDown!=NULL)
	{
		pImageManager->RemoveImage(m_handleDown);
	}
}



void AppButton::Draw( HDC hdcDst )
{



	//被按下为真

	if( m_isButtonDown == TRUE )
	{
		//贴按下图片
		pImageManager->DrawAlphaImage(m_handleDown,hdcDst,NULL,&m_ActRect);
	}
	//被按下为假 
	else 
	{
		//贴原始图片
		pImageManager->DrawAlphaImage(m_handleUp,hdcDst,NULL,&m_ActRect);

	}

}

BOOL AppButton::InMyArea( int x, int y )
{
	//判断区域
	POINT pt = {x,y};
	return ::PtInRect(&m_ActRect, pt);
}

BOOL AppButton::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
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
				//::PostMessage( m_hWnd, m_nEventDown, (WPARAM)this, 0 );
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
				//::PostMessage( m_hWnd, m_nEventUp, (WPARAM)this, 0 );
			}
			return TRUE;

		}
		return FALSE;
	default:
		return FALSE;
	}
}

void AppButton::setCtrLayout( TiXmlElement * ele )
{

	setCtrRect(ele);

	wstring path;
	AfxGetWorkPath(path);

	string strTail = ele->Attribute(BTN_UP);
	m_handleUp = pImageManager->AddImage((path + StrHelp::StringToWString(strTail)).c_str());

    strTail = ele->Attribute(BTN_DOWN);
	m_handleDown =  pImageManager->AddImage((path + StrHelp::StringToWString(strTail)).c_str());

}

