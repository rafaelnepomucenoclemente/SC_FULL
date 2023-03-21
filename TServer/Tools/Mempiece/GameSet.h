#pragma once


// CGameSet ��ȭ �����Դϴ�.

class CGameSet : public CDialog
{
	DECLARE_DYNAMIC(CGameSet)

public:
	CGameSet(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGameSet();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GAMESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	/////////////////////////////////////////////
	// ���·� �׷��� ����
	void SetGraphicMode(DWORD window, DWORD shader, DWORD character, DWORD paper, DWORD back);
	void GetGraphicMode(DWORD *window, DWORD *shader, DWORD *character, DWORD *paper, DWORD *back);	

	// Window / Shader Mode Check Box
	BOOL m_bWindow;
	BOOL m_bShader;

	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();	

	// Graphic Mode Radio Button
	BOOL m_bChar;
	BOOL m_bPaper;
	BOOL m_bBack;

	afx_msg void OnBnClickedRadio10();
	afx_msg void OnBnClickedRadio11();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio9();
	/////////////////////////////////////////////	
};
