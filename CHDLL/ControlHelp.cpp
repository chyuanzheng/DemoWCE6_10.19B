#include "../common/StdAfx.h"
#include "../common/ControlHelp.h"
#include "../common/GXCreateControls.h"

RegisterHelp::RegisterHelp( const CHAR *cName, FunCrtControl funCreate )
{
	GXCreateControl::RegisterControlCreate(cName, funCreate);
}