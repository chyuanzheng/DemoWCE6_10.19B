#include "../common/StdAfx.h"
#include "../common/Edit.h"

Edit::Edit()
{
	m_hFontID  = 0;
	m_txtColor = RGB(0,0,0);
	SetRect(&m_ActRect,0,0,0,0);
    m_dwAlign = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
	m_pfontManager = FontManager::GetInstance();
}

Edit::~Edit()
{
    
	if( m_hFontID != 0 )
	{
		m_pfontManager->RemoveFontType(m_hFontID);
	}
}

//此函数的 bRedraw 不能在Draw() 函数中 设为 TRUE.



void Edit::Draw( HDC hdcDst )
{

	if (m_hFontID == 0)
	{
		return;
	}

	if(  m_sText.size()>0&& m_sText[0] != 0 )
	{
		m_pfontManager->DrawMamagerText(m_hFontID,hdcDst,&m_ActRect,m_sText.c_str(),m_txtColor,m_dwAlign);
	}
}

BOOL Edit::SetFont( LONG nHeight, LONG nWeight,const WCHAR * ftName )
{
	if (m_hFontID!= 0)
	{
		m_pfontManager->RemoveFontType(m_hFontID);
		m_hFontID = 0;
	}
	m_hFontID = m_pfontManager->AddFontType(nHeight, nWeight, ftName);
	if (m_hFontID==0)
	{
		return FALSE;
	}
	return TRUE;
}

void Edit::SetText( LPCTSTR pText,FreshType rfh/* = FreLater*/)
{
	if (pText != NULL)
		m_sText = pText;
	switch (rfh)
	{
	case DoNull:
		return;
	case FreLater:
		Refresh();
		break;
	case FreInstant:
		Refresh();
		UpdateWindow(m_hWnd);
		break;
	default:
		break;
	}

}

