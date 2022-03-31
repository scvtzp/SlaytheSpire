#pragma once
#include "Monster.h"
class CLooter :
	public CMonster
{
public:
	CLooter();
	virtual ~CLooter();
public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
public:
	void Action_Shuffle();
	void MoveFrame(const float& fSpeed = 1);
};

