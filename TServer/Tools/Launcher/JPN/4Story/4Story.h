// 4Story.h : PROJECT_NAME ����E���α׷��� ��E?�� ?E�E�����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ�E��E?'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CStoryApp:
// �� Ŭ������ ������ ��Eؼ??4Story.cpp�� E��Ͻʽÿ?
//

class CStoryApp : public CWinApp
{
public:
	CStoryApp();

// ������
	public:
	virtual BOOL InitInstance();

// ��?E

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
