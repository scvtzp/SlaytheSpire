#include "stdafx.h"
#include "Stage_DoDe.h"
#include "Deca.h"
#include "Donu.h"

CStage_DoDe::CStage_DoDe()
{
}


CStage_DoDe::~CStage_DoDe()
{
	Release();
}

HRESULT CStage_DoDe::Initialize()
{
	GET_INSTANCE(CObjMgr)->Set_Scroll(0.f, 0.f);

	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Boss2.ogg");

	CObj* pObj = CAbstractFactory<CDonu>::Create();
	GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_MONSTER, pObj);

	pObj = CAbstractFactory<CDeca>::Create();
	GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_MONSTER, pObj);

	pObj = CAbstractFactory<CMyButton>::Create();
	pObj->Set_Pos(1100.f, 560.f);
	GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_BUTTON, pObj);

	return S_OK;
}

void CStage_DoDe::Update()
{
	GET_INSTANCE(CObjMgr)->Update();
}

void CStage_DoDe::LateUpdate()
{
	GET_INSTANCE(CObjMgr)->LateUpdate();
	GET_INSTANCE(CSceneMgr)->Scene_Check();

}

void CStage_DoDe::Render()
{
	//¹è°æ
	D3DXMATRIX matScale, matTrans, matWorld;

	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"CityScene");
	assert(!(nullptr == pTexInfo));

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX / 2, WINCY / 2, 0.f);

	matWorld = matScale * matTrans;

	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
	GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	//bar
	Render_SingleTex(L"Topbar", WINCX / 2, 40);
	if (GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_MONSTER).empty())
	{
		Render_Gold(BUTTON::D_GoMap2);
	}

	//render
	GET_INSTANCE(CObjMgr)->Render();

	Render_Cursors();
}

void CStage_DoDe::Release()
{
	for (auto& pObj : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_MONSTER))
	{
		Safe_Delete(pObj);
	}
	GET_INSTANCE(CObjMgr)->clearList(OBJ::OBJ_MONSTER);

	for (auto& pObj : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_BUTTON))
	{
		Safe_Delete(pObj);
	}
	GET_INSTANCE(CObjMgr)->clearList(OBJ::OBJ_BUTTON);
}
