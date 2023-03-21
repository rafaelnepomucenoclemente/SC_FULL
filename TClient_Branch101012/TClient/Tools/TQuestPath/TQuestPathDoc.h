// TQuestPathDoc.h : CTQuestPathDoc Ŭ������ �������̽�
//


#pragma once

class CTQuestPathDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CTQuestPathDoc();
	DECLARE_DYNCREATE(CTQuestPathDoc)

// Ư��
public:
	MAPTQITEM m_mapTMISSION;
	MAPTQITEM m_mapTQCLASS;

	CTGameDB m_vTGAMEDB;
	LPTQITEM m_pTQITEM;

public:
	void ReleaseBUF();

// �۾�
public:
	CTreeCtrl *GetQuestTreeCtrl();

	LPTQITEM FindTMISSION( DWORD dwID);
	LPTQITEM FindTQCLASS( DWORD dwID);
	CString GetTNPCName( WORD wID);

	LPTTITEM PickTTITEM(
		LPVTTITEM pVTTITEM,
		BYTE bType,
		DWORD dwID);
	BYTE LoadTQUEST();

	BYTE GetAutosetData(
		LPTTITEM pTRESULT,
		LPTQITEM pTQITEM,
		LPTTITEM pTTITEM);

	void UpdateDATA( LPTQITEM pTQITEM);
	void ResetTERM( LPTQITEM pTQITEM);

// ������
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ����
public:
	virtual ~CTQuestPathDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDbLoadQuest();
	afx_msg void OnDbLoadGame();
};
