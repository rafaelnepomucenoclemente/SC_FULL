// Mempiece.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CMempieceApp:
// �� Ŭ������ ������ ���ؼ��� Mempiece.cpp�� �����Ͻʽÿ�.
//

class CMempieceApp : public CWinApp
{
public:
	CMempieceApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CMempieceApp theApp;
