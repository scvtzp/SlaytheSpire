#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	~CMonster();
	// CObj을(를) 통해 상속됨

	void Monster_Action();
protected:
	bool m_bHitEffect = false;;
	float m_fHitEffectTime;
	float m_Frame;

	//사실상 transient 전용
	int m_iDamage = 0;
};

