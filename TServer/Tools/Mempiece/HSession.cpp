// HSession.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"

// CHSession

CHSession::CHSession()
{
	m_pOwner = NULL;
	m_bValid = FALSE;
	m_nWroteBytes = m_nSendBufferSize = 0;
}

CHSession::~CHSession()
{
	End();
}


// CHSession ��� �Լ��Դϴ�.
void CHSession::SetOwner(CMempieceDlg *pOwner)
{
	m_pOwner = pOwner;
}
BOOL CHSession::Start(LPCTSTR strAddr, DWORD dwPort)
{
	End();

#ifndef _AFXDLL                                                                                    
#define _AFX_SOCK_THREAD_STATE AFX_MODULE_THREAD_STATE
#define _afxSockThreadState AfxGetModuleThreadState()
	_AFX_SOCK_THREAD_STATE* pState = _afxSockThreadState;
	if (pState->m_pmapSocketHandle == NULL)
		pState->m_pmapSocketHandle = new CMapPtrToPtr;
	if (pState->m_pmapDeadSockets == NULL)
		pState->m_pmapDeadSockets = new CMapPtrToPtr;
	if (pState->m_plistSocketNotifications == NULL)
		pState->m_plistSocketNotifications = new CPtrList;
#endif

	if(!Create())
	{
		int nError = GetLastError();
		return FALSE;
	}
	if(!Connect(strAddr, dwPort))
	{
		int err = GetLastError();
		if( err != WSAEWOULDBLOCK )
		{
			End();
			return FALSE;
		}
	}
	return TRUE;
}
void CHSession::End()
{
	m_bValid = FALSE;

	while(!m_qSEND.empty())
	{
		delete m_qSEND.front();
		m_qSEND.pop();
	}

	if(m_hSocket != INVALID_SOCKET)
		Close();
}

void CHSession::Say(CPacket *pPacket)
{
	if(!IsValid())
	{
		delete pPacket;
		return;
	}

	m_qSEND.push(pPacket);
	SendPacket(	m_qSEND.front());
}
BOOL CHSession::SendPacket(CPacket *pPacket)
{
	if(!pPacket)
		return FALSE;
	
	m_nSendBufferSize = pPacket->GetSize();	
	
	while( m_nWroteBytes < m_nSendBufferSize )
	{
		int nWrote = Send(pPacket->GetBuffer() + m_nWroteBytes, m_nSendBufferSize - m_nWroteBytes);
		if(nWrote != SOCKET_ERROR)
			m_nWroteBytes += nWrote;
		else
		{
			int err = GetLastError();
			if(err == WSAEWOULDBLOCK)
				return FALSE;
			else
				return FALSE;
		}
	}

	m_qSEND.pop();
	delete pPacket;
	m_nWroteBytes = m_nSendBufferSize = 0;

	return TRUE;
}

BOOL CHSession::IsValid()
{
	return m_bValid;
}
void CHSession::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CAsyncSocket::OnAccept(nErrorCode);
}

void CHSession::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_bValid = FALSE;
	m_pOwner->OnClose(nErrorCode);
	End();
	CAsyncSocket::OnClose(nErrorCode);
}

void CHSession::OnConnect(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(!m_pOwner) return;

	if( nErrorCode == 0)
	{
		m_bValid = TRUE;
	}
	m_pOwner->OnConnect(nErrorCode);

	CAsyncSocket::OnConnect(nErrorCode);
}

void CHSession::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(nErrorCode == 0)
	{
		if(m_packet.IsReadBufferFull()) m_packet.ExpandIoBuffer();

		int nRead = Receive( 
			m_packet.GetBuffer() + m_packet.GetReadBytes(), 
			m_packet.m_dwBufferSize - m_packet.GetReadBytes());	

		if( !m_packet.ReadBytes( nRead )) return;		

		while(0 != m_packet.GetReadBytes() && 
			m_packet.GetReadBytes() >= m_packet.GetSize() )
		{
			if(m_pOwner->OnReceive(&m_packet))
				End();
			m_packet.Flush();
		}
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

void CHSession::OnSend(int nErrorCode)
{
	while(!m_qSEND.empty())
	{
		if(!SendPacket(m_qSEND.front()))
			break;
	}
	CAsyncSocket::OnSend(nErrorCode);
}
