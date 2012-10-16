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
// FullName:  打开3G设备
// Access:    public 
// Returns:   打开3G设备成功返回true否则返回false
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI bool OpenEVDODevice();

//************************************
// Method:    CloseEVDODevice
// FullName:  关闭3G设备
// Access:    public 
// Returns:   关闭3G设备成功返回true否则返回false
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI bool CloseEVDODevice();

//************************************
// Method:    EVDO_Dial
// FullName:  3G 拨号
// Access:    public 
// Returns:   拨号成功返回true否则返回false
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI bool EVDO_Dial(LPCTSTR ConnectionName);

//************************************
// Method:    EVDO_Hangup
// FullName:  3G 断开连接
// Access:    public 
// Returns:   断开连接成功返回true否则返回false
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI bool EVDO_Hangup();

//************************************
// Method:    GetEVDOStatus
// FullName:  获取3G网络状态
// Access:    public 
// Returns:   返回值按RAS定义
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI int GetEVDOStatus();

//************************************
// Method:    GetWiFiStatus
// FullName:  获取WiFi设备状态
// Access:    public 
// Returns:   返回值
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI CEWIFISTATE GetWiFiStatus();

//************************************
// Method:    GetWiFiDeviceName
// FullName:  获取WIFI设备名称
// Access:    public 
// Returns:   如果得到wifi设备名称则返回名称字符串，否则返回为空串
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI LPCWSTR GetWiFiDeviceName();

//************************************
// Method:    GetWiFiErrorMessage
// FullName:  获取Wifi设备错误消息
// Access:    public 
// Returns:   返回wifi错误消息
// Qualifier:
//************************************
NETWORKMANAGERLIBAPI LPCWSTR GetWiFiErrorMessage();

//************************************
// Method:    GetWifiSignalStrength
// FullName:  获取Wifi设备信号强度
// Access:    public 
// Returns:   NETWORKMANAGERLIBAPI CEWIFISIGNALSTRENGTH
// Qualifier:
// Parameter: LPCWSTR deviceName (WIFI设备名称)
//************************************
NETWORKMANAGERLIBAPI CEWIFISIGNALSTRENGTH GetWifiSignalStrength(LPCWSTR deviceName);

//************************************
// Method:    ScanForBSSIDs
// FullName:  更新查找热点PAN AP
// Access:    public 
// Returns:   返回TRUE成功，否则失败
// Qualifier:
// Parameter: LPCWSTR deviceName (WIFI设备名称)
//************************************
NETWORKMANAGERLIBAPI BOOL ScanForBSSIDs(LPCWSTR deviceName);

//************************************
// Method:    GetBSSIDsNames
// FullName:  获取所有SSID的名称
// Access:    public 
// Returns:   NETWORKMANAGERLIBAPI void
// Qualifier:
// Parameter: LPCWSTR deviceName (WIFI设备名称)
// Parameter: LPWSTR * bssids (返回取得的bssid 名称，LPWSTR数组,LPWSTR长度为32,数组长度任意尽量设置大一点比如20)
// Parameter: DWORD & BSSIDCount (取得的bassid 数量 返回0为没有获取)
//************************************
NETWORKMANAGERLIBAPI void GetBSSIDsNames(LPCWSTR deviceName,LPWSTR* bssids,DWORD& BSSIDCount);

//************************************
// Method:    GetWiFiConnectedStatus
// FullName:  获取wifi设备连接状态
// Access:    public 
// Returns:   NETWORKMANAGERLIBAPI BOOL: TRUE 为连接状态、FALSE 未连接 -1 查询状态失败
// Qualifier:
// Parameter: LPCWSTR deviceName (WIFI设备名称)
//************************************
NETWORKMANAGERLIBAPI BOOL GetWiFiConnectedStatus(LPCWSTR deviceName);

//************************************
// Method:    WIFIConnect
// FullName:  建立WIFI连接
// Access:    public 
// Returns:   NETWORKMANAGERLIBAPI BOOL: TRUE 连接成功 FALSE 连接失败
// Qualifier:
// Parameter: LPCWSTR deviceName (WIFI设备名称)
// Parameter: LPWSTR bssid   (AP 名称)
// Parameter: SecurityType sectype (采用那种安全类型 )
// Parameter: EncryptionType encrypttype (采用那种加密类型)
// Parameter: ULONG securityIndex (密钥索引：从 1 - 4 一般是1)
// Parameter: TCHAR * key (口令)
// Parameter: EAPType wpaeaptype (如果采用WPA_EAP安全模式，则输入EAP加密类型)
//************************************
NETWORKMANAGERLIBAPI BOOL WIFIConnect(LPCWSTR deviceName,LPWSTR bssid,SecurityType sectype,EncryptionType encrypttype,
									  ULONG securityIndex,TCHAR* key,EAPType wpaeaptype);

//************************************
// Method:    WIFIDisConnect
// FullName:  断开WIFI 连接
// Access:    public 
// Returns:   NETWORKMANAGERLIBAPI BOOL
// Qualifier:
// Parameter: LPCWSTR deviceName (WIFI设备名称)
//************************************
NETWORKMANAGERLIBAPI BOOL WIFIDisConnect(LPCWSTR deviceName);
#endif