#include "../common/StdAfx.h"
#include "../common/Launch.h"
#include "../common/AppButton.h"
#include "../common/StrHelp.h"
#include "../common/XmlDef.h"
//#include "aygshell.h"
/************************************************************************/
/* ����û���趨�����ı߽磬���Ի�����ʱ����Ữ��ͷ��
mark*/
/************************************************************************/
Launch::Launch()
{
	//��Ҫ�����ڴ�ı�������Ҫ��Ĭ�Ϲ��캯���и���ֵ
	m_isButtonDown=FALSE;

}

Launch::~Launch()
{

	
}


BOOL Launch::InMyArea( int x, int y )
{
	//�ж�����
	POINT pt = {x,y};
	return ::PtInRect(&m_ActRect, pt);
}

BOOL Launch::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{

	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if (inSlideArea( LOWORD( lParam ), HIWORD( lParam ) ))
		{
			m_isButtonDown=TRUE;
			m_xpos = LOWORD( lParam );
			return TRUE;
		}
		 
		return FALSE;
	case WM_MOUSEMOVE:
		if (m_isButtonDown)
		{
			ControlList::iterator pos;	
			pos = m_pCtrlVet->begin();
			while(pos != m_pCtrlVet->end())
			{
				((AppButton*)(*pos))->slideApp( LOWORD( lParam )-m_xpos );//����û���趨�����ı߽磬���Ի�����ʱ����Ữ��ͷ����ʱ��˵
				pos++;
			}
			m_xpos= LOWORD( lParam );
			AfxValidateRect(NULL);
			return TRUE;
		}
		return FALSE;
	case WM_LBUTTONUP:
		if (m_isButtonDown)
		{
			m_isButtonDown=FALSE;
			return TRUE;
		}
		
		return FALSE;
	default:
		return FALSE;
	}
}

void Launch::setCtrLayout( TiXmlElement * ele )//����Ҫ���м�飬�´β���
{

	setCtrRect(ele);


    int uitv,hitv,vitv;
	int appwidth,appheight;
	int hnum,vnum;

	ele->Attribute(UNIT_INTERVAL,&uitv);
	ele->Attribute(V_MARGIN,&m_vmar);
	ele->Attribute(H_IVTERVAL,&hitv);
	ele->Attribute(V_IVTERVAL,&vitv);

	ele->Attribute(APP_WIDTH,&appwidth);
	ele->Attribute(APP_HEIGHT,&appheight);

	ele->Attribute(H_NUM,&hnum);
	ele->Attribute(V_NUM,&vnum);
	int temp = uitv+appwidth*hnum +(hnum-1)*hitv;

	RECT rt;
	int  count=0;

	TiXmlElement * chid = ele->FirstChildElement();
	string ctrname;
	AppButton *ctr;
	while(chid)
	{

		rt.left = uitv/2 + count/vnum*(appwidth+hitv)+ count/vnum/hnum*(uitv-hitv);
		rt.right = rt.left+appwidth;
		rt.top =  m_vmar + count%vnum*(appheight+vitv);
		rt.bottom = rt.top + appheight;
		ctrname = chid->Value();

		if (ctrname == APP_BUTTON)
		{
			ctr = new AppButton;
		}
		if (ctr)
		{
			AddCtrl(ctr);
			ctr->setCtrLayout(chid);
			ctr->setCtrRect(rt);
		}
		chid = chid->NextSiblingElement();
		count++;

	}

}
/************************************************************************/
/* ����ӿؼ��Ƿ���Lanch�ؼ���*/
/************************************************************************/
BOOL Launch::checkRect( const RECT & rect )
{
	return m_ActRect.left<rect.right&&m_ActRect.right>rect.left;
}

/************************************************************************/
/* ���x ��y�ǲ��������µĿհ�������*/
/************************************************************************/
BOOL Launch::inSlideArea( int x, int y )
{
	if (m_vmar>y||y>m_ActRect.bottom-m_vmar)
	{
		return TRUE;
	}
	return FALSE;
}

