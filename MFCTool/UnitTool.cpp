// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool 대화 상자입니다.

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
	// 각각 매칭된 변수에 저장된 값이 반영되거나 반영되어있는 값들을 얻어온다. 
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


// CUnitTool 메시지 처리기입니다.


void CUnitTool::OnBnClickedCopy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 
	UpdateData(TRUE); // - 다이얼 로그 박스로부터 입력된 값들을 얻어옴. TRUE일 경우 
	m_CopyString = m_strTestString; 
	UpdateData(FALSE);// - FALSe 일 경우 변수에 저장된 값들을 다이얼로그 박스에 반영. 
	// UpdateData 함수를 호출하게 되면 DoDataExchange라는 함수가 호출이 된다. 

}


void CUnitTool::OnBnClickedAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	//1. 변수없이 하고 싶은 경우. 
	//	if (dynamic_cast<CButton*>(GetDlgItem(IDC_CHECK1))->GetCheck())
	//pUnit->byItem |= SWORD;
	//2. 변수를 만들어서 하는 경우. 
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strSelectName; 
	UpdateData(TRUE); 
	//GetCurSel - 현재 선택되어있는 목록의 인덱스를 찾아준다. 
	int iSelectIndex = m_ListBox.GetCurSel();
	//GetText - 인덱스 번째에 있는 문자열을 얻어오는 함수. 
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

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_RadioBt[0].SetCheck(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CUnitTool::OnBnClickedDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE); 
	auto& iter_find = m_mapUnit.find(m_strFindName);

	if (m_mapUnit.end() == iter_find)
		return; 

	// FindString -리스트 박스에 문자열을 찾아주는 함수. 반환값은 몇번째 인덱스인지. 
	// 1번인자 - 시작점
	//2번인자 - 찾고자하는 문자열. 
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// CFileDialog - 파일 열기 혹은 저장 작업에 필요한 대화상자를 생성하는 객체. 
	/*
	1.모드 지정 - TRUE 읽기, FALSE 저장 
	2. 디폴트 파일 확장명. 
	3. 대화상자에 표시될 최초 파일 명. 
	4. 플레그. 어떻게 열것인가. 
	OFN_HIDEREADONLY - 읽기전용 체크박스 숨김
	OFN_OVERWRITEPROMPT - 중복된 이름으로 저장시 경고 메시지 띄어주는 역할. 
	5.대화상자에 표시될 파일 형식. 
	6. 부모. 
	*/
	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"DataFile(*.dat)|*.dat||", this);

	TCHAR szFilePath[MAX_STR] = L""; 
	// GetCurrentDirectory - 현재 경로를 얻어오는 함수. 
	GetCurrentDirectory(MAX_STR, szFilePath);
	//PathRemoveFileSpec - 맨 하단의 파일명을 잘라주는 함수. 

	//EX) D:\박병건\105A\DefaultWindows\Texture\Stage\Terrain\Tile\Tile0.png
	//PathRemoveFileSpec(szFilePath);
	//EX) D:\박병건\105A\DefaultWindows\Texture\Stage\Terrain\Tile

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"DataFile(*.dat)|*.dat||", this);

	TCHAR szFilePath[MAX_STR] = L"";
	// GetCurrentDirectory - 현재 경로를 얻어오는 함수. 
	GetCurrentDirectory(MAX_STR, szFilePath);
	//PathRemoveFileSpec - 맨 하단의 파일명을 잘라주는 함수. 

	//EX) D:\박병건\105A\DefaultWindows\Texture\Stage\Terrain\Tile\Tile0.png
	//PathRemoveFileSpec(szFilePath);
	//EX) D:\박병건\105A\DefaultWindows\Texture\Stage\Terrain\Tile

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

		// 뭐하면 될까 ?
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
