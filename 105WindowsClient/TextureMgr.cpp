#include "stdafx.h"
#include "TextureMgr.h"
#include "Texture.h"
#include "SingleTex.h"
#include "MultiTex.h"
IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr()
{
}


CTextureMgr::~CTextureMgr()
{
	Release(); 
}

const TEXINFO * CTextureMgr::Get_TexInfo(const wstring & wstrObjectKey, const wstring & wstrStateKey, const int & rImageIndex)
{
	auto& iter = m_mapTexture.find(wstrObjectKey); 
	if (m_mapTexture.end() == iter)
		return nullptr;

	return iter->second->Get_TexInfo(wstrStateKey, rImageIndex); 
}

HRESULT CTextureMgr::InsertTexture(TEXID eTexID, const wstring & wstrFilePath, const wstring & wstrObjectKey, const wstring & wstrStateKey, const int & rCount)
{
	auto& iter_find = m_mapTexture.find(wstrObjectKey); 
	
	if (m_mapTexture.end() == iter_find)
	{
		CTexture* pTexture = nullptr; 

		switch (eTexID)
		{
		case CTextureMgr::SINGLETEX:
			pTexture = new CSingleTex;
			break;
		case CTextureMgr::MULTITEX:
			pTexture = new CMultiTex; 
			break;
		default:
			break;
		}
		if (FAILED(pTexture->InsertTexture(wstrFilePath, wstrStateKey, rCount)))
		{
			wstring ErrMsg = wstrObjectKey + L"Insert Failed"; 
			ERR_MSG(ErrMsg.c_str());
			return E_FAIL; 
		}
		m_mapTexture.emplace(wstrObjectKey, pTexture);
	}
	else if (MULTITEX == eTexID)
	{
		if (FAILED(m_mapTexture[wstrObjectKey]->InsertTexture(wstrFilePath, wstrStateKey, rCount)))
		{
			wstring ErrMsg = wstrStateKey + L" Insert Failed";
			ERR_MSG(ErrMsg.c_str());
			return E_FAIL; 
		}
	}
	return S_OK;
}

void CTextureMgr::Release()
{
	for_each(m_mapTexture.begin(), m_mapTexture.end(), [](auto& iter)
	{
		Safe_Delete(iter.second);

	});
	m_mapTexture.clear();
}
