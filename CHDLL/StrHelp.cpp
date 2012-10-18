#include "../common/StrHelp.h"


string StrHelp::WStringToString( const wstring &wstr )
{
	{
		string str(wstr.length(), ' ');
		copy(wstr.begin(), wstr.end(), str.begin());
		return str; 
	}
}

wstring StrHelp::StringToWString( const string &str )
{
	{
		wstring wstr(str.length(),L' ');
		copy(str.begin(), str.end(), wstr.begin());
		return wstr; 
	}
}
