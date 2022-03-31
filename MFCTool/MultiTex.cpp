#include "stdafx.h"
#include "MultiTex.h"


CMultiTex::CMultiTex()
{
}


CMultiTex::~CMultiTex()
{
	Release();
}

TEXINFO * CMultiTex::Get_TexInfo(const wstring & wstrStateKey , const int & rCount)
{
	auto& iter_find = m_mapMultiTex.find(wstrStateKey); 
	if (m_mapMultiTex.end() == iter_find)
		return nullptr;

	return m_mapMultiTex[wstrStateKey][rCount];
}
//..\Texture\Stage\Terrain\Tile\Tile%d.png
HRESULT CMultiTex::InsertTexture(const wstring & wstrFilePath, const wstring & wstrStateKey , const int & rCount )
{
	auto& iter_find = m_mapMultiTex.find(wstrStateKey); 
	
	if (m_mapMultiTex.end() != iter_find)
		return E_FAIL;
	TCHAR szFullPath[256] = {}; 
	for (int i = 0 ; i < rCount; ++i)
	{
		swprintf_s(szFullPath, wstrFilePath.c_str(), i);
		TEXINFO* pTexInfo = new TEXINFO; 
		if (FAILED(D3DXGetImageInfoFromFile(szFullPath, &pTexInfo->tImageInfo)))
		{
			wstring ErrMsg = wstring(szFullPath) + L"Load Failed"; 
			AfxMessageBox(ErrMsg.c_str());
			Safe_Delete(pTexInfo);
			return E_FAIL; 
		}
		if (FAILED(D3DXCreateTextureFromFileEx(GET_INSTANCE(CDevice)->Get_Device()
			, szFullPath
			, pTexInfo->tImageInfo.Width
			, pTexInfo->tImageInfo.Height
			, pTexInfo->tImageInfo.MipLevels
			, 0
			, pTexInfo->tImageInfo.Format
			, D3DPOOL_MANAGED
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 0
			, nullptr
			, nullptr
			, &pTexInfo->pTexture
			)))
		{
			AfxMessageBox(L"Create texture Failed!"); 
			Safe_Delete(pTexInfo);
			return E_FAIL; 
		}
		m_mapMultiTex[wstrStateKey].emplace_back(pTexInfo);
	}
	return S_OK;
}

void CMultiTex::Release()
{
	for (auto& rMyPair : m_mapMultiTex)
	{
		for (auto& pTexInfo : rMyPair.second)
		{
			pTexInfo->pTexture->Release();
			Safe_Delete(pTexInfo);
		}
		rMyPair.second.clear();
		//rMyPair.second.swap(vector<TEXINFO*>());

		//���� ���� ������ �°� �޸� ������ ������ִ� �Լ�. 
		rMyPair.second.shrink_to_fit();
	}
	m_mapMultiTex.clear();
}
