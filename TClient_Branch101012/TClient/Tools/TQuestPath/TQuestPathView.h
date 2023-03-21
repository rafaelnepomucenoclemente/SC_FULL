// TQuestPathView.h : iCTQuestPathView Ŭ������ �������̽�
//


#pragma once
#include "afxwin.h"
#include "afxcmn.h"


class CTQuestPathView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CTQuestPathView();
	DECLARE_DYNCREATE(CTQuestPathView)

public:
	enum{ IDD = IDD_TQUESTPATH_FORM };

// Ư��
public:
	CTQuestPathDoc* GetDocument() const;

// �۾�
public:
	void UpdateTERMDATA();
	void EnableTermCtrl();
	void EnableCtrl();
	void UpdateDATA();
	void UpdateTERM();

// ������
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// ����
public:
	virtual ~CTQuestPathView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	LPTTITEM m_pTTITEM;

	CString m_strNpcName;
	CString m_strPosX;
	CString m_strPosY;
	CString m_strPosZ;

	CString m_strMSG;
	CString m_strMAP;

	DWORD m_dwQuestID;
	DWORD m_dwNpcID;
	DWORD m_dwMapID;

protected:
	CListCtrl m_cTSTEP;

	CStatic m_cQuestID;
	CStatic m_cNpcID;

	CButton m_cAutoset;
	CButton m_cRestore;
	CButton m_cApply;

	CButton m_cFindNPC;
	CButton m_cPickPOS;
	CButton m_cMAP;

	CEdit m_cNpcName;
	CEdit m_cMapID;
	CEdit m_cPosX;
	CEdit m_cPosY;
	CEdit m_cPosZ;
	CEdit m_cMSG;

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedListStep(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAutoSet();
	afx_msg void OnBnClickedButtonRestore();
	afx_msg void OnBnClickedButtonApply();
};

#ifndef _DEBUG  // TQuestPathView.cpp�� ����� ����
inline CTQuestPathDoc* CTQuestPathView::GetDocument() const
   { return reinterpret_cast<CTQuestPathDoc*>(m_pDocument); }
#endif
