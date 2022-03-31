#include "stdafx.h"
#include "FrameMgr.h"


CFrameMgr::CFrameMgr()
	:m_fDeltaTime(0.f)
	,m_szFPS(L"")
	,m_fFrameTime(0.f)
	,m_fSPF(0.f)
	,m_iFPS(0)
{
	ZeroMemory(&m_OldTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CPUTick, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CurTime, sizeof(LARGE_INTEGER));
}


CFrameMgr::~CFrameMgr()
{
}

void CFrameMgr::Initialize(float fFPS)
{
	// 1초를 넣어준 프레임 수 만큼 쪼개서 돌릴때 쓸것. 
	m_fSPF = 1 / fFPS;
	QueryPerformanceCounter(&m_CurTime); 
	QueryPerformanceCounter(&m_OldTime);
	QueryPerformanceFrequency(&m_CPUTick); 
}

bool CFrameMgr::LockFrame()
{
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceFrequency(&m_CPUTick);
	m_fDeltaTime += float(m_CurTime.QuadPart - m_OldTime.QuadPart) / m_CPUTick.QuadPart; 
	m_OldTime = m_CurTime; 

	if (m_fSPF <= m_fDeltaTime)
	{
		++m_iFPS; 
		m_fDeltaTime = 0.f; 
		return true;
	}
	return false;
}

void CFrameMgr::RenderFPS()
{
	m_fFrameTime += GET_INSTANCE(CTimeMgr)->Get_DeltaTime(); 
	if (1.f <= m_fFrameTime)
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		m_iFPS = 0; 
		m_fFrameTime = 0.f; 
	}

	D3DXMATRIX matTrans; 
	D3DXMatrixTranslation(&matTrans, 100.f, 100.f, 0.f); 
	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans); 
	GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 0, 0)); 

}
