#include "stdafx.h"
#include "Player.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "TestMonster.h"
CPlayer::CPlayer() 
{
}


CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Initialize()
{
	/////////////////////////////////////카드
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Card/ironclad/Defend.png", L"Defend");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Card/ironclad/Strike.png", L"Strike");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Card/ironclad/Whirlwind.png", L"Whirlwind");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Card/ironclad/Pommel_Strike.png", L"Pommel_Strike");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Card/ironclad/Bash.png", L"Bash");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Card/ironclad/Anger.png", L"Anger");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Card/ironclad/BodySlam.png", L"BodySlam");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Card/ironclad/Cleave.png", L"Cleave");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Card/ironclad/Sword_Boomerang.png", L"Sword_Boomerang");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Card/ironclad/Carnage.png", L"Carnage");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Card/ironclad/Barricade.png", L"Barricade");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Card/ironclad/Feed.png", L"Feed");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Card/ironclad/FiendFire.png", L"FiendFire");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Card/ironclad/SeeinfRed.png", L"SeeinfRed");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Card/ironclad/Headbutt.png", L"Headbutt");

	m_tStatus.iCost = 3;
	m_tStatus.iMaxCost = 3;

	m_tStatus.iMaxHp = 80;
	m_tStatus.iRealMaxHp = m_tStatus.iMaxHp;
	m_tStatus.iHp = m_tStatus.iMaxHp;
	m_tStatus.iBlock = 0;
	m_tStatus.iGold = 999;
	m_tStatus.iPastHp = m_tStatus.iHp;

	m_tFrame = { 0, 267 };
	m_tInfo.vPos = { 250.f, 330.f, 0.f }; 
	m_tInfo.vSize = { 1.f, 1.f, 0.f }; 
	m_tInfo.vHitSize = { 100.f, 300.f, 0.f };

	m_bHitCheck = false;
	return S_OK; 
}

int CPlayer::Update()
{
	if (m_tStatus.iPastHp != m_tStatus.iHp)
	{
		m_tFrame = { 0, 14 };
		m_tStatus.iPastHp = m_tStatus.iHp;
		m_bHitCheck = true;
	}

	if (m_bHitCheck)
		MoveFrame(1.5f);
	else
		MoveFrame(0.1f);

	if (m_tStatus.iHp <= 0)
		m_tStatus.iHp = 0;

	switch (m_iAttMove)
	{
	case 1:
		m_tInfo.vPos.x += 7;
		if (m_tInfo.vPos.x >= 350)
		{
			m_iAttMove = 2;
		}
		break;

	case 2:
		m_tInfo.vPos.x -= 7;
		if (m_tInfo.vPos.x <= 250)
		{
			m_iAttMove = 0;
			m_tInfo.vPos.x = 250.f;
		}
		break;

	default:
		break;
	}

	Update_Rect();

	Key_Update();

	Buff_Update();
	return 0;
}

void CPlayer::LateUpdate()
{
	m_tStatus.iCost = 3;
}

void CPlayer::Render()
{
	D3DXMATRIX matScale, matTrans, matRotationZ, matWorld;
	TCHAR		m_szFPS[MIN_STR];
	Render_HpBar(m_tInfo.vPos.x, m_tInfo.vPos.y + 50, m_tStatus.iHp / (float)m_tStatus.iRealMaxHp);

	if (m_bHitCheck)
	{
		Render_MultiTex(L"Player", L"Hit", int(m_tFrame.fFrameStart),m_tInfo.vPos.x, m_tInfo.vPos.y);
	}
	else
	{
		Render_MultiTex(L"Player", L"Idle", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y);
	}
	//////////////////ui
	
	Render_SingleTex(L"layer1", m_tInfo.vPos.x - 200, m_tInfo.vPos.y + 200, 0.8f, 0.8f);
	Render_SingleTex(L"layer2", m_tInfo.vPos.x - 200, m_tInfo.vPos.y + 200, 0.8f, 0.8f);
	Render_SingleTex(L"layer3", m_tInfo.vPos.x - 200, m_tInfo.vPos.y + 200, 0.8f, 0.8f);
	Render_SingleTex(L"layer4", m_tInfo.vPos.x - 200, m_tInfo.vPos.y + 200, 0.8f, 0.8f);
	Render_SingleTex(L"layer5", m_tInfo.vPos.x - 200, m_tInfo.vPos.y + 200, 0.8f, 0.8f);
	Render_SingleTex(L"layer6", m_tInfo.vPos.x - 200, m_tInfo.vPos.y + 200, 0.8f, 0.8f);

	//////////////////////

	/////////////////////////
	swprintf_s(m_szFPS, L"%d / %d", m_tStatus.iCost, m_tStatus.iMaxCost);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x-225, m_tInfo.vPos.y+190, 0.f);
	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
	GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	//////////////////
	////////////////topbar
	//이름
	swprintf_s(m_szFPS, L"아이언클래드");

	D3DXMatrixTranslation(&matTrans, 50, 10, 0.f);
	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
	GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	//HP
	swprintf_s(m_szFPS, L"%d / %d", m_tStatus.iHp, m_tStatus.iMaxHp);

	D3DXMatrixTranslation(&matTrans, 300, 10, 0.f);
	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
	GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 250, 128, 114));
	//Gold
	swprintf_s(m_szFPS, L"%d", m_tStatus.iGold);

	D3DXMatrixTranslation(&matTrans, 480, 10, 0.f);
	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
	GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 238, 199, 81));

	Buff_Render();
}

void CPlayer::Release()
{
}


void CPlayer::MoveFrame(const float & fSpeed /*= 1*/)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * (GET_INSTANCE(CTimeMgr)->Get_DeltaTime() * fSpeed);

	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
	{
		m_tFrame.fFrameStart = 0.f;

		if (m_tFrame.fFrameEnd == 14)
		{
			m_tFrame = { 0, 267 };

			m_bHitCheck = false;
		}

	}
}