// ServerState.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CServerStateApp:
// �� Ŭ������ ������ ���ؼ��� ServerState.cpp�� �����Ͻʽÿ�.
//

class CServerStateApp : public CWinApp
{
public:
	CServerStateApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CServerStateApp theApp;
