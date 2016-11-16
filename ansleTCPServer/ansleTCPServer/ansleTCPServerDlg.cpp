
// ansleTCPServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ansleTCPServer.h"
#include "ansleTCPServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//����TCP �յ��ͻ���������Ϣ
#define WM_RECV_TCP_DATA WM_USER + 101
//����TCP�ͻ���������Ϣ
#define WM_TCP_CLIENT_CONNECT WM_USER + 102

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CansleTCPServerDlg �Ի���




CansleTCPServerDlg::CansleTCPServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CansleTCPServerDlg::IDD, pParent)
	,m_localPort(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CansleTCPServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_LOCALPORT, m_localPort);
}

BEGIN_MESSAGE_MAP(CansleTCPServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_RECV_TCP_DATA,OnRecvTCPData)
	ON_MESSAGE(WM_TCP_CLIENT_CONNECT,OnClientConnect)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_LISTEN, &CansleTCPServerDlg::OnBnClickedBtnListen)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CansleTCPServerDlg::OnBnClickedBtnClose)
END_MESSAGE_MAP()


// CansleTCPServerDlg ��Ϣ�������

BOOL CansleTCPServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//����Ĭ��ֵ
	m_localPort = 5000;
	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CansleTCPServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CansleTCPServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CansleTCPServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�ͻ������ӽ����¼�������
void CALLBACK  CansleTCPServerDlg::OnClientConnect(void* pOwner,ansleTCPCustom* pTcpCustom)
{
	TCHAR *szAddress =NULL;
	DWORD dwBufLen = pTcpCustom->m_RemoteHost.GetLength() + 1;
	szAddress = new TCHAR[dwBufLen];
	ZeroMemory(szAddress,dwBufLen*2);
	//�����ڴ棬�õ��ͻ���IP��ַ
	wcscpy(szAddress,pTcpCustom->m_RemoteHost);
	
	CansleTCPServerDlg *pThis = (CansleTCPServerDlg*)pOwner;
	
	//�����첽��Ϣ����ʾ�пͻ������ӣ���Ϣ���������Ҫ�ͷ��ڴ�
	pThis->PostMessage(WM_TCP_CLIENT_CONNECT,0,LPARAM(szAddress));
}

//�ͻ���SOCKET�ر��¼�������
void  CALLBACK CansleTCPServerDlg::OnClientClose(void* pOwner,ansleTCPCustom* pTcpCustom)
{
	TCHAR *szAddress =NULL;
	DWORD dwBufLen = pTcpCustom->m_RemoteHost.GetLength() + 1;
	szAddress = new TCHAR[dwBufLen];
	ZeroMemory(szAddress,dwBufLen*2);
	//�����ڴ棬�õ��ͻ���IP��ַ
	wcscpy(szAddress,pTcpCustom->m_RemoteHost);

	CansleTCPServerDlg *pThis = (CansleTCPServerDlg*)pOwner;
	
	//�����첽��Ϣ����ʾ�пͻ������ӣ���Ϣ���������Ҫ�ͷ��ڴ�
	pThis->PostMessage(WM_TCP_CLIENT_CONNECT,1,LPARAM(szAddress));

}

//���������յ����Կͻ��˵�����
void CALLBACK CansleTCPServerDlg::OnClientRead(void* pOwner,ansleTCPCustom* pTcpCustom,const char * buf,DWORD dwBufLen )
{
	DATA_BUF *pGenBuf = new DATA_BUF;
	char *pRecvBuf = NULL; //���ջ�����
	//�õ�������ָ��
	CansleTCPServerDlg* pThis = (CansleTCPServerDlg*)pOwner;
	//�����յĻ�����������pRecvBuf��
	pRecvBuf = new char[dwBufLen];
	CopyMemory(pRecvBuf,buf,dwBufLen);

	ZeroMemory(pGenBuf,sizeof(DATA_BUF));
	pGenBuf->dwBufLen = dwBufLen;
	pGenBuf->sBuf = pRecvBuf;
	
	//
	wcscpy(pGenBuf->szAddress,pTcpCustom->m_RemoteHost);

	//�����첽��Ϣ����ʾ�յ�TCP���ݣ���Ϣ�����꣬Ӧ�ͷ��ڴ�
	pThis->PostMessage(WM_RECV_TCP_DATA,WPARAM(pGenBuf),LPARAM(pTcpCustom));

   
}

//�ͻ���Socket�����¼�������
void CALLBACK CansleTCPServerDlg::OnClientError(void* pOwner,ansleTCPCustom* pTcpCustom,int nErrorCode)
{
	
}

//��������Socket�����¼�������
void CALLBACK CansleTCPServerDlg::OnServerError(void* pOwner,ansleTCPServerMain* pansleTCPServerMain,int nErrorCode)
{
	
}

//TCP�������ݴ�����
LONG CansleTCPServerDlg::OnRecvTCPData(WPARAM wParam,LPARAM lParam)
{
	DATA_BUF *pGenBuf = (DATA_BUF*)wParam; //ͨ�û�����
	ansleTCPCustom* pTcpCustom= (ansleTCPCustom* )lParam; //TCP�ͻ��˶���
	//������ʾ�б�
	CListBox * pLstRecv = (CListBox*)GetDlgItem(IDC_LST_RECV);
	ASSERT(pLstRecv != NULL);
	//���յ�������
	CString strRecv;
	CString strLen;
	strLen.Format(L"%d",pGenBuf->dwBufLen);
	strRecv = CString(pGenBuf->sBuf);
	
	pLstRecv->AddString(_T("************************************"));
	pLstRecv->AddString(_T("����: ") + CString(pGenBuf->szAddress) );
	pLstRecv->AddString(_T("���ݳ���:")+strLen);
	pLstRecv->AddString(strRecv);

	//���ͻ�Ӧ����
	if (!m_tcpServer.SendData(pTcpCustom,"recv ok",strlen("recv ok")))
	{
		AfxMessageBox(_T("����ʧ��"));
	}

	//�ͷ��ڴ�
	delete[] pGenBuf->sBuf;
	pGenBuf->sBuf = NULL;
	delete pGenBuf;
	pGenBuf = NULL;
	return 0;
}

//�ͻ������ӶϿ���Ϣ����
LONG CansleTCPServerDlg::OnClientConnect(WPARAM wParam,LPARAM lParam)
{
	int iIndex = 0;
	TCHAR *szAddress = (TCHAR*)lParam;
	CString strAddrss = szAddress;
	
	CListBox * pLstConn = (CListBox*)GetDlgItem(IDC_LST_CONN);
	ASSERT(pLstConn != NULL);

	if (wParam == 0)
	{
		pLstConn->AddString(strAddrss + L"��������");
	}
	else
	{
		iIndex = pLstConn->FindString(iIndex,strAddrss + L"��������");
		if (iIndex != LB_ERR)
		{
			pLstConn->DeleteString(iIndex); 
		}
	}

	//�ͷ��ڴ�
	delete[] szAddress;
	szAddress = NULL;
	return 0;
}


//����
void CansleTCPServerDlg::OnBnClickedBtnListen()
{
	UpdateData(TRUE);
	//����m_tcpServer����
   	m_tcpServer.m_LocalPort = m_localPort;
	m_tcpServer.m_pOwner = this;
	m_tcpServer.OnClientConnect = OnClientConnect;
	m_tcpServer.OnClientClose = OnClientClose;
	m_tcpServer.OnClientRead = OnClientRead;
	m_tcpServer.OnClientError = OnClientError;
	m_tcpServer.OnServerError = OnServerError;
	if (m_tcpServer.Open() <= 0)
	{
		AfxMessageBox(_T("����ʧ��"));
		return;
	}
}


//�ر�
void CansleTCPServerDlg::OnBnClickedBtnClose()
{
	CListBox * pLstConn = (CListBox*)GetDlgItem(IDC_LST_CONN);
	ASSERT(pLstConn != NULL);
	
	CListBox * pLstRecv = (CListBox*)GetDlgItem(IDC_LST_RECV);
	ASSERT(pLstRecv != NULL);
	
	//
	if (m_tcpServer.Close() <=0)
	{
		AfxMessageBox(_T("�ر�TCP������ʧ��"));
		return;
	}
	
	//����б�
	pLstConn->ResetContent();
	pLstRecv->ResetContent();
}
