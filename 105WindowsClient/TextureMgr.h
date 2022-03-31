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
	HRESULT InsertTexture(TEXID eTexID, // 멀티텍스쳐나 싱글텍스쳐냐에 따라 삽입이 달라지겠지 ? 그래서 그거 구분하려고 ! 
		const wstring& wstrFilePath, // 경로 받아와서 넘겨줄거임. 
		const wstring& wstrObjectKey, // 싱글텍스쳐나 멀티 텍스쳐나 둘다 필요 그러므로 디폴트 매개변수 X
		const wstring& wstrStateKey = L"",// 멀티일 경우 필요한 인자기 때문에 디폴트 매개변수 ㅇ
		const int& rCount = 0);// 이하 동문. 
	void Release(); 

private:
	// wstring - 오브젝트 키값. 
	// 
	map<wstring, CTexture*> m_mapTexture; 
};

