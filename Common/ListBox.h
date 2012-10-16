#pragma once

#include "AbControl.h"
#include "ImagesManager.h"
#include "Font.h"
typedef  list<wstring> LIST_STR;

class CE_CONTROL_API ListBox : public AbControl
{
private:
	LIST_STR  *m_pListstr;
	UINT     m_nIDBack;
	UINT     m_hFontID;
	UINT     m_nEventChoose;
	UINT     m_nLineHeight;
	UINT     m_nLineAmount;

	BOOL     m_bShow;
	BOOL     m_bEvent;//是否发送消息
	INT      m_nStartLine;//m_liststr中的起始行

	//m_liststr中的选择行，m_liststr.size() > = m_nChooseLine >= m_nStartLine
	//如果 m_nChooseLine = -1 表示没有选择
	INT       m_nChooseLine;
	INT       m_nYmovement;
	//事件
    RECT    m_drawRect;
	INT     m_startTop;
	//判断是否被按下
	TCHAR     m_isButtonDown;
	CImagesManager *pImageManager;
	FontManager *m_pfontManager;
protected:
	//绘画
	virtual void Draw( HDC hdcDst );
	//响应自身事件
	virtual BOOL Response( HDC hdc,	UINT nMsg, WPARAM wParam, LPARAM lParam );
	BOOL InMyArea( int x, int y );
	BOOL FreshChoose(int y);
	BOOL CalculateDrawRect();
    

public:
	ListBox();
	virtual ~ListBox();
	void  ShowList(BOOL bShow);
	BOOL  Init(const TCHAR* pfileBack,UINT nHeight, const RECT& rt, UINT nEvent, BOOL bShow = FALSE);
	BOOL  SetFont(  LONG nHeight, LONG nWeight,const WCHAR * ftName = L"宋体" );

};
