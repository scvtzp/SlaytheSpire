// MyPage1.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MyPage1.h"
#include "afxdialogex.h"


// MyPage1 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMyPage1, CPropertyPage)

CMyPage1::CMyPage1()
	: CPropertyPage(IDD_MYPAGE1)
{

}

CMyPage1::~CMyPage1()
{
}

void CMyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyPage1, CPropertyPage)
END_MESSAGE_MAP()


// MyPage1 �޽��� ó�����Դϴ�.