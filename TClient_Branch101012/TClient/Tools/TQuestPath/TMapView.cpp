// TMapView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TQuestPath.h"
#include "TMapView.h"


// CTMapView

IMPLEMENT_DYNCREATE(CTMapView, CView)

CTMapView::CTMapView()
{
}

CTMapView::~CTMapView()
{
}

BEGIN_MESSAGE_MAP(CTMapView, CView)
END_MESSAGE_MAP()


// CTMapView �׸����Դϴ�.

void CTMapView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CTMapView �����Դϴ�.

#ifdef _DEBUG
void CTMapView::AssertValid() const
{
	CView::AssertValid();
}

void CTMapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// CTMapView �޽��� ó�����Դϴ�.
