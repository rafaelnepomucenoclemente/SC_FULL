// TMacroMachine.h : TMacroMachine ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"       // �� ��ȣ


// CTMacroMachineApp:
// �� Ŭ������ ������ ���ؼ��� TMacroMachine.cpp�� �����Ͻʽÿ�.
//

class CTMacroMachineApp : public CWinApp
{
public:
	CTMacroMachineApp();


// ������
public:
	virtual BOOL InitInstance();

// ����
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTMacroMachineApp theApp;
