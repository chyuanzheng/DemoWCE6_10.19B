#pragma once
#include "AbControl.h"
#include "Font.h"
#define MAX_NUM_TEXT 200
class CE_CONTROL_API Edit : public AbControl
{

public:
	typedef enum FreshType {DoNull, FreLater,FreInstant};
	Edit();
	~Edit();
    BOOL  SetFont(  LONG nHeight, LONG nWeight,const WCHAR * ftName = L"ËÎÌå" );
	void  SetText( LPCTSTR  pText,FreshType rfh = FreLater);
	void  SetTextColor( COLORREF color ){m_txtColor = color;}
	void  SetArea( const RECT &rect ){m_ActRect = rect;}
    void  SetAlign( DWORD dw ){m_dwAlign = dw;}
	void  Refresh( ){AfxValidateRect(m_hWnd,m_ActRect);}
	//ÉèÖÃ×ÖÌå¾ä±ú
protected:
    virtual void Draw( HDC hdcDst );
    DWORD    m_dwAlign;
    UINT     m_hFontID;
	wstring  m_sText;
	COLORREF m_txtColor;
private:
	FontManager *m_pfontManager;
};
