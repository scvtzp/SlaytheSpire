#pragma once
#include "Monster.h"
class CByrd :
	public CMonster
{
public:
	CByrd();
	virtual ~CByrd();
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
	int m_iTransCount;
	bool m_bTrans = false;;
	bool m_bTransFrame = false;;
};

