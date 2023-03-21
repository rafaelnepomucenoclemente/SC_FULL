// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "TMacroMachine.h"

#include "MainFrm.h"
#include ".\mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE( WM_SESSION_MSG, OnSessionMSG) // WM_USER_MSG
	ON_MESSAGE( WM_SESSION_CLOSE, OnSessionClose)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	// TODO: ���� ������ ��ŷ�� �� ���� �Ϸ��� �� �� ���� �����Ͻʽÿ�.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	// Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return TRUE;
}


// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame �޽��� ó����
LRESULT CMainFrame::OnSessionMSG( WPARAM wParam, LPARAM lParam)
{	
	CTachyonSession* pSession = CTachyonSession::GetSession(wParam);
	if(!pSession)
		return 0;

	int nError = WSAGETSELECTERROR(lParam);

    if(pSession)
	{
		switch(WSAGETSELECTEVENT(lParam))
		{
		case FD_CONNECT	: 
			pSession->OnConnect(nError); 
			break;
		case FD_READ	: 
			pSession->PushTType(nError, TYPE_RECEIVE);
			break;
		case FD_CLOSE	: 
			if(pSession->GetConnectType() == CON_MAP)
				pSession->m_pOwner->OnClose(pSession, nError);
			int a = 0;
			break;
		}
	}

	return 0;
}
LRESULT CMainFrame::OnSessionClose( WPARAM wParam, LPARAM lParam)
{
	CTachyonSession* pSession = CTachyonSession::GetSession(wParam);
	int nError = WSAGETSELECTERROR(lParam);

	if(pSession && pSession->GetConnectType() == CON_MAP )
        pSession->m_pOwner->OnClose(pSession, nError);

	return 0;
}