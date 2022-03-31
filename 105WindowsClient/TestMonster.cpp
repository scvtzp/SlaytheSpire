#include "stdafx.h"
#include "TestMonster.h"


CTestMonster::CTestMonster()
{
}


CTestMonster::~CTestMonster()
{
}

HRESULT CTestMonster::Initialize()
{
	m_tStatus.iCost = 3;
	m_tStatus.iMaxHp = 10;
	m_tStatus.iRealMaxHp = m_tStatus.iMaxHp;
	m_tStatus.iHp = m_tStatus.iMaxHp;
	m_tStatus.iPastHp = m_tStatus.iMaxHp;
	m_tStatus.iBlock = 0;
	m_tStatus.iAtt = 5;
	m_tStatus.iGold = rand() % 100;

	ActionID = Action::ACTION_END;

	m_tFrame = { 0, 131 };
	m_tInfo.vPos = { 950.f, 400.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vHitSize = { 200.f, 300.f, 0.f };

	m_bHitEffect = false;
	m_fHitEffectTime = 0;

	m_iAttMove = 0;
	m_iDeadA = 255;
	return S_OK;
}

int CTestMonster::Update()
{
	if (m_iDeadA <= 0)
	{
		return OBJ_DEAD;
	}

	switch (m_iAttMove)
	{
	case 1:
		m_tInfo.vPos.x -= 7;
		if (m_tInfo.vPos.x <= 850)
		{
			m_iAttMove = 2;
		}
		break;

	case 2:
		m_tInfo.vPos.x += 7;
		if (m_tInfo.vPos.x >= 950)
		{
			m_iAttMove = 0;
			m_tInfo.vPos.x = 950.f;
		}
		break;

	default:
		break;
	}
	if (m_tStatus.iPastHp != m_tStatus.iHp)
	{
		m_tStatus.iPastHp = m_tStatus.iHp;
		m_bHitEffect = true;
	}

	HP_Update();

	MoveFrame(0.2f);

	Action_Shuffle();

	Update_Rect();
	Buff_Update();
	return 0;
}

void CTestMonster::LateUpdate()
{

}

void CTestMonster::Render()
{
	D3DXMATRIX matScale, matTrans, matWorld;

	if (m_tStatus.iHp <= 0)
	{
		m_iDeadA -= 3;
	}

	Render_MultiTex(L"Monster", L"idle", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);

	///////////////////////////////////////////////////////////////////
	TCHAR		m_szFPS[MIN_STR];

	///////////////////////////////////////////////////////////////////////
	if (ActionID == Action::Attack)
	{
		Render_SingleTex(L"attack_intent_3", m_tInfo.vPos.x, m_tInfo.vPos.y - 100);
		swprintf_s(m_szFPS, L"%d", m_tStatus.iAtt);

		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + 3, m_tInfo.vPos.y - 97, 0.f);
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if (ActionID == Action::PowerBuff)
	{
		Render_SingleTex(L"buff1L", m_tInfo.vPos.x, m_tInfo.vPos.y - 100);
	}

	///////공버프 표시
	if (m_tStatus.iAttBuff > 0)
	{
		Render_SingleTex(L"attack_intent_4", m_tInfo.vPos.x - 80, m_tInfo.vPos.y + 160, 0.5f, 0.5f);
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

void CTestMonster::Release()
{
}

void CTestMonster::Action_Shuffle()
{
	if (ActionID == Action::ACTION_END)
	{
		switch (rand()%2)
		{
		case 0:
			ActionID = Action::Attack;
			break;
		case 1:
			ActionID = Action::PowerBuff;
			break;
		}
	}
	//ActionID
}

void CTestMonster::MoveFrame(const float & fSpeed /*= 1*/)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * (GET_INSTANCE(CTimeMgr)->Get_DeltaTime() * fSpeed);

	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
		m_tFrame.fFrameStart = 0.f;
}

// 숙제. 회전 공식 증명하기. 