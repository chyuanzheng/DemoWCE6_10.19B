#pragma once

#include "AbControl.h"

class CE_CONTROL_API Percent : public AbControl
{
protected:
	UINT     m_nEvent;
	//°´Å¥Í¼Æ¬
	HBITMAP  m_map_back;
	HBITMAP  m_map_sli;

	RECT     m_act_rt;
    RECT     m_sli_rt;
    RECT     m_note_rt;

	INT     m_xWidth;
	INT     m_yHeight;
	//ÅÐ¶ÏÊÇ·ñ±»°´ÏÂ
    FLOAT    m_fPer;
	TCHAR     m_isButtonDown;
    //UINT     m_spDeal;
    WCHAR    m_wsPost[10];
    LONG     m_max;
    LONG     m_min;
    int      m_showType;
public:
	Percent();
	virtual ~Percent();
    enum {sint, sfloat};
	void Init( WORD wMapSli, WORD wMapBack, UINT nEvent, const RECT &rect ,FLOAT f_sli, 
        FLOAT f_note, LONG l_het, FLOAT fp, LONG min, LONG max,const WCHAR *post,int showType = sint);
    void SetPer(FLOAT fper,bool bRedraw = true);
    void SetDisable(bool bDisable);

protected:
	//»æ»­
	virtual void Draw( HDC hdcDst );
	virtual BOOL Response( HDC hdc,	UINT nMsg, WPARAM wParam, LPARAM lParam );
private:
    void BufDraw( HDC hdcDst );
	BOOL InMyArea( int x, int y );
    BOOL ComputePer( int x );
    BOOL m_bIsDisable;
};
