#include "StdAfx.h"
#include "Slider.h"

Slider::Slider()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值
    m_fStart_pos = -1;
    m_fstepNum =0;
    m_dn_down = NULL;
	m_dn_up = NULL;
	m_up_down = NULL;
	m_up_up = NULL;
	m_sd_down = NULL;
	m_sd_up = NULL;
    m_sd_slider  = NULL;

    m_nEvent = 0;
}

Slider::~Slider()
{
    FreeRes();
}
void  Slider::FreeRes()
{
	if( m_dn_down != NULL  )
		::DeleteObject( m_dn_down );
	if( m_dn_up != NULL )
		::DeleteObject( m_dn_up ); 
	if( m_up_down != NULL  )
		::DeleteObject( m_up_down );
	if( m_up_up != NULL )
		::DeleteObject( m_up_up ); 
	if( m_sd_down != NULL  )
		::DeleteObject( m_sd_down );
	if( m_sd_up != NULL )
		::DeleteObject( m_sd_up ); 
	if( m_sd_slider != NULL )
		::DeleteObject( m_sd_slider ); 
}
void Slider::Init(const SliderInfo& pSdInfo)
{

    FreeRes();	
	m_isButtonDown = NONE_SPACE;
    m_nEvent = pSdInfo.nEvent;
    m_nAmt = pSdInfo.nStep;

    m_dn_up = ::LoadBitmap( AfxGetInstanceHandle(), MAKEINTRESOURCE( pSdInfo.Dn_wMapUp ) );
    m_dn_down = ::LoadBitmap( AfxGetInstanceHandle(), MAKEINTRESOURCE(  pSdInfo.Dn_wMapDown ) );
    m_up_up = ::LoadBitmap( AfxGetInstanceHandle(), MAKEINTRESOURCE( pSdInfo.Up_wMapUp ) );
    m_up_down = ::LoadBitmap( AfxGetInstanceHandle(), MAKEINTRESOURCE(  pSdInfo.Up_wMapDown ) );
    m_sd_up = ::LoadBitmap( AfxGetInstanceHandle(), MAKEINTRESOURCE( pSdInfo.Sd_wMapUp ) );
    m_sd_down = ::LoadBitmap( AfxGetInstanceHandle(), MAKEINTRESOURCE(  pSdInfo.Sd_wMapDown ) );
    m_sd_slider = ::LoadBitmap( AfxGetInstanceHandle(), MAKEINTRESOURCE(  pSdInfo.Sd_slider ) );//滑块

	BITMAP bmp;
	::GetObject( m_dn_up, sizeof( BITMAP ), &bmp );
    ::SetRect( &m_dn_rect, pSdInfo.Dn_pnt.x, pSdInfo.Dn_pnt.y, pSdInfo.Dn_pnt.x+bmp.bmWidth, pSdInfo.Dn_pnt.y+bmp.bmHeight);

	::GetObject( m_up_up, sizeof( BITMAP ), &bmp );
    ::SetRect( &m_up_rect, pSdInfo.Up_pnt.x, pSdInfo.Up_pnt.y, pSdInfo.Up_pnt.x+bmp.bmWidth, pSdInfo.Up_pnt.y+bmp.bmHeight);

	::GetObject( m_sd_up, sizeof( BITMAP ), &bmp );
    ::SetRect( &m_sd_rect, pSdInfo.Sd_pnt.x, pSdInfo.Sd_pnt.y, pSdInfo.Sd_pnt.x+bmp.bmWidth, pSdInfo.Sd_pnt.y+bmp.bmHeight);

    m_lScale = FLOAT(m_sd_rect.bottom-m_sd_rect.top);
	//::GetObject( m_sd_slider, sizeof( BITMAP ), &bmp );
}
void Slider::SetPos(FLOAT fStart_pos,FLOAT fSlid_pp,bool isShow)
{
    if(fSlid_pp>1)
    {
        m_fStart_pos = -1;
    }
    else
    {
        if(fStart_pos+fSlid_pp>1)
        {
            fStart_pos = 0;
        }
        m_fstep = (m_sd_rect.bottom -m_sd_rect.top)*fSlid_pp/m_nAmt;
        m_fStart_pos = fStart_pos;
        m_fSlid_pp = fSlid_pp;
    }
    if(isShow)
    {
        HDC hdc = ::GetDC(m_hWnd);
        DrawSd( hdc );
        ::ReleaseDC(m_hWnd, hdc);
    }
}
void Slider::Draw( HDC hdcDst )
{
    DrawUp( hdcDst );
    DrawSd( hdcDst );
    DrawDn( hdcDst );
}
void Slider::DrawUp( HDC hdcDst )
{
    HBITMAP hOldMap;
    HDC hdcSrc = ::CreateCompatibleDC( NULL );
	if( m_isButtonDown == UP_BTN )
	{
		//贴按下图片
		hOldMap = (HBITMAP)::SelectObject( hdcSrc, m_up_down);
	}
	else
	{
		//贴原始图片
		hOldMap = (HBITMAP)::SelectObject( hdcSrc, m_up_up);
	}
    ::TransparentBlt( hdcDst, m_up_rect.left, m_up_rect.top, m_up_rect.right-m_up_rect.left, m_up_rect.bottom-m_up_rect.top, 
        hdcSrc, 0, 0, m_up_rect.right-m_up_rect.left, m_up_rect.bottom-m_up_rect.top, RGB(132,0,132) );
	::SelectObject( hdcSrc, hOldMap );//将对象选出内存dc
    ::DeleteDC( hdcSrc );
}
void Slider::DrawSd( HDC hdcDst )
{
    HBITMAP hOldMap;
    HDC hdcSrc = ::CreateCompatibleDC( NULL );
    HBITMAP hMemMap = ::CreateCompatibleBitmap( hdcDst, m_sd_rect.right-m_sd_rect.left, m_sd_rect.bottom-m_sd_rect.top);
    hOldMap = (HBITMAP)::SelectObject( hdcSrc, hMemMap);

    HBITMAP hOldMap2;
    HDC hdcSrc2 = ::CreateCompatibleDC( NULL );

    if(m_fStart_pos < 0 )
    {
        hOldMap2 = (HBITMAP)::SelectObject( hdcSrc2, m_sd_down);
    }
    else
    {
        hOldMap2 = (HBITMAP)::SelectObject( hdcSrc2, m_sd_up);
    }
    ::BitBlt( hdcSrc, 0, 0, m_sd_rect.right-m_sd_rect.left, m_sd_rect.bottom-m_sd_rect.top, 
        hdcSrc2, 0,0, SRCCOPY );
    if(m_fStart_pos >= 0)
    {


        ::SelectObject( hdcSrc2, m_sd_slider);
#ifdef CH_CE_DEBUG
        ::TransparentBlt(hdcSrc,2, (int)(m_lScale*m_fStart_pos), m_sd_rect.right-m_sd_rect.left-2, (int)(m_lScale*m_fSlid_pp), 
            hdcSrc2, 0,0,m_sd_rect.right-m_sd_rect.left-4, m_sd_rect.bottom-m_sd_rect.top,RGB(132,0,132) );
#else
        ::StretchBlt(hdcSrc,2, (int)(m_lScale*m_fStart_pos), m_sd_rect.right-m_sd_rect.left-2, (int)(m_lScale*m_fSlid_pp), 
            hdcSrc2, 0,0,m_sd_rect.right-m_sd_rect.left-4, m_sd_rect.bottom-m_sd_rect.top,SRCCOPY );
#endif

    }
    ::SelectObject( hdcSrc2, hOldMap2 );//将对象选出内存dc
    ::DeleteDC( hdcSrc2 );

    ::BitBlt( hdcDst, m_sd_rect.left, m_sd_rect.top, m_sd_rect.right-m_sd_rect.left, m_sd_rect.bottom-m_sd_rect.top, 
        hdcSrc,0,0, SRCCOPY );
	::SelectObject( hdcSrc, hOldMap );//将对象选出内存dc
    ::DeleteObject(hMemMap);
    ::DeleteDC( hdcSrc );
}
void Slider::DrawDn( HDC hdcDst )
{
    HBITMAP hOldMap;
    HDC hdcSrc = ::CreateCompatibleDC( NULL );
	if( m_isButtonDown == DOWN_BTN )
	{
		//贴按下图片
		hOldMap = (HBITMAP)::SelectObject( hdcSrc, m_dn_down);
	}
	else
	{
		//贴原始图片
		hOldMap = (HBITMAP)::SelectObject( hdcSrc, m_dn_up);
	}
    ::TransparentBlt( hdcDst, m_dn_rect.left, m_dn_rect.top, m_dn_rect.right-m_dn_rect.left, m_dn_rect.bottom-m_dn_rect.top, 
        hdcSrc, 0, 0, m_dn_rect.right-m_dn_rect.left, m_dn_rect.bottom-m_dn_rect.top, RGB(132,0,132) );
	::SelectObject( hdcSrc, hOldMap );//将对象选出内存dc
    ::DeleteDC( hdcSrc );
}
BTN_SLID Slider::InMyArea( int x, int y )
{
	//判断区域
    m_isButtonDown = NONE_SPACE;
    if(InRect(x,y,m_up_rect) )
    {
        m_isButtonDown = UP_BTN;
    }
    else if(InRect(x,y,m_dn_rect))
    {
        m_isButtonDown = DOWN_BTN;
    }
    else if(InRect(x,y,m_sd_rect) )
    {
        LONG ly =  y-m_sd_rect.top;
        if(ly<m_lScale*m_fStart_pos)
        {
            m_isButtonDown = UP_SPACE;
        }
        else if(ly<m_lScale*(m_fStart_pos+m_fSlid_pp))
        {
            m_isButtonDown = MID_SPACE;
        }
        else
        {
            m_isButtonDown = DOWN_SPACE;
        }
    }
	return m_isButtonDown;
}
BOOL Slider::InRect( int x, int y, RECT& rect )
{
    return (x>rect.left&&x<rect.right&&y>rect.top&&y<rect.bottom);
}

BOOL Slider::Response( HDC hdc, UINT nMsg, WPARAM wParam, LPARAM lParam )
{
    static int pre_x, pre_y;
	//HBITMAP hOldMap;
    if(m_fStart_pos<0)
        return FALSE;

	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
        pre_x = LOWORD( lParam );
        pre_y = HIWORD( lParam );
        m_preButtonDown = InMyArea( pre_x, pre_y );
		if( m_isButtonDown!= NONE_SPACE  )
		{	
            ::SetTimer( m_hWnd,SLIDER_ID,100,NULL);
            if(m_isButtonDown == UP_BTN)
                DrawUp(hdc);
            if(m_isButtonDown == DOWN_BTN)
                DrawDn(hdc);
            HandleSlider( m_isButtonDown, LOWORD( lParam ), HIWORD( lParam ), hdc );
			return TRUE;
		}
		return FALSE;	
	case WM_LBUTTONUP:
		//若本按钮曾经被按下
		if( m_preButtonDown!= NONE_SPACE  )
		{	
            ::KillTimer(m_hWnd,SLIDER_ID);
        }
		if( m_preButtonDown == UP_BTN )
		{
			m_preButtonDown = m_isButtonDown = NONE_SPACE;
            DrawUp( hdc );
			return TRUE;	
		}
		if( m_preButtonDown == DOWN_BTN )
		{
			m_preButtonDown = m_isButtonDown = NONE_SPACE;
            DrawDn( hdc );
			return TRUE;	
		}
        m_preButtonDown = m_isButtonDown = NONE_SPACE;
		return FALSE;
	case WM_MOUSEMOVE:
        pre_x = LOWORD( lParam );
        pre_y = HIWORD( lParam );
        InMyArea( pre_x, pre_y );
        if(m_preButtonDown == MID_SPACE )
        {
            HandleSlider( m_preButtonDown, LOWORD( lParam ), HIWORD( lParam ), hdc , true );
            return TRUE;
        }
		return FALSE;
    case WM_TIMER:
        if( wParam ==SLIDER_ID)
        {
            if(m_preButtonDown != MID_SPACE && m_preButtonDown !=NONE_SPACE && m_preButtonDown == InMyArea( pre_x, pre_y ) )
            {
                HandleSlider( m_preButtonDown, -1, -1, hdc , true );
            }
            return TRUE;
        }
	default:
		return FALSE;
	}
    return FALSE;
}

void Slider::HandleSlider(BTN_SLID btn_slid,int x, int y, HDC hdc, bool bMove)
{
    static UINT pre_y;
    static DWORD  dwPreTick;
    DWORD dwCurTick = ::GetTickCount();
    DWORD dwTick=0;
    if(!bMove)
    {
        dwPreTick = dwCurTick;
        switch( btn_slid )
        {
        case UP_BTN:
            MoveStepUp(true);
            break;
        case DOWN_BTN:
            MoveStepUp(false);
            break;
        case UP_SPACE:
            MovePageUp(true);
            break;
        case MID_SPACE: 
            pre_y = y;
            break;
        case DOWN_SPACE:
            MovePageUp(false);
            break;
        default:
		    break;
        }
    }
    else
    {

        dwTick = dwCurTick-dwPreTick;
        if(dwTick>200)
        {
            dwPreTick = dwCurTick;
        }
        else if(btn_slid == MID_SPACE)
        {
            
        }
        else
        {
            return;
        }
        switch( btn_slid )
        {
        case UP_BTN:
            MoveStepUp(true);
            break;
        case DOWN_BTN:
            MoveStepUp(false);
            break;
        case MID_SPACE:
            MoveSlider(y-pre_y);
            pre_y = y;
            break;
        case UP_SPACE:
            MovePageUp(true);
            break;
        case DOWN_SPACE:
            MovePageUp(false);
            break;
        default:
		    break;
        }
    }
    DrawSd(hdc);
}
void Slider::MoveStepUp( bool bUp  )
{

    if(!bUp)
    {
        m_fStart_pos = (m_fStart_pos*m_lScale+m_fstep)/m_lScale;
        if( m_fStart_pos>(1-m_fSlid_pp) )
        {
            m_fStart_pos = 1-m_fSlid_pp;
        }
    }
    else
    {
        m_fStart_pos = (m_fStart_pos*m_lScale-m_fstep)/m_lScale;
        if( m_fStart_pos<0 )
        {
            m_fStart_pos = 0;
        }
    }
    SendMsg();
}
void Slider::MovePageUp( bool bUp )
{

    if(!bUp)
    {
        m_fStart_pos = m_fStart_pos + m_fSlid_pp;
        if( m_fStart_pos>(1-m_fSlid_pp) )
        {
            m_fStart_pos = 1-m_fSlid_pp;
        }
    }
    else
    {
        m_fStart_pos = m_fStart_pos - m_fSlid_pp;
        if( m_fStart_pos<0 )
        {
            m_fStart_pos = 0;
        }
    }
    SendMsg();
}
void Slider::MoveSlider( INT nspace )
{

    m_fStart_pos = (m_fStart_pos*m_lScale+nspace)/m_lScale;
    if( m_fStart_pos>(1-m_fSlid_pp) )
    {
        m_fStart_pos = 1-m_fSlid_pp;
    }
    if( m_fStart_pos<0 )
    {
        m_fStart_pos = 0;
    }
    SendMsg();
}
void Slider::SendMsg()
{

    int nCode = int ((m_lScale*m_fStart_pos+0.001)/m_fstep);
    if(m_fstepNum != nCode)
    {
        m_fstepNum =nCode;
        ::PostMessage( m_hWnd, m_nEvent, (WPARAM)nCode, 0 );
    }
}