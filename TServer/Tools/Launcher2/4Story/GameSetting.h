#pragma once
#include "afxwin.h"

#include "xSkinButton.h"
#include "bitmapslider.h"
#include "PlaySetting.h"
#include "Bitmappickercombo.h"

// CGameSetting ��ȭ �����Դϴ�.
// ���� �ý��� ����

// �׷��� ����
#define REG_WINDOW				_T("WindowedMode")	// â���
#define REG_SHADER				_T("UseShader")		// Shader �������
#define REG_CHARACTER			_T("ObjDETAIL")		// ĳ���� ǰ��
#define REG_MAPDETAIL			_T("MapDETAIL")		// ���� ǰ��
#define REG_TEXDETAIL			_T("TextureDETAIL")	// ���þ�

#define TMIN_RANGEOPTION				((FLOAT) 0.7f)
#define TMAX_RANGEOPTION				((FLOAT) 1.0f)

class CGameSetting : public CDialog
{
	DECLARE_DYNAMIC(CGameSetting)

public:
	CGameSetting(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGameSetting();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedCheckShader();
	afx_msg void OnBnClickedCheckWinmode();
	afx_msg void OnBnClickedRadioChar1(); // ĳ���� ǰ��
	afx_msg void OnBnClickedRadioChar2();
	afx_msg void OnBnClickedRadioChar3();
	afx_msg void OnBnClickedRadioGeo1(); // ���� ǰ��
	afx_msg void OnBnClickedRadioGeo2();
	afx_msg void OnBnClickedRadioGeo3();
	afx_msg void OnBnClickedRadioView1(); // �ؽ��� ǰ��
	afx_msg void OnBnClickedRadioView2();
	afx_msg void OnBnClickedRadioView3();
	afx_msg void OnBnClickedBtnClose(); // �ݱ� ��ư
	afx_msg void OnBnClickedBtnGameTab(); // ���� [�÷���] ���� ��ȭ���� ���̱�. �̴�ȭ���ڴ� ���� [�ý���] ���� ��ȭ������

	afx_msg LRESULT OnBitmapSliderMoved(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBitmapSliderMoving(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedChkBgshadow();
	afx_msg void OnBnClickedChkDlightmap();
	afx_msg void OnBnClickedChkBgsfx();
	afx_msg void OnBnClickedChkFlightmap();
	afx_msg void OnBnClickedChkFarimg();
	afx_msg void OnBnClickedChkVolume();
	afx_msg void OnBnClickedChkBgm();
	afx_msg void OnBnClickedChkSfxvolume();
	afx_msg void OnCbnSelchangeCbResolution();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);



	// �׷��� ����
	void SetGraphicMode(DWORD _window, DWORD _BGShadow, DWORD _DLightMap, DWORD _BGSFX, DWORD _FLightMap, DWORD _FarImg);
	void GetGraphicMode(DWORD *_wiindow, DWORD *_BGShadow, DWORD *_DLightMap, DWORD *_BGSFX, DWORD *_FLightMap, DWORD *_FarImg);
	
	// ���� ��뿩�� ����
	void SetVolumeMode(DWORD _volume, DWORD _BGM, DWORD _SFXVolume);
	void GetVolumeMode(DWORD *_volume, DWORD *_BGM, DWORD *_SFXVolume);
	
	// ���� �� ����
	void SetVolumeValue(DWORD _objRange, DWORD _volume, DWORD _BGMVolume, DWORD _SFXVolume);
	void GetVolumeValue(DWORD *_objRange, DWORD *_volume, DWORD *_BGMVolume, DWORD *_SFXVolume);

	// ĳ���� ǰ��, ����ǰ��, �ؽ��� ǰ�� ���� ��ư �ʱ� ����
	void SetRadioButtons(DWORD _char, DWORD _map, DWORD _texture);

	BOOL ReadRegistry();
	BOOL WriteRegistry();
	void LoadBGSkin();
	void LoadControlSkin();
	void SetDefaultOption();
	void InitResolution();
	void SetResolutionCtrl(CString strMode);
	void SetResolution(CString strMode);

	// ��Ų ���� ���̾�α׿��� Ư������ ��������� �ٲٱ�.
	// Load�� ��Ʈ��(CBitmap)�� �Ѱ� �ش�.
	void TransparentDialog(CBitmap* _pCBitmap, COLORREF  _color);
	void TransparentDialog2(COLORREF _color); // winNT�̻� user32.dll ���
	
	static CGameSetting* GetInstance()	{static CGameSetting inst; return &inst;}

public:
	
	//��潺Ų
	HBITMAP		hBmp;
	CBitmap		m_bmpBG;
	BYTE		sFlag;
	int			m_iBGWidth;
	int			m_iBGHeight;

	CString		m_strCountry;
	CString		m_strResolution;

	//
	DWORD		m_dwObjRange;	// �þ߰Ÿ�
	DWORD		m_dwMainVolume;	// ��ü ����
	DWORD		m_dwBGMVolume;	// �������
	DWORD		m_dwSFXVolume;	// ȿ����
	DWORD		m_dwObjDetailValue; // ĳ���� ǰ��
	DWORD		m_dwMapDetailValue; // ���� ǰ��
	DWORD		m_dwTextureDetailValue; // �ؽ��� ǰ�� 
	DWORD		m_dwScreenWidth;
	DWORD		m_dwScreenHeight;

	BOOL m_bShader;
	BOOL m_bWindow;
	BOOL m_bChar;
	BOOL m_bPaper;
	BOOL m_bBack;

	BOOL m_bBGShadow;
	BOOL m_bDLightMap;
	BOOL m_bBGSFX;
	BOOL m_bFLightMap;
	BOOL m_bFarImg;
	BOOL m_bVolume;
	BOOL m_bBGM;
	BOOL m_bSFXVolume;


	CxSkinButton m_chkShader;    // Shader ��뿩��
	CxSkinButton m_chkWinMode;   // â��� 
	CxSkinButton m_chkBGShadow;  // ��� �׸���.   ������Ʈ�� ���� �׸� : MapSHADOW
	CxSkinButton m_chkDLightMap; // ���� ����Ʈ��. 
	CxSkinButton m_chkBGSFX;	 // ��� Ư��ȿ��. ������Ʈ�� ���� �׸� : MapSFX
	CxSkinButton m_chkFLightMap; // �ʵ� ����Ʈ��. 
	CxSkinButton m_chkFarImg;	 // ���� �̹���.   
	
	CxSkinButton m_radioCHR3;	 // ĳ���� ǰ�� ��.	������Ʈ�� ���� �׸� :  ObjDETAIL
	CxSkinButton m_radioCHR2;	 
	CxSkinButton m_radioCHR1;	
	
	CxSkinButton m_radioMapDetail3; // ���� ǰ�� ��
	CxSkinButton m_radioMapDetail2; 
	CxSkinButton m_radioMapDetail1; 
	
	CxSkinButton m_radioTextureDetail3; // �ؽ��� ǰ�� ��
	CxSkinButton m_radioTextureDetail2;
	CxSkinButton m_radioTextureDetail1;
	
		
	CBitmapSlider m_sliderViewRange; // �þ� �Ÿ�. ������Ʈ�� ���� �׸� : OBJRange(���ڿ�)
	CBitmapSlider m_sliderVolume;	 // ��ü ����. ������Ʈ�� ���� �׸� : MainVolume
	CBitmapSlider m_sliderBGM;		 // ������� . ������Ʈ�� ���� �׸� : BGMVolume
	CBitmapSlider m_sliderSFXVolume; // ȿ����.    ������Ʈ�� ���� �׸� : SFXVolume

	CxSkinButton m_chkVolume;		// ��ü ���� ��뿩��
	CxSkinButton m_chkBGM;			// ����� ��뿩��
	CxSkinButton m_chkSFXVolume;	// ȿ���� ��뿩��

	CxSkinButton m_btnClose; 
	CxSkinButton m_btnGame; // ���Ӽ��� ��ư(�ǹ�ư)	
	
	CBitmapPickerCombo m_cbResolution;
	
};
