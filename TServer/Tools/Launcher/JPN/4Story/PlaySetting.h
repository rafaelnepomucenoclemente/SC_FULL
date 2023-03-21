#pragma once

#include "xskinbutton.h"

#define WS_EX_LAYERED     0x00080000 
#define LWA_COLORKEY      1 
#define LWA_ALPHA         2 

// CPlaySetting ��E?�����Դϴ�.

class CPlaySetting : public CDialog
{
	DECLARE_DYNAMIC(CPlaySetting)

public:
	CPlaySetting(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPlaySetting();

// ��E?���� �������Դϴ�.
	enum { IDD = IDD_PLAYSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:	

	//��潺Ų
	HBITMAP		hBmp;
	CBitmap		m_bmpBG;
	BYTE		sFlag;
	int			m_iBGWidth;
	int			m_iBGHeight;

	CString		m_strCountry;

	CxSkinButton m_chkNPCName;			// NPC �̸�
	CxSkinButton m_chkCharName;			// ĳ���� �̸�
	CxSkinButton m_chkMonName;			// ���� �̸�
	CxSkinButton m_chkAutoHelp;			// �ڵ� ����
	CxSkinButton m_chkTalkBox;			// ��ǳ�� ���̱�E
	CxSkinButton m_chkHUD;				// HUD ���̱�E
	CxSkinButton m_chkDenyWhisper;		// �Ӹ� �ź�
	CxSkinButton m_chkDenyCommunity;	// Ŀ�´�Ƽ �ź�
	CxSkinButton m_chkConChat;			// ���� ä�� ����E
	CxSkinButton m_btnClose;			// â�ݱ�E��ư
	CxSkinButton m_btnSys;				// �ý��� �� ��ư
	CxSkinButton m_chkClickMove;		// ���콺 Ŭ�� �̵�

	BOOL m_bNPCName;		
	BOOL m_bCharName;
	BOOL m_bMonName;
	BOOL m_bAutoHelp;
	BOOL m_bTalkBox;
	BOOL m_bHUD;
	BOOL m_bDenyWhisper;
	BOOL m_bDenyCom;
	BOOL m_bConChat;
	BOOL m_bClickMove;

public:

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnSetTab();
	afx_msg void OnBnClickedClosePlayset();
	afx_msg void OnBnClickedChkNpcname();
	afx_msg void OnBnClickedChkCharname();
	afx_msg void OnBnClickedChkMonname();
	afx_msg void OnBnClickedChkAutohelp();
	afx_msg void OnBnClickedChkTalkbox();
	afx_msg void OnBnClickedChkHud();
	afx_msg void OnBnClickedChkDenywhi();
	afx_msg void OnBnClickedChkDenycom();
	afx_msg void OnBnClickedChkConchat();
	afx_msg void OnBnClickedChkClickmove();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	
	void LoadBGSkin();
	void LoadControlSkin();
	BOOL WriteRegistry();
	BOOL ReadRegistry();
	void SetDefaultOption();
	
	// ��Ų ��?E���̾�α׿��� Ư������ ���������� �ٲٱ�E
	// Load�� ��Ʈ��(CBitmap)�� �Ѱ� �ش�.
	void TransparentDialog(CBitmap* _pCBitmap, COLORREF  _color); 
	void TransparentDialog2(COLORREF _color); // winNT�̻�Euser32.dll �翁E	
	
};
