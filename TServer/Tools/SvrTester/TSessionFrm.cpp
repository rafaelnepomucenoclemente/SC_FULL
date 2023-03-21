// TSessionFrm.cpp : CTSessionFrm Ŭ������ ����
//
#include "stdafx.h"
#include "SvrTester.h"

#include "TSessionFrm.h"
#include ".\tsessionfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTSessionFrm

IMPLEMENT_DYNCREATE(CTSessionFrm, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CTSessionFrm, CMDIChildWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CTSessionFrm ����/�Ҹ�

CTSessionFrm::CTSessionFrm()
{
	
}

CTSessionFrm::~CTSessionFrm()
{	
}


BOOL CTSessionFrm::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡�� Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


// CTSessionFrm ����

#ifdef _DEBUG
void CTSessionFrm::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CTSessionFrm::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG


// CTSessionFrm �޽��� ó����

void CTSessionFrm::ActivateFrame(int nCmdShow)
{
	CMDIChildWnd::ActivateFrame(SW_SHOWMAXIMIZED);
}

int CTSessionFrm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(!m_wndSideBar.Create(this, IDD_DIALOGBAR1, WS_CHILD | WS_VISIBLE | CBRS_LEFT, IDD_DIALOGBAR))
	{
		TRACE0("���̵�ٸ� ������ ���߽��ϴ�.\n");
		return -1;
	}    

	// CTSessionDlg Dialogbar
	m_dlgSideBar.Create(IDD_TSESSIONDLG, &m_wndSideBar);	
	m_dlgSideBar.ShowWindow(SW_SHOW);

	// TSessionFrm�� Ŭ���������͸� �Ѱ��ش�
	CSvrTesterApp* pApp = (CSvrTesterApp*)AfxGetApp();
	pApp->pTSessionFrm = this;

	return 0;
}

////////////////////////////////////////////////////////
// Get Session Dlg
CTSessionDlg* CTSessionFrm::GetTSessionDlg()
{
	return &m_dlgSideBar;
}
////////////////////////////////////////////////////////