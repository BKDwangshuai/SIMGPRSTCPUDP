
// ansleUDPDlg.h : ͷ�ļ�
//

#pragma once
#include "ansleUDPClass.h"

//UDP ����������Ϣ
#define WM_RECV_UDP_DATA WM_USER + 101

// CansleUDPDlg �Ի���
class CansleUDPDlg : public CDialog
{
// ����
public:
	CansleUDPDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ANSLEUDP_DIALOG };

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
	// UDP�������ݴ�����
	afx_msg LONG OnRecvUdpData(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	//UDP���������¼�
	static void CALLBACK OnUdpCERecv(void * pOwner,char* buf,DWORD dwBufLen,sockaddr * addr);
	//UDPͨѶ�����¼�
	static void CALLBACK OnUdpCEError(void * pOwner,int nErrorCode);
public:
	CString m_RemoteHost;
	int m_RemotePort;
	int m_LocalPort;
private:
	//����UDPͨѶ�����
	ansleUDPClass m_CEUdp;

public:
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnSend();

};
