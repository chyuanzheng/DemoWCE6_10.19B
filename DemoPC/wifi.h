#ifndef _WIFI_H_
#define _WIFI_H_

#include "stdafx.h"
#include "wzcsapi.h"
#include <vector>

#define BSSID_LEN 6
#define SSID_LEN 32
#define INADDR_LEN 4
#define MAX_DNS_NAME_LENGTH 256

#define MAX_WPA_PSK_KEY_LENGTH 32
#define MAX_WPA_PAYLOAD_LENGTH 64

enum AuthType_SSID
{
	AuthType_None,
	AuthType_WEP,
	AuthType_WPA_EAP,
	AuthType_WPA_PSK
};

#define MAX_WPA_PAYLOAD_LENGTH 64

enum EncryptionType
{
	EncryptionType_None = 0,
	EncryptionType_WEP,
	EncryptionType_TKIP,
	EncryptionType_AES
};

enum SecurityType
{
	SecurityType_Open = 1,			// open
	SecurityType_Shared_WEP = 2,	// Shared key WEP
	SecurityType_WPA_EAP = 4,		// WPA with 802.1x / EAP authentication
	SecurityType_WPA_PSK = 5,		// WPA with PSK authentication
	SecurityType_WPA2_EAP = 6,		// WPA2 with 802.1x / EAP authentication
	SecurityType_WPA2_PSK = 7,		// WPA2 with PSK authentication
	SecurityType_Both = 8			// Both open and Shared key WEP
};

enum EAPType
{
	EAPType_None = 0,
	EAPType_PAP = 1,
	EAPType_Chap = 2,
	EAPType_MD5 = 4,
	EAPType_EAP = 6,
	EAPType_TLS = 13,
	EAPType_LEAP = 17,
	EAPType_TTLS = 21,
	EAPType_PEAP = 25,
	EAPType_MSCHAPv2 = 26	
};

namespace WIFI
{

	struct BSSIDInfo
	{
		BYTE BSSID[BSSID_LEN];	//mac
		WCHAR SSID[SSID_LEN];
		int RSSI;
		int Channel;
		int Infastructure;
		int Auth;
	};

	class CAvailableAPList 
	{ 
	public: 
		CAvailableAPList(void); 
		CAvailableAPList(const LPBYTE lpByte); 
		CAvailableAPList(const CAvailableAPList& wlan); 
		CAvailableAPList operator = (const CAvailableAPList& wlan); 

		void    Clear(); 
		BOOL    ParseFrom(const LPBYTE lpByte); 
		LPCWSTR GetLastErrorMsg(){ return this->m_strErr.c_str(); } 

		BOOL    get_NDIS_WLAN_BSSID(const LPBYTE lpByte, PNDIS_WLAN_BSSID pBssid); 
		BOOL    get_NDIS_802_11_CONFIGURATION(const LPBYTE lpByte, PNDIS_802_11_CONFIGURATION pConfig); 
		BOOL    get_NDIS_802_11_CONFIGURATION_FH(const LPBYTE lpByte, PNDIS_802_11_CONFIGURATION_FH pConfigFH); 

		~CAvailableAPList(void); 

	public: 
		static const int   LengthOffset = 4; 
		static const int   MacAddressOffset = LengthOffset + 4; 
		static const int   ReservedOffset = MacAddressOffset + 6; 
		static const int   SsidOffset = ReservedOffset + 2; 
		static const int   PrivacyOffset = SsidOffset + 36;    // The ssid length plus 32 character array. 
		static const int   RssiOffset = PrivacyOffset + 4; 
		static const int   NetworkTypeInUseOffset = RssiOffset + 4; 
		static const int   ConfigurationOffset = NetworkTypeInUseOffset + sizeof(NDIS_802_11_NETWORK_TYPE);    
		static const int   InfrastructureModeOffset = ConfigurationOffset + 32;   
		static const int   SupportedRatesOffset = InfrastructureModeOffset + 4;    

		NDIS_802_11_BSSID_LIST          m_bssidList; 
		std::vector<NDIS_WLAN_BSSID>    m_vectBssid; 

	private: 
		std::wstring                    m_strErr; 
	}; 

	class CPreferredAPList 
	{ 
	public: 
		CPreferredAPList(void); 
		CPreferredAPList(const LPBYTE lpByte); 
		CPreferredAPList(const CPreferredAPList& wlan); 
		CPreferredAPList operator = (const CPreferredAPList& wlan); 

		void    Clear(); 
		BOOL    ParseFrom(const LPBYTE lpByte); 
		LPCWSTR GetLastErrorMsg(){ return this->m_strErr.c_str(); } 

		BOOL    get_WZC_WLAN_CONFIG(const LPBYTE lpByte, PWZC_WLAN_CONFIG pConfig); 

		~CPreferredAPList(void); 

	public: 
		static  const int   NumberOfItemsOffset = 0; 
		static  const int   BaseIndexOffset = 4; 
		static  const int   ConfigOffset = 8; 

	public: 
		WZC_802_11_CONFIG_LIST          m_stSsidList; 
		std::vector<WZC_WLAN_CONFIG>    m_vectStSsid; 

	private: 
		std::wstring                    m_strErr; 
	}; 

	class CWirelessUtil 
	{ 
	public: 
		CWirelessUtil(); 
		~CWirelessUtil(); 
		BOOL            Init(); 
		void            DeInit(); 
		LPCWSTR         GetFirstDeviceName(); 
		LPCWSTR         GetLastErrorMsg(){ return this->m_strErr.c_str(); } 
		BOOL            IsInit(){ return this->m_bInit; } 

		BOOL            GetSignalStrength(LPCTSTR ptcDeviceName, INT* piSignalStrength); 
		std::wstring    SignalStrengthToString(INT nSignalStrength); 
		BOOL            GetSsid(LPCTSTR ptcDeviceName, LPBYTE lpSsid, size_t nMaxLen); 
		std::wstring    SsidToString(LPBYTE lpByte, int nLen = -1); 
		BOOL            GetBSSIDList(LPCTSTR ptcDeviceName, CAvailableAPList* pWlan); 
		BOOL            ScanForBSSIDList(LPCTSTR ptcDeviceName); 
		BOOL            GetStSSIDList(LPCTSTR ptcDeviceName, CPreferredAPList* pWlan); 
		BOOL            SetInterface(LPCTSTR ptcDeviceName, LPCTSTR szSsid); 
		bool            GetBSSIDList(LPCTSTR ptcDeviceName, struct BSSIDInfo *pDest, DWORD &dwBufSizeBytes, DWORD &dwReturnedItems);
		BOOL            GetWifiConnected(LPCTSTR ptcDeviceName);
		BOOL            Connect(LPCTSTR ptcDeviceName,LPWSTR bssid,SecurityType sectype,EncryptionType encrypttype,
			                             ULONG secrityIndex,TCHAR* Key,EAPType wpaeaptype);
	    BOOL            Disconnect(LPCTSTR ptcDeviceName);

	protected: 
		BOOL    IsNativeWifiDevice(LPCTSTR ptcDeviceName, INT *piSignalStrength); 
		long    MapWirelessSignalStrengthToRSSI(IN  ULONG ulWss); 

	private: 
		HANDLE          m_hNdisUio; 
		INTFS_KEY_TABLE m_keyTable; 
		std::wstring    m_strErr; 
		BOOL            m_bInit; 
		void    setWEPKey2(WZC_WLAN_CONFIG& wzcConfig1,ULONG secIndex,TCHAR* WEPKey);
	}; 

}
#endif