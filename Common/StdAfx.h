#pragma once
#pragma warning(disable:4996) //����ʾһ��
#pragma warning(disable:4251) //
#define CH_CE_DEBUG
#ifdef CH_CE_DEBUG
//#ifndef _SECURE_ATL
//#define _SECURE_ATL 1
//#endif

//#ifndef VC_EXTRALEAN
//#define VC_EXTRALEAN		// �� Windows ͷ���ų�����ʹ�õ�����
//#endif
//
//// ���������ʹ��������ָ����ƽ̨֮ǰ��ƽ̨�����޸�����Ķ��塣
//// �йز�ͬƽ̨����Ӧֵ��������Ϣ����ο� MSDN��
//#ifndef WINVER				// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
//#define WINVER 0x0501		// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
//#endif


#include <windows.h>

// C ����ʱͷ�ļ�
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

#ifndef WINVER				// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define WINVER 0x0501		// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif

#ifndef _WIN32_WINNT		// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define _WIN32_WINNT 0x0501	// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif						

#ifndef _WIN32_WINDOWS		// ����ʹ���ض��� Windows 98 ����߰汾�Ĺ��ܡ�
#define _WIN32_WINDOWS 0x0410 // ����ֵ����Ϊ�ʵ���ֵ����ָ���� Windows Me ����߰汾��ΪĿ�ꡣ
#endif

#ifndef _WIN32_IE			// ����ʹ���ض��� IE 6.0 ����߰汾�Ĺ��ܡ�
#define _WIN32_IE 0x0600	// ����ֵ����Ϊ��Ӧ��ֵ���������� IE �������汾��
#endif

#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
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



