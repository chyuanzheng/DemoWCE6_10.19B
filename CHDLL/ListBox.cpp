#include "StdAfx.h"
#include "ListBox.h"
//#include "aygshell.h"

ListBox::ListBox()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值

	m_nIDBack = 0;
	m_nStartLine = 0;
	m_nChooseLine = -1;
	m_nLineAmount = 0;
	m_nYmovement= 0;
	m_bEvent = FALSE;
	
	m_nEventChoose = 0;
	pImageManager= CImagesManager::GetInstance();
	m_pfontManager = FontManager::GetInstance();
	m_hFontID  = m_pfontManager->AddFontType(20, 500);

	m_pListstr = new LIST_STR;
}

ListBox::~ListBox()
{

	delete m_pListstr;
	if (m_nIDBack!=0)
	{
		pImageManager->RemoveImage(m_nIDBack);
	}
	if( m_hFontID != 0 )
	{
		m_pfontManager->RemoveFontType(m_hFontID);
	}
}


BOOL ListBox::Init( const TCHAR* pfileBack,UINT nHeight, const RECT& rt, UINT nEvent, BOOL bShow /*= FALSE*/ )
{
	wstring Path;
	AfxGetWorkPath(Path);
	wstring  str;
	str = Path + pfileBack;//m_nIDBack
	m_nIDBack = pImageManager->AddImage(str.c_str());

	_ASSERT((rt.bottom - rt.top)%nHeight == 0);
	m_nLineHeight = nHeight;
	m_nLineAmount = (rt.bottom - rt.top)/nHeight;
	m_ActRect = rt;

	m_isButtonDown = FALSE;
	m_nEventChoose = nEvent;
	m_bShow =  bShow;
	return true;

}
BOOL ListBox::SetFont( LONG nHeight, LONG nWeight,const WCHAR * ftName )
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

void ListBox::Draw( HDC hdcDst )
{
	if (!m_bShow)
	{
		return;
	}
	if (m_nIDBack == 0)
	{
		return;
	}
	pImageManager->DrawAlphaImage(m_nIDBack,hdcDst,NULL,&m_ActRect);
	


	//被按下为真


}

BOOL ListBox::InMyArea( int x, int y )
{
	//判断区域
	POINT pt = {x,y};
	return ::PtInRect(&m_ActRect, pt);
}

BOOL ListBox::Response( HDC hdc, UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;
	static int s_nYmove = 0;
	if (!m_bShow)
	{
		return FALSE;
	}
	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if( InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
		{	
			FreshChoose( HIWORD( lParam ) );
			::SetCapture( m_hWnd );
			m_isButtonDown = TRUE;
			m_bEvent = TRUE;
			m_nYmovement = 0;
			s_nYmove =  HIWORD( lParam );
			m_startTop = m_ActRect.top;
			AfxValidateRect(m_hWnd,m_ActRect);
			return TRUE;
		}
		return FALSE;
	case WM_MOUSEMOVE:
		if (m_isButtonDown)
		{
			m_nYmovement = HIWORD( lParam ) - s_nYmove;
			if (m_bEvent && abs(m_nYmovement) > m_nLineHeight/3)
			{
				m_bEvent = FALSE;
			}
			if (!m_bEvent)//只有在移动了一定位置的时候才开始移动
			{
				m_nChooseLine = -1;
				CalculateDrawRect();
				AfxValidateRect(m_hWnd,m_ActRect);
			}
			else
			{
				m_nYmovement = 0;
			}
			return TRUE;
		}
		return FALSE;
	case WM_LBUTTONUP:
		//若本按钮曾经被按下
		if( m_isButtonDown == TRUE )
		{
			::ReleaseCapture();
			m_isButtonDown = FALSE;
			m_nYmovement = HIWORD( lParam ) - s_nYmove;
			m_startTop = m_ActRect.top;
			AfxValidateRect(m_hWnd,m_ActRect);
			if (m_bEvent)
			{
				::PostMessage( m_hWnd, m_nEventChoose, (WPARAM)this, (LPARAM)m_nChooseLine );
			}
			return TRUE;

		}
		return FALSE;
	default:
		return FALSE;
	}
}

void ListBox::ShowList( BOOL bShow )
{
	m_bShow = bShow;
	AfxValidateRect(m_hWnd,m_ActRect);
}

BOOL ListBox::FreshChoose( int y )
{
	int Yv = m_ActRect.top - y;
	_ASSERT(Yv >=0);
	int addline =  Yv/m_nLineHeight ;//+ (Yv%m_nLineHeight != 0)?1:0 - 1;
	int line = m_nStartLine + addline;
	if (line < m_pListstr->size())
	{
		m_nChooseLine = line;
	}
	return TRUE;
	
}

BOOL ListBox::CalculateDrawRect()
{
	UINT Ymove = abs(m_nYmovement);
	int  isNegative  = -1;
	if (m_nYmovement > 0)
	{
		isNegative = 1;
	}
	int nline = abs(Ymove)/m_nLineHeight;
	int top  = m_ActRect.top - Ymove % m_nLineHeight;
	m_nStartLine = m_nStartLine - isNegative*nline  - (isNegative>0)?1:0;
	return TRUE;
	 
}