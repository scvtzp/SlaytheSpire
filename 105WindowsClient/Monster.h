#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	~CMonster();
	// CObj��(��) ���� ��ӵ�

	void Monster_Action();
protected:
	bool m_bHitEffect = false;;
	float m_fHitEffectTime;
	float m_Frame;

	//��ǻ� transient ����
	int m_iDamage = 0;
};

