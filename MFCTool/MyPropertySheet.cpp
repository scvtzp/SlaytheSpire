// MyPropertySheet.cpp : ���� �����Դϴ�.
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


// MyPropertySheet �޽��� ó�����Դϴ�.


void CMyPropertySheet::OnClose()
{
	// ������Ƽ ��Ʈ �ȿ� ������Ƽ �������� ���� �ټ� �ִ�. 


	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// ���� X�� ������ �ٽ� ������Ƽ��Ʈ�� Ű�Եȴٸ� ��Ÿ�ӿ����� �߻��Ѵ�. 
	// �̰��� X�� ������ ������â�� �ı��Ǿ� �ٽ� ����׷��� �����°�. 
	// �׷��� WM_CLOSE��� �޽����� �߻��Ҷ� â�� �ı���Ű�� ���� �ƴ϶� .
	// �ܼ� â�� ����°����� �ٲ���. 

	//CPropertySheet::OnClose();
	ShowWindow(SW_HIDE);
}
