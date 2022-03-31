#include "stdafx.h"
#include "Shop.h"
#include "Player.h"
#include "Card.h"
#include "MyButton.h"
#include "CardID.h"
CShop::CShop()
{

}

CShop::~CShop()
{
	Release();
}

HRESULT CShop::Initialize()
{
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Shop.ogg");

	int j = 0;
	for (int i = 0; i<7; i++)
	{
		CCardID* pCardID = new CCardID;

		switch (rand()%10)
		{
		case 0:
			pCardID->Set_CardName(CARD::Barricade);
			pCardID->Set_Cost(3);			
			break;
		case 1:
			pCardID->Set_CardName(CARD::Feed);
			pCardID->Set_Cost(1);
			pCardID->Set_Damage(10);
			break;
		case 2:
			pCardID->Set_CardName(CARD::Bash);
			pCardID->Set_Cost(2);
			pCardID->Set_Damage(8);
			break;
		case 3:
			pCardID->Set_CardName(CARD::Pommel_Strick);
			pCardID->Set_Cost(1);
			pCardID->Set_Damage(9);
			pCardID->Set_Draw(1);
			break;
		case 4:
			pCardID->Set_CardName(CARD::SeeinfRed);
			pCardID->Set_Cost(1);
			break;
		case 5:
			pCardID->Set_CardName(CARD::Anger);
			pCardID->Set_Cost(0);
			pCardID->Set_Damage(6);
			break;
		case 6:
			pCardID->Set_CardName(CARD::FiendFire);
			pCardID->Set_Cost(2);
			pCardID->Set_Damage(0);
			break;
		case 7:
			pCardID->Set_CardName(CARD::Cleave);
			pCardID->Set_Cost(1);
			pCardID->Set_Damage(8);
			break;
		default:
			pCardID->Set_CardName(CARD::Pommel_Strick);
			pCardID->Set_Cost(1);
			pCardID->Set_Damage(9);
			pCardID->Set_Draw(1);
			break;
		}
		pCardID->Initialize();

		pCardID->Set_Gold(rand() % 100);
		pCardID->Set_Size(0.25f);

		if (i * 200 > 800)
		{
			j++;
		}
		pCardID->Set_Pos(240 + (i * 200) - (j*1000), 200 + j * 300);
		
		pCardID->Update_Rect();

		m_VecShop.emplace_back(pCardID);
	}

	m_tFrame = {0, 160};
	m_tInfo.vPos = {WINCX / 2, WINCY/2, 0.f};
	m_bShopCheck = false;
	m_bPurgeHit = false;
	return S_OK;
}

void CShop::Update()
{
	GET_INSTANCE(CObjMgr)->Update(SHOP);

	//Frame
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * (GET_INSTANCE(CTimeMgr)->Get_DeltaTime() * 0.2f);

	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
	{
		m_tFrame.fFrameStart = 0.f;
	}
}

void CShop::LateUpdate()
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

	GET_INSTANCE(CSceneMgr)->Scene_Check();
}

void CShop::Render()
{
	////마우스 포인터
	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);
	Down = Key_Down(VK_LBUTTON);

	//배경
	D3DXMATRIX matScale, matTrans, matWorld;

	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"BottomScene");
	assert(!(nullptr == pTexInfo));

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX / 2, WINCY / 2, 0.f);

	matWorld = matScale * matTrans;

	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
	GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	//render
	GET_INSTANCE(CObjMgr)->Render(SHOP);

	Render_SingleTex(L"MerchantObj", m_tInfo.vPos.x, m_tInfo.vPos.y+20, 0.75f, 0.75f);
	Render_MultiTex(L"Merchant", L"Idle", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y);

	ShopOpen();

	//커서 on/off
	if (!m_bShopCheck)
	{
		Render_SingleTex(L"Cursors", pt.x + 10, pt.y + 10, 0.7f, 0.7f);
	}

	//제거
	else if (m_bPurgeHit)
	{
		Render_SingleTex(L"BLACK", WINCX / 2, WINCY / 2, 1.f, 1.f, 200);

		float x = 200, y = 250;

		for (auto& itor : dynamic_cast<CCard*>(GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_CARD).front())->Get_VecDeck())
		{
			itor->Set_Pos(x, y);
			itor->Update_Rect();

			if (CCollisionMgr::Collision_Card_Mouse(itor->Get_Rect()))
			{
				if (Down)
				{
					if (GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Get_Gold() - 50 >= 0)
					{
						itor->Set_Number(-2);
						GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_Gold(50);

						m_bPurgeHit = false;
						m_bSold_Out = true;
					}
				}
				itor->Set_Size(0.8f);
			}
			else
			{
				itor->Set_Size(0.7f);
			}


			itor->Render_Button(x, y);

			x += 200;
			if (x > 1000)
			{
				x = 200;
				y += 250;
			}

			Render_SingleTex(L"cancelButton", 200.f, 650.f);
			if (pt.x <= 200 && pt.x >= 0 && pt.y >= 530 && pt.y <= 650)
			{
				Render_SingleTex(L"cancelButtonON", 200.f, 650.f);
				if (Down)
				{
					m_bPurgeHit = false;
					m_bSold_Out = false;
				}
			}
		}
		GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_CARD).front()->Update();

		Render_SingleTex(L"Cursors", pt.x + 10, pt.y + 10, 0.7f, 0.7f);
	}
	else
	{
		for (auto& itor : m_VecShop)
		{
			if (itor->Get_Number() == -1)
			{
				continue;
			}
			if (CCollisionMgr::Collision_Card_Mouse(itor->Get_Rect()))
			{
				if (Key_Pressing(VK_LBUTTON))
				{
					if (GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Get_Gold() - itor->Get_Gold() >= 0)
					{
						dynamic_cast<CCard*>(GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_CARD).front())->Add_Card(itor);
						GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_Gold(itor->Get_Gold());
						itor->Set_Number(-1);
					}
				}
				itor->Set_Size(0.7f);
			}
			else
			{
				itor->Set_Size(0.6f);
			}
			///////////////////////
			itor->Render();
			TCHAR		Text[MIN_STR];

			swprintf_s(Text, L"가격 : %d", itor->Get_Gold());

			D3DXMatrixTranslation(&matTrans, itor->Get_PosX()-50, itor->Get_PosY() + 130, 0.f);
			GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
			GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), Text, lstrlen(Text), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		////////////////// 카드 제거 서비스
		if (m_bSold_Out)
		{
			Render_SingleTex(L"sold_out", 1040.f, 500.f, 0.6f, 0.6f);
		}
		else if (pt.x <= 1140 && pt.x >= 940 && pt.y >= 375 && pt.y <= 625)
		{

			Render_SingleTex(L"purge", 1040.f, 500.f, 0.6f, 0.6f);
			if (Key_Pressing(VK_LBUTTON) || m_bPurgeHit)
			{
				m_bPurgeHit = true;
				m_bShopCheck = true;
			}
		}
		else
		{
			Render_SingleTex(L"purge", 1040.f, 500.f, 0.5f, 0.5f);
		}

		TCHAR		Text[MIN_STR];

		swprintf_s(Text, L"가격 : 50");

		D3DXMatrixTranslation(&matTrans, 990.f, 630.f, 0.f);
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), Text, lstrlen(Text), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		Render_SingleTex(L"merchantHand", pt.x, pt.y - 330, 0.75f, 0.75f);
	}


	//bar
	Render_SingleTex(L"Topbar", WINCX / 2, 40);
	TCHAR		Text[MIN_STR];

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

	Key_Update();
}

void CShop::Release()
{
}

bool CShop::ShopOpen()
{
	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	if (pt.x <= 740 && pt.x >= 540 && pt.y >= 260 && pt.y <= 460 && Down || m_bShopCheck)
	{
		m_bShopCheck = true;

		Render_SingleTex(L"rug", WINCX / 2, WINCY / 2, 0.63f, 0.63f);

		Render_SingleTex(L"cancelButton", 200.f, 650.f);
		if (pt.x <= 200 && pt.x >= 0 && pt.y >= 530 && pt.y <= 650 )
		{
			Render_SingleTex(L"cancelButtonON", 200.f, 650.f);
			if (Down)
				m_bShopCheck = false;
		}

		return true;
	}

	return false;
}

/////////////////////KeyMgr
bool CShop::Key_Pressing(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000)
		return true;
	return false;
}

bool CShop::Key_Down(int _key)
{
	if (!m_bKeyState[_key] && (GetAsyncKeyState(_key) & 0x8000))
	{
		m_bKeyState[_key] = !m_bKeyState[_key];
		return true;
	}
	return false;
}

bool CShop::Key_Up(int _key)
{
	if (m_bKeyState[_key] && !(GetAsyncKeyState(_key) & 0x8000))
	{
		m_bKeyState[_key] = !m_bKeyState[_key];
		return true;
	}
	return false;
}

void CShop::Key_Update()
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
