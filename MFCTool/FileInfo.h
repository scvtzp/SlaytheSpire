#pragma once
// 순수 파일다루는 기능만 제공할 객체 
class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();
public:
	static CString ConvertRelativePath(const CString& rstrFullPath);
	// 경로를 받아와서 절대경로에서 상대경로로 변경해주고 오브젝트키 스테이트키 파일의 갯수까지 센다음 
	// 리스트 안에다가 삽입할 것. 
	static void DirInfoEx(const wstring& rwstrPath, list<IMAGEPATH*>& listImagePath); 
	static int DirFileConut(const wstring& rwstrPath);
};

