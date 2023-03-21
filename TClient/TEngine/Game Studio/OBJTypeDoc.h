#pragma once
#include "TachyonDoc.h"
#include "ItemBase.h"


// COBJTypeDoc 문서입니다.

class COBJTypeDoc : public CTachyonDoc
{
	DECLARE_DYNCREATE(COBJTypeDoc)

public:
	COBJTypeDoc();
	virtual ~COBJTypeDoc();
	virtual void Serialize(CArchive& ar);   // 문서 입/출력을 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	COBJTypeItem* m_pItem;

public:
	virtual void InitData( LPVOID pData);
	virtual void Update();

protected:
	virtual BOOL OnNewDocument();
	DECLARE_MESSAGE_MAP()
};
