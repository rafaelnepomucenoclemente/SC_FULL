// TListItem.cpp: implementation of the TListItem class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TListItem::TListItem()
{
	m_strText = _T("");
	m_param = -1;
	m_dwTextColor = 0;
	m_blIsImageList = FALSE;
	m_nImageIndex = 0;
	m_nHMargine = 0;
}

TListItem::~TListItem()
{

}
