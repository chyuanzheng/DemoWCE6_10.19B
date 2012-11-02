// AppClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AppClient.h"
#include "AppClientDlg.h"
#include <winsock2.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAppClientDlg �Ի���

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


// CAppClientDlg ��Ϣ�������

BOOL CAppClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//OnBnClickedButton1();
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

#define SERVERPORT			5556			//������TCP�˿�
#define	BUF_SZIE	64
void CAppClientDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	WSADATA			wsd;			//WSADATA����
	SOCKET			sHost;			//�������׽���
	SOCKADDR_IN		servAddr;		//��������ַ
	char			buf[BUF_SZIE];	//�������ݻ�����
	int				retVal;			//����ֵ

	//��ʼ���׽��ֶ�̬��
	if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
	{
		printf("WSAStartup failed!\n");
	}

	//�����׽���
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	
	if(INVALID_SOCKET == sHost)
	{
		printf("socket failed!\n");
		WSACleanup();//�ͷ��׽�����Դ
	}

	//���÷�������ַ
	servAddr.sin_family =AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons((short)SERVERPORT);
	int	nServAddlen  = sizeof(servAddr);

	//���ӷ�����
	retVal=connect(sHost,(LPSOCKADDR)&servAddr, sizeof(servAddr));	
	if(SOCKET_ERROR == retVal)
	{
		printf("connect failed!\n");	
		closesocket(sHost);	//�ر��׽���
		WSACleanup();		//�ͷ��׽�����Դ
	}

	//���������������
	ZeroMemory(buf, BUF_SZIE);
	strcpy(buf, "MyTCP");
	retVal = send(sHost, buf, strlen(buf), 0);
	if (SOCKET_ERROR == retVal)
	{
		printf("send failed!\n");
		closesocket(sHost);	//�ر��׽���
		WSACleanup();		//�ͷ��׽�����Դ
	}

	//�˳�
	closesocket(sHost);	//�ر��׽���
	WSACleanup();		//�ͷ��׽�����Դ
}
