// PathFine.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "PathFine.h"
#include "afxdialogex.h"


// CPathFine 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPathFind, CDialog)

CPathFind::CPathFind(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_PATHFINE, pParent)
{

}

CPathFind::~CPathFind()
{
}

void CPathFind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}


BEGIN_MESSAGE_MAP(CPathFind, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPathFind::OnBnClickedSave)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CPathFine 메시지 처리기입니다.


void CPathFind::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CPathFind::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE);
	TCHAR szPathBuf[MAX_STR] = L""; 

	int iCount = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0); 

	for (int i = 0 ; i < iCount ; ++i)
	{
		DragQueryFile(hDropInfo, i, szPathBuf, MAX_STR); 
		// 기본 밑작업은 긑. 
	}
	CDialog::OnDropFiles(hDropInfo);
	UpdateData(FALSE); 
}
