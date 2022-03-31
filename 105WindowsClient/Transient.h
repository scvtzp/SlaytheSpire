#pragma once
#include "Monster.h"
class CTransient :
	public CMonster
{
public:
	CTransient();
	virtual ~CTransient();
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
	int m_iCount=5;
};

