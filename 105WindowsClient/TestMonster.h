#pragma once
#include "Monster.h"
class CTestMonster :
	public CMonster
{
public:
	CTestMonster();
	virtual ~CTestMonster();

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
private:
};

