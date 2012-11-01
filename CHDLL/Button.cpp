#include "../common/StdAfx.h"
#include "../common/Button.h"
#include "../common/StrHelp.h"
#include "../common/XmlDef.h"
#include "../common/MesDef.h"
//#include "aygshell.h"

Button::Button()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值

}

Button::~Button()
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



void Button::Draw( HDC hdcDst )
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
			if( InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
			{
				AfxPostMessage( CTR_MESSAGE, (WPARAM)this, MES_LBUTTONUP );
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

	 AbControl::setCtrLayout(ele);

	wstring path;
	AfxGetWorkPath(path);

	string strTail = ele->Attribute(BTN_UP);
	m_handleUp = pImageManager->AddImage((path + StrHelp::StringToWString(strTail)).c_str());

    strTail = ele->Attribute(BTN_DOWN);
	m_handleDown =  pImageManager->AddImage((path + StrHelp::StringToWString(strTail)).c_str());

}

