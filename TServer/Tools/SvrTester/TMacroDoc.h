#pragma once


// CTMacroDoc �����Դϴ�.

class CTMacroDoc : public CDocument
{
	DECLARE_DYNCREATE(CTMacroDoc)

public:
	CTMacroDoc();
	virtual ~CTMacroDoc();
	virtual void Serialize(CArchive& ar);   // ���� ��/����� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
	
};
