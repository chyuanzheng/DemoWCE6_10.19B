#pragma once
#include "AbControl.h"

class Activity;
typedef Activity* (*FunCrtActivity)();
class CE_CONTROL_API Activity : public AbControl
{
    friend class AFX_MODULE_STATE;
public:
	Activity();

	BOOL setContentView(const WCHAR* layout);
	virtual public void onCreate();
	//BOOL InitBoard(UINT imageid, RECT *pRc=NULL);
	Activity *GetParentBoard(){return m_pParentBoard;}
	const RECT & GetActRect(){return m_ActRect;}

	virtual ~Activity ();
    
    virtual void Draw( HDC hdcDst );

  
	HANDLE    m_handleBack;
protected:
	virtual void setCtrLayout( TiXmlElement * ele );
	void    DestroyBoard();
    void    DestroyAllBoard();
    BOOL    DlClick();
    
private:
    Activity *m_pParentBoard;
    DWORD    m_ntime;
};

