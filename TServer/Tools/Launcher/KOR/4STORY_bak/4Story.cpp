// 4Story.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "4Story.h"
#include "4StoryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStoryApp

BEGIN_MESSAGE_MAP(CStoryApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CStoryApp ����

CStoryApp::CStoryApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CStoryApp ��ü�Դϴ�.

CStoryApp theApp;


// CStoryApp �ʱ�ȭ

BOOL CStoryApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControls()�� �ʿ��մϴ�. 
	// InitCommonControls()�� ������� ������ â�� ���� �� �����ϴ�.
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
	dlg.ReadRegistry();

	SetCurrentDirectory( dlg.GetLocalString() );

	if(!dlg.BeginProtect())
	{
		CString strTITLE;
		CString strMSG;

		strMSG.LoadString(IDS_ERROR_LOAD_FILE);
		MessageBox( NULL, strMSG, APP_NAME, MB_OK);

		return FALSE;
	}

	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ ��ȭ ���ڰ� Ȯ���� ���� �������� ��� ó����
		// �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ ��ȭ ���ڰ� ��Ҹ� ���� �������� ��� ó����
		// �ڵ带 ��ġ�մϴ�.
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�
	// ���� ���α׷��� ���� �� �ֵ��� FALSE�� ��ȯ�մϴ�.
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


void CStoryApp::LoadStdProfileSettings()
{
	CWinApp::LoadStdProfileSettings();

	((CStoryDlg *) m_pMainWnd)->m_strPARAM = GetProfileString(
		_T("Config"),
		_T("PARAM"),
		_T(""));
}

void CStoryApp::SaveStdProfileSettings()
{
	CWinApp::SaveStdProfileSettings();

	WriteProfileString(
		_T("Config"),
		_T("PARAM"),
		LPCSTR(((CStoryDlg *) m_pMainWnd)->m_strPARAM));
}
