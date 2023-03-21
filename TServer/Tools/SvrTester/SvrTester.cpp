// SvrTester.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "SvrTester.h"
#include "MainFrm.h"

#include "TSessionDoc.h"
#include "TMacroDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSvrTesterApp

BEGIN_MESSAGE_MAP(CSvrTesterApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CSvrTesterApp ����

CSvrTesterApp::CSvrTesterApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

CSvrTesterApp::~CSvrTesterApp()
{
	m_mapDocTemp.clear();
}



// ������ CSvrTesterApp ��ü�Դϴ�.

CSvrTesterApp theApp;

// CSvrTesterApp �ʱ�ȭ

BOOL CSvrTesterApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControls()�� �ʿ��մϴ�. 
	// InitCommonControls()�� ������� ������ â�� ���� �� �����ϴ�.
	InitCommonControls();

	CWinApp::InitInstance();

	// OLE ���̺귯���� �ʱ�ȭ�մϴ�.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.
	// ���� ���α׷��� ���� ���ø��� ����մϴ�. ���� ���ø���
	// ����, ������ â �� �� ������ ���� ������ �մϴ�.

	//////////////////////////////////////////////////////////////////////////////////
	CMultiDocTemplate* pDocTemplate1;
	pDocTemplate1 = new CMultiDocTemplate(IDR_SvrTesterTYPE,
		RUNTIME_CLASS(CTSessionDoc),
		RUNTIME_CLASS(CTSessionFrm), // ����� ���� MDI �ڽ� �������Դϴ�.
		RUNTIME_CLASS(CTSessionView));
	if (!pDocTemplate1)
		return FALSE;
	AddDocTemplate(pDocTemplate1);

	// m_mapView�� ����
	m_mapDocTemp.insert(MAPDOCTEMP::value_type(TSESSION, pDocTemplate1)); 

	CMultiDocTemplate* pDocTemplate2;
	pDocTemplate2 = new CMultiDocTemplate(IDR_SvrTesterTYPE,
		RUNTIME_CLASS(CTMacroDoc),
		RUNTIME_CLASS(CTMacroFrm), // ����� ���� MDI �ڽ� �������Դϴ�.
		RUNTIME_CLASS(CTMacroView));
	if (!pDocTemplate2)
		return FALSE;
	AddDocTemplate(pDocTemplate2);

	// m_mapView�� ����
	m_mapDocTemp.insert(MAPDOCTEMP::value_type(TMACRO, pDocTemplate2)); 
	//////////////////////////////////////////////////////////////////////////////////

	// �� MDI ������ â�� ����ϴ�.
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	// MDI ���� ���α׷������� m_pMainWnd�� ������ �� �ٷ� �̷��� ȣ���� �߻��ؾ� �մϴ�.
	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if( cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew ) // OnFileNew ������Ѵ�.
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// ����ٿ� ������ ����� ����ġ�մϴ�. ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �� â�� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.	
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED); // ��üâũ��
	pMainFrame->UpdateWindow();

	pDocTemplate2->OpenDocumentFile(NULL); // ������ ����.	
	pDocTemplate1->OpenDocumentFile(NULL); // ������ ����.

	return TRUE;
}



// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CSvrTesterApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSvrTesterApp �޽��� ó����

// DocTemplate ����
CMultiDocTemplate* CSvrTesterApp::GetDocTemplate(int nPageID)
{
	MAPDOCTEMP::iterator finder = m_mapDocTemp.find(nPageID);
	return (*finder).second;
}

/////////////////////////////////////////////////////////////////////////////////////
// TSessionView / TSessionFrm Return
CTSessionView* CSvrTesterApp::GetTSessionView() 
{
    MAPDOCTEMP::iterator finder = m_mapDocTemp.find(0);
	POSITION pos = (*finder).second->GetFirstDocPosition();
	CDocument* pDoc = (*finder).second->GetNextDoc(pos);
	if(!pDoc) 
		return NULL;

	pos = pDoc->GetFirstViewPosition();
	CTSessionView* pView = (CTSessionView*)pDoc->GetNextView(pos);
	return pView;
}
CTSessionFrm* CSvrTesterApp::GetTSessionFrm() 
{    
	return pTSessionFrm;
}
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
// TMacroView / TMacroFrm Return
CTMacroView* CSvrTesterApp::GetTMacroView() 
{   
	MAPDOCTEMP::iterator finder = m_mapDocTemp.find(1);
	POSITION pos = (*finder).second->GetFirstDocPosition();
	CDocument* pDoc = (*finder).second->GetNextDoc(pos);
	if(!pDoc) 
		return NULL;

	pos = pDoc->GetFirstViewPosition();
	CTMacroView* pView = (CTMacroView*)pDoc->GetNextView(pos);
	return pView;	
}	
CTMacroFrm* CSvrTesterApp::GetTMacroFrm() 
{    
	return pTMacroFrm;
}
/////////////////////////////////////////////////////////////////////////////////////