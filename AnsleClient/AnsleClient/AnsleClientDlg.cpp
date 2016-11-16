
// AnsleClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <stdlib.h>
#include "AnsleClient.h"
#include "AnsleClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//����TCP �ͻ��˽��յ�������Ϣ
#define WM_RECV_TCP_DATA WM_USER + 101
//����TCP�ͻ������ӶϿ���Ϣ
#define WM_TCP_CLIENT_DISCONNECT WM_USER + 102


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


// CAnsleClientDlg �Ի���




CAnsleClientDlg::CAnsleClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnsleClientDlg::IDD, pParent)
	, m_remoteHost(_T(""))
	, m_remotePort(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnsleClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_REMOTEHOST, m_remoteHost);
	DDX_Text(pDX, IDC_EDT_REMOTEPORT, m_remotePort);
}

BEGIN_MESSAGE_MAP(CAnsleClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_RECV_TCP_DATA,OnRecvTCPData)
	ON_MESSAGE(WM_TCP_CLIENT_DISCONNECT,OnClientDisconnect)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_CONN, &CAnsleClientDlg::OnBnClickedBtnConn)
	ON_BN_CLICKED(IDC_BTN_DISCONN, &CAnsleClientDlg::OnBnClickedBtnDisconn)
	ON_BN_CLICKED(IDC_BTN_SENDDATA, &CAnsleClientDlg::OnBnClickedBtnSenddata)
END_MESSAGE_MAP()


// CAnsleClientDlg ��Ϣ�������

BOOL CAnsleClientDlg::OnInitDialog()
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
	//��ʼ������ֵ
	m_remoteHost = GetLocalIP();
	m_remotePort = 5000;
	UpdateData(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CAnsleClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAnsleClientDlg::OnPaint()
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
HCURSOR CAnsleClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//���ӶϿ��¼�
void CALLBACK CAnsleClientDlg::OnDisConnect(void* pOwner)
{
	//�õ�������ָ��
	CAnsleClientDlg* pThis = (CAnsleClientDlg*)pOwner;
	//������Ϣ��ʾ�ͻ������ӶϿ�
	pThis->PostMessage(WM_TCP_CLIENT_DISCONNECT,0,0);
}

//���ݽ����¼�
void CALLBACK CAnsleClientDlg::OnTcpRead(void* pOwner,const char * buf,DWORD dwBufLen )
{
	BYTE *pRecvBuf = NULL; //���ջ�����
	//�õ�������ָ��
	CAnsleClientDlg* pThis = (CAnsleClientDlg*)pOwner;
	//�����յĻ�����������pRecvBuf��
	pRecvBuf = new BYTE[dwBufLen];
	CopyMemory(pRecvBuf,buf,dwBufLen);

	//�����첽��Ϣ����ʾ�յ�TCP���ݣ���Ϣ�����꣬Ӧ�ͷ��ڴ�
	pThis->PostMessage(WM_RECV_TCP_DATA,WPARAM(pRecvBuf),dwBufLen);

}

//Socket�����¼�
void CALLBACK CAnsleClientDlg::OnTcpError(void* pOwner,int nErrorCode)
{
	TRACE(L"�ͻ���socket��������");
}

//TCP�������ݴ�����
LONG CAnsleClientDlg::OnRecvTCPData(WPARAM wParam,LPARAM lParam)
{
	CString strOldRecv = L"";
	CString strRecv = L"";
	//���յ���BUF
	CHAR *pBuf = (CHAR*)wParam;
	//���յ���BUF����
	DWORD dwBufLen = lParam;
	//���տ�
	CEdit *pEdtRecvMsg = (CEdit*)GetDlgItem(IDC_EDT_RECV);
	ASSERT(pEdtRecvMsg != NULL);

	//�õ����տ��е���ʷ�ı�
	pEdtRecvMsg->GetWindowTextW(strOldRecv);
	//
	strRecv = CString(pBuf);
	//���½��յ����ı���ӵ����տ���
	strOldRecv = strOldRecv + strRecv + L"\r\n";
	pEdtRecvMsg->SetWindowTextW(strOldRecv);

	//�ͷ��ڴ�
	delete[] pBuf;
	pBuf = NULL;
	return 0;
}

//�ͻ������ӶϿ���Ϣ����
LONG CAnsleClientDlg::OnClientDisconnect(WPARAM wParam,LPARAM lParam)
{
	//�õ�״̬����ǩ
	CStatic * pStatus = (CStatic *)GetDlgItem(IDC_LBL_CONNSTATUS);
	ASSERT(pStatus != NULL);

	pStatus->SetWindowText(_T("���ӶϿ�"));
	return 0;
}

void CAnsleClientDlg::OnBnClickedBtnConn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CStatic *pStatus = (CStatic*)GetDlgItem(IDC_LBL_CONNSTATUS);
	ASSERT(pStatus != NULL);
	//����m_tcpClient����
	m_tcpClient.m_remoteHost = m_remoteHost;
	m_tcpClient.m_port = m_remotePort;
	m_tcpClient.OnDisConnect = OnDisConnect;
	m_tcpClient.OnRead = OnTcpRead;
	m_tcpClient.OnError = OnTcpError;
	//�򿪿ͻ���socket
	m_tcpClient.Open(this);

	//�����������������
	if (m_tcpClient.Connect())
	{

		pStatus->SetWindowText(L"��������");
		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("��������ʧ��"));
		pStatus->SetWindowText(L"���ӶϿ�");
		return;
	}

	//����m_tcpClient����
	m_tcpClient1.m_remoteHost = m_remoteHost;
	m_tcpClient1.m_port = m_remotePort;
	m_tcpClient1.OnDisConnect = OnDisConnect;
	m_tcpClient1.OnRead = OnTcpRead;
	m_tcpClient1.OnError = OnTcpError;
	//�򿪿ͻ���socket
	m_tcpClient1.Open(this);

	//�����������������
	if (m_tcpClient1.Connect())
	{

		pStatus->SetWindowText(L"��������");
		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("��������ʧ��"));
		pStatus->SetWindowText(L"���ӶϿ�");
		return;
	}
	//����m_tcpClient����
	m_tcpClient2.m_remoteHost = m_remoteHost;
	m_tcpClient2.m_port = m_remotePort;
	m_tcpClient2.OnDisConnect = OnDisConnect;
	m_tcpClient2.OnRead = OnTcpRead;
	m_tcpClient2.OnError = OnTcpError;
	//�򿪿ͻ���socket
	m_tcpClient2.Open(this);

	//�����������������
	if (m_tcpClient2.Connect())
	{

		pStatus->SetWindowText(L"��������");
		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("��������ʧ��"));
		pStatus->SetWindowText(L"���ӶϿ�");
		return;
	}
}

void CAnsleClientDlg::OnBnClickedBtnDisconn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStatic *pStatus = (CStatic*)GetDlgItem(IDC_LBL_CONNSTATUS);
	ASSERT(pStatus != NULL);
	//�رտͻ����׽���
	if (m_tcpClient.Close())
	{
		pStatus->SetWindowText(L"���ӶϿ�");
		KillTimer(1); 
	}
	else
	{
		AfxMessageBox(_T("���ӶϿ�ʧ��"));
	}	
	if (m_tcpClient1.Close())
	{
		pStatus->SetWindowText(L"���ӶϿ�");
	}
	else
	{
		AfxMessageBox(_T("���ӶϿ�ʧ��"));
	}	
	if (m_tcpClient2.Close())
	{
		pStatus->SetWindowText(L"���ӶϿ�");
	}
	else
	{
		AfxMessageBox(_T("���ӶϿ�ʧ��"));
	}	
}

void CAnsleClientDlg::OnBnClickedBtnSenddata()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strSendData;
	char * sendBuf;
	int sendLen=0;
	CEdit *pEdtSend = (CEdit*)GetDlgItem(IDC_EDT_SEND);
	pEdtSend->GetWindowTextW(strSendData);

	//���÷��ͻ�����
	sendLen = strSendData.GetLength()*2 + 2;
	sendBuf = new char[sendLen];
	ZeroMemory(sendBuf,sendLen);
	wcstombs(sendBuf,strSendData,sendLen);
	sendLen = strlen(sendBuf)+1;
	//��������
	if (!m_tcpClient.SendData(sendBuf,sendLen))
	{
		AfxMessageBox(_T("����ʧ��"));
	}
	//��������
	if (!m_tcpClient1.SendData(sendBuf,sendLen))
	{
		AfxMessageBox(_T("����ʧ��"));
	}
	//��������
	if (!m_tcpClient2.SendData(sendBuf,sendLen))
	{
		AfxMessageBox(_T("����ʧ��"));
	}
	//�ͷ��ڴ�
	delete[] sendBuf;
	sendBuf = NULL;		
}

CString CAnsleClientDlg::GetLocalIP()
{
	HOSTENT *LocalAddress;
	char	*Buff;
	TCHAR	*wBuff;
	CString strReturn = _T("");

	//�����µĻ�����
	Buff = new char[256];
	wBuff = new TCHAR[256];
	//�ÿջ�����
	memset(Buff, '\0', 256);
	memset(wBuff, TEXT('\0'), 256*sizeof(TCHAR));
	//�õ����ؼ������
	if (gethostname(Buff, 256) == 0)
	{
		//ת����˫�ֽ��ַ���
		mbstowcs(wBuff, Buff, 256);
		//�õ����ص�ַ
		LocalAddress = gethostbyname(Buff);
		//�ÿ�buff
		memset(Buff, '\0', 256);
		//��ϱ���IP��ַ
		sprintf(Buff, "%d.%d.%d.%d\0", LocalAddress->h_addr_list[0][0] & 0xFF,
			LocalAddress->h_addr_list[0][1] & 0x00FF, LocalAddress->h_addr_list[0][2] & 0x0000FF, LocalAddress->h_addr_list[0][3] & 0x000000FF);
		//�ÿ�wBuff
		memset(wBuff, TEXT('\0'), 256*sizeof(TCHAR));
		//ת����˫�ֽ��ַ���
		mbstowcs(wBuff, Buff, 256);
		//���÷���ֵ
		strReturn = wBuff;
	}
	else
	{
	}

	//�ͷ�Buff������
	delete[] Buff;
	Buff = NULL;
	//�ͷ�wBuff������
	delete[] wBuff;
	wBuff = NULL;
	return strReturn;
}
/////////////////////////////////////////////////////////