// TMacroAddDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TMacroMachine.h"
#include "TMacroAddDlg.h"
#include ".\tmacroadddlg.h"


// CTMacroAddDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTMacroAddDlg, CDialog)
CTMacroAddDlg::CTMacroAddDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTMacroAddDlg::IDD, pParent)
{
}

CTMacroAddDlg::~CTMacroAddDlg()
{
}

void CTMacroAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbLoop);
}


BEGIN_MESSAGE_MAP(CTMacroAddDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CTMacroAddDlg �޽��� ó�����Դϴ�.

BOOL CTMacroAddDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cbLoop.AddString(_T("FALSE"));
	m_cbLoop.AddString(_T("TRUE"));
	m_cbLoop.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CTMacroAddDlg::OnBnClickedOk()
{
	m_bLoop = m_cbLoop.GetCurSel();
	GetDlgItemText(IDC_EDIT1, m_strName);

	if(m_strName == _T(""))
	{
		AfxMessageBox(_T("�̸��� ������ �������� �����ϴ�."));
		return;
	}

	OnOK();
}