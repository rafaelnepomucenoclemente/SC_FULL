// 4StoryDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Unzip.h"
#include "4Story.h"
#include "4StoryDlg.h"
#include <XTrapArg.h>
#include <XTrap4Launcher.h>
#include ".\4storydlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TMP_TIMER						(100)

// CStoryDlg 대화 상자

ULONGLONG CStoryDlg::m_lVIDEOMEM = 0;
ULONGLONG CStoryDlg::m_lSYSMEM = 0;

CStoryDlg::CStoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStoryDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_strHompageURLForLuancher = HOMEPAGE_NAME;
	m_strNoticeURLForLuancher = LAUNCHERWEB_NAME;

	m_bHACK = TMP_HACK_NONE;
	m_bRUN = FALSE;
	m_hWND = NULL;
	m_hMP = NULL;

	m_bCancel = FALSE;
	m_blPatchFileUpdate = FALSE;
	m_bDownloading = FALSE;
	m_bIsFtpConnecting = FALSE;
	m_strAppName = APP_NAME;
	m_hDownload = NULL;
	m_bProgressing = FALSE;
	m_bSecond	= 0;
}
CStoryDlg::~CStoryDlg() 
{
	if( sFlag )
	{
		m_bSkin.Detach();
		//::DeleteObject(hBmp);
	}

	// 버튼 깜박임
	if(m_bFlash)
	{
		m_bFlash = FALSE;
		KillTimer(1);
	}
	if(m_bSecond)
	{
		m_bSecond = 0;
		KillTimer(99);
	}

}
void CStoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_CURRENT, m_progressCurrent);
	DDX_Control(pDX, IDC_PROGRESS_TOTAL, m_progressTotal);
	DDX_Control(pDX, IDC_BUTTON_HOMEPAGE, m_bHome);
	DDX_Control(pDX, IDC_BUTTON_SETTING, m_bSetting);
	DDX_Control(pDX, IDOK, m_bOK);
	DDX_Control(pDX, IDCANCEL, m_bCANCEL);
}

BEGIN_MESSAGE_MAP(CStoryDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_HOMEPAGE, OnBnClickedButtonHomepage)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CStoryDlg 메시지 처리기

BOOL CStoryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_bCancel = FALSE;
	m_blPatchFileUpdate = FALSE;
	m_bDownloading = FALSE;
	m_bIsFtpConnecting = FALSE;
	m_strAppName = APP_NAME;
	m_hDownload = NULL;
	m_bProgressing = FALSE;

	HMODULE hModule = ::GetModuleHandle(NULL);
	if(hModule == 0)
	{			
		OnCancel();
		return FALSE;
	}
	::GetModuleFileName(hModule, m_szPatchFileName, _MAX_PATH);

	char GAME_TITLE[256]={0,};	
	CString strNew = m_szPatchFileName;	
	int n = strNew.Find(APP_EXT);
	if(n > 0)
	{
		strNew.Delete(n,lstrlen(APP_EXT));
		n = strNew.ReverseFind('\\');
		if(n >= 0)
			strNew.Delete(0, n+1);
	}
	strcpy(GAME_TITLE,strNew);

	HANDLE hMutex = NULL;
	if( !OpenMutex(MUTEX_ALL_ACCESS,false,GAME_TITLE) )
		hMutex = CreateMutex(NULL,TRUE,GAME_TITLE);
	else
	{	
		memset(GAME_TITLE,0,sizeof(GAME_TITLE));
		AfxMessageBox(_T("4Story Launcher Already Running !!"));
		OnCancel();
		return FALSE;
	}

	WSADATA wsaDATA;
	WORD wVersionRequested = MAKEWORD( 2, 2);
	int nERROR = WSAStartup( wVersionRequested, &wsaDATA);

//	ReadURLFile();
//	ReadTextFile();

	SetHWND(GetSafeHwnd());
	m_vModuleGuard.UseDynamicIB(FALSE);

	
	XTrap_L_Patch((char*)xArg, NULL, 60000);
	//InitWeb();

	if(!ReadRegistry())
	{
		if( AfxMessageBox(_T("Can not read Registry"),MB_OK ) == IDOK)
		{
			OnCancel();
			return FALSE;
		}
	}

	m_session.SetOwner(this);
	SessionStart(m_strIP, m_wPort);

	m_progressCurrent.SetRange( 0, 100 );
	m_progressTotal.SetRange( 0, 100 );

	CButton * pOK = (CButton *)GetDlgItem(IDOK);
	if(pOK)
		pOK->EnableWindow(FALSE);

	// [환경설정] 버튼 비활성화 JINUK
	CButton * pSet = (CButton *)GetDlgItem(IDC_BUTTON_SETTING);
	if(pSet)
		pSet->EnableWindow(TRUE);

	m_bFlash = FALSE; // 버튼 깜박임

	////////////////////////////////////////////////////////////////
	m_bOK.LoadBitmap(IDB_BITMAP_SN, IDB_BITMAP_SP, IDB_BITMAP_SH, IDB_BITMAP_SD);
	m_bCANCEL.LoadBitmap(IDB_BITMAP_EN, IDB_BITMAP_EP, IDB_BITMAP_EH, 0);
	m_bHome.LoadBitmap(IDB_BITMAP_HN, IDB_BITMAP_HP, IDB_BITMAP_HH, 0);
	m_bSetting.LoadBitmap(IDB_BITMAP_ON, IDB_BITMAP_OP, IDB_BITMAP_OH, 0);

	CString str = TOOLTIP_START;
	m_bOK.SetToolTipText(&str);

	str = TOOLTIP_CLOSE;
	m_bCANCEL.SetToolTipText(&str);

	str = TOOLTIP_HOME;
	m_bHome.SetToolTipText(&str);

	str = TOOLTIP_OPTION;
	m_bSetting.SetToolTipText(&str);

	LoadSkin();
	SetControlPos(); // 컨트롤 위치 지정

	// progress bar color change
	::SendMessage(m_progressCurrent, PBM_SETBARCOLOR, 0, (LPARAM)(COLORREF)RGB(0,169,157));
	::SendMessage(m_progressTotal, PBM_SETBARCOLOR, 0, (LPARAM)(COLORREF)RGB(0,169,157));

	m_progressCurrent.SetBkColor(TRANSPARENT);
	m_progressTotal.SetBkColor(TRANSPARENT);

	SetWindowText(m_strAppName);

	

	// 환경설정 다이얼로그
	//m_pdlgPlaySetting = new CPlaySetting();
	//m_pdlgPlaySetting->Create(IDD_PLAYSET);
	//m_pdlgPlaySetting->ShowWindow(SW_HIDE);
	SetTimer(99,1000,NULL);
	if( CheckIsFirst() )
	{
		ShowSettingFrame();

		int SCREEN_X = GetSystemMetrics( SM_CXSCREEN );
		int SCREEN_Y = GetSystemMetrics( SM_CYSCREEN );

		CString strResolution;
		strResolution.Format( _T("%d X %d"), SCREEN_X, SCREEN_Y );

		CGameSetting*	pGameSetting = CGameSetting::GetInstance();
		pGameSetting->SetResolutionCtrl( strResolution );
		pGameSetting->SetResolution( strResolution );
	}

	
	SetTimer(99,1000,NULL);
	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CStoryDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다. 
HCURSOR CStoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CStoryDlg::DestroyWindow()
{
	DownloadEnd();
	return CDialog::DestroyWindow();
}

LRESULT CStoryDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	switch(message)
	{
	case WM_RESTART_PATCH:
		{
			OnCancel();

			m_strDownload.ReleaseBuffer();
			CString strNew=m_szPatchFileName;

			STARTUPINFO StartupInfo;
			PROCESS_INFORMATION ProcessInfo;

			ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
			ZeroMemory(&ProcessInfo, sizeof(PROCESS_INFORMATION)); 

			StartupInfo.cb = sizeof(STARTUPINFO);
			StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
			StartupInfo.wShowWindow = SW_SHOWNORMAL;

			int n = strNew.ReverseFind('.');
			strNew.Insert(n,BACKUP_EXT);

			if(!CreateProcess(strNew, NULL, 
				NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo))
				AfxMessageBox(IDS_DOWNLOAD_FAIL);
		}
		break;
	case WM_STOP_DOWNLOAD:
		DestroyWindow();
		break;

	case WM_CLOSE_SESSION:
		DownloadEnd();
		break;
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

void CStoryDlg::InitWeb()
{
	CRect rect;
	GetClientRect(&rect);

	CRect WebRect( 0, 0, rect.Width()/2, rect.Height()/2 );

	CString strUrl = m_strNoticeURLForLuancher;
	if(strUrl == _T(""))
		strUrl = LAUNCHERWEB_NAME;

	m_webCtrl.Create(_T("WebControl"), WS_CHILD|WS_VISIBLE, WebRect, (CWnd*)this, 1001 );
	m_webCtrl.Navigate( strUrl, NULL, NULL, NULL, NULL );
	m_webCtrl.MoveWindow(rect.Width()/3-30, 92, rect.Width()/2+137, rect.Height()/2+46);	
}

BOOL CStoryDlg::ReadRegistry()
{
	BYTE bCurrent = FALSE;

	HKEY hKeyRet;	
	HKEY hKey = HKEY_LOCAL_MACHINE;

	CString strSubkey;
	strSubkey = m_strSubkey;
	if(strSubkey == _T(""))
		strSubkey = m_strAppName + REG_COUNTRY;

	strSubkey += _T("\\PB");	

	m_strRegSubKey.Format(_T("%s%s"), REG_SUBKEY, strSubkey);

	int err = RegOpenKey(hKey, m_strRegSubKey, &hKeyRet);
	if(ERROR_SUCCESS != err)
	{
		RegCloseKey(hKeyRet);
		//hKey = HKEY_CURRENT_USER;

		bCurrent = TRUE;
	}

	err = RegCreateKey(hKey, m_strRegSubKey, &hKeyRet);
	if(ERROR_SUCCESS != err)
		return FALSE;

	BYTE	data[1024];
	DWORD   type;
	DWORD   cbdata =1024;

	//version
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, REG_VALUE_VERSION, NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return FALSE;

	m_dwVersion = *((LPDWORD)data);
	m_dwNextVersion = m_dwVersion;

	//local path 
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, REG_VALUE_LOCAL, NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_SZ)
		return FALSE;

	m_strLocal = m_strDownload = data;

	//exe file
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, REG_VALUE_EXE, NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_SZ)
		return FALSE;

	m_strGame = data;

	//patch svr address
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, REG_VALUE_PATCHSVR, NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_SZ)
		return FALSE;

	m_strIP = data;

	//patch svr port
	cbdata = 1024;
	memset(data, 0, 1024);
	err = RegQueryValueEx(hKeyRet, REG_VALUE_PATCHPORT, NULL, &type, data, &cbdata);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return FALSE;

	m_wPort = *((LPWORD)data);

	RegCloseKey(hKeyRet);

	if(bCurrent)
	{
		if(!CopyRegistry())
			return FALSE;
	}

	return TRUE;
}

void CStoryDlg::ReadURLFile()
{
	CStdioFile file;
	if( file.Open( "url.txt", CFile::modeRead | CFile::typeText ) )
	{
		file.ReadString( m_strHompageURLForLuancher );

		CString strLinkForGame;
		file.ReadString( strLinkForGame );

		CString strBtnNameForGame;
		file.ReadString( strBtnNameForGame );

		file.ReadString( m_strNoticeURLForLuancher );

		file.Close();
	}
}

void CStoryDlg::ReadTextFile()
{
	m_strSubkey = _T("");

	CStdioFile file;
	if( file.Open( "4story.txt", CFile::modeRead | CFile::typeText ) )
	{
		file.ReadString( m_strSubkey );

		file.Close();
	}
}

BOOL CStoryDlg::CopyRegistry()
{
	HKEY hKeyRet;
	HKEY hKey = HKEY_LOCAL_MACHINE;

	CString strSubkey;
	strSubkey = m_strAppName + REG_COUNTRY;	
	strSubkey += _T("\\PB");

	m_strRegSubKey.Format(_T("%s%s"), REG_SUBKEY, strSubkey);

	int err = RegCreateKey(hKey, m_strRegSubKey, &hKeyRet);
	if(ERROR_SUCCESS != err)
		return FALSE;

	BYTE	data[1024];
	DWORD   type = REG_DWORD;
	DWORD   cbData = 4;

	memcpy(data, &m_dwVersion, sizeof(DWORD));
	err = RegSetValueEx(hKeyRet, REG_VALUE_VERSION, 0, REG_DWORD, data, cbData);
	if(ERROR_SUCCESS != err)
		return FALSE;

	LPCSTR strLocal = m_strLocal;
	err = RegSetValueEx(
		hKeyRet,
		REG_VALUE_LOCAL, 
		0, 
		REG_SZ, 
		(LPBYTE)strLocal, 
		(DWORD) (lstrlen(strLocal)+1)*sizeof(TCHAR));
	if(ERROR_SUCCESS != err)
		return FALSE;

	LPCSTR strGame = m_strGame;
	err = RegSetValueEx(
		hKeyRet,
		REG_VALUE_EXE, 
		0, 
		REG_SZ, 
		(LPBYTE)strGame, 
		(DWORD) (lstrlen(strGame)+1)*sizeof(TCHAR));
	if(ERROR_SUCCESS != err)
		return FALSE;

	LPCSTR strIP = m_strIP;
	err = RegSetValueEx(
		hKeyRet,
		REG_VALUE_PATCHSVR, 
		0, 
		REG_SZ, 
		(LPBYTE)strIP, 
		(DWORD) (lstrlen(strIP)+1)*sizeof(TCHAR));
	if(ERROR_SUCCESS != err)
		return FALSE;

	DWORD dwPort = m_wPort;
	memcpy(data, &dwPort, sizeof(DWORD));
	err = RegSetValueEx(hKeyRet, REG_VALUE_PATCHPORT, 0, REG_DWORD, data, cbData);
	if(ERROR_SUCCESS != err)
		return FALSE;

	RegCloseKey(hKeyRet);
	return TRUE;
}
void CStoryDlg::LoadSkin()
{
	sFlag = m_bSkin.LoadBitmap(IDB_BITMAP_BASE);

	if( sFlag )
	{
		BITMAP bmp;
		m_bSkin.GetBitmap(&bmp);

		SetWindowPos( NULL, 0, 0, bmp.bmWidth, bmp.bmHeight, SWP_NOZORDER );
	}
}
void CStoryDlg::SetControlPos()
{
	CRect rect;
	GetClientRect(&rect);

	//m_webCtrl.MoveWindow(rect.Width()/3-30, 92, rect.Width()/2+137, rect.Height()/2+46);

	m_progressCurrent.MoveWindow( rect.Width()/2-66, 431, rect.Width()/2+42, 8 );
	m_progressTotal.MoveWindow( rect.Width()/2-66, 447, rect.Width()/2+42, 8 );

	CRect bRect;
	GetDlgItem(IDOK)->GetWindowRect(&bRect);

	m_bHome.MoveWindow( 229, 476, bRect.Width(), bRect.Height() );
	m_bSetting.MoveWindow( 229+bRect.Width()+18, 476, bRect.Width(), bRect.Height() );
	m_bOK.MoveWindow( 229+bRect.Width()*2+36, 476, bRect.Width(), bRect.Height() );
	m_bCANCEL.MoveWindow( 229+bRect.Width()*3+54, 476, bRect.Width(), bRect.Height() );	
}
CString CStoryDlg::LoadString(int nID)
{
	CString strMsg;
	strMsg.LoadString(nID);
	return strMsg;
}
void CStoryDlg::OnConnect(int nErrorCode)
{
	if(nErrorCode)
	{
		AfxMessageBox(LoadString(IDS_CONNECT_FAIL));
		return;
	}
	else
	{
		CheckRunningExe(m_strGame);
		SendCT_PATCH_REQ();
	}
}
void CStoryDlg::OnClose(int nErrorCode)
{
	if(nErrorCode)
	{
		DownloadEnd();
		CString str;
		str.Format(_T("Error Code %d"), nErrorCode);
		AfxMessageBox(str);
	}
}
DWORD CStoryDlg::OnReceive(CPacket * pPacket)
{
	switch(pPacket->GetID())
	{
		HP_RECEIVE(CT_PATCH_ACK)
	default:
		return 1;
	}
}
void CStoryDlg::SessionStart(CString strIp, DWORD dwPort)
{
	if(!m_session.Start(strIp, dwPort))
		AfxMessageBox(LoadString(IDS_CONNECT_FAIL));
}
void CStoryDlg::Say(CPacket * pPacket)
{
	m_session.Say(pPacket);
}

DWORD WINAPI CStoryDlg::_Download(LPVOID lpParam)
{
	return ((CStoryDlg*)lpParam)->Download();
}
DWORD CStoryDlg::Download()
{
	m_bDownloading = TRUE;

	////////////////////////////////////////////////
	// 현승룡 웹 뜨기전까지 쓰레드 실행 막음
	while( m_webCtrl.GetBusy() )
		Sleep(500);
	////////////////////////////////////////////////

	CFile fileNew;
	CStdioFile * remotefile = NULL;

	__int64 nTotalRead = 0;
	size_t nTotal = m_qPatchFile.size();
	int nCurrent=0;
	DWORD	dwRead=0;

	while(m_bDownloading)
	{
		LPPATCHFILE pPatchFile = NULL;
		if(m_qPatchFile.size())
			pPatchFile = (LPPATCHFILE)m_qPatchFile.front();

		if(!pPatchFile || !m_bDownloading )
			break;

		if(!pPatchFile->m_strPath.IsEmpty())
		{
			CString strPathName = m_strDownload+_T("\\")+pPatchFile->m_strPath;
			if(!CreateDirectoryEx(strPathName))
			{
				m_bDownloading = FALSE;
				break;
			}
			if(!SetCurrentDirectory(strPathName))
			{
				m_bDownloading = FALSE;
				break;
			}
		}
		else
		{	
			if(!SetCurrentDirectory(m_strDownload))
			{
				m_bDownloading = FALSE;
				break;
			}
		}

		char	lpBuffer[1024+1];
		DWORD	dwNumberOfBytesRead;

		TCHAR   szCause[255];
		CString Cause;
		Cause.Format("YES");

		CString strURL = m_strFtpSvr + _T("/");
		if(!pPatchFile->m_strPath.IsEmpty())
			strURL += pPatchFile->m_strPath + _T("/");

		strURL += pPatchFile->m_strName;

		TRY
		{
			CInternetSession mysession;
			remotefile = mysession.OpenURL(strURL,1,INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_RELOAD);
			if(!remotefile)
			{
				m_bDownloading = FALSE;
				break;
			}

			remotefile->Seek(dwRead, CFile::begin);

			if(fileNew.m_hFile == CFile::hFileNull)
			{
				fileNew.Open(pPatchFile->m_strName, CFile::modeCreate | CFile::modeWrite);
				if(fileNew.m_hFile == CFile::hFileNull)
				{
					m_bDownloading = FALSE;
					break;
				}
			}

			while (dwNumberOfBytesRead = remotefile->Read(lpBuffer, 1024))
			{
				if(!m_bDownloading)
					break;

				fileNew.Write(lpBuffer, dwNumberOfBytesRead);
				dwRead += dwNumberOfBytesRead;
				nTotalRead += dwNumberOfBytesRead;
				Progress(pPatchFile->m_strName, pPatchFile->m_dwSize, dwRead, nTotalRead,PROGRESS_TYPE_DOWNLOAD);
			}

			remotefile->Close();
			delete remotefile;
			remotefile = NULL;
			dwRead = 0;

			fileNew.Close();

			if(m_bDownloading)
			{
				CString strSource, strTarget;
				strTarget.Empty();
				strSource.Empty();

				strSource = m_strDownload;
				strSource += _T("\\");

				if(!pPatchFile->m_strPath.IsEmpty())
				{
					strSource += pPatchFile->m_strPath + _T("\\");
					strTarget = _T("\\")+pPatchFile->m_strPath;
				}
				strSource += pPatchFile->m_strName;
				Progress(pPatchFile->m_strName, pPatchFile->m_dwSize, dwRead, nTotalRead, PROGRESS_TYPE_UNZIP);
				if( UNZ_OK != Unzip( strSource, strTarget ))
				{
					m_bDownloading = FALSE;
					break;
				}
				if(!m_blPatchFileUpdate)
                    SetVersion(pPatchFile->m_dwVersion);

				delete pPatchFile;
				pPatchFile = NULL;
				m_qPatchFile.pop();

				if(m_blPatchFileUpdate)
					break;
			}
		}
		CATCH_ALL(error)
		{
			error->GetErrorMessage(szCause,254,NULL);

			if(remotefile)
			{
				remotefile->Close();
				delete remotefile;
				remotefile = NULL;
			}

			Cause.Format(LoadString(IDS_DOWNLOAD_RETRY), szCause);
			if(AfxMessageBox(Cause, MB_YESNO) == IDYES)
				continue;
			else
				m_bDownloading = FALSE;

			if(fileNew.m_hFile != CFile::hFileNull)
				fileNew.Close();
		}
		END_CATCH_ALL;
	}

	if(fileNew.m_hFile != CFile::hFileNull)
		fileNew.Close();

	if(remotefile)
	{
		remotefile->Close();
		delete remotefile;
		remotefile = NULL;
	}

	DownloadFinish();
	m_bDownloading = FALSE;

	return 0;
}
void CStoryDlg::DownloadFinish()
{
	RemoveDownloadDirectory();

	if(m_bDownloading)
		CheckPatch();
	else
	{
		if(m_bCancel)
			PostMessage(WM_STOP_DOWNLOAD);
		else
			AfxMessageBox(LoadString(IDS_FTP_FAIL));
	}

	PostMessage(WM_CLOSE_SESSION);
}

void CStoryDlg::DownloadEnd()
{
	m_bDownloading = FALSE;

	if(m_bProgressing)
		return;

	if( m_hDownload )
	{
		WaitForSingleObject(m_hDownload,10000);
		CloseHandle(m_hDownload);
		m_hDownload = NULL;
		RemoveDownloadDirectory();
	}

	while(m_qPatchFile.size())
	{
		delete m_qPatchFile.front();
		m_qPatchFile.pop();
	}

	if(m_session.m_hSocket != INVALID_SOCKET)
		m_session.End();
}
void CStoryDlg::RemoveDownloadDirectory()
{
	DeleteDirectory(m_strDownload);

	if(SetCurrentDirectory(m_strLocal))
		_rmdir(m_strDownload);
}
void CStoryDlg::DeleteDirectory(LPCTSTR strPath)
{
	WIN32_FIND_DATA FileData;
	if(SetCurrentDirectory(strPath))
	{
		HANDLE hSearch = FindFirstFile(_T("*"), &FileData);
		if( hSearch == INVALID_HANDLE_VALUE) return;

		BOOL bContinue = TRUE;
		while(bContinue)
		{
			if( FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if( 0!=strcmp(FileData.cFileName, ".") && 
					0!=strcmp(FileData.cFileName, "..") )
				{
					CString strFullPath = strPath;

					strFullPath+= _T("\\");
					strFullPath += FileData.cFileName;

					DeleteDirectory(strFullPath);
					if(SetCurrentDirectory(strPath))
						_rmdir(strFullPath);
				}
			}
			else
				DeleteFile(FileData.cFileName);

			if(!FindNextFile(hSearch, &FileData)) bContinue = FALSE;
		}

		FindClose(hSearch);
	}
}

void CStoryDlg::CheckPatch()
{
	if(m_blPatchFileUpdate)
		PostMessage(WM_RESTART_PATCH);
	else
	{
		m_strDownload.ReleaseBuffer();
		CString strNew=m_szPatchFileName;

		// 게임 시작 버튼 활성화
		CButton * pOK = (CButton *)GetDlgItem(IDOK);
		if(pOK)
		{
			m_bFlash = TRUE; // 버튼 깜박임
			pOK->EnableWindow(TRUE);
			SetTimer(1, 500, NULL);
		}

		// 환경설정 버튼 활성화
		CButton * pSet = (CButton *)GetDlgItem(IDC_BUTTON_SETTING);
		if(pSet)
		{
			pSet->EnableWindow(TRUE);
		}

		int n = strNew.Find(BACKUP_EXT);
		if(n > 0)
		{
			strNew.Delete(n,lstrlen(BACKUP_EXT));
			n = strNew.ReverseFind('\\');
			if(n >= 0)
				strNew.Delete(0, n+1);

			CopyFile(m_szPatchFileName, strNew, FALSE);
		}
	}	
}
int CStoryDlg::Unzip(LPCTSTR strZip, LPCTSTR strDirectory)
{
	int err = UNZ_OK;
	unz_global_info zipinfo;

	unzFile zip = unzOpen( strZip );
	if( NULL == zip )
		return -1;

	err = unzGetGlobalInfo( zip, &zipinfo );
	if( UNZ_OK != err)
	{
		unzClose( zip );
		return err;
	}

	DWORD totalcnt = zipinfo.number_entry;

	err =unzGoToFirstFile( zip );
	if( UNZ_OK != err)
	{
		unzClose( zip );
		return err;
	}

	for( DWORD i = 0; i < totalcnt && err == UNZ_OK; i++)
	{
		if( UNZ_OK == err || UNZ_END_OF_LIST_OF_FILE == err )
		{
			TCHAR szFileName[256];
			unz_file_info file_info;

			err = unzGetCurrentFileInfo( zip, &file_info, szFileName, 256, NULL, 0, NULL, 0);
			if( UNZ_OK != err )
			{
				unzClose( zip );
				return err;
			}

			CString strParse = szFileName;
			int nCurPos = 0;
			strParse.Tokenize(_T("."), nCurPos);
			if(nCurPos >= strParse.GetLength())
			{
				err = unzGoToNextFile( zip );
				continue;
			}

			VerifyDirectory(m_strLocal, strDirectory, FALSE);

			CString strTargetDir = m_strLocal + strDirectory;
			if( !SetCurrentDirectory( strTargetDir ))
			{
				unzClose( zip );
				return -1;
			}

			CString strOld, strNew;
			char szPatchFileName[_MAX_PATH], szFileExt[_MAX_PATH];
			_splitpath(m_szPatchFileName, NULL, NULL, szPatchFileName, szFileExt);

			strOld = strTargetDir+szFileName;
			if(!lstrcmpi(strOld, m_szPatchFileName))
			{
				CString strNew = szPatchFileName;
				strNew += BACKUP_EXT;
				strNew += szFileExt;
				lstrcpy(szFileName, strNew);
				m_blPatchFileUpdate = TRUE;
			}

			VerifyDirectory(strTargetDir, szFileName, TRUE);

			CFile file;
			if(!file.Open(szFileName, CFile::modeCreate|CFile::shareExclusive|CFile::modeWrite))
			{
				SetFileAttributes( szFileName, FILE_ATTRIBUTE_NORMAL );
				if( !file.Open(szFileName, CFile::modeCreate|CFile::shareExclusive|CFile::modeWrite) )
				{
					unzClose( zip );
					return -1; // 수정
				}
			}

			err = unzOpenCurrentFile( zip );
			if( UNZ_OK != err)
			{
				unzClose( zip);
				file.Close();

				return err;
			}

			DWORD dwSize = file_info.uncompressed_size;
			LPVOID data =  malloc(dwSize);

			if(! data )
			{
				unzClose( zip);
				file.Close();
				return -1;
			}

			err = unzReadCurrentFile( zip, data, dwSize );
			if( err < 0)
			{
				unzCloseCurrentFile( zip );
				unzClose( zip );
				file.Close();
				return err;
			}

			file.Write(data, dwSize);
			file.Flush();

			free(data);

			if( UNZ_CRCERROR == unzCloseCurrentFile( zip ))
			{
				unzClose( zip);
				file.Flush();
				file.Close();
				return UNZ_CRCERROR;
			}

			file.Close();
		}
		err = unzGoToNextFile( zip );
	}

	return unzClose( zip );
}
BOOL CStoryDlg::SetVersion(DWORD dwVer)
{
	HKEY hKeyRet;
	HKEY hKey = HKEY_LOCAL_MACHINE;

	CString strSubkey;
	strSubkey = m_strAppName + REG_COUNTRY;	
	strSubkey += _T("\\PB");

	m_strRegSubKey.Format(_T("%s%s"), REG_SUBKEY, strSubkey);

	int err = RegCreateKey(hKey, m_strRegSubKey, &hKeyRet);
	if(ERROR_SUCCESS != err)
		return FALSE;

	BYTE	data[1024];
	DWORD   type = REG_DWORD;
	DWORD   cbData = 4;

	memcpy(data, &dwVer, sizeof(DWORD));

	err = RegSetValueEx(hKeyRet, REG_VALUE_VERSION, 0, REG_DWORD, data, cbData);
	if(ERROR_SUCCESS != err)
		return FALSE;

	RegCloseKey(hKeyRet);
	return TRUE;
}
void CStoryDlg::VerifyDirectory(LPCTSTR target, LPCTSTR path, BOOL bHaveFile)
{
	TCHAR parse[256];
	char * tok = NULL;
	CString strDirectory;

	lstrcpy( parse, path );
	tok = strtok((char *)parse, PATH_DELIMETERS);
	if( !tok )
		return;

	strDirectory = target;

	if( bHaveFile )
	{
		do
		{
			if(lstrcmp(tok, _T(".")))
			{
				CreateDirectory(strDirectory, NULL);
				strDirectory += '\\';
				strDirectory += tok;
			}
		}while(NULL!= (tok = strtok(NULL, PATH_DELIMETERS)));
	}
	else
	{	
		CreateDirectory(strDirectory, NULL);										
		do
		{
			if(lstrcmp(tok, _T(".")))
			{	
				strDirectory += '\\';
				strDirectory += tok;
				CreateDirectory(strDirectory, NULL);										
			}
		}while(NULL!= (tok = strtok(NULL, PATH_DELIMETERS)));
	}
}
BOOL CStoryDlg::CreateDirectoryEx(CString strPath)
{
	if( strPath.IsEmpty() ) return TRUE;

	if( !CreateDirectory( strPath, NULL ))
	{
		DWORD dwErr = GetLastError();
		if( dwErr == ERROR_ALREADY_EXISTS ) return TRUE;

		if( dwErr == ERROR_PATH_NOT_FOUND )
		{
			int nPos = 0;
			int nNext = strPath.Find(_T("\\"), 0);
			while(nNext >=0 )
			{
				nPos = nNext;
				nNext = strPath.Find(_T("\\"), nPos+1 );
			}

			CString strCreate = strPath.Left( nPos );
			if( CreateDirectoryEx( strCreate) )
				return CreateDirectory(strPath, NULL );
		}
		return FALSE;
	}

	return TRUE;
}
void CStoryDlg::Progress(CString strName, DWORD dwSize, DWORD dwCurrent, __int64 nTotal, BYTE bType)
{
	if(!m_bDownloading)
		return;

	switch(bType)
	{
	case PROGRESS_TYPE_DOWNLOAD:
		{
			m_bProgressing = TRUE;
			int nPos = int(dwSize ? __int64(100) * dwCurrent / dwSize : 0);
			m_progressCurrent.SetPos( nPos );

			nPos = int(100 * nTotal / m_nPatchTotalSize);
			m_progressTotal.SetPos( nPos );
			m_bProgressing = FALSE;
		}
		break;
	default:
		break;
	}	
}

void CStoryDlg::StartGame()
{
	if(SetCurrentDirectory( m_strLocal ))
	{
		STARTUPINFO StartupInfo;
		PROCESS_INFORMATION ProcessInfo;

		ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
		ZeroMemory(&ProcessInfo, sizeof(PROCESS_INFORMATION)); 

		StartupInfo.cb = sizeof(STARTUPINFO);
		StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
		StartupInfo.wShowWindow = SW_SHOWNORMAL;

		CString strCommandLine;
		strCommandLine.Format(_T("%s %s %d"), m_strGame, m_strGameSvr, m_wGamePort);

		if(!CreateProcess(m_strGame, strCommandLine.LockBuffer(), 
			NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo))
		{
			strCommandLine.ReleaseBuffer();
			return;
		}

		strCommandLine.ReleaseBuffer();
	}
}

DWORD CStoryDlg::OnCT_PATCH_ACK(CPacket * pPacket)
{
	m_nPatchTotalSize = 0;

	DWORD dwLoginAddr;
	WORD wLoginPort;

	WORD wCount;
	DWORD dwVersion;
	CString strPath;
	CString strName;
	DWORD dwSize;

	(*pPacket)
		>> m_strFtpSvr
		>> dwLoginAddr
		>> wLoginPort
		>> wCount;

	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = dwLoginAddr;
	m_strGameSvr = inet_ntoa(addr.sin_addr);
	m_wGamePort = wLoginPort;

	for(WORD i=0; i<wCount; i++)
	{
		(*pPacket)
			>> dwVersion
			>> strPath
			>> strName
			>> dwSize;

		LPPATCHFILE pFile = new PATCHFILE();
		pFile->m_dwVersion = dwVersion;
		pFile->m_strPath = strPath;
		pFile->m_strName = strName;
		pFile->m_dwSize = dwSize;

		m_nPatchTotalSize += dwSize;
		m_qPatchFile.push(pFile);
	}

	SendCT_PATCHSTART_REQ();

	Progress(_T(""), 0, 0, 0, PROGRESS_TYPE_START);

	m_strDownload += _T("\\_download");
	CFileFind ff;
	if(ff.FindFile(m_strDownload))
		RemoveDownloadDirectory();

	if(wCount)
	{
		DWORD dwThreadID;
		CreateDirectory( m_strDownload , NULL);
		m_hDownload = CreateThread(NULL, 0, _Download, (LPVOID)this, CREATE_SUSPENDED, &dwThreadID);
		if( !m_hDownload )
		{
			AfxMessageBox(LoadString(IDS_THREAD_FAIL));
			return 1;
		}
		ResumeThread(m_hDownload);
	}
	else
	{
		m_progressCurrent.SetPos(100);
		m_progressTotal.SetPos(100);
		CheckPatch();
		return 1;
	}
	return 0;
}
void CStoryDlg::SendCT_PATCH_REQ()
{
	CPacket * pMsg = new CPacket();
	pMsg->SetID(CT_PATCH_REQ)
		<< m_dwVersion;
	Say(pMsg);
}

void CStoryDlg::SendCT_PATCHSTART_REQ()
{
	CPacket * pMsg = new CPacket();
	pMsg->SetID(CT_PATCHSTART_REQ);
	Say(pMsg);
}

void CStoryDlg::OnBnClickedButtonHomepage()
{
	CString strUrl = m_strHompageURLForLuancher;
	if(strUrl == _T(""))
		strUrl = HOMEPAGE_NAME;

	ShellExecute(NULL, _T("open"), _T("iexplore"), (LPCTSTR)strUrl, NULL, SW_SHOWNORMAL);
}

void CStoryDlg::OnBnClickedButtonSetting()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	ShowSettingFrame();
}

BOOL CStoryDlg::WriteRegistry()
{
	HKEY hKeyRet;
	HKEY hKey = HKEY_CURRENT_USER; //HKEY_LOCAL_MACHINE;

	CString strSubkey;
	strSubkey = m_strAppName + REG_COUNTRY;
	strSubkey += _T("\\Settings"); //_T("\\PB");

	m_strRegSubKey.Format(_T("%s%s"), REG_SUBKEY, strSubkey);

	int err = RegCreateKey(hKey, m_strRegSubKey, &hKeyRet);
	if(ERROR_SUCCESS != err)
		return FALSE;

	char	strBuf[1024];
	BYTE	data[1024];
	DWORD   type = REG_DWORD;
	DWORD   cbData = 4;

	// window mode
	//memcpy(data, &m_dwWindowMode, sizeof(DWORD));
	//err = RegSetValueEx(hKeyRet, REG_VALUE_WINDOW, 0, REG_DWORD, data, cbData);

	if(m_dwWindowMode == 1)
		strcpy(strBuf,"TRUE");
	else
		strcpy(strBuf,"FALSE");

	err = RegSetValueEx(hKeyRet, REG_WINDOW, 0, REG_SZ, (BYTE*)strBuf, (DWORD)strlen(strBuf));

	if(ERROR_SUCCESS != err)
		return FALSE;

	// shader mode
	if(m_dwShaderMode == 1)
		strcpy(strBuf,"TRUE");
	else
		strcpy(strBuf,"FALSE");

	err = RegSetValueEx(hKeyRet, REG_SHADER, 0, REG_SZ, (BYTE*)strBuf, (DWORD)strlen(strBuf));
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return FALSE;

	// character mode // 캐릭터 품질
	memcpy(data, &m_dwCharMode, sizeof(DWORD));
	err = RegSetValueEx(hKeyRet, REG_CHARACTER, 0, REG_DWORD, data, cbData);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return FALSE;

	// paper matrix mode // 지형 품질
	memcpy(data, &m_dwPaperMode, sizeof(DWORD));
	err = RegSetValueEx(hKeyRet, REG_MAPDETAIL, 0, REG_DWORD, data, cbData);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return FALSE;

	// background mode // 텍스쳐 품질
	memcpy(data, &m_dwBackMode, sizeof(DWORD));
	err = RegSetValueEx(hKeyRet, REG_TEXDETAIL, 0, REG_DWORD, data, cbData);
	if( ERROR_SUCCESS != err || type != REG_DWORD)
		return FALSE;

	RegCloseKey(hKeyRet);

	return TRUE;
}


void CStoryDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_bFlash)
	{
		m_bFlash = FALSE;
		KillTimer(1);
	}
	if(m_bSecond)
	{
		m_bSecond = 0;
		KillTimer(99);
	}

	//StartGame();

	SetCurrentDirectory( m_strLocal );

	EndThread();
	m_bHACK = LaunchTClient();

	OnOK();
}

void CStoryDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_bFlash)
	{
		m_bFlash = FALSE;
		KillTimer(1);
	}
	if(m_bSecond)
	{
		m_bSecond = 0;
		KillTimer(99);
	}

	if(m_bDownloading)
	{
		m_bCancel = TRUE;
		DownloadEnd();
	}
	else
		DestroyWindow();
}

BOOL CStoryDlg::OnEraseBkgnd(CDC* pDC)
{
	if( sFlag )
	{	
		CRect rect;
		GetClientRect(&rect);		

		CDC MemDC;
		MemDC.CreateCompatibleDC(pDC);
		CBitmap* pbmpOld = MemDC.SelectObject( &m_bSkin );

		BITMAP bmp;
		m_bSkin.GetBitmap(&bmp);

		pDC->StretchBlt(0, 0, rect.right, rect.bottom, &MemDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
		MemDC.SelectObject( pbmpOld );

		ReleaseDC(pDC);
	}	

	return TRUE;
	//	return CDialog::OnEraseBkgnd(pDC);
}

void CStoryDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialog::OnLButtonDown(nFlags, point);
}

void CStoryDlg::OnTimer(UINT nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch(nIDEvent)
	{
	case 1:
		m_bOK.FlashButton();
		m_bFlash++;
		break;
	case 99:
		m_bSecond++;
		break;
	}

	if(m_bFlash == 10)
		KillTimer(1);

	if(m_bSecond == 3)
	{			
		KillTimer(99);
		m_bSecond = 0;
		InitWeb();
	}

	CDialog::OnTimer(nIDEvent);
}

void CStoryDlg::OnDestroy()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.


	SetHWND(NULL);
	EndThread();
	HackMSG();	

	CDialog::OnDestroy();
}

void CStoryDlg::InitCAPS()
{
	IDxDiagProvider *pProvider = NULL;
	DXDIAG_INIT_PARAMS vPARAM;

	if( FAILED(CoCreateInstance(
		CLSID_DxDiagProvider,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IDxDiagProvider,
		(LPVOID *) &pProvider)))
		return;

	ZeroMemory( &vPARAM, sizeof(DXDIAG_INIT_PARAMS));
	vPARAM.dwDxDiagHeaderVersion = DXDIAG_DX9_SDK_VERSION;
	vPARAM.bAllowWHQLChecks = TRUE;
	vPARAM.pReserved = NULL;
	vPARAM.dwSize = sizeof(DXDIAG_INIT_PARAMS);

	if(SUCCEEDED(pProvider->Initialize(&vPARAM)))
	{
		IDxDiagContainer *pROOT = NULL;

		if(SUCCEEDED(pProvider->GetRootContainer(&pROOT)))
		{
			IDxDiagContainer *pContainer = NULL;

			if(SUCCEEDED(pROOT->GetChildContainer( L"DxDiag_SystemInfo", &pContainer)))
			{
				VARIANT vVALUE;
				VariantInit(&vVALUE);

				if(SUCCEEDED(pContainer->GetProp( L"ullPhysicalMemory", &vVALUE)))
					m_lSYSMEM = _wtoi64(vVALUE.bstrVal);

				VariantClear(&vVALUE);
				pContainer->Release();
			}

			if(SUCCEEDED(pROOT->GetChildContainer( L"DxDiag_DisplayDevices", &pContainer)))
			{
				DWORD dwCount = 0;

				if( SUCCEEDED(pContainer->GetNumberOfChildContainers(&dwCount)) && dwCount > 0 )
				{
					WCHAR szNAME[MAX_PATH];

					if(SUCCEEDED(pContainer->EnumChildContainerNames( 0, szNAME, MAX_PATH)))
					{
						IDxDiagContainer *pDisplay = NULL;

						if(SUCCEEDED(pContainer->GetChildContainer( szNAME, &pDisplay)))
						{
							VARIANT vVALUE;
							VariantInit(&vVALUE);

							if(SUCCEEDED(pDisplay->GetProp( L"szDisplayMemoryEnglish", &vVALUE)))
								m_lVIDEOMEM = _wtoi64(vVALUE.bstrVal);

							VariantClear(&vVALUE);
							pDisplay->Release();
						}
					}
				}

				pContainer->Release();
			}

			pROOT->Release();
		}
	}

	pProvider->Release();
}

BOOL CStoryDlg::InitDevice()
{
	m_Device.m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if(!m_Device.m_pD3D)
	{
		MessageBox(_T("Resolution Init Error"),APP_NAME);		
		return FALSE;
	}

	D3DDISPLAYMODE d3ddm;
	BOOL bWindowMode = FALSE;
	if(bWindowMode)
	{
		HRESULT hr = m_Device.m_pD3D->GetAdapterDisplayMode(
			D3DADAPTER_DEFAULT,
			&d3ddm);

		if(FAILED(hr))
		{
			m_Device.m_pD3D->Release();
			m_Device.m_pD3D = NULL;

			return FALSE;
		}
	}
	else
		d3ddm.Format = D3DFMT_X8R8G8B8;

	ZeroMemory( &m_Device.m_vPRESENT, sizeof(m_Device.m_vPRESENT));
	m_Device.m_vPRESENT.BackBufferFormat = d3ddm.Format;

	return TRUE;
}


void CStoryDlg::CollectResolution()
{
	DEVMODE devMode;
	::EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);
	INT nCurrentFrequently = devMode.dmDisplayFrequency;

	InitDevice();

	if(!m_Device.m_pD3D)
	{
		CString strFMT;
		strFMT.Format("%d X %d",DEFAULT_SCREEN_X,DEFAULT_SCREEN_Y);
		strFMT.Trim(_T(" "));
		theApp.InsertResolution(DEFAULT_SCREEN_X,DEFAULT_SCREEN_Y,strFMT);
		return;
	}

	UINT uCount = m_Device.m_pD3D->GetAdapterModeCount(
		D3DADAPTER_DEFAULT,
		m_Device.m_vPRESENT.BackBufferFormat);

	for( UINT i=0 ; i < uCount ; ++i )
	{
		D3DDISPLAYMODE Mode;

		if( D3D_OK  == m_Device.m_pD3D->EnumAdapterModes(
			D3DADAPTER_DEFAULT,
			m_Device.m_vPRESENT.BackBufferFormat,
			i,
			&Mode) )
		{
			if( Mode.Width >= DEFAULT_SCREEN_X &&
				Mode.Height >= DEFAULT_SCREEN_Y &&
				Mode.Format == m_Device.m_vPRESENT.BackBufferFormat &&
				Mode.RefreshRate == nCurrentFrequently )
			{
				CString strFMT;
				strFMT.Format( "%d X %d ", Mode.Width,Mode.Height );
				theApp.InsertResolution(Mode.Width,Mode.Height,strFMT);
			}
		}
	}
}
void CStoryDlg::CheckRunningExe(CString strDestEXE)
{
	if(strDestEXE.IsEmpty())
		return;

	//////////////////////////////////////////////////////////////////////////
	//TClient.exe 가 실행중이면 일정시간 기다렸다가 강제종료 시키기

	BYTE bRunTClient = TRUE;
	BYTE bDelaySecond = 10;
	BYTE bWaitCount = 0;
	CString strEXE = _T("");
	PROCESSENTRY32 proc; 
	proc.dwSize = sizeof(PROCESSENTRY32);

	while(bRunTClient && bWaitCount <= bDelaySecond)
	{
		bRunTClient = FALSE;
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		Process32First(snapshot, &proc);     
		while(Process32Next(snapshot, &proc))     
		{   
			strEXE = proc.szExeFile;

			if(strEXE == strDestEXE)
			{
				Sleep(1000);
				bRunTClient = TRUE;
				bWaitCount++;
				break;			
			}
		}		
	}
	if(bRunTClient)
	{
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, proc.th32ProcessID); 
		if(hProcess) 		
			::TerminateProcess(hProcess, 0); 		 
	}	
}

void CStoryDlg::ShowSettingFrame()
{
	static bInit = TRUE;

	// 게임설정 대화상자 모달리스로 띄우기
	CPlaySetting*	pPlaySetting = CPlaySetting::GetInstance();
	CGameSetting*	pGameSetting = CGameSetting::GetInstance();

	if( bInit )
	{
		bInit = FALSE;

		InitCAPS();

		if( m_lSYSMEM >= 1000000000 && m_lVIDEOMEM >= 256 )
			theApp.m_bOptionLevel = OPTION_HI; // High
		else if( m_lSYSMEM < 1000000000 && m_lVIDEOMEM < 256 )
			theApp.m_bOptionLevel = OPTION_LOW; // Low
		else
			theApp.m_bOptionLevel = OPTION_MID; // Med

		CollectResolution();

		pPlaySetting->Create(IDD_PLAYSET);
		pGameSetting->Create(IDD_SETTING);
	}

	pPlaySetting->ShowWindow(SW_HIDE);
	pGameSetting->ShowWindow(SW_SHOW);
}

BOOL CStoryDlg::CheckIsFirst()
{
	CString strAppName = APP_NAME;
	CString strSubkey;
	CString strRegSubKey;

	strSubkey = strAppName + REG_COUNTRY;
	strSubkey += _T("\\Settings");
	strRegSubKey.Format(_T("%s%s"), REG_SUBKEY, strSubkey);

	HKEY hKeyRet;
	if( RegOpenKey( HKEY_CURRENT_USER, strRegSubKey, &hKeyRet ) != ERROR_SUCCESS )
	{
		RegCloseKey(hKeyRet);
		return TRUE;
	}

	BYTE	data[1024];
	DWORD   type;
	DWORD   cbdata =1024;
	BOOL	bReturn = TRUE;

	memset(data, 0, 1024);
	int err = RegQueryValueEx(hKeyRet, _T("IsFirst") , NULL, &type, data, &cbdata);
	if( err == ERROR_SUCCESS && REG_DWORD )
		bReturn = *((LPWORD)data);

	if( bReturn == FALSE )
	{
		RegCloseKey( hKeyRet );
		return bReturn;
	}

	BOOL	bSetData = FALSE;
	cbdata = sizeof( BOOL );
	memset( data, 0, 1024 );
	memcpy( data, &bSetData, sizeof( BOOL ) );
	err = RegSetValueEx(hKeyRet, "IsFirst", 0, REG_DWORD, data, cbdata);
	if( err != ERROR_SUCCESS  )
	{
		RegCloseKey( hKeyRet );
		return bReturn;
	}

	RegCloseKey(hKeyRet);

	return bReturn;
}

void CStoryDlg::HackMSG()
{
	switch(m_bHACK)
	{
	case TMP_HACK_INVALID_PE	:
		{
			CString strTITLE;
			CString strMSG;

			strMSG.LoadString(IDS_ERROR_LOAD_FILE);
			::MessageBox( NULL, strMSG, APP_NAME, MB_OK);
		}

		break;

	case TMP_HACK_TIMEOUT	:
		{
			CString strTITLE;
			CString strMSG;

			strMSG.LoadString(IDS_ERROR_TIMEOUT);
			::MessageBox( NULL, strMSG, APP_NAME, MB_OK);
		}

		break;

	case TMP_HACK_FOUND		:
		{
			CString strTITLE;
			CString strMSG;

			strMSG.LoadString(IDS_ERROR_HACK_DETECTED);
			::MessageBox( NULL, strMSG, APP_NAME, MB_OK);
		}

		break;
	}
}

BYTE CStoryDlg::BeginProtect()
{
	DWORD dwThreadID;

	InitializeCriticalSection(&m_cs);
	SetRUN(TRUE);

	//if( !m_vModuleGuard.InitProtector(CString(_T(".\\TClientMP.mpc"))) ||
	if( !m_vModuleGuard.InitProtector( MAKEINTRESOURCE(IDR_MPCFILE), _T("MPCFILE")) ||
		!m_vModuleGuard.BeginWatch() )
	{
		EndProtect();
		m_bRUN = FALSE;

		return FALSE;
	}

	m_hMP = ::CreateThread(
		NULL, 0,
		_MPThread,
		(LPVOID) this,
		0, &dwThreadID);

	if(!m_hMP)
	{
		EndProtect();
		m_bRUN = FALSE;

		return FALSE;
	}

	return TRUE;
}

void CStoryDlg::EndThread()
{
	if(m_hMP)
	{
		SetRUN(FALSE);
		WaitForSingleObject( m_hMP, INFINITE);

		m_hMP = NULL;
	}
}

void CStoryDlg::EndProtect()
{
	EndThread();

	DeleteCriticalSection(&m_cs);
	m_vModuleGuard.ClearModule();
}

DWORD WINAPI CStoryDlg::_MPThread( LPVOID lpParam)
{
	((CStoryDlg *) lpParam)->MPThread();
	return 0;
}

void CStoryDlg::MPThread()
{
	while(GetRUN())
	{
		if(!m_vModuleGuard.CheckValid())
			PostQUIT();

		Sleep(TMP_TIMER);
	}
}

void CStoryDlg::SetRUN( BYTE bRUN)
{
	SMART_LOCKCS(&m_cs);
	m_bRUN = bRUN;
}

BYTE CStoryDlg::GetRUN()
{
	SMART_LOCKCS(&m_cs);
	return m_bRUN ? TRUE : FALSE;
}

void CStoryDlg::SetHWND( HWND hWND)
{
	SMART_LOCKCS(&m_cs);
	m_hWND = hWND;
}

void CStoryDlg::PostQUIT()
{
	SMART_LOCKCS(&m_cs);

	if(!m_bHACK)
		m_bHACK = m_vModuleGuard.HackDetected() ? TMP_HACK_FOUND : TMP_HACK_TIMEOUT;

	if(m_hWND)
		::PostMessage( m_hWND, WM_COMMAND, IDCANCEL, 0);
}

BYTE CStoryDlg::LaunchTClient()
{
	CTModuleProtector vLauncher;

	CString strCommandLine;
	strCommandLine.Format(_T("%s %d"), m_strGameSvr, m_wGamePort);

	if(m_bHACK)
		return m_bHACK;

	if(!m_vModuleGuard.CheckValid())
		return m_vModuleGuard.HackDetected() ? TMP_HACK_FOUND : TMP_HACK_TIMEOUT;

	if(!vLauncher.InitProtector(CString(_T(".\\TClientMP.mpc"))))
		return TMP_HACK_INVALID_PE;
	vLauncher.UseDynamicIB(FALSE);

	return vLauncher.ExecPE( &CString(_T(".\\TClient.exe")), &strCommandLine) ? TMP_HACK_NONE : TMP_HACK_INVALID_PE;
}

CString CStoryDlg::GetLocalString()
{
	return m_strLocal;
}

