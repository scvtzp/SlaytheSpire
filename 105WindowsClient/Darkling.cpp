#include "stdafx.h"
#include "Darkling.h"


CDarkling::CDarkling()
{
}


CDarkling::~CDarkling()
{
}

HRESULT CDarkling::Initialize()
{

	m_tStatus.iMaxHp = rand() % 60;
	if (m_tStatus.iMaxHp <= 45)
		m_tStatus.iMaxHp = 45 + rand()%10;
	m_tStatus.iRealMaxHp = m_tStatus.iMaxHp;

	m_tStatus.iHp = m_tStatus.iMaxHp;
	m_tStatus.iPastHp = m_tStatus.iMaxHp;
	m_tStatus.iBlock = 0;
	m_tStatus.iAtt = 8;

	m_tStatus.iAttXXX = 2;
	m_tStatus.iGold = rand() % 300;

	ActionID = Action::ACTION_END;

	m_tFrame = { 0, 102 };
	m_tInfo.vPos = { 950.f, 400.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vHitSize = { 200.f, 200.f, 0.f };
	m_bHitEffect = false;
	m_fHitEffectTime = 0;
	m_Frame = 0.2f;
	m_iAttMove = 0;
	m_iDeadA = 255;
	return S_OK;
}

int CDarkling::Update()
{
	if (m_iDeadA <= 0)
		return OBJ_DEAD;
	if (m_tStatus.iHp <= 0)
		m_tStatus.iHp = 0;
	if (m_tStatus.iPastHp != m_tStatus.iHp)
	{
		m_tStatus.iPastHp = m_tStatus.iHp;
		m_tFrame = { 0, 14 };
		m_bHitEffect = true;
	}
	
	bool Dead = true;
	for (auto& Monster : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_MONSTER))
	{
		if (dynamic_cast<CMonster*>(Monster)->Get_HP() > 0)
		{
			Dead = false;
		}
	}

	if (Dead)
	{
		m_bdead = true;
	}

	MoveFrame(m_Frame);
	Action_Shuffle();
	Update_Rect();
	return 0;
}

void CDarkling::LateUpdate()
{

	if (m_iDeadCount >= 2)
	{
		for (auto& Monster : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_MONSTER))
		{
			if (dynamic_cast<CMonster*>(Monster)->Get_HP() > 0)
			{
				m_tStatus.iHp = m_tStatus.iMaxHp;
				m_iDeadCount = 0;
			}
		}

		if(m_tStatus.iHp <= 0)
			m_bdead = true;
	}

	if (m_tStatus.iHp <= 0)
	{
		ActionID = Action::Stun;
		m_iDeadCount++;
	}
}

void CDarkling::Render()
{
	if (m_tStatus.iHp <= 0 && m_bdead)
		m_iDeadA -= 3;


	if (m_tFrame.fFrameEnd == 14)
	{
		m_Frame = 1.3f;
		Render_MultiTex(L"darkling", L"Hit", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);
	}
	else if (m_iAttMove != 0)
	{
		if (m_iAttMove == 1)
		{
			m_Frame = 0.5f;
			m_tFrame = { 0, 40 };
			m_iAttMove = 2;
		}
		if (int(m_tFrame.fFrameStart) >= 40)
			Render_MultiTex(L"darkling", L"Att", 39, m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);
		else
			Render_MultiTex(L"darkling", L"Att", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);
	}
	else
	{
		m_Frame = 0.2f;
		Render_MultiTex(L"darkling", L"idle", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);
	}
	///////////////////////////////////////////////////////////////////
	TCHAR		m_szFPS[MIN_STR];
	D3DXMATRIX matTrans;

	///////////////////////////////////////////////////////////////////////
	if (ActionID == Action::Attack)
	{
		Render_SingleTex(L"attack_intent_3", m_tInfo.vPos.x, m_tInfo.vPos.y - 100);
		swprintf_s(m_szFPS, L"%d", m_tStatus.iAtt);

		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + 3, m_tInfo.vPos.y - 97, 0.f);
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if (ActionID == Action::AttackXXX)
	{
		Render_SingleTex(L"attack_intent_3", m_tInfo.vPos.x, m_tInfo.vPos.y - 100);
		swprintf_s(m_szFPS, L"%d x %d", m_tStatus.iAtt, m_tStatus.iAttXXX);

		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + 3, m_tInfo.vPos.y - 97, 0.f);
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if (ActionID == Action::ShieldBuff)
	{
		Render_SingleTex(L"defendL", m_tInfo.vPos.x, m_tInfo.vPos.y - 100);
	}
	else if (ActionID == Action::Stun)
	{
		Render_SingleTex(L"stunL", m_tInfo.vPos.x, m_tInfo.vPos.y - 100);
	}


	if (m_bHitEffect)
	{
		m_fHitEffectTime += 100.f * (GET_INSTANCE(CTimeMgr)->Get_DeltaTime() * 2.3f);
		if (m_fHitEffectTime >= 100)
		{
			m_fHitEffectTime = 0;
			m_bHitEffect = false;
		}
		D3DXMATRIX matScale, matTrans, matRotationZ, matWorld;

		const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"slash");
		assert(!(nullptr == pTexInfo));

		float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
		D3DXMatrixRotationZ(&matRotationZ, 90.f);


		matWorld = matScale * matRotationZ * matTrans;

		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
		GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(155, 237, 162, 0));
	}

	HP_Update();
	Render_HpBar(m_tInfo.vPos.x, m_tInfo.vPos.y, ((float)m_tStatus.iHp / m_tStatus.iRealMaxHp));
}

void CDarkling::Release()
{
}

void CDarkling::Action_Shuffle()
{
	if (ActionID == Action::ACTION_END)
	{
		switch (rand() % 3)
		{
		case 0:
			ActionID = Action::Attack;
			break;
		case 1:
			ActionID = Action::ShieldBuff;
			break;
		case 2:
			ActionID = Action::AttackXXX;
			break;
		}
	}
	//ActionID
}

void CDarkling::MoveFrame(const float & fSpeed /*= 1*/)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * (GET_INSTANCE(CTimeMgr)->Get_DeltaTime() * fSpeed);

	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
	{
		m_tFrame.fFrameStart = 0.f;
		if (m_tFrame.fFrameEnd == 14)
		{
			m_iAttMove = 0;
			m_tFrame.fFrameEnd = 102;
		}
		else if (m_tFrame.fFrameEnd == 40)
		{
			m_iAttMove = 0;
			m_tFrame.fFrameEnd = 102;
		}
	}
}