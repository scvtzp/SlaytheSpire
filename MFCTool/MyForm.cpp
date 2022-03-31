// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
	, m_MySheet(L"낄낄")
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyForm::OnBnClickedUnitTool)
	ON_BN_CLICKED(IDC_BUTTON6, &CMyForm::OnBnClickedMapTool)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyForm::OnBnClickedPropertySheet)
END_MESSAGE_MAP()


// CMyForm 진단입니다.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm 메시지 처리기입니다.


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_tFont.CreatePointFont(200, L"궁서");
	GetDlgItem(IDC_BUTTON1)->SetFont(&m_tFont);

	if (m_UnitTool.GetSafeHwnd() == nullptr)
		m_UnitTool.Create(IDD_UNITTOOL);
	if (m_MapTool.GetSafeHwnd() == nullptr)
		m_MapTool.Create(IDD_MAPTOOL); 

	if (m_MySheet.GetSafeHwnd() == nullptr)
		m_MySheet.Create(0, WS_OVERLAPPEDWINDOW);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CMyForm::OnBnClickedUnitTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//AfxMessageBox(L"ㅋㅋㅋ 잘 호출되지? ㅋㅋㅋ"); 


	m_UnitTool.ShowWindow(SW_SHOW); 

}


void CMyForm::OnBnClickedMapTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_MapTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedPropertySheet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_MySheet.ShowWindow(SW_SHOW); 
}
