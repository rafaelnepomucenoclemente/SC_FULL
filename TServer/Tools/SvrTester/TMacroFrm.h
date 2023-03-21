#pragma once

#include "TMacroDlg.h"

// CTMacroFrm �������Դϴ�.

class CTMacroFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CTMacroFrm)
protected:
	CTMacroFrm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CTMacroFrm();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void ActivateFrame(int nCmdShow = -1);
public:
	CDialogBar		m_wndSideBar;
	CTMacroDlg		m_dlgSideBar;	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	////////////////////////////////////////////////////////
	// Get Macro Dlg
	CTMacroDlg* GetTMacroDlg();
	////////////////////////////////////////////////////////	
};