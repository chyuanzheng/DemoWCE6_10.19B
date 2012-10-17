#pragma once
#include "../common/CWnd.h"
#include "../common/Font.h"
#include "../common/ImagesManager.h"

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
