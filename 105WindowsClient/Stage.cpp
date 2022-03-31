#include "stdafx.h"
#include "Stage.h"
#include "TestMonster.h"
#include "MyButton.h"

CStage::CStage()
{
}


CStage::~CStage()
{
	Release(); 
}

HRESULT CStage::Initialize()
{
	//CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Level1.ogg");

	CObj* pObj = CAbstractFactory<CTestMonster>::Create();
	GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_MONSTER, pObj);

	pObj = CAbstractFactory<CTestMonster>::Create();
	pObj->Set_PosPlus(150.f, 50.f);
	GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_MONSTER, pObj);

	pObj = CAbstractFactory<CMyButton>::Create();
	pObj->Set_Pos(1100.f, 560.f);
	pObj->Set_HitSize(180.f, 60.f);
	GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_BUTTON, pObj);

	return S_OK;
}

void CStage::Update()
{
	GET_INSTANCE(CObjMgr)->Update();


}

void CStage::LateUpdate()
{
	GET_INSTANCE(CObjMgr)->LateUpdate();

	GET_INSTANCE(CSceneMgr)->Scene_Check();
}

void CStage::Render()
{
	//���
	D3DXMATRIX matScale, matTrans, matWorld;

	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"BottomScene");
	assert(!(nullptr == pTexInfo));

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX/2 , WINCY / 2, 0.f);

	matWorld = matScale * matTrans;

	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
	GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	
	//bar
	Render_SingleTex(L"Topbar", WINCX / 2, 40);



	if (GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_MONSTER).empty())
	{
		Render_Gold(BUTTON::D_GoMap1);
	}

	//render
	GET_INSTANCE(CObjMgr)->Render();

	Render_Cursors();
}

void CStage::Release()
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
	CSoundMgr::Get_Instance()->StopAll();

}