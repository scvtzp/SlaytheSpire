#pragma once
class CTexture
{
public:
	CTexture();
	virtual ~CTexture();
public:
	virtual TEXINFO* Get_TexInfo(const wstring& wstrStateKey = L"", const int& rCount = 0)PURE;
public:
	virtual HRESULT InsertTexture(const wstring& wstrFilePath, 
		const wstring& wstrStateKey = L""/*멀티택스쳐에만 사용할 인자*/, 
		// 우리 이제 그림 나눌때 오브젝트키와 스테이트 키를 나눠서 보관 할 것. 
		// ex) ObjectKey - Player or Monster or Bullet, NPC
		// ex) StateKey - Player의 IDle 상태 혹은 뛰기 혹은 공격 혹은 죽다 등등 상태 가 될 것. 
		const int& rCount = 0/* 애도 멀티에서만 사용할 인자 디폴트 매개변수 사용 */)PURE;
	virtual void Release()PURE; 
};

