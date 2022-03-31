#include "stdafx.h"
#include "MyButton.h"
#include "Monster.h"
#include "Card.h"

CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}

HRESULT CMyButton::Initialize()
{
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vHitSize = {100.f,100.f,0.f};
	m_ButtonID = BUTTON::TURNEND;
	m_bGetCard = false;

	return S_OK;
}

int CMyButton::Update()
{
	Update_Rect();
	m_bMouseHit = CCollisionMgr::Collision_Card_Mouse(Get_Rect());

	return 0;
}

void CMyButton::LateUpdate()
{
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	if (m_bMouseHit && Key_Down(VK_LBUTTON)) //충돌
	{
		CSoundMgr::Get_Instance()->PlaySound(L"UI_Click.wav", CSoundMgr::MAXCHANNEL);
		GET_INSTANCE(CObjMgr)->Set_Scroll(0.f, 0.f);

		switch (m_ButtonID)
		{
		case BUTTON::TURNEND:
			CSoundMgr::Get_Instance()->PlaySound(L"BT_EndTurn.ogg", CSoundMgr::PLAYER);
			GET_INSTANCE(CObjMgr)->Set_CardCheck();
			for (auto& Monster : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_MONSTER))
			{
				Monster->Set_BlockZero();
				dynamic_cast<CMonster*>(Monster)->Monster_Action();
				Monster->LateUpdate();
				if (Monster->Check_DeBuff(DEBUFF::Debuff_Vulnerable))
					;
				else
					;//Monster->Set_Hp(10);
			}
			if (GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Check_Buff(BUFF::Buff_Barricade))
				;
			else
				GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_BlockZero();

			CSoundMgr::Get_Instance()->PlaySound(L"BT_EnemyTurn.ogg", CSoundMgr::MONSTER);

			break;
		case BUTTON::M_TestMonster:

			GET_INSTANCE(CSceneMgr)->Set_Scene(SCENE::SCENE_STAGE);
			break;
		case BUTTON::M_Looter:

			GET_INSTANCE(CSceneMgr)->Set_Scene(SCENE::STAGE_Looter);
			break;
		case BUTTON::M_Byrd:

			GET_INSTANCE(CSceneMgr)->Set_Scene(SCENE::STAGE_Byrd);
			break;
		case BUTTON::M_Darkling:

			GET_INSTANCE(CSceneMgr)->Set_Scene(SCENE::STAGE_Darkling);
			break;
		case BUTTON::M_GiantHead:
			GET_INSTANCE(CSceneMgr)->Set_Scene(SCENE::STAGE_GiantHead);
			break;
		case BUTTON::M_Transient:

			GET_INSTANCE(CSceneMgr)->Set_Scene(SCENE::STAGE_Transient);
			break;
		case BUTTON::M_Slime:
			break;
		case BUTTON::B_Guardian:
			GET_INSTANCE(CSceneMgr)->Set_Scene(SCENE::SCENE_STAGE_GUARDIAN);
			break;
		case BUTTON::B_DoDe:
			GET_INSTANCE(CSceneMgr)->Set_Scene(SCENE::STAGE_DoDe);
			break;
		case BUTTON::B_Hexa:
			GET_INSTANCE(CSceneMgr)->Set_Scene(SCENE::STAGE_Hexa);
			break;
		case BUTTON::Get_Card:
			m_bGetCard = true;
			break;
		case BUTTON::Get_Gold:
			CSoundMgr::Get_Instance()->PlaySound(L"Get_Gold.ogg", CSoundMgr::UI);
			m_bRenderCK = false;
			GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_Gold(-1 *  GET_INSTANCE(CObjMgr)->Get_Gold());
			break;
		case BUTTON::D_Shop:
			GET_INSTANCE(CSceneMgr)->Set_Scene(SCENE::SCENE_SHOP);
			break;
		case BUTTON::D_Camp:
			GET_INSTANCE(CSceneMgr)->Set_Scene(SCENE::SCENE_Sleep);
			break;		
		case BUTTON::D_GoMap1:
			GET_INSTANCE(CObjMgr)->Set_CardCheck();
			if (GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Check_Buff(BUFF::Buff_Barricade))
				;
			else
				GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_BlockZero();

			GET_INSTANCE(CSceneMgr)->Set_Scene(SCENE::SCENE_MAP1);
			break;
		case BUTTON::D_GoMap2:
			GET_INSTANCE(CObjMgr)->Set_CardCheck();
			if (GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Check_Buff(BUFF::Buff_Barricade))
				;
			else
				GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_BlockZero();

			GET_INSTANCE(CSceneMgr)->Set_Scene(SCENE::SCENE_MAP2);
			break;
		case BUTTON::D_GoMap3:
			GET_INSTANCE(CObjMgr)->Set_CardCheck();
			if (GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Check_Buff(BUFF::Buff_Barricade))
				;
			else
				GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_BlockZero();

			GET_INSTANCE(CSceneMgr)->Set_Scene(SCENE::SCENE_MAP3);
			break;
		default:
			break;
		}
	}
	Key_Update();
}

void CMyButton::Render()
{
	TCHAR		m_szFPS[MIN_STR];
	D3DXMATRIX  matTrans;
	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);


	if (BShowCard)
		ShowCardIn(ObjectKey);


	if (!m_bRenderCK)
		return;

	switch (m_ButtonID)
	{
	case BUTTON::TURNEND:
		//		if (pt.x >= 1010 && pt.x <= 1190 && pt.y <= 590 && pt.y >= 530)
		if (m_bMouseHit)
			Render_SingleTex(L"endTurnButtonGlow", 1100, 560, 0.7f, 0.7f);
		else
			Render_SingleTex(L"endTurnButton", 1100, 560, 0.7f, 0.7f);
		swprintf_s(m_szFPS, L"턴 종료");
		D3DXMatrixTranslation(&matTrans, 1060, 553, 0.f);
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case BUTTON::M_TestMonster:
		Render_SingleTex(L"monster", m_tInfo.vPos.x, m_tInfo.vPos.y+GET_INSTANCE(CObjMgr)->Get_ScrollY(), 0.5f, 0.5f);
		break;
	case BUTTON::M_Looter:
		Render_SingleTex(L"monster", m_tInfo.vPos.x, m_tInfo.vPos.y + GET_INSTANCE(CObjMgr)->Get_ScrollY(), 0.5f, 0.5f);
		break;
	case BUTTON::M_Byrd:
		Render_SingleTex(L"monster", m_tInfo.vPos.x, m_tInfo.vPos.y + GET_INSTANCE(CObjMgr)->Get_ScrollY(), 0.5f, 0.5f);
		break;
	case BUTTON::M_Darkling:
		Render_SingleTex(L"elite", m_tInfo.vPos.x, m_tInfo.vPos.y + GET_INSTANCE(CObjMgr)->Get_ScrollY(), 0.5f, 0.5f);
		break;
	case BUTTON::M_GiantHead:
		Render_SingleTex(L"elite", m_tInfo.vPos.x, m_tInfo.vPos.y + GET_INSTANCE(CObjMgr)->Get_ScrollY(), 0.5f, 0.5f);
		break;
	case BUTTON::M_Transient:
		Render_SingleTex(L"elite", m_tInfo.vPos.x, m_tInfo.vPos.y + GET_INSTANCE(CObjMgr)->Get_ScrollY(), 0.5f, 0.5f);
		break;
	case BUTTON::M_Slime:
		break;
	case BUTTON::B_Guardian:
		break;
	case BUTTON::B_DoDe:
		break;
	case BUTTON::B_Hexa:
		break;
	case BUTTON::Get_Card:
		Render_SingleTex(L"rewardListItemPanel", m_tInfo.vPos.x, m_tInfo.vPos.y, 0.7f, 0.7f, 100, 255, 255, 255);
		Render_SingleTex(L"normalCardReward", m_tInfo.vPos.x - 100, m_tInfo.vPos.y, 0.7f, 0.7f, 255, 255, 255, 255);
		swprintf_s(m_szFPS, L"덱에 카드를 추가");
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - 80, m_tInfo.vPos.y, 0.f);
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case BUTTON::Get_Gold:
		Render_SingleTex(L"rewardListItemPanel", m_tInfo.vPos.x, m_tInfo.vPos.y, 0.7f, 0.7f, 100, 255, 255, 255);
		Render_SingleTex(L"gold", m_tInfo.vPos.x-100, m_tInfo.vPos.y, 0.7f, 0.7f, 255, 255, 255, 255);
		swprintf_s(m_szFPS, L"%d 골드", GET_INSTANCE(CObjMgr)->Get_Gold());
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - 80, m_tInfo.vPos.y, 0.f);
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case BUTTON::D_Shop:
		Render_SingleTex(L"shop", m_tInfo.vPos.x, m_tInfo.vPos.y + GET_INSTANCE(CObjMgr)->Get_ScrollY(), 0.5f, 0.5f);
		break;
	case BUTTON::D_Camp:
		Render_SingleTex(L"rest", m_tInfo.vPos.x, m_tInfo.vPos.y + GET_INSTANCE(CObjMgr)->Get_ScrollY(), 0.5f, 0.5f);
		break;
	case BUTTON::D_GoMap1:
		Render_SingleTex(L"proceedButton", m_tInfo.vPos.x, m_tInfo.vPos.y, 0.7f, 0.7f);
		break;
	case BUTTON::D_GoMap2:
		Render_SingleTex(L"proceedButton", m_tInfo.vPos.x, m_tInfo.vPos.y, 0.7f, 0.7f);
		break;
	case BUTTON::D_GoMap3:
		Render_SingleTex(L"proceedButton", m_tInfo.vPos.x, m_tInfo.vPos.y, 0.7f, 0.7f);
		break;
	default:
		break;
	}

	if (m_bGetCard)
	{
		m_bGetCard = false;
		CCardID* pCardID;
		pCardID = new CCardID;
		BShowCard = true;
		m_bRenderCK = false;

		switch (rand() % 13)
		{
		case 0:
			pCardID->Set_CardName(CARD::Barricade);
			pCardID->Set_Cost(3);
			ObjectKey = L"Barricade";
			break;
		case 1:
			pCardID->Set_CardName(CARD::Feed);
			pCardID->Set_Cost(1);
			pCardID->Set_Damage(10);
			ObjectKey = L"Feed";
			break;
		case 2:
			pCardID->Set_CardName(CARD::Bash);
			pCardID->Set_Cost(2);
			pCardID->Set_Damage(8);
			ObjectKey = L"Bash";
			break;
		case 3:
		case 4:
			pCardID->Set_CardName(CARD::SeeinfRed);
			pCardID->Set_Cost(1);
			ObjectKey = L"SeeinfRed";
			break;
		case 5:
			pCardID->Set_CardName(CARD::Anger);
			pCardID->Set_Cost(0);
			ObjectKey = L"Anger";
			break;
		case 6:
			pCardID->Set_CardName(CARD::FiendFire);
			pCardID->Set_Cost(2);
			pCardID->Set_Damage(0);
			ObjectKey = L"FiendFire";
			break;
		case 7:
			pCardID->Set_CardName(CARD::Cleave);
			pCardID->Set_Cost(1);
			pCardID->Set_Damage(8);
			ObjectKey = L"Cleave";
			break;
		case 8:
			pCardID->Set_CardName(CARD::Strike);
			pCardID->Set_Cost(1);
			pCardID->Set_Damage(6);
			ObjectKey = L"Strike";
			break;
		case 9:
			pCardID->Set_CardName(CARD::Defend);
			pCardID->Set_Cost(1);
			pCardID->Set_Block(5);
			ObjectKey = L"Defend";
			break;
		case 10:
			pCardID->Set_CardName(CARD::Whirlwind);
			pCardID->Set_Damage(5);
			ObjectKey = L"Whirlwind";
			break;
		case 11:
			pCardID->Set_CardName(CARD::Carnage);
			pCardID->Set_Cost(2);
			pCardID->Set_Damage(20);
			ObjectKey = L"Carnage";
			break;
		case 12:
			pCardID->Set_CardName(CARD::BodySlam);
			pCardID->Set_Cost(1);
			pCardID->Set_Damage(0);
			ObjectKey = L"BodySlam";
			break;
		default:
			break;
		}
		pCardID->Initialize();
		dynamic_cast<CCard*>(GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_CARD).front())->Add_Card(pCardID);
	}
}

void CMyButton::Release()
{
}

void CMyButton::ShowCardIn(const wstring & wstrObjectKey)
{
	Render_SingleTex(wstrObjectKey, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.8f, 0.8f);
	m_tInfo.vPos.x -= 10;
	m_tInfo.vPos.y += 10;		

	if (m_tInfo.vPos.x < 0 || m_tInfo.vPos.y > WINCY)
		BShowCard = false;
}
