#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}

void CMonster::Monster_Action()
{
	if (this == nullptr)
	{
		return;
	}

	if (ActionID == Action::Attack)
	{
		GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_Hp(m_tStatus.iAtt - m_iDamage);
		m_iAttMove = 1;
	}
	else if (ActionID == Action::PowerBuff)
	{
		m_tStatus.iAtt++;
		m_tStatus.iPastAtt = m_tStatus.iAtt;
		m_tStatus.iAttBuff++;
	}

	else if (ActionID == Action::ShieldBuff)
	{
		m_tStatus.iBlock += 10;
	}

	else if (ActionID == Action::Run)
	{
		;
	}
	else if (ActionID == Action::looter_Attack)
	{
		int gold=rand()%100;

		if (GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Get_Gold() < gold)
		{
			gold = GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Get_Gold();
		}
		GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_Gold(gold);

		m_tStatus.iGold += gold;

		m_iAttMove = 1;
	}
	else if (ActionID == Action::Stun)
	{
		;
	}
	else if (ActionID == Action::AttackXXX)
	{
		for (int i = 0; i < m_tStatus.iAttXXX; i++)
		{
			GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_Hp(m_tStatus.iAtt);
		}
		m_iAttMove = 1;
	}
	else if (ActionID == Action::Donu_Att)
	{
		for (int i = 0; i < m_tStatus.iAttXXX; i++)
		{
			GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_Hp(m_tStatus.iAtt);
		}
		m_iAttMove = 1;
	}
	else if (ActionID == Action::Donu_Buff)
	{
		for (auto& Monster : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_MONSTER))
		{
			Monster->Set_AttPlus(3);
		}
	}
	else if (ActionID == Action::Deca_Att)
	{
		for (int i = 0; i < m_tStatus.iAttXXX; i++)
		{
			GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER).front()->Set_Hp(m_tStatus.iAtt);
		}
		m_iAttMove = 1;
	}
	else if (ActionID == Action::Deca_Buff)
	{
		for (auto& Monster : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_MONSTER))
		{
			Monster->Set_Block(16);
		}
	}

	ActionID = Action::ACTION_END;
}
