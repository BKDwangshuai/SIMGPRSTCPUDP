
// AnsleClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAnsleClientApp:
// �йش����ʵ�֣������ AnsleClient.cpp
//

class CAnsleClientApp : public CWinAppEx
{
public:
	CAnsleClientApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAnsleClientApp theApp;