// TChatFilter.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CTChatFilterApp:
// �� Ŭ������ ������ ���ؼ��� TChatFilter.cpp�� �����Ͻʽÿ�.
//

class CTChatFilterApp : public CWinApp
{
public:
	CTChatFilterApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()

};

extern CTChatFilterApp theApp;
