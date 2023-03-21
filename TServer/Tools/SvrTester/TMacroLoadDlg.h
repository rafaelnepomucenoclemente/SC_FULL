#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CTMacroLoadDlg ��ȭ �����Դϴ�.

class CTMacroLoadDlg : public CDialog
{
	DECLARE_DYNAMIC(CTMacroLoadDlg)

public:
	CTMacroLoadDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTMacroLoadDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TMACROLOADDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:	
	virtual BOOL OnInitDialog();

	///////////////////////////////////////////////
	// Macro ID Vector
	VECTORDWORD vMID;
	///////////////////////////////////////////////

	///////////////////////////////////////////////
    // Tree / ListBox
	CTreeCtrl m_tree;
	CImageList *m_pImageList;
	CListBox m_listbox;
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	// Macro Insert / Delete
	void InsertList();
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);

	void DeleteList();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnLbnDblclkList1();
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	// IDOK
	afx_msg void OnBnClickedOk();
	///////////////////////////////////////////////	
};
