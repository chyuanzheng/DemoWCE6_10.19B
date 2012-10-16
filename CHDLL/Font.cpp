#include "StdAfx.h"
#include "Font.h"

FontManager *FontManager::m_pInstance = NULL;
FontManager* FontManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new FontManager();
	}
	return m_pInstance;
}
FontManager::FontManager()
{
	
}

FontManager::~FontManager()
{
	_ASSERT(m_hfonts.size() == 0);
}

LOGFONT * FontManager::GetLogFont( LONG nHeight, LONG nWeight,const WCHAR * ftName )
{
	m_pLogFont.lfHeight  = nHeight;//大小
	m_pLogFont.lfWidth   = 0;
	m_pLogFont.lfEscapement = 0;//字符串倾斜度，除10
	m_pLogFont.lfOrientation = 0;
	m_pLogFont.lfWeight  =  nWeight;//字体重量（粗细）
	m_pLogFont.lfItalic  = FALSE;//斜体
	m_pLogFont.lfUnderline  = FALSE;
	m_pLogFont.lfStrikeOut  = FALSE;
	m_pLogFont.lfCharSet  = DEFAULT_CHARSET;//ANSI_CHARSET;
	m_pLogFont.lfOutPrecision = OUT_DEFAULT_PRECIS; 
	m_pLogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	m_pLogFont.lfQuality  = ANTIALIASED_QUALITY;
	m_pLogFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	if (ftName != NULL)
	{
		lstrcpy( m_pLogFont.lfFaceName,ftName );
	}
	else
	{
		lstrcpy( m_pLogFont.lfFaceName,_T("宋体") );
	}
	return &m_pLogFont;
}

int   FontManager::AddFontRes(const WCHAR *res)
{
	if( 0 != AddFontResource( res ) )
	{
		::SendMessage(HWND_BROADCAST,WM_FONTCHANGE,0,0);
	}
	return 1;
}



UINT FontManager::GetAFreeID()
{
	int retid = 1;

	MAP_HFONT_ID::iterator iter;

	for (iter = m_hfonts.begin();iter != m_hfonts.end();iter++)
	{
		if (retid == iter->first)
		{
			retid++;
		}
		else if (retid < iter->first)
		{
			break;
		}

	}
	_ASSERT(m_hfonts.find(retid) == m_hfonts.end());
	return retid;
}

UINT FontManager::AddFontType(  LONG nHeight, LONG nWeight /*= 0*/, const WCHAR * ftName  /*= NULL*/  )
{
	UINT ResID = GetAFreeID();
	HFONT hf = CreateFontIndirect (GetLogFont(nHeight,nWeight,ftName));
	if (NULL == hf)
	{
		return 0;//返回0表示错误
	}
	m_hfonts.insert(pair<UINT,HFONT> (ResID,hf));
	return ResID;
}

BOOL FontManager::RemoveFontType( UINT ResID )
{
	MAP_HFONT_ID::iterator iter=m_hfonts.find(ResID);
	if(iter!=m_hfonts.end())
	{
		DeleteObject(iter->second);
		m_hfonts.erase(iter);
		return TRUE;
	}
	else return FALSE;
}

BOOL FontManager::DrawMamagerText( UINT ResID,HDC destDC,RECT* destRC, const TCHAR *text,COLORREF fontcolor /*= RGB(0,0,0)*/, unsigned int mode /*= DT_TOP|DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK*/ )
{

	MAP_HFONT_ID::iterator iter=m_hfonts.find(ResID);
	if(iter==m_hfonts.end())
	{
		return FALSE;
	}

	HFONT hOldFont = (HFONT)SelectObject(destDC,iter->second);
	SetBkMode(destDC,TRANSPARENT);
	SetTextColor(destDC,fontcolor);
	::DrawText(destDC,text,lstrlen(text),destRC,mode);
	SelectObject(destDC,hOldFont);
	return TRUE;

}