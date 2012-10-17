#include "../common/StdAfx.h"
#include "../common/Activity.h"
//#include "aygshell.h"

/////////////////////////////////////////////////////////////////////////
// BaseBoard message map and member functions

//有两点需要考虑，1，图像字符串的存放，
//2 InitBoard失败怎么办
Activity::Activity (HWND hwnd,Activity* pParent)
    :AbControl(hwnd)
    ,m_pParentBoard(pParent)
{
	m_bIsDomal = FALSE;
	m_resID = 0;
	pImageManager= CImagesManager::GetInstance();
	
}

BOOL Activity::InitBoard(LPCTSTR imagefile, const RECT *pRc)
{
	wstring Path;
	AfxGetWorkPath(Path);

	wstring imagetPath;
	imagetPath=  Path + imagefile;

	m_resID = pImageManager->AddImage(imagetPath.c_str());

	if (m_resID==0)
	{
		return FALSE;
	}
	AfxSetBoard(m_hWnd,this);//这里保存必要的BaseBoard指针

	if (pRc != NULL)
	{
		m_ActRect = *pRc;
	}
	else
	{
		GetWindowRect(m_hWnd,&m_ActRect);
		::SetRect(&m_ActRect,0,0,m_ActRect.right-m_ActRect.left,m_ActRect.bottom-m_ActRect.top);
	}
	m_ntime = 0;

	return true;
}


Activity::~Activity ()
{
	if (m_resID!=0)
	{
		pImageManager->RemoveImage(m_resID);
	}
}


void  Activity::DestroyBoard()
{
    if(m_pParentBoard)//cyz
    {
		if (m_bIsDomal)
		{
			m_bIsDomal = FALSE;
		}
        AfxSetBoard(m_hWnd,m_pParentBoard);//cyz
    }
	else
	{
		AfxSetBoard(m_hWnd,NULL);
		::PostMessage(m_hWnd,WM_EXIT_PROSS,0,0);
	}
	delete this;
	//::DestroyWindow(m_hWnd);
    return;//如果是有父窗口则返回FALSE
}
void  Activity::DestroyAllBoard()
{
    Activity *pBb;
    Activity *pPraBb = this;
    while(pPraBb){
        pBb = pPraBb;
        pPraBb = pBb->m_pParentBoard;
        pBb->DestroyBoard();
    }
}


void Activity::Draw( HDC hdcDst )
{
	pImageManager->DrawAlphaImage(m_resID,hdcDst,NULL,&m_ActRect);
    //::BitBlt(hdcDst, 0, 0, m_nWidth, m_nHeight,m_hBackDC,0,0,SRCCOPY);
}

BOOL Activity::DlClick()
{
    DWORD ncur;
    DWORD npre;
    ncur = ::GetTickCount();
    npre = m_ntime;
    m_ntime = ncur;
    if( ( ncur- npre)>0 &&( ncur- npre) <300 )
        return TRUE;
    return FALSE;
}

INT Activity::DoModal()
{
	_ASSERT(m_bIsDomal==FALSE);
	m_bIsDomal = TRUE;

	MSG    msg;
	while(GetMessage(&msg, NULL, 0, 0 ))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (m_bIsDomal== FALSE)
		{
			break;
		}
	}

	return 1;
}