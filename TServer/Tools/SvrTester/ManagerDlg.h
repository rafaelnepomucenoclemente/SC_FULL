#pragma once


// CManagerDlg ��ȭ �����Դϴ�.

class CManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(CManagerDlg)

public:
	CManagerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CManagerDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MANAGERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSerchProtocol();
	afx_msg void OnBnClickedOk();

public:
	CString m_strIP;
	CString m_strPort;
	CString m_strFile;
	CString m_strUser;
	CString m_strPass;
	virtual BOOL OnInitDialog();
};
