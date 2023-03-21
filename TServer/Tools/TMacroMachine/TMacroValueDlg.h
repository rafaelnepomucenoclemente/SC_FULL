#pragma once
#include "afxwin.h"
#include "md5.h"

// CTMacroValueDlg ��ȭ �����Դϴ�.

class CTMacroValueDlg : public CDialog
{
	DECLARE_DYNAMIC(CTMacroValueDlg)

public:
	CTMacroValueDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTMacroValueDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TMACROVALUEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbValueType;
	CComboBox m_cbType;

	BYTE m_bValueType;
	BYTE m_bType;
	CString m_strName;
	CString m_strValue;

	void SetValue(BYTE bValueType, BYTE bType, CString strName, CString strValue);

public:
	CString EncryptPW(CString& strSOURCE);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombo2();

};
