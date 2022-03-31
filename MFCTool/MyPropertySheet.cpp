// MyPropertySheet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MyPropertySheet.h"


// MyPropertySheet

IMPLEMENT_DYNAMIC(CMyPropertySheet, CPropertySheet)

CMyPropertySheet::CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CMyPropertySheet::CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_MyPage1); 
	AddPage(&m_MyPage2);
}

CMyPropertySheet::~CMyPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CMyPropertySheet, CPropertySheet)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// MyPropertySheet 메시지 처리기입니다.


void CMyPropertySheet::OnClose()
{
	// 프로퍼티 시트 안에 프로퍼티 페이지를 나줘 줄수 있다. 


	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 지금 X를 누른후 다시 프로퍼티시트를 키게된다면 런타임에러가 발생한다. 
	// 이것은 X를 누를때 윈도우창이 파괴되어 다시 열라그러니 못여는것. 
	// 그래서 WM_CLOSE라는 메시지가 발생할때 창을 파괴시키는 것이 아니라 .
	// 단순 창을 숨기는것으로 바꿔줌. 

	//CPropertySheet::OnClose();
	ShowWindow(SW_HIDE);
}
