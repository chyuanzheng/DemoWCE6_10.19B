/////////////////////////////////////////////////////////////////////////////
//
// RASUtil.h : classes wrapping the functionality of the RAS API
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __CeRas_h__
#define __CeRas_h__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ras.h>		// Remote Access Service API
#include <raserror.h>	// RAS Error codes
#include <vector>
#include <map>

#include "CeThread.h"		// critical section class
#include "CeString.h"

using namespace std;

#define IDS_RAS_OPENPORT                201
#define IDS_RAS_PORTOPENED              202
#define IDS_RAS_CONNECTDEVICE           203
#define IDS_RAS_DEVICECONNECTED         204
#define IDS_RAS_ALLDEVICESCONNECTED     205
#define IDS_RAS_AUTHENTICATE            206
#define IDS_RAS_AUTHNOTIFY              207
#define IDS_RAS_AUTHRETRY               208
#define IDS_RAS_AUTHCALLBACK            209
#define IDS_RAS_AUTHCHANGEPASSWORD      210
#define IDS_RAS_AUTHPROJECT             211
#define IDS_RAS_AUTHLINKSPEED           212
#define IDS_RAS_AUTHACK                 213
#define IDS_RAS_REAUTHENTICATE          214
#define IDS_RAS_AUTHENTICATED           215
#define IDS_RAS_PREPAREFORCALLBACK      216
#define IDS_RAS_WAITFORMODEMRESET       217
#define IDS_RAS_WAITFORCALLBACK         218
#define IDS_RAS_INTERACTIVE             219
#define IDS_RAS_RETRYAUTHENTICATION     220
#define IDS_RAS_CALLBACKSETBYCALLER     221
#define IDS_RAS_PASSWORDEXPIRED         222
#define IDS_RAS_CONNECTED               223
#define IDS_RAS_DISCONNECTED            224
#define IDS_RAS_UNDEFINED_STATE         225
#define IDS_RAS_PROJECTED               226
#define IDS_RAS_STARTAUTHENTICATION     227
#define IDS_RAS_CALLBACKCOMPLETE        228
#define IDS_RAS_LOGONNETWORK            229
#define IDS_RAS_SUBENTRYCONNECTED       230
#define IDS_RAS_SUBENTRYDISCONNECTED    231

typedef vector<CeString> CeStringArray;

/////////////////////////////////////////////////////////////////////////////
// The classes in this file include:

class CeRasDevInfo;
class CeRasEntryName;
class CeRasEntry;
class CeRasDialParams;
class CeRasConn;
class CeRasDialExt;

class CeRasAmb;
class CeRasPppNbf;
class CeRasPppIpx;
class CeRasPppIp;

/////////////////////////////////////////////////////////////////////////////
// CeRasDevInfo
typedef RASDEVINFO _rasdevinfo;
class CeRasDevInfo : public _rasdevinfo
{
public:
	CeRasDevInfo()
	{
		memset((_rasdevinfo *)this, 0, sizeof _rasdevinfo);
		dwSize = sizeof(RASDEVINFO);
	}
	~CeRasDevInfo() {}

#ifndef _WIN32_WCE
	static int GetAll(RASDEVINFO** arDevInfo);
#endif

};

/////////////////////////////////////////////////////////////////////////////
// CeRasConnStatus
typedef RASCONNSTATUS _rasconnstatus;
class CeRasConnStatus : public _rasconnstatus
{
public:
	CeRasConnStatus()
	{
		memset((_rasconnstatus *)this, 0, sizeof _rasconnstatus);
		dwSize = sizeof(RASCONNSTATUS);
	}
	~CeRasConnStatus() {}
};

/////////////////////////////////////////////////////////////////////////////
// CeRasEntryName
typedef RASENTRYNAME _rasentryname;
class CeRasEntryName : public _rasentryname
{
public:
	CeRasEntryName()
	{
		memset((_rasentryname*)this, 0, sizeof _rasentryname);
		dwSize = sizeof _rasentryname;
	}
	~CeRasEntryName() {}
};


/////////////////////////////////////////////////////////////////////////////
// CeRasDialExt
typedef RASDIALEXTENSIONS _rasdialextensions;
class CeRasDialExt : public _rasdialextensions
{
public:
	CeRasDialExt(DWORD dwfOpt = 0, HWND hwnd = NULL)
	{
		memset((_rasdialextensions*)this, 0, sizeof _rasdialextensions);
		dwSize = sizeof _rasdialextensions;
		dwfOptions = dwfOpt;
		hwndParent = hwnd;

	}
	~CeRasDialExt() {}

	DWORD GetOptions() const { return dwfOptions; }
	void  SetOptions(DWORD dwfOpt) { dwfOptions = dwfOpt; }

	HWND GetParentHWnd() const { return hwndParent; }
	void SetParentHWnd(HWND hwnd) { hwndParent = hwnd; }
};


/////////////////////////////////////////////////////////////////////////////
// CeRasAmb
#ifdef RASAMB
typedef RASAMB _rasamb;
class CeRasAmb : public _rasamb
{
public:
	CeRasAmb()
	{
		memset((_rasamb *)this, 0, sizeof _rasamb);
		dwSize = sizeof _rasamb;
	}
	~CeRasAmb() {}
};
#endif

/////////////////////////////////////////////////////////////////////////////
// CeRasPppNbf
#ifdef RASPPPNBF
typedef RASPPPNBF _raspppnbf;
class CeRasPppNbf : public _raspppnbf
{
public:
	CeRasPppNbf()
	{
		memset((_raspppnbf *)this, 0, sizeof _raspppnbf);
		dwSize = sizeof(RASPPPNBF);
	}
	~CeRasPppNbf() {}
};
#endif


/////////////////////////////////////////////////////////////////////////////
// CeRasPppIpx
#ifdef RASPPPIPX
typedef RASPPPIPX _raspppipx;
class CeRasPppIpx : public _raspppipx
{
public:
	CeRasPppIpx()
	{
		memset((_raspppipx *)this, 0, sizeof _raspppipx);
		dwSize = sizeof(RASPPPIPX);
	}
	~CeRasPppIpx() {}
};
#endif

/////////////////////////////////////////////////////////////////////////////
// CeRasPppIp
#ifdef RASPPPIP
typedef RASPPPIP _raspppip;
class CeRasPppIp : public _raspppip
{
public:
	CeRasPppIp()
	{
		memset((_raspppip *)this, 0, sizeof _raspppip);
		dwSize = sizeof(RASPPPIP);
	}
	~CeRasPppIp() {}
};
#endif

/////////////////////////////////////////////////////////////////////////////
// CeRasEntry
typedef RASENTRY _rasentry;
class CeRasEntry : public _rasentry
{
public:
	CeRasEntry(LPCTSTR lpszDevName=NULL, LPCTSTR lpszPhone=NULL, LPCTSTR lpszAreaCode=NULL, LPCTSTR lpszCountryCode=NULL);
	~CeRasEntry();

	// get/set entry using this object
	void Create(LPCTSTR szName);
	void Get(LPCTSTR szName, LPBYTE* lpbDevInfo = NULL);
	void Set(LPCTSTR szName, LPBYTE lpbDevInfo = NULL);

#ifndef _WIN32_WCE
	void SetWin95(LPCTSTR szName);
#endif

	void SetDevice(LPCTSTR strDevName);
	void SetPhone(LPCTSTR strPhoneNumber, LPCTSTR  strAreaCode=NULL, LPCTSTR strCountryCode=NULL);

	static void Rename(LPCTSTR szNameTo, LPCTSTR szNameFrom);
	static void Delete(LPCTSTR szName);

	static int GetAll(RASENTRYNAME** arEntries);

	static long StringToIP(LPCTSTR szIP);
	static RASIPADDR StringToRASIP(LPCTSTR strIP);

private:
	static void IPHelper();

	CeStringArray m_arAdditional;
};

/////////////////////////////////////////////////////////////////////////////
// CeRasDialParams
typedef RASDIALPARAMS _rasdialparams;
class CeRasDialParams : public _rasdialparams
{
public:
	CeRasDialParams(LPCTSTR lpszEntry, LPCTSTR lpszUserName, LPCTSTR lpszPassword)
	{
		memset((_rasdialparams*)this, 0, sizeof _rasdialparams);
		dwSize = sizeof _rasdialparams;
		_tcscpy(szEntryName, lpszEntry);
		_tcscpy(szUserName, lpszUserName);
		_tcscpy(szPassword, lpszPassword); 
	}
	~CeRasDialParams() {}

	// Note that the default copy constructor is just dandy
};


typedef RASCONN _rasconn;
class CeRasConn : public _rasconn
{
protected:
	//
	// Monitors asynchronous connections automatically
	//
	class CeRasConnMapper
	{
	private:
		CeCriticalSection m_cs;
		map<HRASCONN, void*> m_mapConn;

	public:
		BOOL AddMapping(HRASCONN hRASConn, CeRasConn* pConn)
		{
			m_cs.Enter();
			m_mapConn.insert(pair<HRASCONN,void*>(hRASConn, pConn));
			m_cs.Leave();

			return TRUE;
		}

		CeRasConn* GetMapping(HRASCONN hRASConn)
		{
			m_cs.Enter();
			CeRasConn* pConn = NULL;
            map<HRASCONN, void*>::iterator iter = m_mapConn.find(hRASConn);
			if(iter != m_mapConn.end())
				CeRasConn* pConn = (CeRasConn *)(iter->second);	
			m_cs.Leave();

			return pConn;
		}

		CeRasConn* RemoveMapping(HRASCONN hRASConn)
		{
			m_cs.Enter();
			CeRasConn* pConn = NULL;
            map<HRASCONN, void*>::iterator iter = m_mapConn.find(hRASConn);
			if(iter != m_mapConn.end())
			{
                CeRasConn* pConn = (CeRasConn *)(iter->second);	
				m_mapConn.erase(iter);
			}
			m_cs.Leave();

			return pConn;
		}
	};

	static CeRasConnMapper s_mapConn;

public:
	// DECLARE_DYNAMIC(CeRasConn)

	CeRasConn();
	virtual ~CeRasConn();

	DWORD SetTimeout(DWORD dwMilliseconds)
		{
			DWORD dwOld = m_dwTimeOut;
			m_dwTimeOut = dwMilliseconds;
			return dwOld;
		}
	DWORD GetTimeout() const
		{ return m_dwTimeOut; }

	int SetRetries(int nRetries)
		{
			int nOld = m_nRetries;
			m_nRetries = nRetries;
			return nOld;
		}
	DWORD GetRetries() const
		{ return m_nRetries; }

	void Dial(LPRASDIALPARAMS lpRasDialParams, BOOL bSynchronous=TRUE, LPRASDIALEXTENSIONS lpRASDialExt=NULL);
	void Hangup(BOOL bSynchronous=TRUE);

	static CeString GetStatus(RASCONNSTATE rasconnstate);
	DWORD GetStatus(CeRasConnStatus& rasState);
	CeString GetStatus();
	BOOL IsConnected();

#if !defined(_WIN32_WCE)
	void GetProjectionInfo(LPRASAMB pInfo);
	void GetProjectionInfo(LPRASPPPNBF pInfo);
	void GetProjectionInfo(LPRASPPPIPX pInfo);
	void GetProjectionInfo(LPRASPPPIP pInfo);
#endif

	static VOID WINAPI RasDialNotificationFn(HRASCONN hrasconn, UINT unMsg, RASCONNSTATE rascs, DWORD dwError, DWORD dwExtendedError);
	virtual void OnDialStatus(UINT unMsg, RASCONNSTATE rascs, DWORD dwError, DWORD dwExtendedError);
	virtual void LogEvent(short nPriority, LPCTSTR szEvent) const;

	static int GetAll(RASCONN** arConn);

	BOOL IsDialComplete() const
		{ return m_bComplete; }
	void SetDialComplete(DWORD dwError);
	void WaitForDialComplete();

#ifdef _DEBUG
//	virtual void AssertValid( ) const;
//	virtual void Dump( CDumpContext& dc ) const;
#endif

private:
	// Dialing parameters for active call
//	LPTSTR m_lpszPhoneBook;
	LPRASDIALPARAMS m_lpRasDialParams;
	BOOL m_bSynchronous;

	// Connection complete status
	BOOL m_bComplete;

	// Event used to make WaitForConnect() work
	CeManualEvent m_eventDialComplete;

	// Dialing status for active dial
	UINT m_unMsg;
	RASCONNSTATE m_rascs;
	DWORD m_dwError;
	DWORD m_dwExtendedError;
	DWORD m_dwTimeOut;
	int m_nRetries;
};

#endif // __CeRas_h__
