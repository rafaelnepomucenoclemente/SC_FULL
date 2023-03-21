// ServerStateDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ServerState.h"
#include "ServerStateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DEF_BEEP_EVENT				(1000)


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


// CServerStateDlg ��ȭ ����



CServerStateDlg::CServerStateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerStateDlg::IDD, pParent)
	, m_bChecked(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerStateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_ctrlServerState);
	DDX_Check(pDX, IDC_CHECK1, m_bChecked);
}

BEGIN_MESSAGE_MAP(CServerStateDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_BUTTON, OnBnClickedCheckButton)
	ON_BN_CLICKED(IDC_LIST_BUTTON, OnBnClickedListButton)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST, OnLvnDeleteitemList)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CServerStateDlg �޽��� ó����

BOOL CServerStateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_ctrlServerState.SetExtendedStyle(m_ctrlServerState.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ctrlServerState.InsertColumn(0, _T("���� �̸�"), LVCFMT_CENTER, 100);
	m_ctrlServerState.InsertColumn(1, _T("IP"), LVCFMT_CENTER, 100);
	m_ctrlServerState.InsertColumn(2, _T("Port"), LVCFMT_CENTER, 60);
	m_ctrlServerState.InsertColumn(3, _T("���� ����"), LVCFMT_CENTER, 100);
	m_ctrlServerState.DeleteAllItems();

	CServerStateSock::m_pctrlServerState = &m_ctrlServerState;
	CServerStateSock::m_pHost = this;

	m_bChecked = TRUE;
	UpdateData(FALSE);

	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

void CServerStateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CServerStateDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ
		
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CServerStateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CServerStateDlg::OnBnClickedCheckButton()
{
	DoBeep(FALSE);

	for( int i=0; i<m_ctrlServerState.GetItemCount(); i++)
	{
		CServerStateSock *pCON = (CServerStateSock *) m_ctrlServerState.GetItemData(i);
		CString strIP = m_ctrlServerState.GetItemText( i, 1);
		CString strPort = m_ctrlServerState.GetItemText( i, 2);

		if(pCON)
			pCON->Connect( LPCSTR(strIP), atoi(strPort));
	}
}

void CServerStateDlg::OnBnClickedListButton()
{
	CStdioFile file;
	CString str;

	file.Open(_T("test.txt"), CFile::modeRead); 
	CString resToken;

	while(file.ReadString(str))
	{
		str.TrimRight();
		str.TrimLeft();

		if(!str.IsEmpty())
		{
			CServerStateSock *pCON = new CServerStateSock();
			TCHAR strNAME[MAX_PATH];
			TCHAR strIP[MAX_PATH];
			TCHAR strPort[MAX_PATH];

			sscanf( str, _T("%s %s %s"),
				strNAME,
				strIP,
				strPort);

			pCON->m_nIndex = m_ctrlServerState.InsertItem(
				m_ctrlServerState.GetItemCount(),
				strNAME);

			pCON->Create(
				0, SOCK_STREAM,
				FD_READ|
				FD_WRITE|
				FD_OOB|
				FD_CONNECT
				FD_CLOSE);

			m_ctrlServerState.SetItemText( pCON->m_nIndex, 1, strIP);
			m_ctrlServerState.SetItemText( pCON->m_nIndex, 2, strPort);
			m_ctrlServerState.SetItemData( pCON->m_nIndex, (DWORD_PTR) pCON);
		}
	}

	file.Close();
}

void CServerStateDlg::DoBeep( BOOL flag)
{
	if(flag)
		SetTimer( DEF_BEEP_EVENT, 1000, NULL);
	else
		KillTimer(DEF_BEEP_EVENT);
}

void CServerStateDlg::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	if( nIDEvent == DEF_BEEP_EVENT )
		Beep( 2000, 500);
}

void CServerStateDlg::OnBnClickedCheck1()
{
	UpdateData();
}

void CServerStateDlg::OnLvnDeleteitemList( NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	if( pNMLV && pNMLV->iItem >= 0 )
	{
		CServerStateSock *pCON = (CServerStateSock *) m_ctrlServerState.GetItemData(pNMLV->iItem);
		delete pCON;
	}
}

void CServerStateDlg::OnDestroy()
{
	m_ctrlServerState.DeleteAllItems();
	CDialog::OnDestroy();
}
