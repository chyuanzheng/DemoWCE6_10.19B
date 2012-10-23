#pragma once
#pragma warning(disable:4996) //仅显示一个
#pragma warning(disable:4251) //
#define CH_CE_DEBUG
#ifdef CH_CE_DEBUG
//#ifndef _SECURE_ATL
//#define _SECURE_ATL 1
//#endif

//#ifndef VC_EXTRALEAN
//#define VC_EXTRALEAN		// 从 Windows 头中排除极少使用的资料
//#endif
//
//// 如果您必须使用下列所指定的平台之前的平台，则修改下面的定义。
//// 有关不同平台的相应值的最新信息，请参考 MSDN。
//#ifndef WINVER				// 允许使用特定于 Windows XP 或更高版本的功能。
//#define WINVER 0x0501		// 将此值更改为相应的值，以适用于 Windows 的其他版本。
//#endif


#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


#include <vector>
#include <deque>
#include <map>
#include <list>
#include <string>
#include <algorithm>
#include "../TinyXml/tinyxml.h"

using namespace std;
#include "AfxFuc.h"
#pragma warning(disable:4996)
#pragma warning(disable:4018)




#else

#ifndef WINVER				// 允许使用特定于 Windows XP 或更高版本的功能。
#define WINVER 0x0501		// 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif

#ifndef _WIN32_WINNT		// 允许使用特定于 Windows XP 或更高版本的功能。
#define _WIN32_WINNT 0x0501	// 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif						

#ifndef _WIN32_WINDOWS		// 允许使用特定于 Windows 98 或更高版本的功能。
#define _WIN32_WINDOWS 0x0410 // 将此值更改为适当的值，以指定将 Windows Me 或更高版本作为目标。
#endif

#ifndef _WIN32_IE			// 允许使用特定于 IE 6.0 或更高版本的功能。
#define _WIN32_IE 0x0600	// 将此值更改为相应的值，以适用于 IE 的其他版本。
#endif

#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 在此处引用程序需要的其他头文件
//#include <afxwin.h>
#include <crtdbg.h>
#include <vector>
#include <deque>
#include <map>
#include <list>
#include <string>
#include <algorithm>
using namespace std;
#include "AfxFuc.h"
#pragma warning(disable:4996)
#pragma warning(disable:4018)
#pragma warning(disable:4267)


#endif



