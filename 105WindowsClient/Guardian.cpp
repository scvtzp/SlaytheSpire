#include "stdafx.h"
#include "Guardian.h"


CGuardian::CGuardian()
{
}


CGuardian::~CGuardian()
{
}

HRESULT CGuardian::Initialize()
{
	m_tStatus.iCost = 3;
	m_tStatus.iMaxHp = 200;
	m_tStatus.iRealMaxHp = 200;
	m_tStatus.iHp = m_tStatus.iMaxHp;
	m_tStatus.iPastHp = m_tStatus.iMaxHp;
	m_tStatus.iBlock = 0;
	m_tStatus.iAtt = 5;
	m_tStatus.iGold = 500;

	ActionID = Action::ACTION_END;

	m_tFrame = { 0, 160 };
	m_tInfo.vPos = { 950.f, 350.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vHitSize = { 200.f, 200.f, 0.f };

	m_iAttMove = 0;

	m_iTrans = m_tStatus.iMaxHp - 100;
	m_bTrans = false;
	m_bTransFrame = false;
	m_bHitEffect = false;
	m_fHitEffectTime = 0;
	m_iDeadA = 255;
	return S_OK;
}

int CGuardian::Update()
{
	if (m_iDeadA <= 0)
	{
		return OBJ_DEAD;
	}
	if (m_tStatus.iHp < 0)
		m_tStatus.iHp = 0;
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
		GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_Hp(m_tStatus.iReflect);
		m_bHitEffect = true;
	}

	MoveFrame(0.2f);

	Action_Shuffle();

	Update_Rect();

	return 0;
}

void CGuardian::LateUpdate()
{
}

void CGuardian::Render()
{
	if (m_tStatus.iHp <= 0)
	{
		m_iDeadA -= 3;
	}

	if (m_bTrans)
	{
		m_tStatus.iReflect = 3;
		Render_MultiTex(L"Monster_guardian", L"defensive", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);
		m_bTransFrame = false;
	}
	else if (m_iTrans >= m_tStatus.iHp || m_bTransFrame)
	{
		if (!m_bTransFrame)
		{
			m_tFrame = { 0, 80 };
		}
		Render_MultiTex(L"Monster_guardian", L"trans", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);
		m_bTransFrame = true;
		m_iTrans = m_tStatus.iHp - 100;
	}
	else
	{
		m_tStatus.iReflect = 0;
		Render_MultiTex(L"Monster_guardian", L"idle", int(m_tFrame.fFrameStart), m_tInfo.vPos.x, m_tInfo.vPos.y, m_iDeadA);
	}

	///////////////////////////////////////////////////////////////////
	D3DXMATRIX matScale, matTrans, matWorld;
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
		Render_SingleTex(L"buff1L", m_tInfo.vPos.x, m_tInfo.vPos.y-200);
	}
	else if (ActionID == Action::ShieldBuff)
	{
		Render_SingleTex(L"defendL", m_tInfo.vPos.x, m_tInfo.vPos.y - 200);
	}

	if (m_tStatus.iReflect != 0)
	{
		Render_SingleTex(L"bronzeScales", m_tInfo.vPos.x - 40, m_tInfo.vPos.y + 150, 0.5f, 0.5f);

		swprintf_s(m_szFPS, L"%d", m_tStatus.iReflect);

		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x-37, m_tInfo.vPos.y + 153, 0.f);
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
	Render_HpBar(m_tInfo.vPos.x, m_tInfo.vPos.y, ((float)m_tStatus.iHp / m_tStatus.iRealMaxHp));

}

void CGuardian::Release()
{
}

void CGuardian::Action_Shuffle()
{

	if (m_bTrans) //µðÆæ½º
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
				ActionID = Action::ShieldBuff;
				break;
			}
		}
	}
	else //±âº»
	{
		if (ActionID == Action::ACTION_END)
		{
			switch (rand() % 2)
			{
			case 0:
				ActionID = Action::Attack;
				break;
			case 1:
				ActionID = Action::PowerBuff;
				break;
			}
		}
	}
}

void CGuardian::MoveFrame(const float & fSpeed /*= 1*/)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * (GET_INSTANCE(CTimeMgr)->Get_DeltaTime() * fSpeed);

	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
	{
		m_tFrame.fFrameStart = 0.f;

		if (m_tFrame.fFrameEnd == 80)
		{
			m_tFrame = { 0, 160 };

			m_bTrans = true;
		}
	}
}