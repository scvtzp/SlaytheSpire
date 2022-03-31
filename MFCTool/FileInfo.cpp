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
	// 뽑아낸 상대경로. 
	TCHAR szRelativePath[MAX_STR] = L""; 

	// 현재 프로젝트의 경로를 얻어올것. 
	TCHAR szCurDirectory[MAX_STR] = L""; 
	GetCurrentDirectory(MAX_STR, szCurDirectory);


	PathRelativePathTo(szRelativePath, szCurDirectory, FILE_ATTRIBUTE_DIRECTORY, rstrFullPath.GetString(), FILE_ATTRIBUTE_DIRECTORY); 
	//from에서 To로 찾아가는 상대경로를 반환 해줄것. 



	return CString(szRelativePath);
}
//D:\박병건\105A\DefaultWindows\Texture\Stage\Terrain\*.*
//D:\박병건\105A\DefaultWindows\Texture\Stage\Terrain\Tile
void CFileInfo::DirInfoEx(const wstring & rwstrPath, list<IMAGEPATH*>& listImagePath)
{
	// 파일 관련된 경로 제어 관련 클래스. 
	CFileFind find; 

	//"\\*.*";= 이것이 뜻하는 바는 모든 파일과 모든 확장자를 표현하는 방식. 
	wstring wstrFilePath = rwstrPath + L"\\*.*";

	// FindFile - 주어진 경로에 파일의 유무를 확인하는 함수. 
	// 존재하지 않으면 FALSE 만약 파일이 있다면 TRUE; 
	// 
	bool bContinue = find.FindFile(wstrFilePath.c_str());
	while (bContinue)
	{
		// FindNextFile - 동일 경로 상에 다음 파일들을 찾아 나서는 함수. 
		//더이상 찾을것이 없다면 false를 반환. 있다면 true 
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
