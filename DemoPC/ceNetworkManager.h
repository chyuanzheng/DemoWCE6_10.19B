#ifndef _CENETWORKMANAGER_H_
#define _CENETWORKMANAGER_H_

#include "stdafx.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NETWORKMANAGERLIB_EXPORT
#define NETWORKMANAGERLIBAPI __declspec(dllexport)
#else
#define NETWORKMANAGERLIBAPI __declspec(dllimport)
#endif

#ifdef __cplusplus 
} /* extern "C" */

#endif

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
typedef enum tagCEWIFIState
{
	WIFI_Nothing = 0,
	WIFI_InitFailed,
	WIFI_InitSuccess,
	WIFI_DeviceConnected,
	WIFI_DeviceInvalid,
	WIFI_Connected,
	WIFI_ConnectFailed,
	WIFI_Disconnect,
	WIFI_DisconnectFailed
}
CEWIFISTATE, *LPCEWIFISTATE;

typedef enum tagCEWIFISignalStrength
{
	WIFI_Signal_None,
	WIFI_Signal_VeryLow,
	WIFI_Signal_Low,
	WIFI_Signal_Good,
	WIFI_Signal_VeryGood,
	WIFI_Signal_Excellent
}
CEWIFISIGNALSTRENGTH, *LPCEWIFISIGNALSTRENGTH;

//************************************
// Method:    OpenEVDODevice
// FullName:  ��3G�豸
// Access:    public 
// Returns:   ��3G�豸�ɹ�����true���򷵻�false
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI bool OpenEVDODevice();

//************************************
// Method:    CloseEVDODevice
// FullName:  �ر�3G�豸
// Access:    public 
// Returns:   �ر�3G�豸�ɹ�����true���򷵻�false
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI bool CloseEVDODevice();

//************************************
// Method:    EVDO_Dial
// FullName:  3G ����
// Access:    public 
// Returns:   ���ųɹ�����true���򷵻�false
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI bool EVDO_Dial(LPCTSTR ConnectionName);

//************************************
// Method:    EVDO_Hangup
// FullName:  3G �Ͽ�����
// Access:    public 
// Returns:   �Ͽ����ӳɹ�����true���򷵻�false
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI bool EVDO_Hangup();

//************************************
// Method:    GetEVDOStatus
// FullName:  ��ȡ3G����״̬
// Access:    public 
// Returns:   ����ֵ��RAS����
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI int GetEVDOStatus();

//************************************
// Method:    GetWiFiStatus
// FullName:  ��ȡWiFi�豸״̬
// Access:    public 
// Returns:   ����ֵ
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI CEWIFISTATE GetWiFiStatus();

//************************************
// Method:    GetWiFiDeviceName
// FullName:  ��ȡWIFI�豸����
// Access:    public 
// Returns:   ����õ�wifi�豸�����򷵻������ַ��������򷵻�Ϊ�մ�
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI LPCWSTR GetWiFiDeviceName();

//************************************
// Method:    GetWiFiErrorMessage
// FullName:  ��ȡWifi�豸������Ϣ
// Access:    public 
// Returns:   ����wifi������Ϣ
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI LPCWSTR GetWiFiErrorMessage();

//************************************
// Method:    GetWifiSignalStrength
// FullName:  ��ȡWifi�豸�ź�ǿ��
// Access:    public 
// Returns:   NETWORKMANAGERLIBAPI CEWIFISIGNALSTRENGTH
// Qualifier:
// Parameter: LPCWSTR deviceName (WIFI�豸����)
//************************************
NETWORKMANAGERLIBAPI CEWIFISIGNALSTRENGTH GetWifiSignalStrength(LPCWSTR deviceName);

//************************************
// Method:    ScanForBSSIDs
// FullName:  ���²����ȵ�PAN AP
// Access:    public 
// Returns:   ����TRUE�ɹ�������ʧ��
// Qualifier:
// Parameter: LPCWSTR deviceName (WIFI�豸����)
//************************************
NETWORKMANAGERLIBAPI BOOL ScanForBSSIDs(LPCWSTR deviceName);

//************************************
// Method:    GetBSSIDsNames
// FullName:  ��ȡ����SSID������
// Access:    public 
// Returns:   NETWORKMANAGERLIBAPI void
// Qualifier:
// Parameter: LPCWSTR deviceName (WIFI�豸����)
// Parameter: LPWSTR * bssids (����ȡ�õ�bssid ���ƣ�LPWSTR����,LPWSTR����Ϊ32,���鳤�����⾡�����ô�һ�����20)
// Parameter: DWORD & BSSIDCount (ȡ�õ�bassid ���� ����0Ϊû�л�ȡ)
//************************************
NETWORKMANAGERLIBAPI void GetBSSIDsNames(LPCWSTR deviceName,LPWSTR* bssids,DWORD& BSSIDCount);

//************************************
// Method:    GetWiFiConnectedStatus
// FullName:  ��ȡwifi�豸����״̬
// Access:    public 
// Returns:   NETWORKMANAGERLIBAPI BOOL: TRUE Ϊ����״̬��FALSE δ���� -1 ��ѯ״̬ʧ��
// Qualifier:
// Parameter: LPCWSTR deviceName (WIFI�豸����)
//************************************
NETWORKMANAGERLIBAPI BOOL GetWiFiConnectedStatus(LPCWSTR deviceName);

//************************************
// Method:    WIFIConnect
// FullName:  ����WIFI����
// Access:    public 
// Returns:   NETWORKMANAGERLIBAPI BOOL: TRUE ���ӳɹ� FALSE ����ʧ��
// Qualifier:
// Parameter: LPCWSTR deviceName (WIFI�豸����)
// Parameter: LPWSTR bssid   (AP ����)
// Parameter: SecurityType sectype (�������ְ�ȫ���� )
// Parameter: EncryptionType encrypttype (�������ּ�������)
// Parameter: ULONG securityIndex (��Կ�������� 1 - 4 һ����1)
// Parameter: TCHAR * key (����)
// Parameter: EAPType wpaeaptype (�������WPA_EAP��ȫģʽ��������EAP��������)
//************************************
NETWORKMANAGERLIBAPI BOOL WIFIConnect(LPCWSTR deviceName,LPWSTR bssid,SecurityType sectype,EncryptionType encrypttype,
									  ULONG securityIndex,TCHAR* key,EAPType wpaeaptype);

//************************************
// Method:    WIFIDisConnect
// FullName:  �Ͽ�WIFI ����
// Access:    public 
// Returns:   NETWORKMANAGERLIBAPI BOOL
// Qualifier:
// Parameter: LPCWSTR deviceName (WIFI�豸����)
//************************************
NETWORKMANAGERLIBAPI BOOL WIFIDisConnect(LPCWSTR deviceName);
#endif