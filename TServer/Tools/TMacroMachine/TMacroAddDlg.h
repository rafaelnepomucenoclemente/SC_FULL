#pragma once
#include "afxwin.h"


// CTMacroAddDlg ��ȭ �����Դϴ�.

class CTMacroAddDlg : public CDialog
{
	DECLARE_DYNAMIC(CTMacroAddDlg)

public:
	CTMacroAddDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTMacroAddDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TMACROADDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbLoop;
	CString m_strName;
	BYTE m_bLoop;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
