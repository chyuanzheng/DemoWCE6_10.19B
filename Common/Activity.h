#pragma once
#include "AbControl.h"
#include "ImagesManager.h"
class Activity;
typedef Activity* (*FunCrtActivity)();
class CE_CONTROL_API Activity : public AbControl
{
    friend class AFX_MODULE_STATE;
public:
    Activity(HWND hwnd, Activity* pParent =NULL);
	Activity();

	BOOL setContentView(const WCHAR* layout);
	virtual public void onCreate();
	//BOOL InitBoard(UINT imageid, RECT *pRc=NULL);
	Activity *GetParentBoard(){return m_pParentBoard;}
	const RECT & GetActRect(){return m_ActRect;}
	BOOL IsDomodal(){return m_bIsDomal;}
	INT  DoModal();

	virtual ~Activity ();
    
    virtual void Draw( HDC hdcDst );

    virtual void DrawTraBoard(HDC hdc ){};
  
	UINT    m_resID;
protected:
	virtual void setCtrLayout( TiXmlElement * ele );
	void    DestroyBoard();
    void    DestroyAllBoard();
    BOOL    DlClick();
    
private:
	BOOL    m_bIsDomal;
	CImagesManager *pImageManager;
    Activity *m_pParentBoard;
    DWORD    m_ntime;
};

