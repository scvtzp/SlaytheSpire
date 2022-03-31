#include "stdafx.h"
#include "Terrain.h"
#include "MFCToolView.h"

CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release(); 

}

void CTerrain::TileChange(const D3DXVECTOR3 & rMouse, const BYTE & rbyDrawID, const BYTE & rbyOption/*=0*/)
{
	int iIndex = Get_Index(rMouse);

	if (-1 == iIndex)
		return; 

	m_vecTile[iIndex]->byDrawID = rbyDrawID; 
	m_vecTile[iIndex]->byOption = rbyOption; 
}

int CTerrain::Get_Index(const D3DXVECTOR3 & rPos)
{
	size_t iSize = m_vecTile.size(); 
	for (size_t i = 0; i < iSize ; ++i)
	{
		if (IsPicking(rPos, i))
			return i; 
	}
	return -1;
}

bool CTerrain::IsPicking(const D3DXVECTOR3 & rPos, const int & iIndex)
{
	// ㅇㅋ? 
	// 12, 3, 6, 9 순으로 마름모꼴 꼭지점 구하기. 
 	D3DXVECTOR3 vPoint[4] = 
 	{
 		{m_vecTile[iIndex]->vPos.x , m_vecTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f},
 		{m_vecTile[iIndex]->vPos.x + (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y, 0.f},
 		{ m_vecTile[iIndex]->vPos.x , m_vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f },
 		{ m_vecTile[iIndex]->vPos.x - (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y, 0.f }
 	};
	// 시계방향으로 각각 방향벡터 구할 것. 
	D3DXVECTOR3 vDir[4] = 
	{
		// 목적지 - 출발지 
		vPoint[1] - vPoint[0], 
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	D3DXVECTOR3 vNormal[4] = {}; 
	for (int i = 0; i < 4; ++i)
		vNormal[i] = { -vDir[i].y, vDir[i].x, 0.f };

	D3DXVECTOR3 vMouseDir[4] = 
	{
		rPos - vPoint[0],
		rPos - vPoint[1],
		rPos - vPoint[2],
		rPos - vPoint[3],
	};

	for (int i = 0 ; i < 4 ; ++i)
	{
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);

		if (0 < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;

	}
	return true; 
// 	// 두가지 직선의 방정식을 이용한 방식
// 	// 또하나는 내적을 이용하는 방식.
// 	//y = ax + b; 
// 	//0 = ax + b - y ;
// 	//1번째 기울기 구하기!
// 	// 일단 기울기 부터 구하자. 
// 
// 	float fInclination[4] =
// 	{
// 		(TILECY / 2.f) / (TILECX / 2.f),
// 		-(TILECY / 2.f) / (TILECX / 2.f),
// 		(TILECY / 2.f) / (TILECX / 2.f),
// 		-(TILECY / 2.f) / (TILECX / 2.f)
// 	};
// 
// 	// 2. 꼭지점 구하기. 
// 	// 꼭지점은 12, 3, 6, 9 시 순으로 구할 것. 
// 	D3DXVECTOR3 vPoint[4] = 
// 	{
// 		{m_vecTile[iIndex]->vPos.x , m_vecTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f},
// 		{m_vecTile[iIndex]->vPos.x + (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y, 0.f},
// 		{ m_vecTile[iIndex]->vPos.x , m_vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f },
// 		{ m_vecTile[iIndex]->vPos.x - (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y, 0.f }
// 	};
// 
// 	// y 절편 구하기. (b)
// 	// y = ax + b; -> b = y - ax 
// 	float fIntercept[4] = 
// 	{
// 		vPoint[0].y - (fInclination[0] * vPoint[0].x),
// 		vPoint[1].y - (fInclination[1] * vPoint[1].x),
// 		vPoint[2].y - (fInclination[2] * vPoint[2].x),
// 		vPoint[3].y - (fInclination[3] * vPoint[3].x)
// 	};
// 	
// 	//0 = ax + b - y ; 임의의 점 x y 에 이제 rPos 즉 마우스 좌표를 대입해서 
// 	// 양수냐 음수냐를 비교하면. 
// 	// 깔끔하게 픽킹 완료. 
// 	if (0 < fInclination[0] * rPos.x + fIntercept[0] - rPos.y && // 첫번째 선에서는 양수
// 		0 < fInclination[1] * rPos.x + fIntercept[1] - rPos.y && // 둘째 선에서도 양수 
// 		0 > fInclination[2] * rPos.x + fIntercept[2] - rPos.y && // 셋째 선에서는 음수 
// 		0 > fInclination[3] * rPos.x + fIntercept[3] - rPos.y) // 넷째 선에서는 음수.  이 4가지 조건이 모두 참이라면
// 		// 이것은 마우스 포인트 위치가 마름모 꼴 안에 있다. 
// 		return true;
// 
// 
// 	return false;
}

void CTerrain::SetRatio(D3DXMATRIX * pOut, const float & fRatioX, const float & fRatioY)
{
	/*
	11	12	13	14
	21	22	23	24
	31	32	33	34
	41	42	43	44

	*/
	pOut->_11 *= fRatioX;
	pOut->_21 *= fRatioX;
	pOut->_31 *= fRatioX;
	pOut->_41 *= fRatioX;

	pOut->_12 *= fRatioY;
	pOut->_22 *= fRatioY;
	pOut->_32 *= fRatioY;
	pOut->_42 *= fRatioY;

}

HRESULT CTerrain::Initialize()
{
	float fX = 0.f, fY = 0.f; 
	TILE* pTile = nullptr; 
	for (int i = 0 ; i < TILEY ; ++i)
	{
		for (int j = 0 ; j < TILEX ; ++j)
		{
			fX = float((j * TILECX) + ((i % 2) * (TILECX >> 1)));
			fY = float(i * (TILECY >> 1));
			pTile = new TILE; 
			pTile->vPos = { fX, fY, 0.f };
			pTile->vSize = { 1.f, 1.f, 0.f }; 
			pTile->byDrawID = 23; 
			pTile->byOption = 0; 
			m_vecTile.emplace_back(pTile);
		}
	}
	return S_OK;
}

void CTerrain::Render()
{
	D3DXMATRIX matScale, matTrans, matWorld; 
	D3DXMatrixIdentity(&matWorld); 
	RECT rc = {}; 
	m_pView->GetClientRect(&rc);
	float fX = WINCX / float(rc.right - rc.left);
	float fY = WINCY / float(rc.bottom - rc.top);
	int iIndex = 0; 
	TCHAR szBuf[64] = L""; 
	//m_vecTile[30]->byDrawID = 2;
	for (auto& pTile : m_vecTile)
	{
		swprintf_s(szBuf, L"%d", iIndex);
		const TEXINFO* pTexInfo  = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Terrain", L"Tile", pTile->byDrawID);
		if (nullptr == pTexInfo)
			return; 
		float fCenterX = pTexInfo->tImageInfo.Width * 0.5f; 
		float fCenterY = pTexInfo->tImageInfo.Height * 0.5f; 

		//GetScrollPos - 스크롤 얻어오는 함수. 0일경우 x , 1일경우 y 

		D3DXMatrixScaling(&matScale, pTile->vSize.x, pTile->vSize.y, 0.f); 
		D3DXMatrixTranslation(&matTrans, pTile->vPos.x - m_pView->GetScrollPos(0), pTile->vPos.y - m_pView->GetScrollPos(1), 0.f);
		matWorld = matScale * matTrans; 
		SetRatio(&matWorld, fX, fY);
		// 크, 자, 이, 공, 부 
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
		GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 0,0,0));
		++iIndex; 
	}
	// 2D에서 직교백터를 뽑아내는 방법. 
	// X와 Y를 바꾸고 X에 -만 붙여주면 끝! 
	// 
}

void CTerrain::MiniRender()
{
	D3DXMATRIX matScale, matTrans, matWorld; 

	size_t iSize = m_vecTile.size(); 
	for (size_t i = 0 ; i < iSize; ++i)
	{
		const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
		if (nullptr == pTexInfo)
			return; 

		float fCenterX = pTexInfo->tImageInfo.Width * 0.5f; 
		float fCenterY = pTexInfo->tImageInfo.Height *0.5f; 

		D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f); 
		D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x - m_pView->GetScrollPos(0), m_vecTile[i]->vPos.y - m_pView->GetScrollPos(1), 0.f); 
		matWorld = matScale * matTrans; 

		SetRatio(&matWorld, 0.2f, 0.6f);

		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld); 
		GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}

void CTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>); 
// 	for (auto& pTile : m_vecTile)
// 	{
// 		if (pTile)
// 		{
// 			delete pTile; 
// 			pTile = nullptr; 
// 		}
// 	}
	// ㅋㅋ 람다식이야. 신기하지 ? ㅋㅋㅋ
// 	[&]() 
// 	{
// 		for (auto& pTile : m_vecTile)
// 		{
// 			Safe_Delete(pTile); 
// 		}
// 	}();
	m_vecTile.clear(); 
	//m_vecTile.swap(vector<TILE*>()); 
	m_vecTile.shrink_to_fit();
}
