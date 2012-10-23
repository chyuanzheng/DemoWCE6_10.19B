#include "../common/StdAfx.h"
#include "../common/XmlDef.h"
#include "../common/AbControl.h"




AbControl::AbControl()
{

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

/** �ؼ�����Ϣ������ں��� 
    ��WM_DESTROY WM_EXIT_PROSS WM_PAINT ���ڴ˴���
    �ȴ����ؼ�����Ϣ ��Response��
    Ȼ���ٴ����ؼ��е��ӿؼ�����Ϣ
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

/** �ؼ���WM_PAINT��Ϣ������ں��� 
*/
void AbControl::Paint( HDC hdcDst )
{
	Draw(hdcDst);
	ControlList::iterator pos;	
	pos = m_pCtrlVet->begin();
	while(pos != m_pCtrlVet->end())
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


void AbControl::setCtrRect( TiXmlElement * ele )
{
	int data;
	ele->Attribute(LAYOUT_X,&data);
	m_ActRect.left = data;

	ele->Attribute(LAYOUT_Y,&data);
	m_ActRect.top =  data;

	ele->Attribute(LAYOUT_WIDTH,&data);
	m_ActRect.right =  data + m_ActRect.left;

	ele->Attribute(LAYOUT_HEIGHT,&data);
	m_ActRect.bottom =  data + m_ActRect.top;
}
