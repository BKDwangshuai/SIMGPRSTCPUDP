
// ansleTCPServerDlg.h : ͷ�ļ�
//

#pragma once
#include "ansleTCPServerMain.h"
#include "ansleTCPCustom.h"

//����ͨ�û�����
typedef struct  _DATA_BUF
{
	DWORD dwBufLen;
	char* sBuf;	
	TCHAR szAddress[MAX_PATH];
}DATA_BUF,*PDATA_BUF;


// CansleTCPServerDlg �Ի���
class CansleTCPServerDlg : public CDialog
{
// ����
public:
	CansleTCPServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ANSLETCPSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//TCP�������ݴ�����
	afx_msg LONG OnRecvTCPData(WPARAM wParam,LPARAM lParam);
	//�ͻ������ӶϿ���Ϣ����
	afx_msg LONG OnClientConnect(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	//����ansleTCPServerMain����
	ansleTCPServerMain m_tcpServer;

public:
	DWORD m_localPort;

private:
	//�ͻ������ӽ����¼�������
	static void CALLBACK	OnClientConnect(void* pOwner,ansleTCPCustom *pTcpCustom);
	//�ͻ���SOCKET�ر��¼�������
	static void  CALLBACK OnClientClose(void* pOwner,ansleTCPCustom*pTcpCustom);
	//���������յ����Կͻ��˵�����
	static  void CALLBACK OnClientRead(void* pOwner,ansleTCPCustom* pTcpCustom,const char * buf,DWORD dwBufLen );
	//�ͻ���Socket�����¼�������
	static  void CALLBACK OnClientError(void* pOwner,ansleTCPCustom* pTcpCustom,int nErrorCode);
	//��������Socket�����¼�������
	static void CALLBACK OnServerError(void* pOwner,ansleTCPServerMain* pansleTCPServerMain,int nErrorCode);

public:
	afx_msg void OnBnClickedBtnListen();
	afx_msg void OnBnClickedBtnClose();
};
