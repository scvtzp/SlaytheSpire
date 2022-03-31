#pragma once
class CTexture; 
class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)
public:
	enum TEXID{SINGLETEX, MULTITEX};
private:
	CTextureMgr();
	~CTextureMgr();
public:
	const TEXINFO* Get_TexInfo(const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const int& rImageIndex = 0);
public:
	HRESULT InsertTexture(TEXID eTexID, // ��Ƽ�ؽ��ĳ� �̱��ؽ��ĳĿ� ���� ������ �޶������� ? �׷��� �װ� �����Ϸ��� ! 
		const wstring& wstrFilePath, // ��� �޾ƿͼ� �Ѱ��ٰ���. 
		const wstring& wstrObjectKey, // �̱��ؽ��ĳ� ��Ƽ �ؽ��ĳ� �Ѵ� �ʿ� �׷��Ƿ� ����Ʈ �Ű����� X
		const wstring& wstrStateKey = L"",// ��Ƽ�� ��� �ʿ��� ���ڱ� ������ ����Ʈ �Ű����� ��
		const int& rCount = 0);// ���� ����. 
	void Release(); 

private:
	// wstring - ������Ʈ Ű��. 
	// 
	map<wstring, CTexture*> m_mapTexture; 
};

