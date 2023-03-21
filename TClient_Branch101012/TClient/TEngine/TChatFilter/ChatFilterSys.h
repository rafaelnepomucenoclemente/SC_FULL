#ifndef CHATFILTER_SYS
#define CHATFILTER_SYS


//!	Chat Filtering System.
/*!
*	@brief		ä�����͸�.
*
*/
class CTChatFilterSys
{
private :

	CTChatFilterFile*				m_pFile;
	bool							m_bForbiddenAtFirst;
	bool							m_bUsedForbiddenWords;

protected :

	int								ReplaceNoCase( CString& strUserChat, CString strOld, CString strNew );
	bool							Function( CString& strUserChat, int nLength, bool bCheckHeader = false, bool bFastCheck = false );

public :

									CTChatFilterSys();
									~CTChatFilterSys();

									/*!
									*	@brief	����� �����ϰ� �ִ��� üũ.
									*	@param	strUserChat�� üũ�ϴ� ���� ������ ���� �� �� �ֱ� ������ ���纻��.
									*/
	bool							CheckFobiddenWords( CString strUserChat );

									/*!
									*	@brief	����� �����ϰ� ������ Block.
									*	@param	strUserChat�� ����� ���ԵǾ� ������ CTChatFilter::strReplace �� ��ü��.
									*/
	void							ConvertString( CString& strUserChat, bool bCheckHeader = false );

public :

	bool							UsedFobiddenAtFirst() const;
	bool							UsedFobiddenWords() const;
	void							SetFilterFile( CTChatFilterFile* pFile );
	CTChatFilterFile*				GetFilterFile();
};

#endif