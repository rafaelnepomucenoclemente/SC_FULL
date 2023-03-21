#pragma once


// CTQuestView ���Դϴ�.

class CTQuestView : public CTreeView
{
	DECLARE_DYNCREATE(CTQuestView)

public:
	CTQuestPathDoc* GetDocument() const;

public:
	CImageList m_listTreeImage;

protected:
	CTQuestView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CTQuestView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnTvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // TQuestPathView.cpp�� ����� ����
inline CTQuestPathDoc* CTQuestView::GetDocument() const
   { return reinterpret_cast<CTQuestPathDoc*>(m_pDocument); }
#endif
