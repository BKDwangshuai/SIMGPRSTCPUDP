#pragma once
#include "winsock.h"
#include "ansleTCPServerMain.h"

class ansleTCPCustom
{
public:
	ansleTCPCustom(void);
	~ansleTCPCustom(void);
private:
    //ͨѶ�̺߳���
	static DWORD WINAPI SocketThreadFunc(PVOID lparam);
public:
	//��socket������ͨѶ�߳�
	BOOL Open(ansleTCPServerMain *pTCPServer);
	//�ر�socket���ر��̣߳��ͷ�Socket��Դ
	BOOL Close();
public:
	//��������
	BOOL SendData(const char * buf , DWORD dwBufLen);
public:
	ansleTCPServerMain * m_TCPServer; //����TCP����˼���Socket
	CString m_RemoteHost; //Զ������IP��ַ
	DWORD m_RemotePort; //Զ�������˿ں�
	SOCKET m_socket;      //ͨѶSocket���
private:
	HANDLE m_exitThreadEvent;  //ͨѶ�߳��˳��¼����
	HANDLE m_tcpThreadHandle;  //ͨѶ�߳̾��
};
