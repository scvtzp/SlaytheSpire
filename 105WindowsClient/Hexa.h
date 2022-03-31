#pragma once
#include "Monster.h"
class CHexa :
	public CMonster
{
public:
	CHexa();
	virtual ~CHexa();
public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
public:
	void Action_Shuffle();
	float Rot = 0;
	float Rot1 = 0;
	int m_iCount = 0;
};

