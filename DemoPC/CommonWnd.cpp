#include "stdAfx.h"
#include "CommonWnd.h"
#include "OpenBoard.h"


/////////////////////////////////////////////////////////////////////////
// CCommonWnd message map and member functions

//SetWindowPos(&CWnd::wndTopMost ,0,0,480,272,SWP_SHOWWINDOW);
const RECT IM_MAIN_RECT = {0,0,800,480};//��ߵ� �˳����� {0,0,480,272};//��ߵ� �˳�����
CCommonWnd::CCommonWnd ()
{
    Create( NULL, L"gfdgs", WS_POPUP, IM_MAIN_RECT, NULL);
    new OpenBoard(m_hWnd);
	m_pfont =  FontManager::GetInstance();
	m_pfont->AddFontRes(L"\\NandFlash\\TabletSoft\\Resources\\Fonts\\msyh.ttf");
	m_pimage =  CImagesManager::GetInstance();

}
CCommonWnd::~CCommonWnd ()
{
	delete m_pfont;
	delete m_pimage;
}
void CCommonWnd::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	CWnd::PostNcDestroy();
	delete this;
}