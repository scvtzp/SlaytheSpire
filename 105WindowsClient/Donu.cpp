#include "stdafx.h"
#include "Donu.h"


CDonu::CDonu()
{
}


CDonu::~CDonu()
{
	Release();
}

HRESULT CDonu::Initialize()
{
	m_tStatus.iMaxHp = 250;
	m_tStatus.iRealMaxHp = 250;

	m_tStatus.iHp = m_tStatus.iMaxHp;
	m_tStatus.iPastHp = m_tStatus.iMaxHp;
	m_tStatus.iBlock = 0;
	m_tStatus.iAtt = 10;
	m_tStatus.iAttXXX = 2;
	m_tStatus.iGold = 250;

	ActionID = Action::ACTION_END;

	m_tFrame = { 0, 59 };
	m_tInfo.vPos = { 950.f, 400.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vHitSize = { 200.f, 200.f, 0.f };
	m_bHitEffect = false;
	m_fHitEffectTime = 0;
	m_Frame = 0.4f;
	m_iAttMove = 0;
	m_iDeadA = 255;
	return S_OK;
}

int CDonu::Update()
{
	if (m_iDeadA <= 0)
		return OBJ_DEAD;

	if (m_tStatus.iPastHp != m_tStatus.iHp)
	{
		m_tStatus.iPastHp = m_tStatus.iHp;
		m_tFrame = { 0, 14 };
		m_bHitEffect = true;
	}
	if (m_tStatus.iHp < 0)
		m_tStatus.iHp = 0;

	MoveFrame(m_Frame);
	Action_Shuffle();
	Update_Rect();

	return 0;
}

void CDonu::LateUpdate()
{
}

void CDonu::Render()
{
	if (m_tStatus.iHp <= 0)
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
		Render_MultiTex(L"donu", L"Att", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);
	}
	else if (m_tFrame.fFrameEnd == 14)
	{
		m_Frame = 1.3f;
		Render_MultiTex(L"donu", L"Hit", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);
	}
	else
	{
		m_Frame = 0.6f;
		Render_MultiTex(L"donu", L"idle", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);
	}

	///////////////////////////////////////////////////////////////////
	TCHAR		m_szFPS[MIN_STR];

	D3DXMATRIX matTrans;

	///////////////////////////////////////////////////////////////////////
	if (ActionID == Action::Donu_Att)
	{
		Render_SingleTex(L"attack_intent_3", m_tInfo.vPos.x, m_tInfo.vPos.y - 100);
		swprintf_s(m_szFPS, L"%d", m_tStatus.iAtt);

		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + 3, m_tInfo.vPos.y - 97, 0.f);
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if (ActionID == Action::Donu_Buff)
	{
		Render_SingleTex(L"buff1L", m_tInfo.vPos.x, m_tInfo.vPos.y - 100);
	}
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


	Render_HpBar(m_tInfo.vPos.x, m_tInfo.vPos.y, ((float)m_tStatus.iHp / m_tStatus.iRealMaxHp));

}

void CDonu::Release()
{
}

void CDonu::Action_Shuffle()
{
	if (ActionID == Action::ACTION_END)
	{
			if (m_bDonuAct)
			{
				ActionID = Action::Donu_Buff;
				m_bDonuAct = false;
			}
			else
			{
				ActionID = Action::Donu_Att;
				m_bDonuAct = true;
			}
	}
}

void CDonu::MoveFrame(const float & fSpeed /*= 1*/)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * (GET_INSTANCE(CTimeMgr)->Get_DeltaTime() * fSpeed);

	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
	{
		m_tFrame.fFrameStart = 0.f;
		if (m_tFrame.fFrameEnd == 14)
		{
			m_tFrame.fFrameEnd = 59;
		}
		if (m_tFrame.fFrameEnd == 40)
		{
			m_iAttMove = 0;
			m_tFrame.fFrameEnd = 59;
		}
	}
}