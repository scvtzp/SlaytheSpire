#include "stdafx.h"
#include "CardID.h"
#include "Card.h"
#include "Player.h"

CCardID::CCardID()
{
}


CCardID::~CCardID()
{

}

HRESULT CCardID::Initialize()
{
	m_tInfo.vPos = { 300.f + m_iNumber * 170, 700.f, 0.f };

	m_vCurPos = m_tInfo.vPos;
	m_tInfo.vSize = { 0.8f, 0.8f, 0.f };
	m_tInfo.vHitSize = { 200.f, 250.f, 0.f };
	m_iCulNumber = m_iNumber;
	m_bClick = false;

	m_iCardUp = 0;

	return S_OK;
}

int CCardID::Update()
{
	if (m_iNumber < 0) //패에 없다면(사용 했다면) 업데이트 패스.
	{
		return 0;
	}

	m_tInfo.vPos = { 300.f + (m_iNumber * 170) + (85 * m_iCardCount), 700.f, 0.f };


	if (m_iCulNumber != m_iNumber)
	{
		m_iCulNumber = m_iNumber;
	}

	//point 설정
	D3DXMATRIX matScale, matRotZ, matTrance;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrance;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);


	Update_Rect();
	m_bMouseHit = CCollisionMgr::Collision_Card_Mouse(Get_Rect());

	Card_Update();

	return m_iNumber;
}

void CCardID::LateUpdate()
{
	Key_Update();
}

void CCardID::Render()
{
	if (m_iNumber == -1)
	{
		return;
	}
	if (m_bCostqnwhr)
	{
		TCHAR		m_szFPS[MIN_STR];
		D3DXMATRIX matScale, matTrans, matRotationZ, matWorld;

		swprintf_s(m_szFPS, L"코스트가 부족합니다");

		D3DXMatrixTranslation(&matTrans, WINCX/2-100, 300.f, 0.f);
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 0, 0));
		m_bCostTime += 100.f * (GET_INSTANCE(CTimeMgr)->Get_DeltaTime() * 2.3f);
		if (m_bCostTime >= 50)
		{
			m_bCostTime = 0;
			m_bCostqnwhr = false;
		}
	}

	if (m_CardName == CARD::Strike)
		Render_SingleTex(L"Strike", m_tInfo.vPos.x, m_tInfo.vPos.y);
	else if (m_CardName == CARD::Defend)
		Render_SingleTex(L"Defend", m_tInfo.vPos.x, m_tInfo.vPos.y);
	else if (m_CardName == CARD::Whirlwind)
		Render_SingleTex(L"Whirlwind", m_tInfo.vPos.x, m_tInfo.vPos.y);
	else if (m_CardName == CARD::Pommel_Strick)
		Render_SingleTex(L"Pommel_Strike", m_tInfo.vPos.x, m_tInfo.vPos.y);
	else if (m_CardName == CARD::Bash)
		Render_SingleTex(L"Bash", m_tInfo.vPos.x, m_tInfo.vPos.y);
	else if (m_CardName == CARD::Anger)
		Render_SingleTex(L"Anger", m_tInfo.vPos.x, m_tInfo.vPos.y);
	else if (m_CardName == CARD::BodySlam)
		Render_SingleTex(L"BodySlam", m_tInfo.vPos.x, m_tInfo.vPos.y);
	else if (m_CardName == CARD::Cleave)
		Render_SingleTex(L"Cleave", m_tInfo.vPos.x, m_tInfo.vPos.y);
	else if (m_CardName == CARD::Sword_Boomerang)
		Render_SingleTex(L"Sword_Boomerang", m_tInfo.vPos.x, m_tInfo.vPos.y);
	else if (m_CardName == CARD::Carnage)
		Render_SingleTex(L"Carnage", m_tInfo.vPos.x, m_tInfo.vPos.y);
	else if (m_CardName == CARD::Barricade)
		Render_SingleTex(L"Barricade", m_tInfo.vPos.x, m_tInfo.vPos.y);
	else if (m_CardName == CARD::Feed)
		Render_SingleTex(L"Feed", m_tInfo.vPos.x, m_tInfo.vPos.y);
	else if (m_CardName == CARD::FiendFire)
		Render_SingleTex(L"FiendFire", m_tInfo.vPos.x, m_tInfo.vPos.y);
	else if (m_CardName == CARD::SeeinfRed)
		Render_SingleTex(L"SeeinfRed", m_tInfo.vPos.x, m_tInfo.vPos.y);
	else if (m_CardName == CARD::Headbutt)
		Render_SingleTex(L"Headbutt", m_tInfo.vPos.x, m_tInfo.vPos.y);
}

void CCardID::Release()
{
}

void CCardID::Render_Button(float x, float y)
{
	//전사
	if (m_CardName == CARD::Strike)
		Render_SingleTex(L"Strike", x, y, 0.8f, 0.8f);
	else if (m_CardName == CARD::Defend)
		Render_SingleTex(L"Defend", x, y, 0.8f, 0.8f);
	else if (m_CardName == CARD::Whirlwind)
		Render_SingleTex(L"Whirlwind", x, y, 0.8f, 0.8f);
	else if (m_CardName == CARD::Pommel_Strick)
		Render_SingleTex(L"Pommel_Strike", x, y, 0.8f, 0.8f);
	else if (m_CardName == CARD::Bash)
		Render_SingleTex(L"Bash", x, y, 0.8f, 0.8f);
	else if (m_CardName == CARD::Anger)
		Render_SingleTex(L"Anger", x, y, 0.8f, 0.8f);
	else if (m_CardName == CARD::BodySlam)
		Render_SingleTex(L"BodySlam", x, y, 0.8f, 0.8f);
	else if (m_CardName == CARD::Cleave)
		Render_SingleTex(L"Cleave", x, y, 0.8f, 0.8f);
	else if (m_CardName == CARD::Sword_Boomerang)
		Render_SingleTex(L"Sword_Boomerang", x, y, 0.8f, 0.8f);
	else if (m_CardName == CARD::Carnage)
		Render_SingleTex(L"Carnage", x, y, 0.8f, 0.8f);
	else if (m_CardName == CARD::Barricade)
		Render_SingleTex(L"Barricade", x, y, 0.8f, 0.8f);
	else if (m_CardName == CARD::Feed)
		Render_SingleTex(L"Feed", x, y, 0.8f, 0.8f);
	else if (m_CardName == CARD::FiendFire)
		Render_SingleTex(L"FiendFire", x, y, 0.8f, 0.8f);
	else if (m_CardName == CARD::SeeinfRed)
		Render_SingleTex(L"SeeinfRed", x, y, 0.8f, 0.8f);
	else if (m_CardName == CARD::Headbutt)
		Render_SingleTex(L"Headbutt", x, y, 0.8f, 0.8f);

}

void CCardID::Set_Number(int a)
{
	m_iNumber = a;
}

void CCardID::Card_Update()
{
	if (m_bMouseHit)
	{
		m_tInfo.vPos.y = 600;
		if (m_tInfo.vSize.x <= 0.9f)
		{
			m_tInfo.vSize.x += 0.02f;
			m_tInfo.vSize.y += 0.02f;
		}
	}
	else
	{
		m_tInfo.vPos.y = 700;
		if (m_tInfo.vSize.x >= 0.8f)
		{
			m_tInfo.vSize.x -= 0.02f;
			m_tInfo.vSize.y -= 0.02f;
		}
	}

	if (Key_Down(VK_LBUTTON))
	{
		if (m_bMouseHit)	//충돌
		{
			m_bClick = true;
		}
	}

	else if (Key_Up(VK_LBUTTON) && m_bClick)
	{
		m_bClick = false;
		m_tInfo.vPos = m_vCurPos;
		
		if (CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_PLAYER).front()->Get_Cost() - m_tCardInfo.iCost < 0)
		{
			m_bCostqnwhr = true;
			return;
		}
		////////////////////////////////////////////////////////////////////카드 업데이트
		//Strike
		if (m_CardName == CARD::Strike)
		{
			bool bTest = CCollisionMgr::Collision_Monster_Mouse(m_tCardInfo, CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_MONSTER), CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_PLAYER));
			if (bTest)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"ATK_FastAtk.ogg", CSoundMgr::PLAYER);
				m_iNumber = -1;
			}
		}
		// Defend
		else if (m_CardName == CARD::Defend)
		{
			CCollisionMgr::Set_Player_Block(CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_PLAYER), m_tCardInfo.iBlock);
			CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_Cost(m_tCardInfo.iCost);
			CSoundMgr::Get_Instance()->PlaySound(L"Get_Defense.ogg", CSoundMgr::PLAYER);
			m_iNumber = -1;
		}
		// Whirlwind
		else if (m_CardName == CARD::Whirlwind)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Card_Whirlwind.ogg", CSoundMgr::PLAYER);

			CCollisionMgr::Whirlwind(CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_MONSTER), m_tCardInfo.iDamage, CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_PLAYER).front()->Get_Cost());

			CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_Cost(CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_PLAYER).front()->Get_Cost());
			m_iNumber = -1;
		}
		// Pommel_Strick
		else if (m_CardName == CARD::Pommel_Strick)
		{
			bool bTest = CCollisionMgr::Collision_Monster_Mouse(m_tCardInfo, CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_MONSTER), CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_PLAYER));
			if (bTest)
			{
				dynamic_cast<CCard*>(GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_CARD).front())->Draw(m_tCardInfo.iDraw);
				CSoundMgr::Get_Instance()->PlaySound(L"ATK_FastAtk.ogg", CSoundMgr::PLAYER);
				m_iNumber = -1;
			}
		}
		//절단
		else if (m_CardName == CARD::Cleave) 
		{
			for (auto& itor : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_MONSTER))
			{
				itor->Set_Hp(m_tCardInfo.iDamage);
			}
			GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_Cost(m_tCardInfo.iCost);
			CSoundMgr::Get_Instance()->PlaySound(L"ATK_FastAtk.ogg", CSoundMgr::PLAYER);
			m_iNumber = -1;
		}
		//몸통박치기
		else if (m_CardName == CARD::BodySlam) 
		{
			m_tCardInfo.iDamage = GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Get_Block();
			bool bTest = CCollisionMgr::Collision_Monster_Mouse(m_tCardInfo, CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_MONSTER), CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_PLAYER));
			if (bTest)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"ATK_FastAtk.ogg", CSoundMgr::PLAYER);
				m_iNumber = -1;
			}
		}
		//대학살
		else if (m_CardName == CARD::Carnage) 
		{
			bool bTest = CCollisionMgr::Collision_Monster_Mouse(m_tCardInfo, CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_MONSTER), CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_PLAYER));
			if (bTest)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"ATK_FastAtk.ogg", CSoundMgr::PLAYER);
				m_iNumber = -2;
			}
		}
		//바리케이트
		else if (m_CardName == CARD::Barricade) 
		{
			GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_Buff(BUFF::Buff_Barricade);
			m_iNumber = -1;
		}
		//강타
		else if (m_CardName == CARD::Bash) 
		{
			bool bTest = CCollisionMgr::Collision_Monster_Mouse(m_tCardInfo, CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_MONSTER), CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_PLAYER));
			if (bTest)
			{
				RECT rc = {};
				POINT	pt;
				GetCursorPos(&pt);
				ScreenToClient(g_hWND, &pt);
				for (auto& itor : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_MONSTER))
				{
					if (itor->Get_Rect().left <= pt.x &&
						itor->Get_Rect().right >= pt.x &&
						itor->Get_Rect().bottom >= pt.y &&
						itor->Get_Rect().top <= pt.y)
					{
						itor->Set_DeBuff(DEBUFF::Debuff_Vulnerable);
					}
				}
				CSoundMgr::Get_Instance()->PlaySound(L"Bff_Debuff.ogg", CSoundMgr::MONSTER);
				CSoundMgr::Get_Instance()->PlaySound(L"ATK_FastAtk.ogg", CSoundMgr::PLAYER);

				m_iNumber = -1;
			}
		}
		//포식
		else if (m_CardName == CARD::Feed) 
		{
			RECT rc = {};
			POINT	pt;
			GetCursorPos(&pt);
			ScreenToClient(g_hWND, &pt);

			for (auto& Player : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER))
			{
				for (auto& Src : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_MONSTER))
				{
					if (Src->Get_Rect().left <= pt.x &&
						Src->Get_Rect().right >= pt.x &&
						Src->Get_Rect().bottom >= pt.y &&
						Src->Get_Rect().top <= pt.y)
					{
						Src->Set_Hp(m_tCardInfo.iDamage);
						if (Src->Get_HP() <= 0)
						{
							Player->Set_MaxHp(3);
						}
						Player->Set_Cost(m_tCardInfo.iCost);
						dynamic_cast<CPlayer*>(Player)->Set_AttMove();

						CSoundMgr::Get_Instance()->PlaySound(L"ATK_FastAtk.ogg", CSoundMgr::PLAYER);
						m_iNumber = -1;
					}
				}
			}
		}

		//지옥불
		else if (m_CardName == CARD::FiendFire) 
		{
			m_tCardInfo.iDamage = dynamic_cast<CCard*>(GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_CARD).front())->Get_HandNum() * 7;
			bool bTest = CCollisionMgr::Collision_Monster_Mouse(m_tCardInfo, CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_MONSTER), CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_PLAYER));

			for (auto& itor : dynamic_cast<CCard*>(GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_CARD).front())->Get_VecHand())
			{
				CSoundMgr::Get_Instance()->PlaySound(L"ATK_FastAtk.ogg", CSoundMgr::PLAYER);
				itor->Set_Number(-2);
			}
		}

		//혈안
		else if (m_CardName == CARD::SeeinfRed) 
		{
			dynamic_cast<CPlayer*>(GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front())->Set_Cost(-1);
			m_iNumber = -2;
		}

		//분노
		else if (m_CardName == CARD::Anger) 
		{
			bool bTest = CCollisionMgr::Collision_Monster_Mouse(m_tCardInfo, CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_MONSTER), CObjMgr::Get_Instance()->Get_listObj(OBJ::OBJ_PLAYER));
			if (bTest)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"ATK_FastAtk.ogg", CSoundMgr::PLAYER);
				m_iNumber = -3;
			}
		}

	}

	if (Key_Pressing(VK_LBUTTON) && m_bClick)
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWND, &pt);

		m_tInfo.vPos = { (float)pt.x, (float)pt.y, 0.f };
	}
}