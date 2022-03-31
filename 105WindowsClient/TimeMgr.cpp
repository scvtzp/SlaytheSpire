#include "stdafx.h"
#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTimeMgr)
CTimeMgr::CTimeMgr()
	: m_fDeltaTime(0.f)
{
	ZeroMemory(&m_OldTime, sizeof(LARGE_INTEGER)); 
	ZeroMemory(&m_CPUTick, sizeof(LARGE_INTEGER)); 
}


CTimeMgr::~CTimeMgr()
{
}

float CTimeMgr::Get_DeltaTime()
{
	return m_fDeltaTime;
}

void CTimeMgr::Initialize()
{
	QueryPerformanceCounter(&m_OldTime); 
	QueryPerformanceFrequency(&m_CPUTick); 
}

void CTimeMgr::UpdateTime()
{
	LARGE_INTEGER CurTime; 
	ZeroMemory(&CurTime, sizeof(CurTime)); 

	QueryPerformanceCounter(&CurTime); 

	QueryPerformanceFrequency(&m_CPUTick); 

	m_fDeltaTime = float(CurTime.QuadPart - m_OldTime.QuadPart) / m_CPUTick.QuadPart; 
	QueryPerformanceCounter(&m_OldTime);

}
