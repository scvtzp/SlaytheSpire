#include "stdafx.h"
#include "Hexa.h"


CHexa::CHexa()
{
}


CHexa::~CHexa()
{
	Release();
}

HRESULT CHexa::Initialize()
{
	m_tStatus.iMaxHp = 250;
	m_tStatus.iRealMaxHp = 250;
	m_tStatus.iHp = m_tStatus.iMaxHp;
	m_tStatus.iPastHp = m_tStatus.iMaxHp;
	m_tStatus.iBlock = 0;
	m_tStatus.iAtt = 15;
	m_tStatus.iAttXXX = 6;
	m_tStatus.iGold = 500;

	ActionID = Action::ACTION_END;

	m_tFrame = { 0, 0 };
	m_tInfo.vPos = { 950.f, 400.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vHitSize = { 300.f, 300.f, 0.f };
	m_bHitEffect = false;
	m_fHitEffectTime = 0;
	m_iAttMove = 0;
	m_iDeadA = 255;
	return S_OK;
}

int CHexa::Update()
{
	if (m_iDeadA <= 0)
		return OBJ_DEAD;
	if (m_tStatus.iHp < 0)
		m_tStatus.iHp = 0;

	if (m_tStatus.iPastHp != m_tStatus.iHp)
	{
		m_tStatus.iPastHp = m_tStatus.iHp;
		m_tFrame = { 0, 14 };
		m_bHitEffect = true;
	}

	Action_Shuffle();
	Update_Rect();

	return 0;
}

void CHexa::LateUpdate()
{
	m_iCount++;
}

void CHexa::Render()
{
	if (m_tStatus.iHp <= 0)
	{
		m_iDeadA -= 3;
	}

	Render_SingleTex(L"shadow", m_tInfo.vPos.x, m_tInfo.vPos.y, 1.0f, 1.0f, m_iDeadA);
	Render_SingleTexRot(L"plasma3", m_tInfo.vPos.x, m_tInfo.vPos.y, Rot1, 1.0f, 1.0f, m_iDeadA);
	Render_SingleTexRot(L"plasma2", m_tInfo.vPos.x, m_tInfo.vPos.y, Rot, 1.0f, 1.0f, m_iDeadA);
	Render_SingleTexRot(L"plasma1", m_tInfo.vPos.x, m_tInfo.vPos.y, Rot1, 1.0f, 1.0f, m_iDeadA);
	Render_SingleTex(L"core", m_tInfo.vPos.x, m_tInfo.vPos.y, 1.0f, 1.0f, m_iDeadA);

	Rot += 0.005f;
	Rot1 -= 0.005f;
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
	else if (ActionID == Action::ShieldBuff)
	{
		Render_SingleTex(L"buff1L", m_tInfo.vPos.x, m_tInfo.vPos.y - 100);
	}
	else if (ActionID == Action::AttackXXX)
	{
		Render_SingleTex(L"attack_intent_3", m_tInfo.vPos.x, m_tInfo.vPos.y - 100);
		swprintf_s(m_szFPS, L"%d x %d", m_tStatus.iAtt, m_tStatus.iAttXXX);

		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + 3, m_tInfo.vPos.y - 97, 0.f);
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	////////////////////////////////////
	switch (m_iCount)
	{
	case 6:
		Render_SingleTex(L"fire1", m_tInfo.vPos.x - 180, m_tInfo.vPos.y - 150, 1.f, 1.f, 255, 175, 135, 7);
		Render_SingleTex(L"fire2", m_tInfo.vPos.x - 180, m_tInfo.vPos.y - 150, 0.75f, 0.75f, 255, 247, 239, 0);
		Render_SingleTex(L"fire1", m_tInfo.vPos.x - 180, m_tInfo.vPos.y - 150, 0.5f, 0.5f, 255, 255, 243, 156);
	case 5:
		Render_SingleTex(L"fire1", m_tInfo.vPos.x - 250, m_tInfo.vPos.y, 1.f, 1.f, 255, 175, 135, 7);
		Render_SingleTex(L"fire2", m_tInfo.vPos.x - 250, m_tInfo.vPos.y, 0.75f, 0.75f, 255, 247, 239, 0);
		Render_SingleTex(L"fire1", m_tInfo.vPos.x - 250, m_tInfo.vPos.y, 0.5f, 0.5f, 255, 255, 243, 156);
	case 4:
		Render_SingleTex(L"fire1", m_tInfo.vPos.x - 180, m_tInfo.vPos.y + 150, 1.f, 1.f, 255, 175, 135, 7);
		Render_SingleTex(L"fire2", m_tInfo.vPos.x - 180, m_tInfo.vPos.y + 150, 0.75f, 0.75f, 255, 247, 239, 0);
		Render_SingleTex(L"fire1", m_tInfo.vPos.x - 180, m_tInfo.vPos.y + 150, 0.5f, 0.5f, 255, 255, 243, 156);
	case 3:
		Render_SingleTex(L"fire1", m_tInfo.vPos.x + 180, m_tInfo.vPos.y + 150, 1.f, 1.f, 255, 175, 135, 7);
		Render_SingleTex(L"fire2", m_tInfo.vPos.x + 180, m_tInfo.vPos.y + 150, 0.75f, 0.75f, 255, 247, 239, 0);
		Render_SingleTex(L"fire1", m_tInfo.vPos.x + 180, m_tInfo.vPos.y + 150, 0.5f, 0.5f, 255, 255, 243, 156);
	case 2:
		Render_SingleTex(L"fire1", m_tInfo.vPos.x + 250, m_tInfo.vPos.y, 1.f, 1.f, 255, 175, 135, 7);
		Render_SingleTex(L"fire2", m_tInfo.vPos.x + 250, m_tInfo.vPos.y, 0.75f, 0.75f, 255, 247, 239, 0);
		Render_SingleTex(L"fire1", m_tInfo.vPos.x + 250, m_tInfo.vPos.y, 0.5f, 0.5f, 255, 255, 243, 156);
	case 1:
		Render_SingleTex(L"fire1", m_tInfo.vPos.x + 180, m_tInfo.vPos.y - 150, 1.f, 1.f, 255, 175, 135, 7);
		Render_SingleTex(L"fire2", m_tInfo.vPos.x + 180, m_tInfo.vPos.y - 150, 0.75f, 0.75f, 255, 247, 239, 0);
		Render_SingleTex(L"fire1", m_tInfo.vPos.x + 180, m_tInfo.vPos.y - 150, 0.5f, 0.5f, 255, 255, 243, 156);
		break;
	default:
		break;
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

	Render_HpBar(m_tInfo.vPos.x, m_tInfo.vPos.y, ((float)m_tStatus.iHp / (float)m_tStatus.iRealMaxHp));
}

void CHexa::Release()
{
}

void CHexa::Action_Shuffle()
{
	if (ActionID == Action::ACTION_END)
	{
		switch (rand() % 2)
		{
		case 0:
			ActionID = Action::Attack;
			break;
		case 1:
			ActionID = Action::ShieldBuff;
			break;
		}

		if (m_iCount >= 6)
		{
			ActionID = Action::AttackXXX;
			m_iCount = 0;
		}
	}
}