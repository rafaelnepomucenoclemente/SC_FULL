// 4Story.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CStoryApp:
// �� Ŭ������ ������ ���ؼ��� 4Story.cpp�� �����Ͻʽÿ�.
//

class CStoryApp : public CWinApp
{
public:
	CStoryApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()

protected:
	struct SCREENMODE
	{
		DWORD dwWidth;
		DWORD dwHeight;
		CString strMode;
	};

public:
	BYTE m_bOptionLevel;
	vector< SCREENMODE > m_vScreenMode;

public:
	void InsertResolution(DWORD dwWidth,DWORD dwHeight,CString strMode);
};

extern CStoryApp theApp;
