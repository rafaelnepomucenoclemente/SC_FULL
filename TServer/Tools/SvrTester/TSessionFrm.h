// TSessionFrm.h : CTSessionFrm Ŭ������ �������̽�
//


#pragma once

#include "TSessionDlg.h"

class CTSessionFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CTSessionFrm)
public:
	CTSessionFrm();

// Ư��
public:

// �۾�
public:

// ������
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����
public:
	virtual ~CTSessionFrm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void ActivateFrame(int nCmdShow = -1);
public:
	CDialogBar		m_wndSideBar;
	CTSessionDlg	m_dlgSideBar;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	////////////////////////////////////////////////////////
	// Get Session Dlg
	CTSessionDlg* GetTSessionDlg();
    ////////////////////////////////////////////////////////
};
