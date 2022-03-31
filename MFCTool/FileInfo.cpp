#include "stdafx.h"
#include "FileInfo.h"


CFileInfo::CFileInfo()
{
}


CFileInfo::~CFileInfo()
{
}

CString CFileInfo::ConvertRelativePath(const CString & rstrFullPath)
{
	// �̾Ƴ� �����. 
	TCHAR szRelativePath[MAX_STR] = L""; 

	// ���� ������Ʈ�� ��θ� ���ð�. 
	TCHAR szCurDirectory[MAX_STR] = L""; 
	GetCurrentDirectory(MAX_STR, szCurDirectory);


	PathRelativePathTo(szRelativePath, szCurDirectory, FILE_ATTRIBUTE_DIRECTORY, rstrFullPath.GetString(), FILE_ATTRIBUTE_DIRECTORY); 
	//from���� To�� ã�ư��� ����θ� ��ȯ ���ٰ�. 



	return CString(szRelativePath);
}
//D:\�ں���\105A\DefaultWindows\Texture\Stage\Terrain\*.*
//D:\�ں���\105A\DefaultWindows\Texture\Stage\Terrain\Tile
void CFileInfo::DirInfoEx(const wstring & rwstrPath, list<IMAGEPATH*>& listImagePath)
{
	// ���� ���õ� ��� ���� ���� Ŭ����. 
	CFileFind find; 

	//"\\*.*";= �̰��� ���ϴ� �ٴ� ��� ���ϰ� ��� Ȯ���ڸ� ǥ���ϴ� ���. 
	wstring wstrFilePath = rwstrPath + L"\\*.*";

	// FindFile - �־��� ��ο� ������ ������ Ȯ���ϴ� �Լ�. 
	// �������� ������ FALSE ���� ������ �ִٸ� TRUE; 
	// 
	bool bContinue = find.FindFile(wstrFilePath.c_str());
	while (bContinue)
	{
		// FindNextFile - ���� ��� �� ���� ���ϵ��� ã�� ������ �Լ�. 
		//���̻� ã������ ���ٸ� false�� ��ȯ. �ִٸ� true 
		bContinue = find.FindNextFile();

		if (find.IsDots())
			continue;

		else if (find.IsDirectory())
		{
			DirInfoEx(find.GetFilePath().GetString(), listImagePath); 
		}
		else
		{

		}
	}
}

int CFileInfo::DirFileConut(const wstring & rwstrPath)
{
	return 0;
}
