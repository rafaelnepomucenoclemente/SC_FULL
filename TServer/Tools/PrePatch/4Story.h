// 4Story.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ

class CStoryApp : public CWinApp
{
public:
	CStoryApp();

	static CStoryDlg* m_Frame;
	
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	DECLARE_MESSAGE_MAP()
};

extern CStoryApp theApp;
