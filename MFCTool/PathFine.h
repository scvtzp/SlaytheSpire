#pragma once
#include "afxwin.h"


// CPathFine 대화 상자입니다.

class CPathFind : public CDialog
{
	DECLARE_DYNAMIC(CPathFind)

public:
	CPathFind(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPathFind();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATHFINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	list<IMAGEPATH*> m_listImagePathInfo; 

	afx_msg void OnBnClickedSave();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
