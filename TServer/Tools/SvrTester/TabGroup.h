#pragma once

#include "TabCtrlST.h"

#include "TSessionTab.h"
#include "TMacroTab.h"

// CTabGroup ��ȭ �����Դϴ�.

class CTabGroup : public CDialog
{
	DECLARE_DYNAMIC(CTabGroup)

public:
	CTabGroup(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabGroup();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TABGROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CTabCtrlST m_TabGroup; // CTabCtrlST Class
	CImageList *m_pImageList; // Image List
public:
	//////////////////////////////////////////////////////////////////////
	// Session Protocol List Load / Clear
	void TSessionTabLoadList();	
	void TSessionListClear();
	//////////////////////////////////////////////////////////////////////	

	//////////////////////////////////////////////////////////////////////
	// Session / Macro Tab Active
	void TSessionActive();
	void TMacroActive();

	// Get Current Tab
	BOOL GetCurTab();

	// Get Session / Macro Tab View
	CTSessionTab* GetTSessionTabView();
	CTMacroTab* GetTMacroTabView();
	//////////////////////////////////////////////////////////////////////	

	// Enter / Escape block
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
