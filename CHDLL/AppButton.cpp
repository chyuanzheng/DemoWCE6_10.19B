#include "../common/StdAfx.h"
#include "../common/AppButton.h"
#include "../common/Launch.h"
#include "../common/StrHelp.h"
#include "../common/XmlDef.h"
//#include "aygshell.h"
#define  DIFF_SHOW            4
AppButton *AppButton::MoveApp=NULL;
AppButton *AppButton::backApp=NULL;
AppButton::AppButton()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值
	m_isButtonDown=FALSE;
	m_xmove=0;
	m_ymove=0;
	m_xpos=0;
	m_ypos=0;

}

AppButton::~AppButton()
{

	if (m_handleUp!=NULL)
	{
		pImageManager->RemoveImage(m_handleUp);
	}
}



void AppButton::Draw( HDC hdcDst )
{



	//被按下为真
	Launch *pla = (Launch *) m_ParentCtrl;
	if (FALSE==pla->checkRect(m_ActRect))
	{
		return;
	}
	if( m_isButtonDown == TRUE )
	{
		//贴按下图片
		pImageManager->DrawAlphaImage(m_handleUp,hdcDst,NULL,&m_appRect,160);
	}
	//被按下为假 
	else 
	{
		//贴原始图片
	    AppButton* ma =	AppButton::MoveApp;
		AppButton* ba =	AppButton::backApp;
		if (ma&&(NULL==ba||ba==this))//存在移动的appbutton ma，以及没有覆盖的appbutton ba，或者有是本控件
		{
			RECT prt;
			ma->getAppRect(prt);

			int width = m_ActRect.right-m_ActRect.left;
			int height = m_ActRect.bottom-m_ActRect.top;
			int x_itl = width - abs(prt.left-m_ActRect.left);
			int y_itl = height - abs(prt.top-m_ActRect.top);

			if (  x_itl>width/5 && y_itl>height/5&&(x_itl+y_itl>(width+height)/5*2))//如果重叠超过1/5,
			{
				if(NULL==ba){
					AppButton::backApp=this;
				}
				RECT rect= {m_ActRect.left+DIFF_SHOW,  m_ActRect.top+DIFF_SHOW,  m_ActRect.right-DIFF_SHOW,  m_ActRect.bottom-DIFF_SHOW};
				pImageManager->DrawAlphaImage(m_handleUp,hdcDst,NULL,&rect,100);
			}
			else{
				if(this==ba){
					AppButton::backApp=NULL;
				}
				pImageManager->DrawAlphaImage(m_handleUp,hdcDst,NULL,&m_ActRect);
			}
		    
		}
		else{
			if(this==ba){
				AppButton::backApp=NULL;
			}
			pImageManager->DrawAlphaImage(m_handleUp,hdcDst,NULL,&m_ActRect);
		}
		

	}

}

BOOL AppButton::InMyArea( int x, int y )
{
	//判断区域
	POINT pt = {x,y};
	return ::PtInRect(&m_ActRect, pt);
}

BOOL AppButton::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if( InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
		{	
			//::SetCapture( m_hWnd );
			m_isButtonDown = TRUE;
			AfxValidateRect(&m_ActRect);
			m_xpos=LOWORD( lParam );
			m_ypos=HIWORD( lParam );
			setLayer(1);
			m_xmove=0;
			m_ymove=0;
			AppButton::MoveApp=this;
			m_appRect=m_ActRect;
			return TRUE;
		}
		return FALSE;
	case WM_MOUSEMOVE:
		if (m_isButtonDown)
		{
			m_xmove = LOWORD( lParam ) - m_xpos;
			m_ymove = HIWORD( lParam ) - m_ypos;
			::SetRect(&m_appRect,m_ActRect.left-DIFF_SHOW+m_xmove,  m_ActRect.top-DIFF_SHOW+m_ymove,  m_ActRect.right+DIFF_SHOW+m_xmove,  m_ActRect.bottom+DIFF_SHOW+m_ymove);
			AfxValidateRect(NULL);
			return TRUE;
		}
		return FALSE;
	case WM_LBUTTONUP:
		//若本按钮曾经被按下
		if( m_isButtonDown == TRUE )
		{
			//::ReleaseCapture();
			m_isButtonDown = FALSE;
			AfxValidateRect(&m_ActRect);
			if( (m_nEventUp!=0) && InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
			{
				//::PostMessage( m_hWnd, m_nEventUp, (WPARAM)this, 0 );
			}
			m_xmove=0;
			m_ymove=0;
			m_xpos=0;
			m_ypos=0;
			setLayer(0);
			if (AppButton::MoveApp==this)
			{
				exchangeApp(AppButton::backApp);
			}
			AppButton::MoveApp=NULL;
			AppButton::backApp=NULL;
			return TRUE;

		}
		return FALSE;
	default:
		return FALSE;
	}
}

void AppButton::setCtrLayout( TiXmlElement * ele )
{

	 AbControl::setCtrLayout(ele);

	wstring path;
	AfxGetWorkPath(path);

	string strTail = ele->Attribute(BTN_UP);
	m_handleUp = pImageManager->AddImage((path + StrHelp::StringToWString(strTail)).c_str());

}

void AppButton::setAppRect( const RECT &rt )
{
	m_appRect=rt;
}


void AppButton::getAppRect( RECT &rt )
{
	rt = m_appRect;
}
/************************************************************************/
/* 交换两个控件的信息                                                   */
/************************************************************************/
void AppButton::exchangeApp( AppButton *pApp )
{
	if (NULL==pApp)
	{
		return;
	}
	RECT rt;
	pApp->getCtrRect(rt);
	pApp->setCtrRect(m_ActRect);
	m_ActRect=rt;
}

void AppButton::slideApp( int xslide )
{
	m_ActRect.left += xslide;
	m_ActRect.right += xslide;
}

