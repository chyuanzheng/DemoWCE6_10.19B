// AppClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AppClient.h"
#include "AppClientDlg.h"
#include <winsock2.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAppClientDlg 对话框

CAppClientDlg::CAppClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAppClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAppClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAppClientDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CAppClientDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAppClientDlg 消息处理程序

BOOL CAppClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//OnBnClickedButton1();
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CAppClientDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_APPCLIENT_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_APPCLIENT_DIALOG));
	}
}
#endif

#define SERVERPORT			5556			//服务器TCP端口
#define	BUF_SZIE	64
void CAppClientDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	WSADATA			wsd;			//WSADATA变量
	SOCKET			sHost;			//服务器套接字
	SOCKADDR_IN		servAddr;		//服务器地址
	char			buf[BUF_SZIE];	//接收数据缓冲区
	int				retVal;			//返回值

	//初始化套结字动态库
	if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
	{
		printf("WSAStartup failed!\n");
	}

	//创建套接字
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	
	if(INVALID_SOCKET == sHost)
	{
		printf("socket failed!\n");
		WSACleanup();//释放套接字资源
	}

	//设置服务器地址
	servAddr.sin_family =AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons((short)SERVERPORT);
	int	nServAddlen  = sizeof(servAddr);

	//连接服务器
	retVal=connect(sHost,(LPSOCKADDR)&servAddr, sizeof(servAddr));	
	if(SOCKET_ERROR == retVal)
	{
		printf("connect failed!\n");	
		closesocket(sHost);	//关闭套接字
		WSACleanup();		//释放套接字资源
	}

	//向服务器发送数据
	ZeroMemory(buf, BUF_SZIE);
	strcpy(buf, "MyTCP");
	retVal = send(sHost, buf, strlen(buf), 0);
	if (SOCKET_ERROR == retVal)
	{
		printf("send failed!\n");
		closesocket(sHost);	//关闭套接字
		WSACleanup();		//释放套接字资源
	}

	//退出
	closesocket(sHost);	//关闭套接字
	WSACleanup();		//释放套接字资源
}
