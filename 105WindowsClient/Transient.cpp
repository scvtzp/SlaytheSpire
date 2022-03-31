#include "stdafx.h"
#include "Transient.h"


CTransient::CTransient()
{
}


CTransient::~CTransient()
{
}

HRESULT CTransient::Initialize()
{

	m_tStatus.iMaxHp = 999;
	m_tStatus.iRealMaxHp = m_tStatus.iMaxHp;
	m_tStatus.iHp = m_tStatus.iMaxHp;
	m_tStatus.iPastHp = m_tStatus.iMaxHp;
	m_tStatus.iBlock = 0;
	m_tStatus.iAtt = 20;
	m_tStatus.iGold = rand() % 400;

	ActionID = Action::ACTION_END;

	m_tFrame = { 0, 320 };
	m_tInfo.vPos = { 950.f, 400.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vHitSize = { 200.f, 200.f, 0.f };
	m_bHitEffect = false;
	m_fHitEffectTime = 0;
	m_Frame = 0.2f;
	m_iDamage = 0;
	m_iAttMove = 0;
	m_iDeadA = 255;
	return S_OK;
}

int CTransient::Update()
{
	if (m_iDeadA <= 0)
	{
		return OBJ_DEAD;
	}

	if (m_tStatus.iPastHp != m_tStatus.iHp)
	{
		m_iDamage += m_tStatus.iPastHp - m_tStatus.iHp;

		m_tStatus.iPastHp = m_tStatus.iHp;
		m_tFrame = { 0, 14 };
		m_bHitEffect = true;
	}
	MoveFrame(m_Frame);

	Action_Shuffle();

	Update_Rect();

	return 0;
}

void CTransient::LateUpdate()
{
	m_iCount--;
	m_iDamage = 0;
}

void CTransient::Render()
{
	if (m_iCount <= 0)
	{
		m_iDeadA -= 3;
	}
	if (m_iAttMove != 0)
	{
		if (m_iAttMove == 1)
		{
			m_Frame = 0.5f;
			m_tFrame = { 0, 40 };
			m_iAttMove = 2;
		}
		Render_MultiTex(L"transient", L"Att", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);
	}
	else if (m_tFrame.fFrameEnd == 14)
	{
		m_Frame = 1.3f;
		Render_MultiTex(L"transient", L"Hit", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);
	}
	else
	{
		m_Frame = 0.2f;
		Render_MultiTex(L"transient", L"idle", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);
	}

	///////////////////////////////////////////////////////////////////
	TCHAR		m_szFPS[MIN_STR];

	D3DXMATRIX matTrans;

	///////////////////////////////////////////////////////////////////////
	if (ActionID == Action::Attack)
	{
		Render_SingleTex(L"attack_intent_3", m_tInfo.vPos.x, m_tInfo.vPos.y - 100);
		swprintf_s(m_szFPS, L"%d", m_tStatus.iAtt- m_iDamage);

		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + 3, m_tInfo.vPos.y - 97, 0.f);
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	////////////////////»ý¸í
	Render_SingleTex(L"shiny", m_tInfo.vPos.x - 40, m_tInfo.vPos.y + 150, 0.5f, 0.5f);
	swprintf_s(m_szFPS, L"%d", m_iCount);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - 37, m_tInfo.vPos.y + 153, 0.f);
	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
	GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	////////////////////////////////////

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

void CTransient::Release()
{
}

void CTransient::Action_Shuffle()
{
	if (ActionID == Action::ACTION_END)
	{
			m_tStatus.iAtt += 10;
			ActionID = Action::Attack;
	}
	//ActionID
}

void CTransient::MoveFrame(const float & fSpeed /*= 1*/)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * (GET_INSTANCE(CTimeMgr)->Get_DeltaTime() * fSpeed);

	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
	{
		m_tFrame.fFrameStart = 0.f;
		if (m_tFrame.fFrameEnd == 14)
		{
			m_tFrame.fFrameEnd = 320;
		}
		if (m_tFrame.fFrameEnd == 40)
		{
			m_iAttMove = 0;
			m_tFrame.fFrameEnd = 320;
		}
	}
}