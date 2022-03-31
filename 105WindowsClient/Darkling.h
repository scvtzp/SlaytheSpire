#pragma once
#include "Monster.h"
class CDarkling :
	public CMonster
{
public:
	CDarkling();
	virtual ~CDarkling();
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
	int m_iDeadCount = 0;
	bool m_bdead = false;
};

