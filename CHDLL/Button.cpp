#include "../common/StdAfx.h"
#include "../common/Button.h"
#include "../common/StrHelp.h"
//#include "aygshell.h"

Button::Button()
{
	//��Ҫ�����ڴ�ı�������Ҫ��Ĭ�Ϲ��캯���и���ֵ

	pImageManager= CImagesManager::GetInstance();
}

Button::~Button()
{

	if (m_nIDUp!=0)
	{
		pImageManager->RemoveImage(m_nIDUp);
	}
	if (m_nIDDown!=0)
	{
		pImageManager->RemoveImage(m_nIDDown);
	}
}

BOOL Button::Init(UINT wMapUp, UINT wMapDown, const RECT& rt, UINT nEventUp, UINT nEventDown)
{
	wstring uppath,downpath;
	AfxGetWorkPath(uppath);
	downpath= uppath;

	WCHAR szTitle[100];				
	LoadString(AfxGetInstanceHandle(), wMapUp, szTitle, 100);
	uppath = uppath + szTitle;
	LoadString(AfxGetInstanceHandle(), wMapDown, szTitle, 100);
	downpath = downpath + szTitle;

	return Init(uppath.c_str(),downpath.c_str(),rt,nEventUp,nEventDown);

}
BOOL  Button::Init(const TCHAR* pfileUp,const TCHAR* pfileDown, const RECT& rt, UINT nEventUp, UINT nEventDown )
{
	wstring Path;
	AfxGetWorkPath(Path);

	wstring upstr,downstr;
	upstr = Path + pfileUp;
	downstr = Path + pfileDown;
	

	m_isButtonDown = FALSE;
	m_nEventUp = nEventUp;
	m_nEventDown =  nEventDown;
	m_ActRect = rt;

	m_nIDUp = pImageManager->AddImage(upstr.c_str());
	m_nIDDown = pImageManager->AddImage(downstr.c_str());
	//m_map_up = SHLoadImageFile (pfileUp);
	//m_map_down = SHLoadImageFile (pfileDown);
	if (m_nIDUp == 0 || m_nIDDown == 0)
	{
		return false;
	}
	return true;
}


void Button::Draw( HDC hdcDst )
{



	//������Ϊ��

	if( m_isButtonDown == TRUE )
	{
		//������ͼƬ
		pImageManager->DrawAlphaImage(m_nIDDown,hdcDst,NULL,&m_ActRect);
	}
	//������Ϊ�� 
	else 
	{
		//��ԭʼͼƬ
		pImageManager->DrawAlphaImage(m_nIDUp,hdcDst,NULL,&m_ActRect);

	}

}

BOOL Button::InMyArea( int x, int y )
{
	//�ж�����
	POINT pt = {x,y};
	return ::PtInRect(&m_ActRect, pt);
}

BOOL Button::Response( HDC hdc, UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if( InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
		{	
			//::SetCapture( m_hWnd );
			m_isButtonDown = TRUE;
			//AfxValidateRect(m_hWnd,m_ActRect);
			::InvalidateRect(m_hWnd,&m_ActRect,false);
			if(m_nEventDown != 0)
			{
				::PostMessage( m_hWnd, m_nEventDown, (WPARAM)this, 0 );
			}
			return TRUE;
		}
		return FALSE;

	case WM_LBUTTONUP:
		//������ť����������
		if( m_isButtonDown == TRUE )
		{
			//::ReleaseCapture();
			m_isButtonDown = FALSE;
			AfxValidateRect(m_hWnd,m_ActRect);
			if( (m_nEventUp!=0) && InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
			{
				::PostMessage( m_hWnd, m_nEventUp, (WPARAM)this, 0 );
			}
			return TRUE;

		}
		return FALSE;
	default:
		return FALSE;
	}
}

void Button::setCtrLayout( TiXmlElement * ele )
{

	int data;
	ele->Attribute("layout_x",&data);
	m_ActRect.left = data;

	ele->Attribute("layout_y",&data);
	m_ActRect.top =  data;

	ele->Attribute("layout_width",&data);
	m_ActRect.right =  data + m_ActRect.left;

	ele->Attribute("layout_height",&data);
	m_ActRect.bottom =  data + m_ActRect.top;

	wstring path;
	AfxGetWorkPath(path);

	string strTail = ele->Attribute("btn_up");
	m_nIDUp = pImageManager->AddImage((path + StrHelp::StringToWString(strTail)).c_str());

    strTail = ele->Attribute("btn_down");
	m_nIDDown =  pImageManager->AddImage((path + StrHelp::StringToWString(strTail)).c_str());

}

