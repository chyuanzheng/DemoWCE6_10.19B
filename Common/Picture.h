#pragma once

#include "AbControl.h"
class  CE_CONTROL_API Picture : public AbControl
{

public:
	Picture();
	virtual ~Picture();
	void Init( WORD wMapBack,const RECT rt, BOOL isConst = TRUE);

protected:
	//»æ»­
	virtual void Draw( HDC hdcDst );
    BOOL m_isConst;
    HBITMAP m_map_back;
    RECT  m_picRect;
    RECT     m_ActRect;
};
