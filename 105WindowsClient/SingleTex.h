#pragma once
#include "Texture.h"
class CSingleTex :
	public CTexture
{
public:
	CSingleTex();
	virtual ~CSingleTex();
public:
	virtual TEXINFO * Get_TexInfo(const wstring & wstrStateKey = L"", const int & rCount = 0) override;
	// CTexture을(를) 통해 상속됨
public:
	virtual HRESULT InsertTexture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const int & rCount = 0) override;
	virtual void Release() override;

private:
	TEXINFO m_tTexInfo; 

};

