// GameSetting.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "4Story.h"
#include "GameSetting.h"
#include ".\gamesetting.h"


// CGameSetting ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CGameSetting, CDialog)
CGameSetting::CGameSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CGameSetting::IDD, pParent)
	, m_bShader(FALSE)
	, m_bWindow(FALSE)
	, m_bChar(FALSE)
	, m_bPaper(FALSE)
	, m_bBack(FALSE)
	, m_dwObjRange(0)
	, m_dwMainVolume(0)
	, m_dwBGMVolume(0)	
	, m_dwSFXVolume(0)   
	, m_bBGShadow(FALSE)
	, m_bDLightMap(FALSE)
	, m_bBGSFX(FALSE)
	, m_bFLightMap(FALSE)
	, m_bFarImg(FALSE)
	, m_bVolume(FALSE)
	, m_bBGM(FALSE)
	, m_bSFXVolume(FALSE)
	, m_dwScreenWidth(DEFAULT_SCREEN_X)
	, m_dwScreenHeight(DEFAULT_SCREEN_Y)
{
	m_strResolution.Format(_T("%d X %d"),DEFAULT_SCREEN_X,DEFAULT_SCREEN_Y);
}

CGameSetting::~CGameSetting()
{
}

void CGameSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_SHADER, m_bShader);
	DDX_Check(pDX, IDC_CHECK_WINMODE, m_bWindow);
	DDX_Control(pDX, IDC_CHECK_SHADER, m_chkShader);
	DDX_Control(pDX, IDC_CHECK_WINMODE, m_chkWinMode);
	DDX_Control(pDX, IDC_CHK_BGSHADOW, m_chkBGShadow);
	DDX_Control(pDX, IDC_CHK_DLIGHTMAP, m_chkDLightMap);
	DDX_Control(pDX, IDC_CHK_BGSFX, m_chkBGSFX);
	DDX_Control(pDX, IDC_CHK_FLIGHTMAP, m_chkFLightMap);
	DDX_Control(pDX, IDC_CHK_FARIMG, m_chkFarImg);
	DDX_Control(pDX, IDC_RADIO_CHAR3, m_radioCHR3);
	DDX_Control(pDX, IDC_RADIO_CHAR1, m_radioCHR1);
	DDX_Control(pDX, IDC_RADIO_CHAR2, m_radioCHR2);
	DDX_Control(pDX, IDC_RADIO_GEO1, m_radioMapDetail1);
	DDX_Control(pDX, IDC_RADIO_GEO2, m_radioMapDetail2);
	DDX_Control(pDX, IDC_RADIO_GEO3, m_radioMapDetail3);
	DDX_Control(pDX, IDC_RADIO_TEXDETAIL1, m_radioTextureDetail1);
	DDX_Control(pDX, IDC_RADIO_TEXDETAIL2, m_radioTextureDetail2);
	DDX_Control(pDX, IDC_RADIO_TEXDETAIL3, m_radioTextureDetail3);	

	DDX_Control(pDX, IDC_SLIDERVIEW, m_sliderViewRange);
	DDX_Control(pDX, IDC_SLIDERVOLUME, m_sliderVolume);
	DDX_Control(pDX, IDC_SLIDERBGM, m_sliderBGM);
	DDX_Control(pDX, IDC_SLIDERSFXVOLUME, m_sliderSFXVolume);
	DDX_Control(pDX, IDC_CHK_VOLUME, m_chkVolume);
	DDX_Control(pDX, IDC_CHK_BGM, m_chkBGM);
	DDX_Control(pDX, IDC_CHK_SFXVOLUME, m_chkSFXVolume);
	DDX_Control(pDX, IDC_BTN_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_BTN_GAME, m_btnGame);
	DDX_Control(pDX, IDC_CB_RESOLUTION, m_cbResolution);

	DDX_Check(pDX, IDC_CHK_BGSHADOW, m_bBGShadow);
	DDX_Check(pDX, IDC_CHK_DLIGHTMAP, m_bDLightMap);
	DDX_Check(pDX, IDC_CHK_BGSFX, m_bBGSFX);
	DDX_Check(pDX, IDC_CHK_FLIGHTMAP, m_bFLightMap);
	DDX_Check(pDX, IDC_CHK_FARIMG, m_bFarImg);
	DDX_Check(pDX, IDC_CHK_VOLUME, m_bVolume);
	DDX_Check(pDX, IDC_CHK_BGM, m_bBGM);
	DDX_Check(pDX, IDC_CHK_SFXVOLUME, m_bSFXVolume);
	
}


BEGIN_MESSAGE_MAP(CGameSetting, CDialog)
	ON_BN_CLICKED(IDC_CHECK_SHADER, OnBnClickedCheckShader)
	ON_BN_CLICKED(IDC_CHECK_WINMODE, OnBnClickedCheckWinmode)
	ON_BN_CLICKED(IDC_RADIO_CHAR1, OnBnClickedRadioChar1)
	ON_BN_CLICKED(IDC_RADIO_CHAR2, OnBnClickedRadioChar2)
	ON_BN_CLICKED(IDC_RADIO_CHAR3, OnBnClickedRadioChar3)
	ON_BN_CLICKED(IDC_RADIO_GEO1, OnBnClickedRadioGeo1)
	ON_BN_CLICKED(IDC_RADIO_GEO2, OnBnClickedRadioGeo2)
	ON_BN_CLICKED(IDC_RADIO_GEO3, OnBnClickedRadioGeo3)
	ON_BN_CLICKED(IDC_RADIO_TEXDETAIL1, OnBnClickedRadioView1)
	ON_BN_CLICKED(IDC_RADIO_TEXDETAIL2, OnBnClickedRadioView2)
	ON_BN_CLICKED(IDC_RADIO_TEXDETAIL3, OnBnClickedRadioView3)
	ON_WM_PAINT()
	ON_MESSAGE(WM_BITMAPSLIDER_MOVED, OnBitmapSliderMoved)
	ON_MESSAGE(WM_BITMAPSLIDER_MOVING, OnBitmapSliderMoving)
ON_WM_LBUTTONDOWN()
ON_BN_CLICKED(IDC_BTN_CLOSE, OnBnClickedBtnClose)
ON_BN_CLICKED(IDC_BTN_GAME, OnBnClickedBtnGameTab)
ON_BN_CLICKED(IDC_CHK_BGSHADOW, OnBnClickedChkBgshadow)
ON_BN_CLICKED(IDC_CHK_DLIGHTMAP, OnBnClickedChkDlightmap)
ON_BN_CLICKED(IDC_CHK_BGSFX, OnBnClickedChkBgsfx)
ON_BN_CLICKED(IDC_CHK_FLIGHTMAP, OnBnClickedChkFlightmap)
ON_BN_CLICKED(IDC_CHK_FARIMG, OnBnClickedChkFarimg)
ON_BN_CLICKED(IDC_CHK_VOLUME, OnBnClickedChkVolume)
ON_BN_CLICKED(IDC_CHK_BGM, OnBnClickedChkBgm)
ON_BN_CLICKED(IDC_CHK_SFXVOLUME, OnBnClickedChkSfxvolume)
ON_WM_ERASEBKGND()
ON_CBN_SELCHANGE(IDC_CB_RESOLUTION, OnCbnSelchangeCbResolution)
END_MESSAGE_MAP()


// CGameSetting �޽��� ó�����Դϴ�.

void CGameSetting::SetGraphicMode(DWORD _window, DWORD _BGShadow, DWORD _DLightMap, DWORD _BGSFX, DWORD _FLightMap, DWORD _FarImg)
{
	m_bWindow = _window;
	m_bBGShadow = _BGShadow;
	m_bDLightMap = _DLightMap;
	m_bBGSFX = _BGSFX;
	m_bFLightMap = _FLightMap;
	m_bFarImg = _FarImg;
}

void CGameSetting::GetGraphicMode(DWORD *_wiindow, DWORD *_BGShadow, DWORD *_DLightMap, DWORD *_BGSFX, DWORD *_FLightMap, DWORD *_FarImg)
{

	*_wiindow = m_bWindow;
	*_BGShadow = m_bBGShadow;
	*_DLightMap = m_bDLightMap;
	*_BGSFX = m_bBGSFX;
	*_FLightMap = m_bFLightMap;
	*_FarImg = m_bFarImg;
}

void CGameSetting::SetVolumeMode(DWORD _volume, DWORD _BGM, DWORD _SFXVolume)
{
	m_bVolume = _volume;
	m_bBGM = _BGM;
	m_bSFXVolume = _SFXVolume;
}

void CGameSetting::GetVolumeMode(DWORD *_volume, DWORD *_BGM, DWORD *_SFXVolume)
{
	*_volume = m_bVolume;
	*_BGM = m_bBGM;
	*_SFXVolume = m_bSFXVolume;
}

void CGameSetting::SetVolumeValue(DWORD _objRange, DWORD _volume, DWORD _BGMVolume, DWORD _SFXVolume)
{
	m_dwObjRange = _objRange;
	m_dwMainVolume = _volume;
	m_dwBGMVolume = _BGMVolume;
	m_dwSFXVolume = _SFXVolume;
}

void CGameSetting::GetVolumeValue(DWORD *_objRange, DWORD *_volume, DWORD *_BGMVolume, DWORD *_SFXVolume)
{
	*_objRange = m_dwObjRange;
	*_volume = m_dwMainVolume;
	*_BGMVolume = m_dwBGMVolume;
	*_SFXVolume = m_dwSFXVolume;
}

void CGameSetting::SetRadioButtons(DWORD _char, DWORD _map, DWORD _texture)
{
	switch(_char)
	{
	case 0: m_radioCHR1.SetCheck(TRUE); break;		
	case 1:	m_radioCHR2.SetCheck(TRUE);	break;
	case 2:	m_radioCHR3.SetCheck(TRUE);	break;
	default: break;
	}

	switch(_map)
	{
	case 0:	m_radioMapDetail1.SetCheck(TRUE);break;
	case 1:	m_radioMapDetail2.SetCheck(TRUE);break;
	case 2:	m_radioMapDetail3.SetCheck(TRUE);break;
	default: break;
	}

	switch(_texture)
	{
	case 0:	m_radioTextureDetail1.SetCheck(TRUE);break;
	case 1:	m_radioTextureDetail2.SetCheck(TRUE);break;
	case 2:	m_radioTextureDetail3.SetCheck(TRUE);break;
	default:break;
	}

}

BOOL CGameSetting::ReadRegistry()
{	
	HKEY hKeyRet;	
	HKEY hKey = HKEY_CURRENT_USER;
	

	int err = 0;
	CString strSubkey;
	CString strRegSubKey;
	CString strAppName;
	CString strBuf;
	
	
	strAppName = APP_NAME;	
	strSubkey = _T("");
	strSubkey = strAppName;
	strSubkey += _T("\\Settings");

	strRegSubKey.Format(_T("%s%s"), REG_SUBKEY, strSubkey);

	err = RegOpenKey(hKey, strRegSubKey, &hKeyRet);
	if(ERROR_SUCCESS != err)
	{
		RegCloseKey(hKeyRet);
		hKey = HKEY_LOCAL_MACHINE;		
	}

	BYTE	data[1024] = {0,};
	DWORD   type;
	DWORD   cbdata =1024;



	// â���
	cbdata = 1024;
	memset(data, 0, 1024);	
	err = RegQueryValueEx(hKeyRet, _T("WindowedMode"), NULL, &type, data, &cbdata);

	if( ERROR_SUCCESS != err || type != REG_SZ)
		return TRUE;

	strBuf = data;

	if( strBuf == _T("TRUE") )
		m_bWindow = 1;
	else
		m_bWindow = 0;


	// ��� �׸���
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, _T("MapSHADOW") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_bBGShadow = *((LPWORD)data);

	// ���� ����Ʈ ��
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, _T("DLIGHTMAP") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_bDLightMap = *((LPWORD)data);

	// ��� Ư��ȿ��
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, _T("MapSFX") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_bBGSFX = *((LPWORD)data);

	// �ʵ� ����Ʈ ��
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, _T("FLIGHTMAP") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_bFLightMap = *((LPWORD)data);

	// ���� �̹���
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, _T("FarIMAGE") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_bFarImg = *((LPWORD)data);


	// ĳ���� ǰ��	
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, _T("ObjDETAIL") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_dwObjDetailValue = *((LPWORD)data);

	// ����ǰ��
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, _T("MapDETAIL") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_dwMapDetailValue = *((LPWORD)data);

	// �ؽ���ǰ��
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, _T("TextureDETAIL") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_dwTextureDetailValue = *((LPWORD)data);

	// �þ� �Ÿ�
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, _T("OBJRange") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_SZ)
		return TRUE;
	strBuf = data;
	m_dwObjRange = (DWORD)(_tstof(strBuf) * 100) ;	


	// ��ü ���� ��� ����
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, _T("MASTER") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_bVolume = *((LPWORD)data);

	// ��ü ���� Value
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, _T("MainVolume") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_dwMainVolume = *((LPWORD)data);

	// ������� ��� ����
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, _T("BGM") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_bBGM = *((LPWORD)data);

	// ������� Value
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, _T("BGMVolume") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_dwBGMVolume = *((LPWORD)data);

	// ȿ���� ��� ����
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, _T("SOUND") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_bSFXVolume = *((LPWORD)data);

	// ȿ���� Value
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, _T("SFXVolume") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_dwSFXVolume = *((LPWORD)data);


	// �ػ� Width
	cbdata = 1024;
	memset(data, 0, 1024);

	err = RegQueryValueEx(hKeyRet, _T("ScreenX") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_dwScreenWidth = *((LPWORD)data);

	// �ػ� Height
	cbdata = 1024;
	memset(data, 0, 1024);

	err = RegQueryValueEx(hKeyRet, _T("ScreenY") , NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return TRUE;
	m_dwScreenHeight = *((LPWORD)data);

	m_strResolution.Format(_T("%d X %d"),m_dwScreenWidth,m_dwScreenHeight);

	return TRUE;
}


BOOL CGameSetting::WriteRegistry()
{
	HKEY hKeyRet;	
	HKEY hKey = HKEY_CURRENT_USER;

	int err = 0;	
	DWORD dwDisposition = 0;
	CString strSubkey;
	CString strRegSubKey;
	CString strAppName;

	strAppName = APP_NAME;	
	strSubkey = _T("");
	strSubkey = strAppName + REG_COUNTRY;
	strSubkey += _T("\\Settings");

	strRegSubKey.Format(_T("%s%s"), REG_SUBKEY, strSubkey);

//	err = RegOpenKey(hKey, strRegSubKey, &hKeyRet);
	err = RegCreateKeyEx( hKey, strRegSubKey, 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,
		&hKeyRet, &dwDisposition );

	char	strTmp[1024] = {0,};
	BYTE	data[1024] = {0,};	
	DWORD   cbData = 4;
	DWORD	cbData1 = sizeof(BOOL);

	// â���
	if(m_bWindow == 1)
		strcpy(strTmp,"TRUE");
	else
		strcpy(strTmp,"FALSE");

	err = RegSetValueEx(hKeyRet, _T("WindowedMode"), 0, REG_SZ, (BYTE*)strTmp, (DWORD)strlen(strTmp));
	if(ERROR_SUCCESS != err)
		return FALSE;

	// �þ� �Ÿ�.Client���� ���� ������	
	float fObjRange = TMIN_RANGEOPTION + (TMAX_RANGEOPTION - TMIN_RANGEOPTION) * FLOAT(m_dwObjRange) / FLOAT(100);

	sprintf(strTmp,"%f",fObjRange);
	err = RegSetValueEx(hKeyRet, _T("OBJRange"), 0, REG_SZ, (BYTE*)strTmp, (DWORD)strlen(strTmp));

	if(ERROR_SUCCESS != err)
		return FALSE;

	// ���׸���
	memcpy(data, &m_bBGShadow, sizeof(BOOL));
	err = RegSetValueEx(hKeyRet, _T("MapSHADOW"), 0, REG_DWORD, data, cbData1 );
	if( ERROR_SUCCESS != err )
		return FALSE;

	// ���� ����Ʈ ��
	memcpy(data, &m_bDLightMap, sizeof(BOOL));
	err = RegSetValueEx(hKeyRet, _T("DLIGHTMAP"), 0, REG_DWORD, data, cbData1 );
	if( ERROR_SUCCESS != err )
		return FALSE;

	// ��� Ư�� ȿ��
	memcpy(data, &m_bBGSFX, sizeof(BOOL));
	err = RegSetValueEx(hKeyRet, _T("MapSFX"), 0, REG_DWORD, data, cbData1 );
	if( ERROR_SUCCESS != err )
		return FALSE;

	// �ʵ� ����Ʈ ��
	memcpy(data, &m_bFLightMap, sizeof(BOOL));
	err = RegSetValueEx(hKeyRet, _T("FLIGHTMAP"), 0, REG_DWORD, data, cbData1);
	if( ERROR_SUCCESS != err )
		return FALSE;

	// ���� �̹���
	memcpy(data, &m_bFarImg, sizeof(BOOL));
	err = RegSetValueEx(hKeyRet, _T("FarIMAGE"), 0, REG_DWORD, data, cbData1);
	if( ERROR_SUCCESS != err )
		return FALSE;

	// ĳ���� ǰ��
	memcpy(data, &m_dwObjDetailValue, sizeof(DWORD));
	err = RegSetValueEx(hKeyRet, _T("ObjDETAIL"), 0, REG_DWORD, data, cbData);
	if( ERROR_SUCCESS != err )
		return FALSE;

	// ���� ǰ��
	memcpy(data, &m_dwMapDetailValue, sizeof(DWORD));
	err = RegSetValueEx(hKeyRet, _T("MapDETAIL"), 0, REG_DWORD, data, cbData);
	if( ERROR_SUCCESS != err )
		return FALSE;

	// �ؽ��� ǰ��
	memcpy(data, &m_dwTextureDetailValue, sizeof(DWORD));
	err = RegSetValueEx(hKeyRet, _T("TextureDETAIL"), 0, REG_DWORD, data, cbData);
	if( ERROR_SUCCESS != err )
		return FALSE;

	// ��ü ���� ��뿩��
	memset(data,0,sizeof(data));
	memcpy(data, &m_bVolume, sizeof(BOOL));
	err = RegSetValueEx(hKeyRet, _T("MASTER"), 0, REG_DWORD, data, cbData1);
	if( ERROR_SUCCESS != err )
		return FALSE;

	// ������� ��뿩��	
	memcpy(data, &m_bBGM, sizeof(BOOL));
	err = RegSetValueEx(hKeyRet, _T("BGM"), 0, REG_DWORD, data, cbData1);
	if( ERROR_SUCCESS != err )
		return FALSE;

	// ȿ���� ��뿩��	
	memcpy(data, &m_bSFXVolume, sizeof(BOOL));
	err = RegSetValueEx(hKeyRet, _T("SOUND"), 0, REG_DWORD, data, cbData1);
	if( ERROR_SUCCESS != err )
		return FALSE;


	// ��ü ���� ��	
	memset(data,0,sizeof(data) );
	memcpy(data, &m_dwMainVolume, sizeof(DWORD));
	err = RegSetValueEx(hKeyRet, _T("MainVolume"), 0, REG_DWORD, data, cbData);
	if( ERROR_SUCCESS != err )
		return FALSE;

	// ������� ���� ��
	memcpy(data, &m_dwBGMVolume, sizeof(DWORD));
	err = RegSetValueEx(hKeyRet, _T("BGMVolume"), 0, REG_DWORD, data, cbData);
	if( ERROR_SUCCESS != err )
		return FALSE;

	// ȿ���� ���� ��
	memcpy(data, &m_dwSFXVolume, sizeof(DWORD));
	err = RegSetValueEx(hKeyRet, _T("SFXVolume"), 0, REG_DWORD, data, cbData);
	if( ERROR_SUCCESS != err )
		return FALSE;

	// �ػ� width
	memcpy(data, &m_dwScreenWidth, sizeof(DWORD));
	err = RegSetValueEx(hKeyRet, _T("ScreenX"), 0, REG_DWORD, data, cbData);
	if( ERROR_SUCCESS != err )
		return FALSE;

	// �ػ� height
	memcpy(data, &m_dwScreenHeight, sizeof(DWORD));
	err = RegSetValueEx(hKeyRet, _T("ScreenY"), 0, REG_DWORD, data, cbData);
	if( ERROR_SUCCESS != err )
		return FALSE;

	return TRUE;
}

void CGameSetting::LoadBGSkin()
{	
	sFlag = m_bmpBG.LoadBitmap(IDB_TABSYS);

	if(sFlag)
	{
		CRect rect,WinRect;
		GetClientRect(rect);
		GetWindowRect(WinRect);

		BITMAP bmp;
		m_bmpBG.GetBitmap(&bmp);

		m_iBGWidth = bmp.bmWidth;
		m_iBGHeight = bmp.bmHeight;

		int PosX = WinRect.left + rect.right/2;
		int PosY = WinRect.top;

		SetWindowPos( NULL, PosX, PosY, bmp.bmWidth, bmp.bmHeight, 0 );
	}
}


void CGameSetting::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
}

void CGameSetting::LoadControlSkin()
{
	//m_btnClose.LoadBitmap(IDB_CLOSE_NORMAL, IDB_CLOSE_HOVER, IDB_CLOSE_DOWN, 0);
	m_btnClose.SetSkin(IDB_CLOSE_NORMAL,IDB_CLOSE_DOWN,IDB_CLOSE_HOVER,0,0,0,1,0,0);
	m_btnGame.SetSkin(IDB_BTN_GAMETAB,IDB_BTN_GAMETAB,IDB_BTN_GAMETAB,0,0,0,1,0,0);

	m_chkShader.SetSkin(IDB_BIT_CHECK_NORMAL,IDB_BIT_CHECK_DOWN,0,0,0,0,1,0,0);		// ���̴� ���
	m_chkWinMode.SetSkin(IDB_BIT_CHECK_NORMAL,IDB_BIT_CHECK_DOWN,0,0,0,0,1,0,0);	// ������ ���
	m_chkBGShadow.SetSkin(IDB_BIT_CHECK_NORMAL,IDB_BIT_CHECK_DOWN,0,0,0,0,1,0,0);	// ���׸���
	m_chkDLightMap.SetSkin(IDB_BIT_CHECK_NORMAL,IDB_BIT_CHECK_DOWN,0,0,0,0,1,0,0);	// ��������Ʈ��
	m_chkBGSFX.SetSkin(IDB_BIT_CHECK_NORMAL,IDB_BIT_CHECK_DOWN,0,0,0,0,1,0,0);		//��� Ư�� ȿ��
	m_chkFLightMap.SetSkin(IDB_BIT_CHECK_NORMAL,IDB_BIT_CHECK_DOWN,0,0,0,0,1,0,0);	// �ʵ� ����Ʈ��
	m_chkFarImg.SetSkin(IDB_BIT_CHECK_NORMAL,IDB_BIT_CHECK_DOWN,0,0,0,0,1,0,0);		// ���� �̹���
	
	// ĳ���� ǰ�� ���� ��ư��
	m_radioCHR3.SetSkin(IDB_RADIO_NORMAL,IDB_RADIO_DOWN,0,0,0,0,1,0,0);
	m_radioCHR2.SetSkin(IDB_RADIO_NORMAL,IDB_RADIO_DOWN,0,0,0,0,1,0,0);
	m_radioCHR1.SetSkin(IDB_RADIO_NORMAL,IDB_RADIO_DOWN,0,0,0,0,1,0,0);
	
	// ���� ǰ�� ���� ��ư��
	m_radioMapDetail3.SetSkin(IDB_RADIO_NORMAL,IDB_RADIO_DOWN,0,0,0,0,1,0,0);
	m_radioMapDetail2.SetSkin(IDB_RADIO_NORMAL,IDB_RADIO_DOWN,0,0,0,0,1,0,0);
	m_radioMapDetail1.SetSkin(IDB_RADIO_NORMAL,IDB_RADIO_DOWN,0,0,0,0,1,0,0);
	
	// �ؽ��� ǰ�� ���� ��ư��
	m_radioTextureDetail3.SetSkin(IDB_RADIO_NORMAL,IDB_RADIO_DOWN,0,0,0,0,1,0,0);
	m_radioTextureDetail2.SetSkin(IDB_RADIO_NORMAL,IDB_RADIO_DOWN,0,0,0,0,1,0,0);
	m_radioTextureDetail1.SetSkin(IDB_RADIO_NORMAL,IDB_RADIO_DOWN,0,0,0,0,1,0,0);


	// �þ߰Ÿ� �����̴�
	m_sliderViewRange.SetBitmapChannel(IDB_SLIDERBG2);
	m_sliderViewRange.SetBitmapThumb(IDB_SLIDERBAR,NULL,TRUE);
	m_sliderViewRange.SetRange(0,100,0);
	int iPos = (int)((m_dwObjRange*0.01 - TMIN_RANGEOPTION) * 100.0f / (TMAX_RANGEOPTION - TMIN_RANGEOPTION));
	m_sliderViewRange.SetPos(iPos);	
	m_sliderViewRange.SetMarginLeft(2);
	m_sliderViewRange.SetMarginRight(3);
	m_sliderViewRange.SetMarginTop(4);
	m_sliderViewRange.DrawFocusRect(FALSE);
	

	// ��ü ���� �����̴�
	m_sliderVolume.SetBitmapChannel(IDB_SLIDERBG2);
	m_sliderVolume.SetBitmapThumb(IDB_SLIDERBAR,NULL,TRUE);
	m_sliderVolume.SetRange(0,100,0);
	m_sliderVolume.SetPos(m_dwMainVolume);	
	m_sliderVolume.SetMarginLeft(2);
	m_sliderVolume.SetMarginRight(3);
	m_sliderVolume.SetMarginTop(4);
	m_sliderVolume.DrawFocusRect(FALSE);

	// ������� �����̴�
	m_sliderBGM.SetBitmapChannel(IDB_SLIDERBG2);
	m_sliderBGM.SetBitmapThumb(IDB_SLIDERBAR,NULL,TRUE);
	m_sliderBGM.SetRange(0,100,0);
	m_sliderBGM.SetPos(m_dwBGMVolume);	
	m_sliderBGM.SetMarginLeft(2);
	m_sliderBGM.SetMarginRight(3);
	m_sliderBGM.SetMarginTop(4);
	m_sliderBGM.DrawFocusRect(FALSE);

	// ȿ���� �����̴�
	m_sliderSFXVolume.SetBitmapChannel(IDB_SLIDERBG2);
	m_sliderSFXVolume.SetBitmapThumb(IDB_SLIDERBAR,NULL,TRUE);
	m_sliderSFXVolume.SetRange(0,100,0);
	m_sliderSFXVolume.SetPos(m_dwSFXVolume);	
	m_sliderSFXVolume.SetMarginLeft(2);
	m_sliderSFXVolume.SetMarginRight(3);
	m_sliderSFXVolume.SetMarginTop(4);
	m_sliderSFXVolume.DrawFocusRect(FALSE);

	
	m_chkVolume.SetSkin(IDB_BIT_CHECK_NORMAL,IDB_BIT_CHECK_DOWN,0,0,0,0,1,0,0);		// ��ü���� üũ�ڽ�
	m_chkBGM.SetSkin(IDB_BIT_CHECK_NORMAL,IDB_BIT_CHECK_DOWN,0,0,0,0,1,0,0);		// ������� üũ�ڽ�
	m_chkSFXVolume.SetSkin(IDB_BIT_CHECK_NORMAL,IDB_BIT_CHECK_DOWN,0,0,0,0,1,0,0);	// ��ü���� üũ�ڽ�
}

BOOL CGameSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	InitResolution();
	SetDefaultOption();	

	if(!ReadRegistry())
	{
		//AfxMessageBox(_T("Can not read Registry"));
	}
	
	SetResolutionCtrl(m_strResolution);
	
	// ��� ��Ų ������
	LoadBGSkin();	
	
	// �� ��ư�� ��Ų ������
	LoadControlSkin();

	SetRadioButtons(m_dwObjDetailValue, m_dwMapDetailValue, m_dwTextureDetailValue);

	// ���̾�α� ����� ����
	TransparentDialog(&m_bmpBG,RGB(255,255,255));
	//TransparentDialog2(RGB(255,255,255)); 

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CGameSetting::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	// ���콺 ���ʹ�ư �巡�׷� ���̾�α� �����Ӱ� �̵�
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CDialog::OnLButtonDown(nFlags, point);
}


LRESULT CGameSetting::OnBitmapSliderMoved(WPARAM wParam, LPARAM lParam)
{
	CString sMsg;

	switch( wParam ) {

	case IDC_SLIDERVIEW :
		m_dwObjRange = (DWORD)m_sliderViewRange.GetPos();
		UpdateData(FALSE);
		break;

	case IDC_SLIDERVOLUME :
		m_dwMainVolume = (DWORD)m_sliderVolume.GetPos();
		UpdateData(FALSE);
		break;

	case IDC_SLIDERBGM :
		m_dwBGMVolume = (DWORD)m_sliderBGM.GetPos();
		UpdateData( FALSE );
		break;

	case IDC_SLIDERSFXVOLUME:
		m_dwSFXVolume = (DWORD)m_sliderSFXVolume.GetPos();
		UpdateData(FALSE);
		break;
		
	}

	return 0;
}

LRESULT CGameSetting::OnBitmapSliderMoving(WPARAM wParam, LPARAM lParam)
{
	switch( wParam ) {

	case IDC_SLIDERVIEW :
		m_dwObjRange = (DWORD)m_sliderViewRange.GetPos();
		UpdateData(FALSE);
		break;

	case IDC_SLIDERVOLUME :
		m_dwMainVolume = (DWORD)m_sliderVolume.GetPos();
		UpdateData(FALSE);
		break;

	case IDC_SLIDERBGM :
		m_dwBGMVolume = (DWORD)m_sliderBGM.GetPos();
		UpdateData( FALSE );
		break;

	case IDC_SLIDERSFXVOLUME:
		m_dwSFXVolume = (DWORD)m_sliderSFXVolume.GetPos();
		UpdateData(FALSE);
		break;

	}

	return 0;
}
void CGameSetting::OnBnClickedBtnClose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	WriteRegistry();
	ShowWindow(SW_HIDE);	
}

void CGameSetting::OnBnClickedBtnGameTab()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	WriteRegistry();

	CRect rect;
	GetClientRect(rect);
	ClientToScreen(rect);
	
	m_pdlgPlaySetting->SetWindowPos(0,rect.left, rect.top, 0,0, SWP_NOSIZE | SWP_SHOWWINDOW);
	ShowWindow(SW_HIDE);
}



void CGameSetting::OnBnClickedCheckShader()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedCheckWinmode()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedRadioChar1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_dwObjDetailValue = 0;
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedRadioChar2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_dwObjDetailValue = 1;
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedRadioChar3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_dwObjDetailValue = 2;
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedRadioGeo1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_dwMapDetailValue = 0;
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedRadioGeo2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_dwMapDetailValue = 1;
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedRadioGeo3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_dwMapDetailValue = 2;
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedRadioView1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_dwTextureDetailValue = 0;
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedRadioView2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_dwTextureDetailValue = 1;
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedRadioView3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_dwTextureDetailValue = 2;
	UpdateData(TRUE);
}


void CGameSetting::OnBnClickedChkBgshadow()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedChkDlightmap()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedChkBgsfx()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedChkFlightmap()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedChkFarimg()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedChkVolume()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedChkBgm()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
}

void CGameSetting::OnBnClickedChkSfxvolume()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
}

void CGameSetting::OnCbnSelchangeCbResolution()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strResolution;

	DWORD dwIndex = m_cbResolution.GetCurSel();
	m_cbResolution.GetLBText(dwIndex,strResolution);

	SetResolution(strResolution);
}

void CGameSetting::TransparentDialog(CBitmap* _pCBitmap, COLORREF  _color)
{
	// ���̾�α� ��� ��Ʈ�� ����� ����.
	COLORREF crTransparent = _color;	// �����. ����(0,0,0)	
	BITMAP Bitmap;	
	_pCBitmap->GetBitmap(&Bitmap);

	
	CPaintDC dc(this);	
	CDC dcMem;

	dcMem.CreateCompatibleDC(&dc);	
	CBitmap* pOldBitmap = dcMem.SelectObject(_pCBitmap);
	
	CRgn crRgn, crRgnTmp;
	
	crRgn.CreateRectRgn(0, 0, 0, 0);	
	
	int iX = 0;
	for (int iY = 0; iY < Bitmap.bmHeight; iY++)
	{
		do
		{			
			while (iX <= Bitmap.bmWidth && dcMem.GetPixel(iX, iY) == crTransparent)
				iX++;
			
			int iLeftX = iX;
			
			while (iX <= Bitmap.bmWidth && dcMem.GetPixel(iX, iY) != crTransparent)
				++iX;
			
			crRgnTmp.CreateRectRgn(iLeftX, iY, iX, iY+1);
			
			crRgn.CombineRgn(&crRgn, &crRgnTmp, RGN_OR);
			
			crRgnTmp.DeleteObject();
		}while(iX < Bitmap.bmWidth);
		iX = 0;
	}
	
	SetWindowRgn(crRgn, TRUE);
	iX = (GetSystemMetrics(SM_CXSCREEN)) / 2 - (Bitmap.bmWidth / 2);
	iY = (GetSystemMetrics(SM_CYSCREEN)) / 2 - (Bitmap.bmHeight / 2);
	SetWindowPos(&wndTopMost, iX, iY, Bitmap.bmWidth, Bitmap.bmHeight, NULL); 

	
	dcMem.SelectObject(pOldBitmap);	
	dcMem.DeleteDC();
	crRgn.DeleteObject();

}


void CGameSetting::TransparentDialog2(COLORREF _color)
{
	int window_style = GetWindowLong(m_hWnd, GWL_EXSTYLE); 

	if(!(window_style & WS_EX_LAYERED))
	{ 
		SetWindowLong(m_hWnd, GWL_EXSTYLE, window_style | WS_EX_LAYERED); 
	} 

	HMODULE h_user32_dll = GetModuleHandle("USER32.DLL"); 

	if(h_user32_dll != NULL)
	{ 
		BOOL (WINAPI *fp_set_layered_window_attributes)(HWND, COLORREF, BYTE, DWORD) = 

			(BOOL (WINAPI *)(HWND, COLORREF, BYTE, DWORD))GetProcAddress(h_user32_dll, 

			"SetLayeredWindowAttributes"); 

		if(fp_set_layered_window_attributes != NULL)
		{ 
			(*fp_set_layered_window_attributes)(m_hWnd, _color, 0, LWA_COLORKEY); 
		} 

	} 
}


// ����� �������� �ٽ� �׸���.(WM_ERASEBKGND)
BOOL CGameSetting::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	// ���̾�α� ��� �׸� ������
	CRect rect;
	GetClientRect(&rect);
	
	CRect rc;
	GetClientRect(rc);
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	int nSavedDC = MemDC.SaveDC();
	
	BITMAP bmp;	
	m_bmpBG.GetBitmap(&bmp);
	CBitmap* pOldBmp = MemDC.SelectObject(&m_bmpBG);	
	pDC->StretchBlt(rect.left, rect.top, rect.right, rect.bottom, &MemDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
	MemDC.SelectObject(pOldBmp);
	MemDC.RestoreDC(nSavedDC);
	MemDC.DeleteDC();
	ReleaseDC(pDC);

	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}

void CGameSetting::SetDefaultOption()
{
	m_strCountry = COUNTRY_CODE;
	if(m_strCountry == _T("GERMANY") )
	{
		switch(theApp.m_bOptionLevel)
		{
		case OPTION_LOW: // Low
			{				
				m_bWindow				= FALSE;	  
				m_bBGShadow				= TRUE;
				m_bDLightMap			= FALSE;
				m_bBGSFX				= FALSE;
				m_bFLightMap			= FALSE;
				m_bFarImg				= FALSE;
				m_bVolume				= TRUE;
				m_bBGM					= TRUE;
				m_bSFXVolume			= TRUE;
				m_dwObjRange			= 70;	// �þ߰Ÿ�				
				m_dwObjDetailValue		= 1; // ĳ���� ǰ��
				m_dwMapDetailValue		= 0; // ���� ǰ��
				m_dwTextureDetailValue	= 0; // �ؽ��� ǰ��
			}
			break;
		case OPTION_MID: // Mid
			{
				m_bWindow				= FALSE;	  
				m_bBGShadow				= TRUE;
				m_bDLightMap			= TRUE;
				m_bBGSFX				= FALSE;
				m_bFLightMap			= FALSE;
				m_bFarImg				= TRUE;
				m_bVolume				= TRUE;								
				m_bBGM					= TRUE;
				m_bSFXVolume			= TRUE;				
				m_dwObjRange			= 75;	// �þ߰Ÿ�				
				m_dwObjDetailValue		= 2; // ĳ���� ǰ��
				m_dwMapDetailValue		= 1; // ���� ǰ��
				m_dwTextureDetailValue  = 1; // �ؽ��� ǰ��

			}
			break;
		case OPTION_HI: // High
			{
				m_bWindow				= FALSE;	  
				m_bBGShadow				= TRUE;
				m_bDLightMap			= TRUE;
				m_bBGSFX				= TRUE;
				m_bFLightMap			= FALSE;
				m_bFarImg				= TRUE;
				m_bVolume				= TRUE;
				m_bBGM					= TRUE;
				m_bSFXVolume			= TRUE;
				m_dwObjRange			= 80;	// �þ߰Ÿ�				
				m_dwObjDetailValue		= 2; // ĳ���� ǰ��
				m_dwMapDetailValue		= 1; // ���� ǰ��
				m_dwTextureDetailValue  = 2; // �ؽ��� ǰ��
			}
			break;
		}
	}
	else 
	{
		switch(theApp.m_bOptionLevel)
		{
		case OPTION_LOW:
			{
				m_bWindow				= FALSE;	  
				m_bBGShadow				= TRUE;
				m_bDLightMap			= FALSE;
				m_bBGSFX				= FALSE;
				m_bFLightMap			= FALSE;
				m_bFarImg				= FALSE;
				m_bVolume				= TRUE;
				m_bBGM					= TRUE;
				m_bSFXVolume			= TRUE;
				m_dwObjRange			= 70;	// �þ߰Ÿ�				
				m_dwObjDetailValue		= 1; // ĳ���� ǰ��
				m_dwMapDetailValue		= 0; // ���� ǰ��
				m_dwTextureDetailValue  = 0; // �ؽ��� ǰ��
			}
			break;
		case OPTION_MID:
			{
				m_bWindow				= FALSE;	  
				m_bBGShadow				= TRUE;
				m_bDLightMap			= TRUE;
				m_bBGSFX				= FALSE;
				m_bFLightMap			= FALSE;
				m_bFarImg				= TRUE;
				m_bVolume				= TRUE;
				m_bBGM					= TRUE;
				m_bSFXVolume			= TRUE;
				m_dwObjRange			= 75;	// �þ߰Ÿ�				
				m_dwObjDetailValue		= 2; // ĳ���� ǰ��
				m_dwMapDetailValue		= 1; // ���� ǰ��
				m_dwTextureDetailValue  = 1; // �ؽ��� ǰ��
			}
		case OPTION_HI:
			{
				m_bWindow				= FALSE;	  
				m_bBGShadow				= TRUE;
				m_bDLightMap			= TRUE;
				m_bBGSFX				= TRUE;
				m_bFLightMap			= FALSE;
				m_bFarImg				= TRUE;
				m_bVolume				= TRUE;
				m_bBGM					= TRUE;
				m_bSFXVolume			= TRUE;
				m_dwObjRange			= 80;	// �þ߰Ÿ�				
				m_dwObjDetailValue		= 2; // ĳ���� ǰ��
				m_dwMapDetailValue		= 1; // ���� ǰ��
				m_dwTextureDetailValue  = 2; // �ؽ��� ǰ��
			}
			break;
		}
	}

	 m_dwMainVolume = 75;
	 m_dwBGMVolume	= 25;
	 m_dwSFXVolume	= 75;
	 m_dwScreenWidth	= DEFAULT_SCREEN_X;
	 m_dwScreenHeight	= DEFAULT_SCREEN_Y;
}

void CGameSetting::InitResolution()
{
	m_cbResolution.ResetContent();

	CBitmap* pBitmap;
	CPalette pPal;
	TCHAR strText[256];
	

	m_cbResolution.SetTextLeftBlank(5);

	for(DWORD i = 0; i < (DWORD)theApp.m_vScreenMode.size(); i++)
	{
		CString strResolution = theApp.m_vScreenMode[i].strMode;
		lstrcpy(strText,strResolution);

		pBitmap = new CBitmap;
		//BOOL bLoad = m_cbResolution.LoadBMPImage("resolution.bmp", pBitmap, &pPal);
		pBitmap->LoadBitmap(IDB_RESOLUTION);

		m_cbResolution.AddBitmap(pBitmap,strText);		
		
	}

	m_cbResolution.SetTextColor_(RGB(210,210,210));
	m_cbResolution.SetFont_("2002L",17);
	m_cbResolution.SetCurSel(0);
		
}

void CGameSetting::SetResolutionCtrl(CString strMode)
{
	CString str;
	DWORD i;
	DWORD dwCount = m_cbResolution.GetCount();
	strMode.Trim(_T(" "));
	
	for(i = 0; i < dwCount; i++)
	{
        m_cbResolution.GetLBText(i,str);
		str.Trim(_T(" "));
		
		if(str == strMode)
		{
			m_cbResolution.SetCurSel(i);
			break;
		}
	}
}

void CGameSetting::SetResolution(CString strMode)
{
	CString str;
	DWORD i;
	DWORD dwCount = (DWORD)theApp.m_vScreenMode.size();
	strMode.Trim(_T(" "));	

	for(i = 0; i < dwCount; i++)
	{
		str = theApp.m_vScreenMode[i].strMode;
		str.Trim(_T(" "));
		
		if(str == strMode)
		{
			m_dwScreenWidth = theApp.m_vScreenMode[i].dwWidth;
			m_dwScreenHeight = theApp.m_vScreenMode[i].dwHeight;
			break;
		}
	}
}

