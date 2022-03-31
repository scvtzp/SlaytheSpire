#pragma once



// MyPropertySheet
#include "MyPage1.h"
#include "MyPage2.h"
class CMyPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMyPropertySheet)

public:
	CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CMyPropertySheet();
public:
	CMyPage1 m_MyPage1; 
	CMyPage2 m_MyPage2; 

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};


