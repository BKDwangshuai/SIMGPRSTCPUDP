#pragma once
#include <winsock.h>
class ansleTCPCustom;
class ansleTCPServerMain;

//����ͻ������ӽ����¼�
typedef void (CALLBACK* ONCLIENTCONNECT)(void* pOwner,ansleTCPCustom*);
//����ͻ���SOCKET�ر��¼�
typedef void (CALLBACK* ONCLIENTCLOSE)(void* pOwner,ansleTCPCustom*);
//����ͻ��˵������ݽ����¼�
typedef void (CALLBACK* ONCLIENTREAD)(void* pOwner,ansleTCPCustom*,const char * buf,DWORD dwBufLen );
//����ͻ���Socket�����¼�
typedef void (CALLBACK* ONCLIENTERROR)(void* pOwner,ansleTCPCustom*,int nErrorCode);
//�����������Socket�����¼�
typedef void (CALLBACK* ONSERVERERROR)(void* pOwner,ansleTCPServerMain*,int nErrorCode);

class ansleTCPServerMain
{
public:
	ansleTCPServerMain(void);
	~ansleTCPServerMain(void);
	public:
  int m_LocalPort; //���÷���˿ں�
  void * m_pOwner;   //��������
private:
	SOCKET m_ServerSocket;     //TCP�������socket
	HANDLE m_serverThreadHandle;  //ͨѶ�߳̾��
	HANDLE m_exitThreadEvent;  //ͨѶ�߳��˳��¼����
public:  //�����¼�
	//�ͻ������ӽ����¼����ص�����
	ONCLIENTCONNECT    OnClientConnect;
	//�ͻ������ӶϿ��¼����ص�����
	ONCLIENTCLOSE OnClientClose;
	//�ͻ��˽��������¼����ص�����
	ONCLIENTREAD       OnClientRead;
	//�ͻ��˷��������¼����ص�����
	ONCLIENTERROR      OnClientError;
	//�������˷��������¼�,�ص�����
	ONSERVERERROR	   OnServerError;
private:
	//TCP�����������̺߳���
	static DWORD WINAPI SocketThreadFunc(PVOID lparam);
public:
	//ɾ���ͻ��˶���
	void RemoteClient(ansleTCPCustom *pClient /*�ͻ��˶���*/);
public:
	//��TCP����
	int Open();
public:
	//�ر�TCP����
	int Close();
public:
	//��������
	BOOL SendData(ansleTCPCustom* pCustom, const char * buf , DWORD dwBufLen);
};
