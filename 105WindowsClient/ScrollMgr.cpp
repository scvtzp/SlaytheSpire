#include "stdafx.h"
#include "ScrollMgr.h"

IMPLEMENT_SINGLETON(CScrollMgr)
CScrollMgr::CScrollMgr()
{
	ZeroMemory(&m_vScroll, sizeof(D3DXVECTOR3)); 
}


CScrollMgr::~CScrollMgr()
{
}

float CScrollMgr::Get_Scroll(SCROLL eScrollID)
{
	switch (eScrollID)
	{
	case CScrollMgr::SCROLL_X:
		return m_vScroll.x; 
	case CScrollMgr::SCROLL_Y:
		return m_vScroll.y;
	default:
		break;
	}
	return 0.0f;
}

D3DXVECTOR3& CScrollMgr::Get_Scroll()
{
	return m_vScroll;
}

void CScrollMgr::Set_Scroll(const D3DXVECTOR3 & rPos)
{
	m_vScroll += rPos;
}
