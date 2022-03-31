#pragma once
#include "afxwin.h"


// CUnitTool 대화 상자입니다.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnitTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	// 복사할 문자열. 
	CString m_strTestString;
	// 복사받을 문자열!
	CString m_CopyString;
	afx_msg void OnBnClickedCopy();
	afx_msg void OnBnClickedAdd();
	// Unit관련
	CString m_strName;
	int m_iAtt;
	int m_iDef;
	map<CString, UNIT*> m_mapUnit;
	afx_msg void OnLbnSelchangeClass();
	// 라디오버튼
	CButton m_RadioBt[3];
	virtual BOOL OnInitDialog();
	CButton m_CheckBox[3];
	afx_msg void OnBnClickedDelete();
	CString m_strFindName;
	afx_msg void OnEnChangeFindName();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
};
