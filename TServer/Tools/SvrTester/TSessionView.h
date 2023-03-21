// TSessionView.h : iCTSessionView Ŭ������ �������̽�
//


#pragma once
#include "afxcmn.h"
#include "afxwin.h"


class CTSessionView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CTSessionView();
	DECLARE_DYNCREATE(CTSessionView)

public:
	enum{ IDD = IDD_SVRTESTER_FORM };

// Ư��
public:
	CTSessionDoc* GetDocument() const;

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
	virtual ~CTSessionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	DECLARE_MESSAGE_MAP()

public:
	///////////////////////////////////////////////////////////////////////////////////
	// Manager Connect / DisConnect
	void ManagerConnect(CString strIP, CString strPort, CString strUser, CString strPass); 
	void ManagerDisConnect(); 
	///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	// Sever Connect / DisConnect
	void Connect(CString strIP, CString strPort, CString strThread);
	void DisConnect();

	// Protocol List Drag
	CRect GetEditPosition();	
	void SetEditProtocol(CString str);

	// All Check
	BOOL m_bAllFlag;
	CButton m_AllCheck;	

	afx_msg void OnBnClickedCheckAll();	

	// Protocol Send
	afx_msg void OnBnClickedButtonSend();
	
	// Receive Message Value
	CListCtrl m_listResult;

	void InitList();	
	void InsertList(CTachyonSession* pSession);
	void ClearList();
	afx_msg void OnBnClickedListClear();

	// Thread ComboBox
	CComboBox m_comboThread;

	// Init ComboBox
	void SetComboThread(DWORD bID); 
	// ComboBox Current Thread Number Get
	int GetDataCurrentComboThread(); 
	int GetIndexCurrentComboThread();
	int GetIndexComboThread(DWORD dwID);
	int GetDataComboThread(int index);
	afx_msg void OnCbnSelchangeComboThread();

	void SetEditConnect(); // Connect Edit Box Set
	///////////////////////////////////////////////////////////////////////////////////			
};

#ifndef _DEBUG  // TSessionView.cpp�� ����� ����
inline CTSessionDoc* CTSessionView::GetDocument() const
   { return reinterpret_cast<CTSessionDoc*>(m_pDocument); }
#endif