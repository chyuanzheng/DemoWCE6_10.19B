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
	BOOL     m_bEvent;//�Ƿ�����Ϣ
	INT      m_nStartLine;//m_liststr�е���ʼ��

	//m_liststr�е�ѡ���У�m_liststr.size() > = m_nChooseLine >= m_nStartLine
	//��� m_nChooseLine = -1 ��ʾû��ѡ��
	INT       m_nChooseLine;
	INT       m_nYmovement;
	//�¼�
    RECT    m_drawRect;
	INT     m_startTop;
	//�ж��Ƿ񱻰���
	TCHAR     m_isButtonDown;
	CImagesManager *pImageManager;
	FontManager *m_pfontManager;
protected:
	//�滭
	virtual void Draw( HDC hdcDst );
	//��Ӧ�����¼�
	virtual BOOL Response( HDC hdc,	UINT nMsg, WPARAM wParam, LPARAM lParam );
	BOOL InMyArea( int x, int y );
	BOOL FreshChoose(int y);
	BOOL CalculateDrawRect();
    

public:
	ListBox();
	virtual ~ListBox();
	void  ShowList(BOOL bShow);
	BOOL  Init(const TCHAR* pfileBack,UINT nHeight, const RECT& rt, UINT nEvent, BOOL bShow = FALSE);
	BOOL  SetFont(  LONG nHeight, LONG nWeight,const WCHAR * ftName = L"����" );

};
