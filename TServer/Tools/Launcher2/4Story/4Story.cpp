// 4Story.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"

// CStoryApp
CStoryApp theApp;

BEGIN_MESSAGE_MAP(CStoryApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CStoryApp::CStoryApp()
{
}

BOOL CStoryApp::InitInstance()
{
	InitCommonControls();
	CWinApp::InitInstance();
	AfxEnableControlContainer();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	CStoryDlg dlg;
	
#ifdef _MODULPROTECTE
	if(!dlg.BeginProtect())
	{
		AfxMessageBox(IDS_ERROR_LOAD_FILE);
		return FALSE;
	}
#endif

	m_pMainWnd = &dlg;
	dlg.DoModal();
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//}

	return FALSE;
}

void CStoryApp::InsertResolution(DWORD dwWidth,DWORD dwHeight,CString strMode)
{
	SCREENMODE SCRMODE;
	SCRMODE.dwWidth = dwWidth;
	SCRMODE.dwHeight = dwHeight;
	SCRMODE.strMode = strMode;

	m_vScreenMode.push_back(SCRMODE);
}