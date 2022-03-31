#include "stdafx.h"
#include "Title.h"


CTitle::CTitle()
{
}


CTitle::~CTitle()
{
	Release();
}

HRESULT CTitle::Initialize()
{
	CSoundMgr::Get_Instance()->Initialize();

	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Menu.ogg");

	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/title.png", L"title");

	return S_OK;
}

void CTitle::Update()
{
}

void CTitle::LateUpdate()
{
	if (GET_INSTANCE(CKeyMgr)->Key_Down(VK_RBUTTON))
	{
		GET_INSTANCE(CSceneMgr)->Scene_Change(SCENE::SCENE_SELECT_PLAYER);
	}

}

void CTitle::Render()
{
	Render_SingleTex(L"title", WINCX / 2, WINCY / 2);
}

void CTitle::Release()
{
}
