#pragma once
#include "Characters.h"
class CPlayer :
	public CCharacters
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
public:
	void MoveFrame(const float& fSpeed = 1);
	void Set_AttMove() { m_iAttMove = 1; }
private:
	//������
	bool m_bHitCheck;
};

