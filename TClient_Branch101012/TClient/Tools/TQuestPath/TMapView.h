#pragma once


// CTMapView ���Դϴ�.

class CTMapView : public CView
{
	DECLARE_DYNCREATE(CTMapView)

protected:
	CTMapView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CTMapView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


