// 4StoryDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "HoverButton.h"
#include "GameSetting.h" // ���� ���� â ����

#include <d3d9.h>
#include <dxdiag.h>
#include <d3dx9.h>

#pragma comment(lib,"dxguid.lib")

typedef enum TMP_HACK_DETECT_TYPE
{
	TMP_HACK_NONE = 0,
	TMP_HACK_FOUND,
	TMP_HACK_TIMEOUT,
	TMP_HACK_INVALID_PE
} *LPTMP_HACK_DETECT_TYPE;

#define WM_RESTART_PATCH			(WM_USER + 109)
#define WM_STOP_DOWNLOAD			(WM_USER + 119)
#define WM_CLOSE_SESSION			(WM_USER + 120)

#define APP_EXT						_T(".exe")
#define APP_NAME					_T("4story")
#define BACKUP_EXT					_T("_bak")
#define PATH_DELIMETERS				_T("/\\")
#define REG_SUBKEY					_T("Software\\Zemi Interactive\\")
#define REG_VALUE_VERSION			_T("version")
#define REG_VALUE_LOCAL				_T("directory")
#define REG_VALUE_EXE				_T("exe")
#define REG_VALUE_PATCHSVR			_T("address")
#define REG_VALUE_PATCHPORT			_T("port")
#define REG_VALUE_DISCLAIMER		_T("disclaimer")
#define REG_VALUE_MODE				_T("mode")

#define DEFAULT_SCREEN_X			1024
#define DEFAULT_SCREEN_Y			768
//=====================================================================================
// ���� �������� ����Ǿ� �ϴ� �׸��
// String Table �� Error Message ����
#define HOMEPAGE_NAME				_T("http://www.4story.de/")
#define LAUNCHERWEB_NAME			_T("http://www.4story.de/launcher")
#define REG_COUNTRY					_T("")
#define TOOLTIP_START				_T("Start the game")
#define TOOLTIP_CLOSE				_T("Close the game")
#define TOOLTIP_HOME				_T("Go to homepage")
#define TOOLTIP_OPTION				_T("Set the option")
#define COUNTRY_CODE				_T("EU")
//=====================================================================================

#define PROGRESS_TYPE_DOWNLOAD		1
#define PROGRESS_TYPE_UNZIP			2
#define PROGRESS_TYPE_DEFAULT		3

#define FTP_USER					_T("zemi4story")
#define FTP_PASS					_T("dhkdeoqkr")

#define OPTION_LOW					0
#define OPTION_MID					1
#define OPTION_HI					2

// �׷��� ����
//#define REG_WINDOW			_T("WindowedMode")
//#define REG_SHADER			_T("UseShader")
//#define REG_CHARACTER			_T("ObjDETAIL")		// ĳ���� ǰ��
//#define REG_PAPERMATRIX		_T("MapDETAIL")		// ���� ǰ��
//#define REG_BACK				_T("TextureDETAIL")	// ���þ�


typedef struct tagPATCHFILE
{
	DWORD m_dwVersion;
	CString m_strPath;
	CString m_strName;
	DWORD m_dwSize;
	DWORD m_dwBetaVer;
}PATCHFILE, *LPPATCHFILE;

typedef vector<LPPATCHFILE>			VPATCHFILE, *LPVPATCHFILE;

typedef struct tagD3DDEVICE
{
	LPDIRECT3D9 m_pD3D;
	D3DPRESENT_PARAMETERS m_vPRESENT;
}D3DDEVICE, *LPD3DDEVICE;

// CStoryDlg ��ȭ ����
class CStoryDlg : public CDialog
{
// ����
public:
	CStoryDlg(CWnd* pParent = NULL);	// ǥ�� ������
	~CStoryDlg();
	enum { IDD = IDD_STORY_DIALOG };
	enum {	DOWN_NONE = 0,	//	�⺻��
			DOWN_PREPATCH,	//	Pre��ġ
			DOWN_INCOMPRE,	//	Pre��ġ�̾�ޱ�
			DOWN_ERR};		//	����

	void OnConnect(int nErrorCode);
	void OnClose(int nErrorCode);
	DWORD OnReceive(CPacket * pPacket);
	void SessionStart(CString strIp, DWORD dwPort);
	void Say(CPacket * pPacket);

	void InitWeb();
	BYTE ReadRegistry();
	BYTE CopyRegistry();
	void ReadURLFile();
	void ReadTextFile();
	void ReadDisclaimerFile();
	BYTE SetDisclaimer(BYTE bDisclaimer);
	void LoadSkin();
	void SetControlPos();	// ��Ʈ�� ��ġ ����
	CString LoadString(int nID);
	BYTE WriteStartRegistry(BYTE bCheak);
	BYTE CheakStartRegistry();

	void DownloadEnd();
	void StartGame();

	static DWORD WINAPI _Download(LPVOID lpParam);
	DWORD Download();
	BYTE PrePatchCheak(LPPATCHFILE& pPatchFile);
	BYTE SetPath(LPPATCHFILE pPatchFile, BYTE bPatchType);
	void DownloadFinish();

	BYTE CreateDirectoryEx(CString strPath);
	void Progress(CString strName, DWORD dwSize, DWORD dwCurrent, __int64 nTotal, BYTE bType);
	int Unzip(LPCTSTR strZip, LPCTSTR strDirectory);
	void VerifyDirectory(LPCTSTR target, LPCTSTR path, BYTE bHaveFile);
	void CheckPatch();
	void RemoveDownloadDirectory();
	void RemoveOldPrePatch();
	void DeleteDirectory(LPCTSTR strPath);
	BYTE SetVersion(DWORD dwVersion);

	void InfoFileWrite();
	void InfoFileRead();
	BYTE FindPatchFile(CString lpPathName);

	BYTE LaunchTClient();
	BYTE BeginProtect();
	void EndProtect();
	void EndThread();

	BYTE WriteRegistry();
	void InitCAPS(); //��ǻ�� ��� �˻�
	BYTE InitDevice();
	void CollectResolution(); // �ػ� �˻�
	CString GetLocalString();

	DWORD OnCT_NEWPATCH_ACK(CPacket * pPacket);
	void SendCT_NEWPATCH_REQ();
	void SendCT_PATCHSTART_REQ();

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButtonHomepage();
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnBnClickedChkPrepatch();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����
	virtual BOOL DestroyWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	HICON		m_hIcon;
	HBITMAP		hBmp;
	CBitmap		m_bSkin;
	CxSkinButton m_chkPrePatch;
	CWebBrowser2 m_webCtrl;

	CHSession	m_session;

	HANDLE		m_hDownload;
	VPATCHFILE	m_vPatchFile;	
	VPATCHFILE	m_vLocal;

	WORD		m_wPort;
	WORD		m_wGamePort;
	WORD		m_wFtpPort;
	DWORD		m_dwVersion;
	DWORD		m_dwNextVersion;
	DWORD		m_dwMinBetaVer;
	__int64		m_nPatchTotalSize;

	char		m_szPatchFileName[_MAX_PATH+1];
	CString		m_strAppName;
	CString 	m_strRegSubKey;
	CString 	m_strGame;
	CString 	m_strGameSvr;

	CString		m_strIP;
	CString		m_strLocal;
	CString		m_strDownload;
	CString		m_strFtpSvr;

	CString		m_strHompageURLForLuancher;
	CString		m_strNoticeURLForLuancher;
	CString		m_strSubkey;

	CString		m_strDisclaimer;
	BYTE		m_bDisclaimer;

	BYTE		m_bFirstPrePatch;
	BYTE		sFlag;
	BYTE		m_blPatchFileUpdate;
	BYTE		m_bDownloading;
	BYTE		m_bCancel;
	BYTE		m_bIsFtpConnecting;	
	BYTE		m_bFlash; // ��ư ������
	BYTE		m_bProgressingColor;



public:
	static ULONGLONG m_lVIDEOMEM;
	static ULONGLONG m_lSYSMEM;

	CProgressCtrl m_progressCurrent;
	CProgressCtrl m_progressTotal;
	CHoverButton m_bHome;
	CHoverButton m_bSetting;
	CHoverButton m_bOK;
	CHoverButton m_bCANCEL;

	// �׷��� ���� ���� ����
	CPlaySetting* m_pdlgPlaySetting;
	DWORD m_dwWindowMode;
	DWORD m_dwShaderMode;
	DWORD m_dwCharMode;
	DWORD m_dwPaperMode;
	DWORD m_dwBackMode;

	D3DDEVICE m_Device;
	
////	���ȸ��
private:
	static DWORD WINAPI _MPThread( LPVOID lpParam);
	void MPThread();
	void SetHWND( HWND hWND);
	void SetRUN( BYTE bRUN);
	void PostQUIT();
	void HackMSG();
	BYTE GetRUN();

protected:
	CTModuleProtector m_vModuleGuard;

	CRITICAL_SECTION m_cs;
	HANDLE m_hMP;
	HWND m_hWND;
	BYTE m_bRUN;

public:
	//CString m_strPARAM;
	BYTE m_bHACK;
};
