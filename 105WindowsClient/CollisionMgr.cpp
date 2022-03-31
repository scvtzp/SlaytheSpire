#include "stdafx.h"
#include "CollisionMgr.h"

#include "Obj.h"
#include "CardID.h"
#include "Player.h"


CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{

				;

			}
		}
	}
}

bool CCollisionMgr::Collision_Card_Mouse(RECT rect)
{
	RECT rc = {};
	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	pt.y -= GET_INSTANCE(CObjMgr)->Get_ScrollY();

	if (rect.left <= pt.x &&
		rect.right >= pt.x &&
		rect.bottom >= pt.y &&
		rect.top <= pt.y)
	{
		return true;
	}
	return false;
}

bool CCollisionMgr::Collision_Monster_Mouse(CARDINFO tCardInfo, list<CObj*>& _Src, list<CObj*>& _Player)
{
	RECT rc = {};
	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	for (auto& Player : _Player)
	{
		for (auto& Src : _Src)
		{
			if (Src->Get_Rect().left <= pt.x &&
				Src->Get_Rect().right >= pt.x &&
				Src->Get_Rect().bottom >= pt.y &&
				Src->Get_Rect().top <= pt.y)
			{
				Src->Set_Hp(tCardInfo.iDamage);
				/////원래 여기아님
				Player->Set_Block(tCardInfo.iBlock);
				Player->Set_Cost(tCardInfo.iCost);
				dynamic_cast<CPlayer*>(Player)->Set_AttMove();

				return true;
			}
		}
	}
	return false;
}

void CCollisionMgr::Set_Player_Block(list<CObj*>& _Player, int a)
{
	for (auto& Player : _Player)
	{
		Player->Set_Block(a);
	}
}

void CCollisionMgr::Whirlwind(list<CObj*>& _Monster, int Att, int Mana)
{
	for (auto& Monster : _Monster)
	{
		Monster->Set_Hp(Att*Mana);
	}

}


void CCollisionMgr::Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* _Dst, CObj* _Src)
{
	return false;
}