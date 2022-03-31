#pragma once
#include "Monster.h"
class CGuardian :
	public CMonster
{
public:
	CGuardian();
	virtual ~CGuardian();
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
	int m_iTrans;
	bool m_bTrans;
	bool m_bTransFrame;
};

