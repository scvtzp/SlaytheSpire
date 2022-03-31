#pragma once
#include "Monster.h"
class CDonu :
	public CMonster
{
public:
	CDonu();
	virtual ~CDonu();
public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
public:
	void Action_Shuffle();
	void MoveFrame(const float& fSpeed = 1);

private:
	bool m_bDonuAct = false;
};

