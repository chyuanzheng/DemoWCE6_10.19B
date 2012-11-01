#include "../common/StdAfx.h"
#include "../common/XmlDef.h"
#include "../common/AbControl.h"




AbControl::AbControl()
{
    m_nlayer = 0;
	pImageManager= CImagesManager::GetInstance();
	m_pCtrlVet = new ControlList;
}
AbControl::~AbControl()
{
	delete m_pCtrlVet;
}
BOOL   AbControl::AddCtrl(AbControl* control)
{
	if (std::find(m_pCtrlVet->begin(), m_pCtrlVet->end(), control) == m_pCtrlVet->end())
	{
		control->m_ParentCtrl = this;
		m_pCtrlVet->push_back(control);
		return true;
	}
	return false;
}

/** 控件的消息处理入口函数 
    （WM_DESTROY WM_EXIT_PROSS WM_PAINT 不在此处理）
    先处理本控件的消息 （Response）
    然后再处理本控件中的子控件的消息
*/
BOOL AbControl::DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam )
{

	if (Response(message, wParam, lParam ) == TRUE)
	{
		return TRUE;
	}
	ControlList::iterator pos;	
	pos = m_pCtrlVet->begin();
	while(pos != m_pCtrlVet->end())
	{
		if ((*pos)->DealCtrlMsg(message, wParam, lParam ))
		{
			return TRUE;
		}
		pos++;
	}
	return FALSE;
}

/** 控件的WM_PAINT消息处理入口函数 
*/
void AbControl::Paint( HDC hdcDst )
{
	Draw(hdcDst);
	ControlList::iterator pos;	
	ControlList  highList;
	pos = m_pCtrlVet->begin();
	while(pos != m_pCtrlVet->end())
	{
		if ((*pos)->getLayer()>0)//目前只支持两层
		{
			highList.push_back(*pos);
		}
		else{
			(*pos)->Paint( hdcDst );
		}
		pos++;
	}

	pos = highList.begin();
	while(pos != highList.end())
	{
		(*pos)->Paint( hdcDst );
		pos++;
	}
}

BOOL AbControl::AdjustRect( int xleft, int ytop )
{

	::SetRect(&m_ActRect,m_ActRect.left+xleft,m_ActRect.top+ytop,
		m_ActRect.left+xleft +m_ActRect.right-m_ActRect.left,
		m_ActRect.top+ytop+m_ActRect.bottom-m_ActRect.top);


	ControlList::iterator pos;	
	pos = m_pCtrlVet->begin();
	while(pos != m_pCtrlVet->end())
	{
		(*pos)->AdjustRect( m_ActRect.left, m_ActRect.top );
		pos++;
	}
	return TRUE;
}


void AbControl::setLayer( int layer/*=0*/ )
{
	ASSERT(layer>=0&&layer<3);
	m_nlayer=layer;
}

void AbControl::getCtrRect( RECT & rt )
{
	 rt=m_ActRect;
}

void AbControl::setCtrRect( const RECT & rt )
{
	m_ActRect = rt;
}

void AbControl::setCtrLayout( TiXmlElement * ele )
{

	
	int data =0;
	const CHAR *elename = ele->Attribute(CTR_NAME);
	if (NULL!=elename)
	{
		m_name=elename;
	}
	ele->Attribute(LAYOUT_X,&data);
	m_ActRect.left = data;

	ele->Attribute(LAYOUT_Y,&data);
	m_ActRect.top =  data;

	ele->Attribute(LAYOUT_WIDTH,&data);
	m_ActRect.right =  data + m_ActRect.left;

	ele->Attribute(LAYOUT_HEIGHT,&data);
	m_ActRect.bottom =  data + m_ActRect.top;

}

AbControl * AbControl::findViewByName( const CHAR* vname )
{
	ASSERT(vname!=NULL);
	ControlList::iterator pos;	
	string ctrname;
	pos = m_pCtrlVet->begin();
	AbControl * pctr=NULL;
	while(pos != m_pCtrlVet->end())
	{
		ctrname=(*pos)->getCtrName();
        if (ctrname==vname)
        {
			pctr = (*pos);;
			break;
        }
		pctr =(*pos)->findViewByName(vname);
		if (NULL!=pctr)
		{
			break;
		}
		pos++;
	}
	return pctr;
}