// SvrTester.h : SvrTester ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"       // �� ��ȣ

#include "STType.h"			// SvrTester Type

#include "TSessionFrm.h"
#include "TSessionView.h"

#include "TMacroFrm.h"
#include "TMacroView.h"

// CSvrTesterApp:
// �� Ŭ������ ������ ���ؼ��� SvrTester.cpp�� �����Ͻʽÿ�.
//

class CSvrTesterApp : public CWinApp
{
public:
	CSvrTesterApp();
	~CSvrTesterApp();


// ������
public:
	virtual BOOL InitInstance();

// ����
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	MAPDOCTEMP m_mapDocTemp; // STType.h �� ����
	CMultiDocTemplate* GetDocTemplate(int nPageID); // DocTemplate ����
	/////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////
	// TSessionView / TSessionFrm Return
	CTSessionView* GetTSessionView(); 	
	CTSessionFrm* GetTSessionFrm();
	CTSessionFrm* pTSessionFrm; // TSessionFrm�� Ŭ����������
	/////////////////////////////////////////////////////////////////////////////////////	

	/////////////////////////////////////////////////////////////////////////////////////	
	// TMacroView / TMacroFrm Return
	CTMacroView* GetTMacroView();	
	CTMacroFrm* GetTMacroFrm();
	CTMacroFrm* pTMacroFrm;	
	/////////////////////////////////////////////////////////////////////////////////////	
};

extern CSvrTesterApp theApp;
