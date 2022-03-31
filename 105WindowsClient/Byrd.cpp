#include "stdafx.h"
#include "Byrd.h"


CByrd::CByrd()
{
}


CByrd::~CByrd()
{
}

HRESULT CByrd::Initialize()
{

	m_tStatus.iMaxHp = rand()%35;
	if (m_tStatus.iMaxHp <= 25)
		m_tStatus.iMaxHp = 25;
	m_tStatus.iRealMaxHp = m_tStatus.iMaxHp;

	m_tStatus.iHp = m_tStatus.iMaxHp;
	m_tStatus.iPastHp = m_tStatus.iMaxHp;
	m_tStatus.iBlock = 0;
	m_tStatus.iAtt = 1;
	m_tStatus.iAttXXX = 5;
	m_tStatus.iPastAtt = m_tStatus.iAtt;
	ActionID = Action::ACTION_END;
	m_tStatus.iGold = rand() % 250;

	//m_tFrame = { 0, 100 };
	m_tFrame = { 0, 40 };
	m_tInfo.vPos = { 950.f, 200.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vHitSize = { 200.f, 200.f, 0.f };
	m_bHitEffect = false;
	m_fHitEffectTime = 0.f;

	m_iTransCount = 0;
	m_iAttMove = 0;
	m_iDeadA = 255;
	return S_OK;
}

int CByrd::Update()
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
		if (!m_bTrans)
		{
			m_tStatus.iHp += (m_tStatus.iPastHp - m_tStatus.iHp) / 2;
		}
		m_tStatus.iPastHp = m_tStatus.iHp;

		m_bHitEffect = true;
		m_iTransCount++;
	}
	MoveFrame(0.2f);

	Action_Shuffle();

	Update_Rect();

	return 0;
}

void CByrd::LateUpdate()
{
	m_iTransCount = 0;
}

void CByrd::Render()
{
	if (m_tStatus.iHp <= 0)
	{
		m_iDeadA -= 3;
	}

	if (m_bTrans)
	{
		m_tFrame = { 0, 320 };
		m_tStatus.iReflect = 3;
		Render_MultiTex(L"byrd", L"ground", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);
		m_bTransFrame = false;
	}
	else if (m_iTransCount >= 3 || m_bTransFrame)
	{
		m_bTransFrame = true;
		m_iTransCount = 0;

		m_tInfo.vPos.y += 4.f;
		Render_MultiTex(L"byrd", L"flying", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);

		if (m_tInfo.vPos.y >= 350)
		{
			m_bTrans = true;
			ActionID = Action::Stun;
		}
	}
	else
	{
		m_tStatus.iReflect = 0;
		Render_MultiTex(L"byrd", L"flying", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);
	}

	///////////////////////////////////////////////////////////////////
	TCHAR		m_szFPS[MIN_STR];
	D3DXMATRIX matTrans;
	///////////////////////////////////////////////////////////////////////
	if (ActionID == Action::PowerBuff)
	{
		Render_SingleTex(L"buff1L", m_tInfo.vPos.x, m_tInfo.vPos.y - 100);
	}
	else if (ActionID == Action::Stun)
	{
		Render_SingleTex(L"stunL", m_tInfo.vPos.x, m_tInfo.vPos.y - 100);
	}
	else if (ActionID == Action::Attack)
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

		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x+3, m_tInfo.vPos.y -97, 0.f);
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	}

	///////공버프 표시
	if (m_tStatus.iAttBuff > 0)
	{
		Render_SingleTex(L"attack_intent_4", m_tInfo.vPos.x - 80, m_tInfo.vPos.y + 150, 0.5f, 0.5f);

		swprintf_s(m_szFPS, L"%d", m_tStatus.iAttBuff);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - 77, m_tInfo.vPos.y + 153, 0.f);
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
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

void CByrd::Release()
{
}

void CByrd::Action_Shuffle()
{
	if (ActionID == Action::ACTION_END)
	{
		switch (rand() % 3)
		{
		case 0:
			ActionID = Action::PowerBuff;
			break;
		case 1:
			ActionID = Action::Attack;
			m_tStatus.iAtt += 10;
			break;
		case 2:
			ActionID = Action::AttackXXX;
			m_tStatus.iAtt = m_tStatus.iPastAtt;
			break;
		}
	}
	//ActionID
}

void CByrd::MoveFrame(const float & fSpeed /*= 1*/)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * (GET_INSTANCE(CTimeMgr)->Get_DeltaTime() * fSpeed);

	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
		m_tFrame.fFrameStart = 0.f;
}

// 숙제. 회전 공식 증명하기. 