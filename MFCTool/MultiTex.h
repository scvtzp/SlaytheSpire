#pragma once
#include "Texture.h"
class CMultiTex :
	public CTexture
{
public:
	CMultiTex();
	virtual ~CMultiTex();
public:
	// CTexture��(��) ���� ��ӵ�
	virtual TEXINFO * Get_TexInfo(const wstring & wstrStateKey , const int & rCount) override;
	virtual HRESULT InsertTexture(const wstring & wstrFilePath, const wstring & wstrStateKey , const int & rCount ) override;
	virtual void Release() override;
private:
	map<wstring, vector<TEXINFO*>> m_mapMultiTex; 
};

