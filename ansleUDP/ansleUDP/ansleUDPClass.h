#pragma once
#include "winsock.h"


//UDP�ͻ��˷��ʹ���ص�����
typedef void (CALLBACK* ONUDPERROR)(void*,int nErrorCode);
//UDP�ͻ��˽������ݻص�����
typedef void (CALLBACK* ONUDPRECV)(void*,char* buf,DWORD dwBufLen,sockaddr* saRecvAddress);

class ansleUDPClass
{
public:
	ansleUDPClass(void);
	~ansleUDPClass(void);
public:
	//��UDPͨѶ
    DWORD Open(void* pOwner,int localPort, LPCTSTR remoteHost ,int remotePort);
	//�ر�UDPͨѶ
	DWORD Close(void);
	//��������
	DWORD SendData(const char *buf, int len);
private:
	//ͨѶ�̺߳���
	static UINT RecvThread(LPVOID lparam);
private:
	SOCKET m_UDPSocket;                   		//UDP SocketͨѶ�׽���
	struct sockaddr_in m_RemoteAddr;     	//�洢Զ��ͨѶ��ַ
	HANDLE m_ExitThreadEvent;            	//�߳��˳��¼�
	void * m_pOwner;                  		//�洢��������
	char m_recvBuf[4096] ;					//�������ݻ�����
public:
	//UDP���������¼�
	ONUDPERROR m_OnUdpError;
	//UDP���������¼�
	ONUDPRECV  m_OnUdpRecv;
};
