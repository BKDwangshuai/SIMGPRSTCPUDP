#pragma once

#include <winsock.h>
//#pragma comment(lib,"winsock.lib")

//�������ӶϿ��¼�
typedef void (CALLBACK* ONDISCONNECT)(void* pOwner);
//���嵱�����ݽ����¼�
typedef void (CALLBACK* ONREAD)(void* pOwner,const char * buf,DWORD dwBufLen );
//����Socket�����¼�
typedef void (CALLBACK* ONERROR)(void* pOwner,int nErrorCode);

class ansleTCPClient
{
public:
	ansleTCPClient(void);
	~ansleTCPClient(void);
public:
	//Զ������IP��ַ
	CString	 m_remoteHost;  
	//Զ�������˿�
    int      m_port;
	/*--���¿ͻ���ͨѶ�¼�--*/
	//���ӶϿ��¼����ص�����
	ONDISCONNECT OnDisConnect;
	//���������¼����ص�����
	ONREAD       OnRead;
	//���������¼����ص�����
	ONERROR      OnError;
private:
	//ͨѶSocket���
	SOCKET m_socket;      
	//ͨѶ�߳��˳��¼����
	HANDLE m_exitThreadEvent; 
	//ͨѶ�߳̾��
	HANDLE m_tcpThreadHandle;
	//��������
	void * m_pOwner;
	//���ջ�����
	char m_recvBuf[4096];
private:
    //ͨѶ�̺߳���
	static DWORD WINAPI SocketThreadFunc(LPVOID lparam);
public:
	//���ڴ򿪿ͻ���socket
	BOOL Open(void * pOwner);
public:
	//���ڹرտͻ���socket
	BOOL Close();
public:
	//���ڽ�����TCP����������
	BOOL Connect();
public:
	//��������˷�������
	BOOL SendData(const char * buf , DWORD dwBufLen);
};
