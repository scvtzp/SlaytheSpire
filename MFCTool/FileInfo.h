#pragma once
// ���� ���ϴٷ�� ��ɸ� ������ ��ü 
class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();
public:
	static CString ConvertRelativePath(const CString& rstrFullPath);
	// ��θ� �޾ƿͼ� �����ο��� ����η� �������ְ� ������ƮŰ ������ƮŰ ������ �������� ������ 
	// ����Ʈ �ȿ��ٰ� ������ ��. 
	static void DirInfoEx(const wstring& rwstrPath, list<IMAGEPATH*>& listImagePath); 
	static int DirFileConut(const wstring& rwstrPath);
};

