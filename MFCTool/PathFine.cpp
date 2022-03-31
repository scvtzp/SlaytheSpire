// PathFine.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "PathFine.h"
#include "afxdialogex.h"


// CPathFine ��ȭ �����Դϴ�.

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


// CPathFine �޽��� ó�����Դϴ�.


void CPathFind::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CPathFind::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	UpdateData(TRUE);
	TCHAR szPathBuf[MAX_STR] = L""; 

	int iCount = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0); 

	for (int i = 0 ; i < iCount ; ++i)
	{
		DragQueryFile(hDropInfo, i, szPathBuf, MAX_STR); 
		// �⺻ ���۾��� �P. 
	}
	CDialog::OnDropFiles(hDropInfo);
	UpdateData(FALSE); 
}
