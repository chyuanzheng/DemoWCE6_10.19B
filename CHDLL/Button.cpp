#include "../common/StdAfx.h"
#include "../common/Button.h"
#include "../common/StrHelp.h"
#include "../common/XmlDef.h"
#include "../common/MesDef.h"
//#include "aygshell.h"

Button::Button()
{
	//��Ҫ�����ڴ�ı�������Ҫ��Ĭ�Ϲ��캯���и���ֵ

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



	//������Ϊ��

	if( m_isButtonDown == TRUE )
	{
		//������ͼƬ
		pImageManager->DrawAlphaImage(m_handleDown,hdcDst,NULL,&m_ActRect);
	}
	//������Ϊ�� 
	else 
	{
		//��ԭʼͼƬ
		pImageManager->DrawAlphaImage(m_handleUp,hdcDst,NULL,&m_ActRect);

	}

}

BOOL Button::InMyArea( int x, int y )
{
	//�ж�����
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
		//������ť����������
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

