#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CTSessionDlg ��ȭ �����Դϴ�.

class CTSessionDlg : public CDialog
{
	DECLARE_DYNAMIC(CTSessionDlg)

public:
	CTSessionDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTSessionDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TSESSIONDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();	

	////////////////////////////////////////////////
	// Sever Connect / DisConnect
	CString m_strIP;
	CString m_strPort;
	CString m_strThread;

	afx_msg void OnBnClickedDisconnect();
	afx_msg void OnBnClickedConnect();
	////////////////////////////////////////////////

	////////////////////////////////////////////////
	// CharInfo Set
	CListCtrl m_listCharInfo;
	CImageList *m_pImageList;

	void SetCharInfo(CString UserID, CString CharID, CString KEY, 
					 CString GroupID, CString Channel, CString SvrID);
	////////////////////////////////////////////////

	////////////////////////////////////////////////
	// Disregard Protocol List
	CListBox m_listDisregard;

	CRect GetListPosition();
    void SetDisregardList(CString str);
	BOOL GetDisregardList(CString strP);
	void ClearDisregardList();
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonMon();
	////////////////////////////////////////////////

	////////////////////////////////////////////////
	// Macro Tree
	CTreeCtrl m_TreeMacro;

	// Macro Tree Clear
	afx_msg void OnBnClickedButtonClear();
	void ClearMacroTree();
	// Macro Tree Load	
	HTREEITEM InsertTreeItem(CString strName, HTREEITEM hTreeItem);	
	afx_msg void OnBnClickedButtonLoad();
	void InsertChildItem(CString strName, HTREEITEM hParent);
	////////////////////////////////////////////////

	// Enter / Escape block
	virtual BOOL PreTranslateMessage(MSG* pMsg);	
};
