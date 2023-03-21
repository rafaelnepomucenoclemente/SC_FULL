// TMacroMachineView.cpp : CTMacroMachineView Ŭ������ ����
//

#include "stdafx.h"
#include "TMacroMachine.h"

#include "TMacroMachineDoc.h"
#include "TMacroMachineView.h"
#include ".\tmacromachineview.h"
#include "TMacroToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTMacroMachineView

IMPLEMENT_DYNCREATE(CTMacroMachineView, CFormView)

BEGIN_MESSAGE_MAP(CTMacroMachineView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_PROTOCOL, OnBnClickedButtonProtocol)
	ON_BN_CLICKED(IDC_BUTTON_MACRO, OnBnClickedButtonMacro)
	ON_BN_CLICKED(IDC_BUTTON_EXCUTE, OnBnClickedButtonExcute)
	ON_BN_CLICKED(IDC_BUTTON_MACROTOOL, OnBnClickedButtonMacrotool)
END_MESSAGE_MAP()

// CTMacroMachineView ����/�Ҹ�

CTMacroMachineView::CTMacroMachineView()
	: CFormView(CTMacroMachineView::IDD)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CTMacroMachineView::~CTMacroMachineView()
{
}

void CTMacroMachineView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_RELAYCHATTING, m_chkRelayChatting);
}

BOOL CTMacroMachineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	// Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CTMacroMachineView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	SetDlgItemText(IDC_IPADDRESS1, _T("192.168.1.166"));
	SetDlgItemText(IDC_EDIT1, _T("4815"));
	SetDlgItemText(IDC_EDIT2, _T("1"));

	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MACROTOOL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MACRO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_EXCUTE)->EnableWindow(FALSE);
}


// CTMacroMachineView ����

#ifdef _DEBUG
void CTMacroMachineView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTMacroMachineView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTMacroMachineDoc* CTMacroMachineView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTMacroMachineDoc)));
	return (CTMacroMachineDoc*)m_pDocument;
}
#endif //_DEBUG


// CTMacroMachineView �޽��� ó����

void CTMacroMachineView::ViewSessionCnt(BYTE bRet)
{
	CString strCnt;	
	strCnt.Format(_T("%d"), GetDocument()->GetSessionSize());
	SetDlgItemText(IDC_STATIC_SIZE, strCnt);

	if(bRet &&
		GetDocument()->GetSessionSize() == GetDocument()->GetThreadSize())
		GetDlgItem(IDC_BUTTON_MACRO)->EnableWindow(TRUE);
	else if(!bRet &&
		!GetDocument()->GetThreadSize()) 
	{
		GetDlgItem(IDC_BUTTON_MACRO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_EXCUTE)->EnableWindow(FALSE);
	}
}

void CTMacroMachineView::OnBnClickedButtonProtocol()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT);

	CString str;
	if(dlg.DoModal() == IDOK)
	{
		str = dlg.GetPathName();
		SetDlgItemText(IDC_EDIT4, str);

		BOOL bRet = FALSE;
		if(!str.IsEmpty())
			bRet = GetDocument()->LoadProtocol(str);

		if(!bRet)
		{
			SetDlgItemText(IDC_EDIT4, _T(""));
			AfxMessageBox(_T("������ �ٽ� �������ּ���"));
		}
		else
		{
			GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_MACROTOOL)->EnableWindow(TRUE);
		}
	}
}

void CTMacroMachineView::OnBnClickedButtonConnect()
{
	CString strAddr;
	CString strPort;
	CString strCnt;
	DWORD dwPort;
	WORD wCnt;

	GetDlgItemText(IDC_IPADDRESS1, strAddr);
	GetDlgItemText(IDC_EDIT1, strPort);
	GetDlgItemText(IDC_EDIT2, strCnt);
	
	dwPort = atoi(strPort);
	wCnt = atoi(strCnt);
	
	if(strAddr.IsEmpty() || !dwPort || !wCnt)
	{
		AfxMessageBox(_T("������ ������ �����Ͽ����ϴ�."));
		return;
	}

	if(!GetDocument()->CreateSession(wCnt))
	{
		AfxMessageBox(_T("�����尡 �������Դϴ�."));
		return;
	}	

	ViewSessionCnt(TRUE);
	GetDocument()->ConnetSession(strAddr, dwPort);
}

void CTMacroMachineView::OnBnClickedButtonDisconnect()
{
	GetDocument()->EndThread();
	SetDlgItemText(IDC_STATIC_SIZE, _T("0"));

	SetDlgItemText(IDC_EDIT5, _T(""));
	GetDlgItem(IDC_BUTTON_MACRO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_EXCUTE)->EnableWindow(FALSE);

	MAPTPROTOCOLTEMP::iterator it;
	for(it = GetDocument()->m_mapTProtocol.begin(); it != GetDocument()->m_mapTProtocol.end(); it++)
		delete (*it).second;
	GetDocument()->m_mapTProtocol.clear();
}

void CTMacroMachineView::OnBnClickedButtonMacrotool()
{
	if(!GetDocument()->m_mapProtocol.size())
		return;

	CTMacroToolDlg dlg;

	dlg.SetBasicProtocol(GetDocument()->m_mapProtocol, GetDocument()->m_mapType);

	dlg.DoModal();
}

void CTMacroMachineView::OnBnClickedButtonMacro()
{
	if(!GetDocument()->GetSessionSize())
	{
		AfxMessageBox(_T("����� ������ �����ϴ�."));
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT);

	CString str;
	if(dlg.DoModal() == IDOK)
	{
		MAPTPROTOCOLTEMP::iterator it;
		for(it = GetDocument()->m_mapTProtocol.begin(); it != GetDocument()->m_mapTProtocol.end(); it++)
			delete (*it).second;
		GetDocument()->m_mapTProtocol.clear();

		str = dlg.GetPathName();
		SetDlgItemText(IDC_EDIT5, str);
		if(!GetDocument()->LoadMacro(str))
		{
			AfxMessageBox(_T("��ũ�ΰ� ����ֽ��ϴ�."));
			SetDlgItemText(IDC_EDIT5, _T(""));
			return;
		}

		GetDlgItem(IDC_BUTTON_EXCUTE)->EnableWindow(TRUE);
	}
}

void CTMacroMachineView::OnBnClickedButtonExcute()
{
	if(!GetDocument()->GetSessionSize())
	{
		AfxMessageBox(_T("����� ������ �����ϴ�."));
		return;
	}

	if(GetDocument()->EmptyMacro())
	{
		AfxMessageBox(_T("��ũ�ΰ� ����ֽ��ϴ�."));
		return;
	}

	GetDocument()->m_bRelayChatting = m_chkRelayChatting.GetCheck();
	GetDocument()->ExcuteMacro();
}

void CTMacroMachineView::UpdateSessionCnt(WORD wCount)
{
	CString strCnt;	
	strCnt.Format(_T("%d"), wCount);
	SetDlgItemText(IDC_STATIC_SIZE, strCnt);
}