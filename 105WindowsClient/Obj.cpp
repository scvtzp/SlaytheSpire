#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
{
}


CObj::~CObj()
{
}

void CObj::Set_Hp(int _iHp)
{
	if (_iHp > m_tStatus.iBlock)
	{
		m_tStatus.iHp -= _iHp - m_tStatus.iBlock;
	}
	m_tStatus.iBlock -= _iHp;
	if (m_tStatus.iBlock < 0)
	{
		m_tStatus.iBlock = 0;
	}
}

void CObj::Set_Pos(float x, float y)
{
	m_tInfo.vPos = { x,y,0.f };
}

void CObj::Set_PosPlus(float x, float y)
{
	m_tInfo.vPos = { m_tInfo.vPos.x + x,m_tInfo.vPos.y + y,0.f };
}

void CObj::Update_Rect()
{
	m_tRect.left = long(m_tInfo.vPos.x - (m_tInfo.vHitSize.x / 2));
	m_tRect.right = long(m_tInfo.vPos.x + (m_tInfo.vHitSize.x / 2));
	m_tRect.top= long(m_tInfo.vPos.y - (m_tInfo.vHitSize.y / 2));
	m_tRect.bottom = long(m_tInfo.vPos.y + (m_tInfo.vHitSize.y / 2));
}

void CObj::Render_SingleTex(const wstring & wstrObjectKey, float x, float y, float _X, float _Y, int A, int R, int G, int B)
{
	D3DXMATRIX matScale, matTrans, matWorld;

	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(wstrObjectKey);
	assert(!(nullptr == pTexInfo));

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x *_X, m_tInfo.vSize.y*_Y, 0.f);
	D3DXMatrixTranslation(&matTrans, x, y, 0.f);

	matWorld = matScale * matTrans;

	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
	GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(A, R, G, B));
}

void CObj::Render_SingleTexRot(const wstring & wstrObjectKey, float x, float y, float Rot, float _X , float _Y , int A , int R , int G , int B)
{
	D3DXMATRIX matScale, matTrans, matRotationZ, matWorld;

	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(wstrObjectKey);
	assert(!(nullptr == pTexInfo));

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x *_X, m_tInfo.vSize.y*_Y, 0.f);
	D3DXMatrixTranslation(&matTrans, x, y, 0.f);
	D3DXMatrixRotationZ(&matRotationZ, Rot);


	matWorld = matScale * matRotationZ * matTrans;

	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
	GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(A, R, G, B));
}


void CObj::Render_MultiTex(const wstring & wstrObjectKey, const wstring & wstrStateKey, const int & rImageIndex, float x, float y, int Alpha, float _X,  float _Y)
{
	D3DXMATRIX matScale, matTrans, matWorld;

	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(wstrObjectKey, wstrStateKey, rImageIndex);
	assert(!(nullptr == pTexInfo));

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x *_X, m_tInfo.vSize.y*_Y, 0.f);
	D3DXMatrixTranslation(&matTrans, x, y, 0.f);

	matWorld = matScale * matTrans;

	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
	GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(Alpha, 255, 255, 255));
}

void CObj::Render_HpBar(float x, float y, float _Y)
{
	Render_SingleTex(L"PlayerHP", x, y + (m_tInfo.vHitSize.y/2), 1.0f, 1.0f, 255, 0, 0, 0);

	float fY = 200*_Y/2;
	D3DXMATRIX matScale, matTrans, matWorld;

	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"PlayerHP");
	assert(!(nullptr == pTexInfo));

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x*_Y, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, x-100 + fY, y+(m_tInfo.vHitSize.y/2), 0.f);

	matWorld = matScale * matTrans;

	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
	GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 0, 0));

	/////////////////

	TCHAR		m_szFPS[MIN_STR];

	swprintf_s(m_szFPS, L"%d / %d", m_tStatus.iHp, m_tStatus.iRealMaxHp);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x-20, y + (m_tInfo.vHitSize.y / 2)-10, 0.f);
	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
	GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));


	if (m_tStatus.iBlock > 0)
	{
		Render_SingleTex(L"block", x-100, y + (m_tInfo.vHitSize.y / 2), 1.0f, 1.0f, 255, 255, 255, 255);
		swprintf_s(m_szFPS, L"%d", m_tStatus.iBlock);

		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - 110, y + (m_tInfo.vHitSize.y / 2) - 10, 0.f);
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}


/////////////////////KeyMgr
bool CObj::Key_Pressing(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000)
		return true;
	return false;
}

bool CObj::Key_Down(int _key)
{
	if (!m_bKeyState[_key] && (GetAsyncKeyState(_key) & 0x8000))
	{
		m_bKeyState[_key] = !m_bKeyState[_key];
		return true;
	}
	return false;
}

bool CObj::Key_Up(int _key)
{
	if (m_bKeyState[_key] && !(GetAsyncKeyState(_key) & 0x8000))
	{
		m_bKeyState[_key] = !m_bKeyState[_key];
		return true;
	}
	return false;
}

void CObj::Key_Update()
{
	// key 상태를 복원하는 함수이다.
	// 복원하지 않을 경우 key_down과 key_up은 단 한번만 수행되기 때문이다.
	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
		if (!m_bKeyState[i] && (GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}
}

void CObj::HP_Update()
{
	if (m_tStatus.iHp < 0)
		m_tStatus.iHp = 0;
}

void CObj::Buff_Update()
{
	if (m_tStatus.Buff != BUFF::BUFF_END)
	{
		for (auto itor : m_tStatus.VecBuff)
		{
			if (itor == m_tStatus.Buff)
			{
				return;
			}
		}

		m_tStatus.VecBuff.emplace_back(m_tStatus.Buff);
		m_tStatus.Buff = BUFF::BUFF_END;
	}

	if (m_tStatus.DeBuff != DEBUFF::DEBUFF_END)
	{
		for (auto itor : m_tStatus.VecDebuff)
		{
			if (itor == m_tStatus.DeBuff)
			{
				return;
			}
		}

		m_tStatus.VecDebuff.emplace_back(m_tStatus.DeBuff);
		m_tStatus.DeBuff = DEBUFF::DEBUFF_END;
	}  
}

void CObj::Buff_Render()
{
	int i = -1;
	for (auto itor : m_tStatus.VecBuff)
	{
		switch (itor)
		{
		case BUFF::Buff_Barricade:
			Render_SingleTex(L"endless", m_tInfo.vPos.x+(i*64), m_tInfo.vPos.y + (m_tInfo.vHitSize.y/2) + 80);
			break;
		default:
			break;
		}
		if (itor != BUFF::BUFF_END)
			i++;
	}

	i = -3;
	for (auto itor : m_tStatus.VecDebuff)
	{
		switch (itor)
		{
		case DEBUFF::Debuff_Vulnerable:
			Render_SingleTex(L"tough_enemies", m_tInfo.vPos.x + (i * 64), m_tInfo.vPos.y + m_tInfo.vHitSize.y + 80);
			break;
		default:
			break;
		}
		if (itor != BUFF::BUFF_END)
			i++;
	}
}

bool CObj::Check_Buff(BUFF::ID ID)
{
	for (auto itor : m_tStatus.VecBuff)
	{
		if (itor == ID)
			return true;
	}
	return false;
}

bool CObj::Check_DeBuff(DEBUFF::ID ID)
{
	for (auto itor : m_tStatus.VecDebuff)
	{
		if (itor == ID)
			return true;
	}
	return false;
}
