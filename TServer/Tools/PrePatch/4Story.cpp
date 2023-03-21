// 4Story.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "4Story.h"
#include "4StoryDlg.h"
#include ".\4story.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStoryApp

BEGIN_MESSAGE_MAP(CStoryApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CStoryDlg* CStoryApp::m_Frame = NULL;
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
	SetRegistryKey(_T("4story Downloadr"));

	SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS );

	if(!m_Frame)
	{
		m_Frame = new CStoryDlg;
		if (!m_Frame)
			return FALSE;
		m_pMainWnd = m_Frame;

		m_Frame->Create(IDD_STORY_DIALOG,NULL);
		m_Frame->ShowWindow(SW_HIDE);
		m_Frame->UpdateWindow();
	}
	return TRUE;

}

int CStoryApp::ExitInstance()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	if(m_Frame)
	{
		delete m_Frame;
		m_Frame = NULL;
	}
	return CWinApp::ExitInstance();
}