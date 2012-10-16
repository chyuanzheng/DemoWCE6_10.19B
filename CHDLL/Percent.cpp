#include "StdAfx.h"
#include "Percent.h"

Percent::Percent()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值
	m_map_back = NULL;
	m_map_sli = NULL;
    m_nEvent = 0;
}

Percent::~Percent()
{

	if( m_map_back != NULL )
		::DeleteObject( m_map_back );
	if( m_map_sli != NULL)
		::DeleteObject( m_map_sli ); 

}


void Percent::Init( WORD wMapSli, WORD wMapBack, UINT nEvent, const RECT &rect,FLOAT f_sli, 
                   FLOAT f_note, LONG l_het, FLOAT fp,LONG min, LONG max, const WCHAR *  post,int showType)
{
    m_showType = showType;
    m_bIsDisable = FALSE;
    _ASSERT(max>min);
    m_max = max;
    m_min = min;
    if(post)
    {
        ::wcscpy(m_wsPost,post);
    }
    else
    {
        m_wsPost[0]=0;
    }
    _ASSERT(f_sli > 0 &&f_note>0 && (f_sli+f_note)<=1);
	if( m_map_back != NULL )
		::DeleteObject( m_map_back );
	if( m_map_sli != NULL )
		::DeleteObject( m_map_sli );

	m_isButtonDown = FALSE;

	m_nEvent = nEvent;
    m_map_sli = ::LoadBitmap( AfxGetInstanceHandle(), MAKEINTRESOURCE( wMapSli ) );
    m_map_back = ::LoadBitmap( AfxGetInstanceHandle(), MAKEINTRESOURCE( wMapBack ) );
    m_act_rt =  rect;
    m_fPer = fp;
    INT lh = rect.bottom - rect.top;
    _ASSERT(lh >= 15&&lh>l_het);
    LONG up = (lh-l_het)/2;
    LONG lw = m_act_rt.right-m_act_rt.left;
    _ASSERT(lw > 30);
    LONG lw_sli =  LONG( lw*f_sli);
    LONG lw_note = LONG( lw*f_note);
    
    ::SetRect(&m_note_rt,lw-lw_note, 0, lw, lh);
    ::SetRect(&m_sli_rt, 0,up, lw_sli, up+l_het);


	BITMAP bmp;
	::GetObject( m_map_sli, sizeof( BITMAP ), &bmp );
	m_xWidth = bmp.bmWidth;
	m_yHeight = bmp.bmHeight;

}
void Percent::SetPer(FLOAT fper,bool bRedraw )//用invalidateRect试下
{
    _ASSERT(fper<=1.0);
    m_fPer = fper;
    if(bRedraw)
    {
        HDC hdc = GetDC( m_hWnd );
        Draw( hdc );
        ::ReleaseDC( m_hWnd, hdc );
    }
}
void Percent::SetDisable(bool bDisable)
{
    m_bIsDisable = bDisable;
}
void Percent::Draw( HDC hdcDst )
{
	
    if(m_bIsDisable)
        return;
    HDC hdcSrc2 = ::CreateCompatibleDC( NULL );
    HBITMAP hMap2 = ::CreateCompatibleBitmap(hdcDst,m_act_rt.right-m_act_rt.left, 
        m_act_rt.bottom - m_act_rt.top);
    HBITMAP hOldMap2 = (HBITMAP)::SelectObject( hdcSrc2, hMap2 );
    ::BitBlt(hdcSrc2,0,0,m_act_rt.right-m_act_rt.left, m_act_rt.bottom-m_act_rt.top, 
        AfxGetBKHdc(m_hWnd),m_act_rt.left,m_act_rt.top,SRCCOPY );

    HDC hdcSrc = ::CreateCompatibleDC( NULL );
	HBITMAP hOldMap = (HBITMAP)::SelectObject( hdcSrc, m_map_back );
    ::StretchBlt( hdcSrc2, m_sli_rt.left, m_sli_rt.top, m_sli_rt.right-m_sli_rt.left, 
        m_sli_rt.bottom-m_sli_rt.top, hdcSrc, 0, 0, m_xWidth, m_yHeight, SRCCOPY );

	::SelectObject( hdcSrc, m_map_sli );
    INT  nwid = INT (m_fPer*(m_sli_rt.right-m_sli_rt.left));
    ::StretchBlt( hdcSrc2, m_sli_rt.left, m_sli_rt.top,  nwid, 
        m_sli_rt.bottom-m_sli_rt.top, hdcSrc, 0, 0, m_xWidth, m_yHeight, SRCCOPY );
	
	::SelectObject( hdcSrc, hOldMap );//将对象选出内存dc
	::DeleteDC( hdcSrc );

    
    ::SetBkMode(hdcSrc2,TRANSPARENT);
    ::SetTextColor(hdcSrc2,RGB(250,250,250));

    WCHAR wchTemp[32];
    FLOAT  fper =  (m_fPer*(m_max - m_min))+m_min;
    if(m_showType == sint){
        swprintf(wchTemp, L"%d", int(fper) );
    }
    else if(m_showType == sfloat){
        swprintf(wchTemp, L"%.1f", fper );
    }

    wcscat(wchTemp, m_wsPost);

    ::DrawText(hdcSrc2, wchTemp, -1, &m_note_rt, DT_LEFT);//cyz
    ::BitBlt(hdcDst,m_act_rt.left,m_act_rt.top, m_act_rt.right-m_act_rt.left, m_act_rt.bottom-m_act_rt.top,
        hdcSrc2,0,0,SRCCOPY );

    ::SelectObject( hdcSrc2, hOldMap2 );//将对象选出内存dc
    ::DeleteObject(hMap2);
    ::DeleteDC( hdcSrc2 );
}
void  Percent::BufDraw( HDC hdcDst )
{
    
    
}
BOOL Percent::InMyArea( int x, int y )
{
	//判断区域
    if( x > m_act_rt.left && x < m_act_rt.left+(m_sli_rt.right - m_sli_rt.left)  && y > m_act_rt.top && y < m_act_rt.bottom )
    {
		return TRUE;
    }
	return FALSE;
}
BOOL Percent::ComputePer( int x )
{
    m_fPer = FLOAT( (x- m_act_rt.left) )/( m_sli_rt.right - m_sli_rt.left);
    if(m_fPer<0)
    {
        m_fPer = 0;
    }
    if(m_fPer>1)
    {
        m_fPer = 1;
    }
    //if(m_fPer>0&&m_fPer<1)
        return TRUE;
}
BOOL Percent::Response( HDC hdc, UINT nMsg, WPARAM wParam, LPARAM lParam )
{
    if(m_bIsDisable)
        return FALSE;
	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if( InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
		{	
			m_isButtonDown = TRUE;
            ComputePer( LOWORD( lParam ) );
            Draw( hdc );
            
			return TRUE;
		}
		return FALSE;
		
	case WM_LBUTTONUP:
		if( m_isButtonDown == TRUE )
		{

			m_isButtonDown = FALSE;
            Draw( hdc );
			if( (m_nEvent!=0) )
			{
				::PostMessage( m_hWnd, m_nEvent, (WPARAM)(&m_fPer), 0 );
			}
			return TRUE;
			
		}
		return FALSE;
	case WM_MOUSEMOVE:
		if( m_isButtonDown )
		{
            if(ComputePer( LOWORD( lParam ) ))
            {
                Draw( hdc );
            }
            return TRUE;
		}
		return FALSE;
	default:
		return FALSE;
	}
}
