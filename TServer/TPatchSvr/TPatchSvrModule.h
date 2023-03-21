#pragma once

#define ON_RECEIVE(p)							case p : return On##p( pDB, pSession);

////////////////////// �ſ�ſ� �߿� - ���� ������ /////////////////////////////////////
//
// 1. �ڱ��ڽ��� ���� �Ϸ��� �ڵ鷯�Լ����� EC_SESSION_INVALIDCHAR�� �����Ѵ�.
//    (�ڵ鷯 �Լ��� �Ķ���ͷ� �Ѿ�� ���� pUser�� ����)
//
// 2. �ٸ� ������ ���� �Ϸ��� �������� �Ķ���ͷ� �Ͽ� CloseSession()�� ȣ���Ѵ�.
//    (�� : CloseSession(pTarget); pTarget�� ������ �����ϵ��� �����ȴ�)
//
// 3. �� �̿��� ������� ���� ������ �����ϸ� �ȵȴ�.
//
//////////////////////////////////////////////////////////////////////////////////////////


class CTPatchSvrModule : public CAtlServiceModuleT< CTPatchSvrModule, IDS_SERVICENAME >
{
protected:
	MAPTSESSION m_mapTSESSION;							// all session pool
	CRITICAL_SECTION m_csPC;	

protected:
	TCHAR m_szDBUserID[ONE_KBYTE];
	TCHAR m_szDBPasswd[ONE_KBYTE];
	TCHAR m_szDSN[ONE_KBYTE];

	BYTE m_bNumWorker;
	BYTE m_bThreadRun;
	BYTE m_bServerID;
	WORD m_wPort;

	CString m_strFTP;
	CString m_strPreFTP;
	SOCKADDR_IN m_addrLOGIN;

	HANDLE m_hWorker[MAX_THREAD];
	HANDLE m_hControl;

	HANDLE m_hIocpControl;
	HANDLE m_hIocpWork;
	SOCKET m_accept;

	CSqlDatabase m_db;
	CSession m_listen;

	COverlappedEx m_ovAccept;
	CPacket m_vAccept;

protected:
	void OnSendComplete( CTPatchSession *pSession, DWORD dwIoBytes);
	void ProcessSession(
		CSqlDatabase *pDB,
		CTPatchSession * pSession,
		DWORD dwIoBytes);

	void OnInvalidSession( CTPatchSession * pSession);			// ��� ����
	void OnCloseSession( CTPatchSession * pSession);				// ��� ����
	void ClosingSession( CTPatchSession * pSession);				// ��� ����
	void CloseSession( CTPatchSession * pSession);				// ������ �����Ϸ��� �� �Լ��� ȣ��

	void ClearThread();
	void UpdateData();

	DWORD InitDB( CSqlDatabase *pDB);
	DWORD LoadData(CSqlDatabase *pDB);

	DWORD CreateThreads();
	BYTE ResumeThreads();

	DWORD LoadConfig();
	DWORD InitNetwork();

	BYTE WaitForConnect();
	BYTE Accept();

	DWORD OnReceive(
		CSqlDatabase *pDB,
		CTPatchSession * pSession);

	DWORD ControlThread();
	DWORD WorkThread();

protected:
	virtual void OnERROR( DWORD dwErrorCode);

	virtual DWORD OnEnter();
	virtual void OnExit();

private:
	static DWORD WINAPI _ControlThread( LPVOID lpParam);
	static DWORD WINAPI _WorkThread( LPVOID lpParam);

protected:
	// �ý��� �޼��� �ڵ鷯
	DWORD OnSM_QUITSERVICE_REQ( CSqlDatabase *pDB, CTPatchSession * pSession);

protected:
	// Patch Server Message
	DWORD OnCT_SERVICEMONITOR_ACK( CSqlDatabase *pDB, CTPatchSession * pSession );
	DWORD OnCT_PATCH_REQ(CSqlDatabase * pDB, CTPatchSession * pSession);
	DWORD OnCT_NEWPATCH_REQ(CSqlDatabase * pDB, CTPatchSession * pSession);
	DWORD OnCT_PREPATCH_REQ(CSqlDatabase * pDB, CTPatchSession * pSession);
	DWORD OnCT_PATCHSTART_REQ(CSqlDatabase * pDB, CTPatchSession * pSession);
	DWORD OnCT_SERVICEDATACLEAR_ACK(CSqlDatabase * pDB, CTPatchSession * pSession);
	DWORD OnCT_CTRLSVR_REQ(CSqlDatabase * pDB, CTPatchSession * pSession);
	DWORD OnCT_PREPATCHCOMPLETE_REQ(CSqlDatabase * pDB, CTPatchSession * pSession);

public:
	CTPatchSvrModule();
	virtual ~CTPatchSvrModule();

public:
	DECLARE_LIBID(LIBID_TPatchSvrLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TPATCHSVR, "{A9C0CF53-7D54-43D7-B01C-D604FB9DF809}")
	HRESULT InitializeSecurity() throw()
	{
		// TODO : CoInitializeSecurity�� ȣ���ϰ� ���񽺿� 
		// �ùٸ� ���� ������
		// �����Ͻʽÿ�. PKT ���� ����, 
		// RPC_C_IMP_LEVEL_IDENTIFY ���� ���� ���� 
		// �� Null�� �ƴ� ������ ���� ������ ���� �����ϸ� �˴ϴ�.

		return S_OK;
	}
	HRESULT RegisterAppId( bool bService = false) throw()
	{
		if(!Uninstall())
			return E_FAIL;

		HRESULT hr = UpdateRegistryAppId(TRUE);
		if(FAILED(hr))
			return hr;

		CRegKey keyAppID;
		LONG lRes = keyAppID.Open( HKEY_CLASSES_ROOT, _T("AppID"), KEY_WRITE);
		if( lRes != ERROR_SUCCESS )
			return AtlHresultFromWin32(lRes);

		CRegKey key;
		lRes = key.Create( keyAppID, GetAppIdT());

		if( lRes != ERROR_SUCCESS )
			return AtlHresultFromWin32(lRes);

		key.DeleteValue(_T("LocalService"));
		if(!bService)
			return S_OK;
		key.SetStringValue(_T("LocalService"), m_szServiceName);

		// Create service
		if(!Install())
			return E_FAIL;

		return S_OK;
	}
	bool ParseCommandLine( LPCTSTR lpCmdLine, HRESULT* pnRetCode) throw()
	{
		TCHAR szTokens[] = _T("-/");
		*pnRetCode = S_OK;

		LPCTSTR lpszToken = FindOneOf( lpCmdLine, szTokens);
		while(lpszToken)
		{
			if( WordCmpI( lpszToken, _T("UnregServer")) == 0 )
			{
				*pnRetCode = UnregisterServer(TRUE);

				if(SUCCEEDED(*pnRetCode))
					*pnRetCode = UnregisterAppId();

				return false;
			}

			// Register as Local Server
			if( WordCmpI( lpszToken, _T("RegServer")) == 0 )
			{
				*pnRetCode = RegisterAppId();

				if(SUCCEEDED(*pnRetCode))
					*pnRetCode = RegisterServer(TRUE);

				return false;
			}

			if( WordCmpI( lpszToken, _T("Service")) == 0 ||
				WordCmpI( lpszToken, _T("Install")) == 0 )
			{
				*pnRetCode = RegisterAppId(true);

				if(SUCCEEDED(*pnRetCode))
					*pnRetCode = RegisterServer(TRUE);

				return false;
			}

			if( WordCmpI( lpszToken, _T("UnInstall")) == 0 )
			{
				*pnRetCode = S_OK;
				if(!Uninstall())
					*pnRetCode = E_FAIL;

				return false;
			}

			if( WordCmpI( lpszToken, _T("Name")) == 0 )
			{
				CString strNAME(FindOneOf( lpszToken, _T(" ")));
				int nPOS = 0;

				strNAME = strNAME.Tokenize( _T(" "), nPOS);
				strcpy( m_szServiceName, LPCTSTR(strNAME));
			}

			lpszToken = FindOneOf( lpszToken, szTokens);
		}

		return true;
	}
	BOOL Install() throw()
	{
		if(IsInstalled())
			return TRUE;

		// Get the executable file path
		TCHAR szFilePath[MAX_PATH + _ATL_QUOTES_SPACE];
		DWORD dwFLen = ::GetModuleFileName(NULL, szFilePath + 1, MAX_PATH);
		if( dwFLen == 0 || dwFLen == MAX_PATH )
			return FALSE;

		// Quote the FilePath before calling CreateService
		szFilePath[0] = _T('\"');
		szFilePath[dwFLen + 1] = _T('\"');
		szFilePath[dwFLen + 2] = 0;

		CString strFilePath;
		strFilePath.Format( "%s -Name %s", szFilePath, m_szServiceName);

		SC_HANDLE hSCM = ::OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if( hSCM == NULL )
		{
			TCHAR szBuf[1024];

			if( AtlLoadString( ATL_SERVICE_MANAGER_OPEN_ERROR, szBuf, 1024) == 0 )
				lstrcpy( szBuf,  _T("Could not open Service Manager"));
			MessageBox( NULL, szBuf, m_szServiceName, MB_OK);

			return FALSE;
		}

		SC_HANDLE hService = ::CreateService(
			hSCM,
			m_szServiceName,
			m_szServiceName,
			SERVICE_ALL_ACCESS,
			SERVICE_WIN32_OWN_PROCESS,
			SERVICE_DEMAND_START,
			SERVICE_ERROR_NORMAL,
			LPCSTR(strFilePath),
			NULL, NULL,
			_T("RPCSS\0"),
			NULL, NULL);

		if( hService == NULL )
		{
			::CloseServiceHandle(hSCM);
			TCHAR szBuf[1024];

			if( AtlLoadString( ATL_SERVICE_START_ERROR, szBuf, 1024) == 0 )
				lstrcpy(szBuf,  _T("Could not start service"));
			MessageBox( NULL, szBuf, m_szServiceName, MB_OK);

			return FALSE;
		}

		::CloseServiceHandle(hService);
		::CloseServiceHandle(hSCM);

		return TRUE;
	}
	HRESULT PreMessageLoop( int nShowCmd);
	HRESULT PostMessageLoop();
};

extern CTPatchSvrModule _AtlModule;
