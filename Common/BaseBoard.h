#pragma once
#include "AbControl.h"
#include "ImagesManager.h"
class CE_CONTROL_API BaseBoard : public AbControl
{
    friend class AFX_MODULE_STATE;
public:
    BaseBoard(HWND hwnd, BaseBoard* pParent =NULL);
	BOOL InitBoard(LPCTSTR imagefile,const RECT *pRc=NULL);
	//BOOL InitBoard(UINT imageid, RECT *pRc=NULL);
	BaseBoard *GetParentBoard(){return m_pParentBoard;}
	const RECT & GetActRect(){return m_ActRect;}
	BOOL IsDomodal(){return m_bIsDomal;}
	INT  DoModal();

	virtual ~BaseBoard ();
    
    virtual void Draw( HDC hdcDst );

    virtual void DrawTraBoard(HDC hdc ){};
  
	UINT    m_resID;
protected:
	void    DestroyBoard();
    void    DestroyAllBoard();
    BOOL    DlClick();
    
private:
	BOOL    m_bIsDomal;
	CImagesManager *pImageManager;
    BaseBoard *m_pParentBoard;
    DWORD    m_ntime;
};

