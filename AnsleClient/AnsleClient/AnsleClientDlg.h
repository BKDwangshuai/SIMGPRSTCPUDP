
// AnsleClientDlg.h : ͷ�ļ�
//

#pragma once
#include "ansleTCPClient.h"

// CAnsleClientDlg �Ի���



class CAnsleClientDlg : public CDialog
{
// ����
public:
	CAnsleClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ANSLECLIENT_DIALOG };

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
	afx_msg LONG OnClientDisconnect(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	//����ansleTCPClient����
	ansleTCPClient m_tcpClient;
	ansleTCPClient m_tcpClient1;
	ansleTCPClient m_tcpClient2;
public:
	CString m_remoteHost;
	DWORD m_remotePort;
private:
	//���ӶϿ��¼�������
	static void CALLBACK OnDisConnect(void* pOwner);
	//�������ݽ����¼�������
	static void CALLBACK OnTcpRead(void* pOwner,const char * buf,DWORD dwBufLen );
	//Socket�����¼�������
	static void CALLBACK OnTcpError(void* pOwner,int nErrorCode);

private:
	//�õ����ص�IP��ַ
	CString GetLocalIP();
public:
	afx_msg void OnBnClickedBtnConn();
	afx_msg void OnBnClickedBtnDisconn();
	afx_msg void OnBnClickedBtnSenddata();
};
