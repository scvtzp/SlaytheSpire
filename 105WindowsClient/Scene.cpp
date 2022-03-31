#include "stdafx.h"
#include "Scene.h"


CScene::CScene()
{
}


CScene::~CScene()
{
}

void CScene::Render_Cursors()
{
	////마우스 포인터
	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);
	Render_SingleTex(L"Cursors", pt.x + 10, pt.y + 10, 0.7f, 0.7f);
}

void CScene::Render_Gold(BUTTON::ID ID)
{
	D3DXMATRIX matScale, matTrans, matWorld;

	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"rewardScreenSheet");
	assert(!(nullptr == pTexInfo));

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale, 0.7f, 0.7f, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX/2, WINCY / 2, 0.f);

	matWorld = matScale * matTrans;

	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
	GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	if (m_bSceneDeadCheck)
	{
		for (auto& pObj : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_BUTTON))
		{
			Safe_Delete(pObj);
		}
		GET_INSTANCE(CObjMgr)->clearList(OBJ::OBJ_BUTTON);

		CObj* pObj = CAbstractFactory<CMyButton>::Create();
		pObj->Set_Pos(WINCX / 2, 200.f);
		dynamic_cast<CMyButton*>(pObj)->Set_Button(BUTTON::Get_Gold);
		GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_BUTTON, pObj);

		pObj = CAbstractFactory<CMyButton>::Create();
		pObj->Set_Pos(WINCX / 2, 300.f);
		dynamic_cast<CMyButton*>(pObj)->Set_Button(BUTTON::Get_Card);
		GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_BUTTON, pObj);
		
		pObj = CAbstractFactory<CMyButton>::Create();
		pObj->Set_Pos(1100.f, 560.f);
		dynamic_cast<CMyButton*>(pObj)->Set_Button(ID);
		GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_BUTTON, pObj);

		m_bSceneDeadCheck = false;
	}
}

void CScene::Render_SingleTex(const wstring & wstrObjectKey, float x, float y, float _X, float _Y, int A)
{
	D3DXMATRIX matScale, matTrans, matWorld;

	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(wstrObjectKey);
	assert(!(nullptr == pTexInfo));

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale, _X, _Y, 0.f);
	D3DXMatrixTranslation(&matTrans, x, y, 0.f);

	matWorld = matScale * matTrans;

	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
	GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(A, 255, 255, 255));
}


void CScene::Render_MultiTex(const wstring & wstrObjectKey, const wstring & wstrStateKey, const int & rImageIndex, float x, float y)
{
	D3DXMATRIX matScale, matTrans, matWorld;

	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(wstrObjectKey, wstrStateKey, rImageIndex);
	assert(!(nullptr == pTexInfo));

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, x, y, 0.f);

	matWorld = matScale * matTrans;

	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
	GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}


