// TMacroDoc.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SvrTester.h"
#include "TMacroDoc.h"


// CTMacroDoc

IMPLEMENT_DYNCREATE(CTMacroDoc, CDocument)

CTMacroDoc::CTMacroDoc()
{	
}

BOOL CTMacroDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CTMacroDoc::~CTMacroDoc()
{	
}


BEGIN_MESSAGE_MAP(CTMacroDoc, CDocument)
END_MESSAGE_MAP()


// CTMacroDoc �����Դϴ�.

#ifdef _DEBUG
void CTMacroDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTMacroDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTMacroDoc serialization�Դϴ�.

void CTMacroDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CTMacroDoc ����Դϴ�.