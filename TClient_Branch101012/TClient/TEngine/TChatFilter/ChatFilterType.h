#ifndef CHATFILTER_TYPE_H
#define CHATFILTER_TYPE_H


// 
struct CTChatFilterOption
{
	static int			bBlockAllSentence;		//!<	ä�ó��� ��ü�� �� = true, ��Ӿ� �ܾ �� = false.
	static int			bUseExceptionList;		//!<	���ܾ� ����Ʈ ��뿩��.
	static int			bIgnoreSpace;			//!<	�����̽��ٸ� �����ϰ� ���Ұ��ΰ�.
	static int			bIgnoreNumChar;			//!<	Ư�����ڸ� �����ϰ� ���Ұ��ΰ�.

	static CString		Apply( CString& str );
};

//
struct CTChatFilter
{
	static CHAR			chReplace;
	static CString		strFileExt;
	static CString		strFileName;
	static CString		strVReplace;
	static CString		strReplace;
	static CString		strBlockMsg;
	static CString		strIgnoreNumChar;
	static CString		strTagIgnoreSpace;
	static CString		strTagIgnoreNumChar;
	static CString		strTagBlockAllChat;
	static CString		strTagException;
};

struct TFILTER_EXCEPTINFO
{
	int		head_gap;
	int		tail_gap;

	TFILTER_EXCEPTINFO( int _head_gap = 0, int _tail_gap = 0 )
		:	head_gap( _head_gap ), tail_gap( _tail_gap ){}
};


typedef std::map< CString, TFILTER_EXCEPTINFO >		TMAP_EXCEPTDATA;
typedef std::map< CString, TMAP_EXCEPTDATA* >	TMAP_FILTERDATA;

typedef TMAP_EXCEPTDATA::iterator				TInner_Iter;
typedef TMAP_FILTERDATA::iterator				TOuter_Iter;


#define TCHAT_HEADER_SIZE 8

#define TCHAR_REPLACE			((char)0x7f)
#define TDEF_WCHAR_NBS			((WCHAR) 0xFEFF)

#define TDEF_MAX_PROGRESS		((int) 1000)
#define TDEF_BASIC_TSTEP		((int) 26)

#define TDEF_CHAR_CR			((BYTE) 13)
#define TDEF_CHAR_NL			((BYTE) 10)
#define TDEF_CHAR_SIZE			((BYTE) 1)

#define TMONSKILL_COUNT			((BYTE) 4)
#define TMAX_MBCS_SIZE			((int) 16)


#endif