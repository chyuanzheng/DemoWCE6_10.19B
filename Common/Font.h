#pragma once
typedef map<UINT,HFONT>  MAP_HFONT_ID;

class CE_CONTROL_API FontManager
{
public:
	virtual ~FontManager();
	static FontManager* GetInstance();
	static int    AddFontRes(const WCHAR *res);
	UINT          AddFontType( LONG nHeight, LONG nWeight = 0, const WCHAR * ftName= NULL);
	BOOL		  RemoveFontType(UINT ResID);
	BOOL		  DrawMamagerText(UINT ResID,HDC destDC,RECT* destRC, const TCHAR *text,COLORREF fontcolor = RGB(0,0,0),  unsigned int mode = DT_TOP|DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);

private:
	FontManager();
	static FontManager *m_pInstance;
	UINT GetAFreeID();

	MAP_HFONT_ID m_hfonts; 
    LOGFONT     m_pLogFont;
	LOGFONT *  GetLogFont( LONG nHeight, LONG nWeight = 0,const WCHAR * ftName= NULL );
};
