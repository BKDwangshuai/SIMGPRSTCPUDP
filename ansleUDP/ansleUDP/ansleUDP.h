
// ansleUDP.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CansleUDPApp:
// �йش����ʵ�֣������ ansleUDP.cpp
//

class CansleUDPApp : public CWinAppEx
{
public:
	CansleUDPApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CansleUDPApp theApp;