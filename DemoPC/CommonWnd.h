#pragma once
#include "CWnd.h"
#include "Font.h"
#include "ImagesManager.h"

class CCommonWnd : public CWnd
{
public:
    CCommonWnd ();
	~CCommonWnd ();
protected:
	virtual void PostNcDestroy();
private:
	FontManager *m_pfont;
	CImagesManager* m_pimage;
};
