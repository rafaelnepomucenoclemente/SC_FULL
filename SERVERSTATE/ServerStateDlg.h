// ServerStateDlg.h : ��� ����
//

#pragma once


// CServerStateDlg ��ȭ ����
class CServerStateDlg : public CDialog
{
// ����
public:
	CServerStateDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_SERVERSTATE_DIALOG };

protected:
	virtual void DoDataExchange( CDataExchange* pDX);	// DDX/DDV ����

	CListCtrl m_ctrlServerState;
	BOOL m_bChecked;

protected:
	HICON m_hIcon;

	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void DoBeep( BOOL flag);

	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedCheckButton();
	afx_msg void OnBnClickedListButton();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnLvnDeleteitemList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
};
