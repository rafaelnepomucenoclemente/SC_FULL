// TMacroMachineView.h : iCTMacroMachineView Ŭ������ �������̽�
//


#pragma once
#include "afxwin.h"


class CTMacroMachineView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CTMacroMachineView();
	DECLARE_DYNCREATE(CTMacroMachineView)

public:
	enum{ IDD = IDD_TMACROMACHINE_FORM };

// Ư��
public:
	CTMacroMachineDoc* GetDocument() const;

// �۾�
public:

// ������
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// ����
public:
	virtual ~CTMacroMachineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	DECLARE_MESSAGE_MAP()

public:
	void ViewSessionCnt(BYTE bRet);
	void UpdateSessionCnt(WORD wCount);
public:
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonProtocol();
	afx_msg void OnBnClickedButtonMacro();
	afx_msg void OnBnClickedButtonExcute();
	afx_msg void OnBnClickedButtonMacrotool();
	CButton m_chkRelayChatting;
};

#ifndef _DEBUG  // TMacroMachineView.cpp�� ����� ����
inline CTMacroMachineDoc* CTMacroMachineView::GetDocument() const
   { return reinterpret_cast<CTMacroMachineDoc*>(m_pDocument); }
#endif

