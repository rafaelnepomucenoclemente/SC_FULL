#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "STType.h"

#define MAX_VALUE_TYPE 7

// CTMacroDlg ��ȭ �����Դϴ�.

class CTMacroDlg : public CDialog
{
	DECLARE_DYNAMIC(CTMacroDlg)

public:
	CTMacroDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTMacroDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TMACRODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:	
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	/////////////////////////////////////////////////
	// Macro Paramater
	CComboBox m_ComboType;
	CListCtrl m_ListParam;
	
	// Macro Paramater List Insert / Del / Init
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonInit();
	
	// Paramater List Move
	afx_msg void OnBnClickedButtonTop();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonBottom();
	afx_msg void OnBnClickedButtonDown();

	// Paramater List Dblclk
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	// Macro Paramater Set	
	void SetMacroParam(CTMacro* pMacro);
	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	// Macro Paramater View
	void MacroParamView(CTMacro* pMacro);
	void ClearMacroParamView();
	/////////////////////////////////////////////////	
};
