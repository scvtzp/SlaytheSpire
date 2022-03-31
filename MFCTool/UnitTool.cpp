// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
	, m_strTestString(_T(""))
	, m_CopyString(_T(""))
	, m_strName(_T(""))
	, m_iAtt(0)
	, m_iDef(0)
	, m_strFindName(_T(""))
{

}

CUnitTool::~CUnitTool()
{
	for (auto& iter : m_mapUnit)
	{
		Safe_Delete(iter.second);
	}
	m_mapUnit.clear(); 
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{

	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strTestString);
	DDX_Text(pDX, IDC_EDIT2, m_CopyString);
	// ���� ��Ī�� ������ ����� ���� �ݿ��ǰų� �ݿ��Ǿ��ִ� ������ ���´�. 
	DDX_Text(pDX, IDC_EDIT3, m_strName);
	DDX_Text(pDX, IDC_EDIT4, m_iAtt);
	DDX_Text(pDX, IDC_EDIT5, m_iDef);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_RadioBt[0]);
	DDX_Control(pDX, IDC_RADIO2, m_RadioBt[1]);
	DDX_Control(pDX, IDC_RADIO3, m_RadioBt[2]);

	DDX_Control(pDX, IDC_CHECK1, m_CheckBox[0]);
	DDX_Control(pDX, IDC_CHECK2, m_CheckBox[1]);
	DDX_Control(pDX, IDC_CHECK3, m_CheckBox[2]);
	DDX_Text(pDX, IDC_EDIT6, m_strFindName);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnBnClickedCopy)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnBnClickedAdd)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnLbnSelchangeClass)
	ON_BN_CLICKED(IDC_BUTTON3, &CUnitTool::OnBnClickedDelete)
	ON_EN_CHANGE(IDC_EDIT6, &CUnitTool::OnEnChangeFindName)
	ON_BN_CLICKED(IDC_BUTTON4, &CUnitTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON5, &CUnitTool::OnBnClickedLoad)
END_MESSAGE_MAP()


// CUnitTool �޽��� ó�����Դϴ�.


void CUnitTool::OnBnClickedCopy()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// 
	UpdateData(TRUE); // - ���̾� �α� �ڽ��κ��� �Էµ� ������ ����. TRUE�� ��� 
	m_CopyString = m_strTestString; 
	UpdateData(FALSE);// - FALSe �� ��� ������ ����� ������ ���̾�α� �ڽ��� �ݿ�. 
	// UpdateData �Լ��� ȣ���ϰ� �Ǹ� DoDataExchange��� �Լ��� ȣ���� �ȴ�. 

}


void CUnitTool::OnBnClickedAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UNIT* pUnit = new UNIT; 
	//ZeroMemory(pUnit, sizeof(UNIT)); 
	UpdateData(TRUE);

	pUnit->strName = m_strName; 
	pUnit->iAtt = m_iAtt; 
	pUnit->iDef = m_iDef; 
	pUnit->byItem = 0; 
	for (int i = 0; i < 3; ++i)
	{
		if (m_RadioBt[i].GetCheck())
		{
			pUnit->byClass = i;
			break;
		}
	}
	// 0000 0000 
	// 0000 0001
	// 0000 0001 =
	//1. �������� �ϰ� ���� ���. 
	//	if (dynamic_cast<CButton*>(GetDlgItem(IDC_CHECK1))->GetCheck())
	//pUnit->byItem |= SWORD;
	//2. ������ ���� �ϴ� ���. 
	if (m_CheckBox[0].GetCheck())
		pUnit->byItem |= SWORD; 
	
	// 0000 0001
	// 0000 0010
	// 0000 0011 =
	if (m_CheckBox[1].GetCheck())
		pUnit->byItem |= AXE;

	if (m_CheckBox[2].GetCheck())
		pUnit->byItem |= BOW;


	m_ListBox.AddString(pUnit->strName.GetString());

	m_mapUnit.emplace(pUnit->strName, pUnit);
	UpdateData(FALSE);

}


void CUnitTool::OnLbnSelchangeClass()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strSelectName; 
	UpdateData(TRUE); 
	//GetCurSel - ���� ���õǾ��ִ� ����� �ε����� ã���ش�. 
	int iSelectIndex = m_ListBox.GetCurSel();
	//GetText - �ε��� ��°�� �ִ� ���ڿ��� ������ �Լ�. 
	m_ListBox.GetText(iSelectIndex, strSelectName);
	auto& iter_find = m_mapUnit.find(strSelectName);

	if (m_mapUnit.end() == iter_find)
		return; 

	for (int i = 0 ; i < 3; ++i)
	{
		m_RadioBt[i].SetCheck(FALSE);
		m_CheckBox[i].SetCheck(FALSE); 
	}

	m_RadioBt[iter_find->second->byClass].SetCheck(TRUE);
	
	if (iter_find->second->byItem & SWORD)
		m_CheckBox[0].SetCheck(TRUE); 
	if (iter_find->second->byItem & AXE)
		m_CheckBox[1].SetCheck(TRUE);
	if (iter_find->second->byItem & BOW)
		m_CheckBox[2].SetCheck(TRUE);

	m_strName = iter_find->second->strName; 
	m_iAtt = iter_find->second->iAtt; 
	m_iDef = iter_find->second->iDef;

	UpdateData(FALSE);
	int i = 0; 
}


BOOL CUnitTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_RadioBt[0].SetCheck(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CUnitTool::OnBnClickedDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE); 
	CString strFindName; 
	int iFindIndex = m_ListBox.GetCurSel();
	if (LB_ERR == iFindIndex)
		return; 

	m_ListBox.GetText(iFindIndex, strFindName);
	m_ListBox.DeleteString(iFindIndex); 

	auto& iter_find = m_mapUnit.find(strFindName); 

	if (m_mapUnit.end() == iter_find)
		return; 

	Safe_Delete(iter_find->second);
	m_mapUnit.erase(iter_find); 
	UpdateData(FALSE); 

}


void CUnitTool::OnEnChangeFindName()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE); 
	auto& iter_find = m_mapUnit.find(m_strFindName);

	if (m_mapUnit.end() == iter_find)
		return; 

	// FindString -����Ʈ �ڽ��� ���ڿ��� ã���ִ� �Լ�. ��ȯ���� ���° �ε�������. 
	// 1������ - ������
	//2������ - ã�����ϴ� ���ڿ�. 
	int iIndex = m_ListBox.FindString(0, m_strFindName);

	if (-1 == iIndex)
		return; 

	m_ListBox.SetCurSel(iIndex);

	m_strName = iter_find->first.GetString(); 
	m_iAtt = iter_find->second->iAtt; 
	m_iDef = iter_find->second->iDef; 

	for (int i = 0 ; i < 3; ++i)
	{
		m_CheckBox[i].SetCheck(FALSE); 
		m_RadioBt[i].SetCheck(FALSE); 
	}
	m_RadioBt[iter_find->second->byClass].SetCheck(TRUE);

	if (SWORD & iter_find->second->byItem)
		m_CheckBox[0].SetCheck(TRUE); 
	if (AXE & iter_find->second->byItem)
		m_CheckBox[1].SetCheck(TRUE); 
	if (BOW & iter_find->second->byItem)
		m_CheckBox[2].SetCheck(TRUE); 

	UpdateData(FALSE); 
}


void CUnitTool::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// CFileDialog - ���� ���� Ȥ�� ���� �۾��� �ʿ��� ��ȭ���ڸ� �����ϴ� ��ü. 
	/*
	1.��� ���� - TRUE �б�, FALSE ���� 
	2. ����Ʈ ���� Ȯ���. 
	3. ��ȭ���ڿ� ǥ�õ� ���� ���� ��. 
	4. �÷���. ��� �����ΰ�. 
	OFN_HIDEREADONLY - �б����� üũ�ڽ� ����
	OFN_OVERWRITEPROMPT - �ߺ��� �̸����� ����� ��� �޽��� ����ִ� ����. 
	5.��ȭ���ڿ� ǥ�õ� ���� ����. 
	6. �θ�. 
	*/
	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"DataFile(*.dat)|*.dat||", this);

	TCHAR szFilePath[MAX_STR] = L""; 
	// GetCurrentDirectory - ���� ��θ� ������ �Լ�. 
	GetCurrentDirectory(MAX_STR, szFilePath);
	//PathRemoveFileSpec - �� �ϴ��� ���ϸ��� �߶��ִ� �Լ�. 

	//EX) D:\�ں���\105A\DefaultWindows\Texture\Stage\Terrain\Tile\Tile0.png
	//PathRemoveFileSpec(szFilePath);
	//EX) D:\�ں���\105A\DefaultWindows\Texture\Stage\Terrain\Tile

	PathRemoveFileSpec(szFilePath); 
	lstrcat(szFilePath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szFilePath;

	if (IDOK == Dlg.DoModal())
	{
		CString strFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(strFilePath.GetString(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr); 
		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Save Failed"); 
			return;
		}
		DWORD dwByte = 0; 
		DWORD dwStrSize = 0;

		for (auto& MyPair : m_mapUnit)
		{
			dwStrSize = sizeof(TCHAR) * (MyPair.first.GetLength() + 1); 
			WriteFile(hFile, &dwStrSize, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, MyPair.first.GetString(), dwStrSize, &dwByte, nullptr);
			WriteFile(hFile, &MyPair.second->iAtt, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &MyPair.second->iDef, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &MyPair.second->byClass, sizeof(BYTE), &dwByte, nullptr);
			WriteFile(hFile, &MyPair.second->byItem, sizeof(BYTE), &dwByte, nullptr);
		}
		CloseHandle(hFile); 
	}
}


void CUnitTool::OnBnClickedLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"DataFile(*.dat)|*.dat||", this);

	TCHAR szFilePath[MAX_STR] = L"";
	// GetCurrentDirectory - ���� ��θ� ������ �Լ�. 
	GetCurrentDirectory(MAX_STR, szFilePath);
	//PathRemoveFileSpec - �� �ϴ��� ���ϸ��� �߶��ִ� �Լ�. 

	//EX) D:\�ں���\105A\DefaultWindows\Texture\Stage\Terrain\Tile\Tile0.png
	//PathRemoveFileSpec(szFilePath);
	//EX) D:\�ں���\105A\DefaultWindows\Texture\Stage\Terrain\Tile

	PathRemoveFileSpec(szFilePath);
	lstrcat(szFilePath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szFilePath;
	if (IDOK == Dlg.DoModal())
	{
		for (auto& MyPair : m_mapUnit)
			delete MyPair.second; 

		m_mapUnit.clear();

		m_ListBox.ResetContent();

		CString strFilePath = Dlg.GetPathName(); 

		// ���ϸ� �ɱ� ?
		HANDLE hFile = CreateFile(strFilePath.GetString(), GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr); 
		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"LoadFailed"); 
			return; 
		}

		DWORD dwByte = 0; 
		DWORD dwStrSize = 0; 
		UNIT tData = {}; 
		while (true)
		{
			ReadFile(hFile, &dwStrSize, sizeof(DWORD), &dwByte, nullptr);
			TCHAR* pName = new TCHAR[dwStrSize]; 

			ReadFile(hFile, pName, dwStrSize, &dwByte, nullptr);
			ReadFile(hFile, &tData.iAtt, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &tData.iDef, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &tData.byClass, sizeof(BYTE), &dwByte, nullptr);
			ReadFile(hFile, &tData.byItem, sizeof(BYTE), &dwByte, nullptr);

			if (0 == dwByte)
			{
				delete[] pName; 
				break; 
			}
			UNIT* pUnit = new UNIT; 
			pUnit->strName = pName; 
			delete[] pName; 
			pUnit->iAtt = tData.iAtt; 
			pUnit->iDef = tData.iDef; 
			pUnit->byClass = tData.byClass; 
			pUnit->byItem = tData.byItem; 
			m_mapUnit.emplace(pUnit->strName, pUnit); 
			m_ListBox.AddString(pUnit->strName);
		}

		CloseHandle(hFile); 
	}
}
