#include "stdafx.h"
#include "Select_Player.h"
#include "Player.h"
#include "Card.h"


CSelect_Player::CSelect_Player()
{
}


CSelect_Player::~CSelect_Player()
{
	Release();
}

HRESULT CSelect_Player::Initialize()
{
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Select_Player/ironcladButton.png", L"ironcladButton");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Select_Player/ironcladPortrait.jpg", L"ironcladPortrait");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Select_Player/silentButton.png", L"silentButton");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Select_Player/silentPortrait.jpg", L"silentPortrait");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Select_Player/defectPortrait.jpg", L"defectPortrait");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Select_Player/defectButton.png", L"defectButton");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Select_Player/watcherButton.png", L"watcherButton");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Select_Player/watcherPortrait.jpg", L"watcherPortrait");

	GET_INSTANCE(CObjMgr)->Set_Map();
	GET_INSTANCE(CObjMgr)->Set_Count(0);

	return S_OK;
}

void CSelect_Player::Update()
{
}

void CSelect_Player::LateUpdate()
{
	if (GET_INSTANCE(CKeyMgr)->Key_Down(VK_RBUTTON))
	{
		GET_INSTANCE(CSceneMgr)->Scene_Change(SCENE::SCENE_STAGE);
	}
}

void CSelect_Player::Render()
{
	bool Check = Key_Down(VK_LBUTTON);
	////마우스 포인터
	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	switch (m_eSelect)
	{
	case CSelect_Player::Ironclad:
		Render_SingleTex(L"ironcladPortrait", WINCX/2, WINCY/2, 0.7f, 0.7f);
		break;
	case CSelect_Player::silent:
		Render_SingleTex(L"silentPortrait", WINCX / 2, WINCY / 2, 0.7f, 0.7f);
		break;
	case CSelect_Player::Defect:
		Render_SingleTex(L"defectPortrait", WINCX / 2, WINCY / 2, 0.7f, 0.7f);
		break;
	case CSelect_Player::Watcher:
		Render_SingleTex(L"watcherPortrait", WINCX / 2, WINCY / 2, 0.7f, 0.7f);
		break;
	default:
		Render_SingleTex(L"watcherPortrait", WINCX / 2, WINCY / 2, 0.7f, 0.7f);
		break;
	}
	Render_SingleTex(L"ironcladButton", 410.f, 600.f, 0.7f, 0.7f);
	Render_SingleTex(L"silentButton", 410.f + 145, 600.f, 0.7f, 0.7f);
	Render_SingleTex(L"defectButton", 410.f + 290, 600.f, 0.7f, 0.7f);
	Render_SingleTex(L"watcherButton", 410.f + 435, 600.f, 0.7f, 0.7f);

	if (m_eSelect == m_eCulSelect)
	{

		if(Check)
		{
			CObj* pObj;
			switch (m_eSelect)
			{
			case CSelect_Player::Ironclad:
				pObj = CAbstractFactory<CPlayer>::Create();
				GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_PLAYER, pObj);

				pObj = CAbstractFactory<CCard>::Create();
				GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_CARD, pObj);

				GET_INSTANCE(CSceneMgr)->Scene_Change(SCENE::SCENE_MAP1);
				break;
			default:
				break;
			}
		}
	}
	if (pt.y <= 670 && pt.y >= 530 && pt.x >= 340 && Check)
	{
		if (pt.x <= 480)
		{
			m_eCulSelect = m_eSelect;
			m_eSelect = Player::Ironclad;
		}
		else if (pt.x <= 625)
		{
			m_eCulSelect = m_eSelect;
			m_eSelect = Player::silent;
		}
		else if (pt.x <= 770)
		{
			m_eCulSelect = m_eSelect;
			m_eSelect = Player::Defect;
		}
		else if (pt.x <= 915)
		{
			m_eCulSelect = m_eSelect;
			m_eSelect = Player::Watcher;
		}
	}

	Render_SingleTex(L"Cursors", pt.x + 10, pt.y + 10, 0.7f, 0.7f);

	Key_Update();
}

void CSelect_Player::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
}

bool CSelect_Player::Key_Down(int _key)
{
	if (!m_bKeyState[_key] && (GetAsyncKeyState(_key) & 0x8000))
	{
		m_bKeyState[_key] = !m_bKeyState[_key];
		return true;
	}
	return false;
}

void CSelect_Player::Key_Update()
{
	// key 상태를 복원하는 함수이다.
	// 복원하지 않을 경우 key_down과 key_up은 단 한번만 수행되기 때문이다.
	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
		if (!m_bKeyState[i] && (GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}


}
