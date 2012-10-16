#include "StdAfx.h"
#include "Picture.h"

Picture::Picture()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值
	m_map_back = NULL;
}

Picture::~Picture()
{

	if( m_map_back != NULL )
		::DeleteObject( m_map_back );
}


void Picture::Init( WORD wMapBack,const RECT rt ,BOOL isConst)
{

	if( m_map_back != NULL )
		::DeleteObject( m_map_back );

    m_map_back = ::LoadBitmap( AfxGetInstanceHandle(), MAKEINTRESOURCE( wMapBack ) );
    m_ActRect = rt;

	BITMAP bmp;
	::GetObject( m_map_back, sizeof( BITMAP ), &bmp );
    ::SetRect(&m_picRect,0,0,bmp.bmWidth,bmp.bmHeight);

    m_isConst = isConst;
    if(m_isConst)
    {
        m_isConst = FALSE;
        Draw(AfxGetBKHdc(m_hWnd));
        m_isConst = TRUE;
    }

	//::SetRect( &m_p_rect,  m_xLeft, m_yTop, m_xLeft + m_xWidth, m_yTop + m_yHeight );
}

void Picture::Draw( HDC hdcDst )
{
    if(!m_isConst)
    {
        return;
    }
    HDC hdcSrc = ::CreateCompatibleDC( NULL );
	HBITMAP	hOldMap = (HBITMAP)::SelectObject( hdcSrc, m_map_back );
    ::StretchBlt( hdcDst, m_ActRect.left, m_ActRect.top, m_ActRect.right-m_ActRect.left, m_ActRect.bottom-m_ActRect.top, 
        hdcSrc, 0, 0, m_picRect.right, m_picRect.bottom, SRCCOPY );
    ::SelectObject( hdcSrc, hOldMap );
    ::DeleteDC(hdcSrc);
}
