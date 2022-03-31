#pragma once
#include "afxwin.h"


// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	// ������ ���ڿ�. 
	CString m_strTestString;
	// ������� ���ڿ�!
	CString m_CopyString;
	afx_msg void OnBnClickedCopy();
	afx_msg void OnBnClickedAdd();
	// Unit����
	CString m_strName;
	int m_iAtt;
	int m_iDef;
	map<CString, UNIT*> m_mapUnit;
	afx_msg void OnLbnSelchangeClass();
	// ������ư
	CButton m_RadioBt[3];
	virtual BOOL OnInitDialog();
	CButton m_CheckBox[3];
	afx_msg void OnBnClickedDelete();
	CString m_strFindName;
	afx_msg void OnEnChangeFindName();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
};
