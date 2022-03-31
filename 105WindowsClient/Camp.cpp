#include "stdafx.h"
#include "Camp.h"


CCamp::CCamp()
{
}


CCamp::~CCamp()
{
}

HRESULT CCamp::Initialize()
{
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"Sleep.ogg");

	return S_OK;
}

void CCamp::Update()
{
	GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Heil();
}

void CCamp::LateUpdate()
{
	if (GET_INSTANCE(CKeyMgr)->Key_Pressing(VK_LEFT))
	{
		GET_INSTANCE(CSceneMgr)->Scene_Change(SCENE::SCENE_MAP1);
	}
	if (GET_INSTANCE(CKeyMgr)->Key_Pressing(VK_RIGHT))
	{
		GET_INSTANCE(CSceneMgr)->Scene_Change(SCENE::SCENE_MAP2);
	}
	if (GET_INSTANCE(CKeyMgr)->Key_Pressing(VK_RETURN))
	{
		GET_INSTANCE(CSceneMgr)->Scene_Change(SCENE::SCENE_MAP3);
	}
}

void CCamp::Render()
{
	Render_SingleTex(L"camp", WINCX/2, WINCY / 2);

	//bar
	Render_SingleTex(L"Topbar", WINCX / 2, 40);
	TCHAR		Text[MIN_STR];
	D3DXMATRIX matScale, matTrans, matWorld;

	////////////////topbar
	//이름
	swprintf_s(Text, L"아이언클래드");

	D3DXMatrixTranslation(&matTrans, 50, 10, 0.f);
	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
	GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), Text, lstrlen(Text), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	//HP
	swprintf_s(Text, L"%d / %d", GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Get_HP(), GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Get_MaxHP());

	D3DXMatrixTranslation(&matTrans, 300, 10, 0.f);
	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
	GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), Text, lstrlen(Text), nullptr, 0, D3DCOLOR_ARGB(255, 250, 128, 114));
	//Gold
	swprintf_s(Text, L"%d", GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Get_Gold());

	D3DXMatrixTranslation(&matTrans, 480, 10, 0.f);
	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
	GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), Text, lstrlen(Text), nullptr, 0, D3DCOLOR_ARGB(255, 238, 199, 81));

}

void CCamp::Release()
{
}
