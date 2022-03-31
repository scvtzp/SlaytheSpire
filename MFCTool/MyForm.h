#pragma once



// CMyForm �� ���Դϴ�.
#include "UnitTool.h"
#include "MapTool.h"
#include "MyPropertySheet.h"

class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyForm();

public:
	CUnitTool m_UnitTool; 
	CMapTool m_MapTool; 
	CMyPropertySheet m_MySheet; 
	CFont m_tFont; 
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedUnitTool();
	afx_msg void OnBnClickedMapTool();
	afx_msg void OnBnClickedPropertySheet();
};


