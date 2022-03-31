#pragma once
#include "Obj.h"
class CCardID : public CObj
{
public:
	CCardID();
	virtual ~CCardID();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

	void Render_Button(float x, float y);

public:
	void Set_CardName(CARD::ID eName)
	{
		m_CardName = eName;
	}
	CARD::ID Get_CardName()
	{
		return m_CardName;
	}

public:
	void Card_Update();

	void Set_Number(int a);
	void Set_Size(float Size) { m_tInfo.vSize = { Size, Size, 0.f }; }
	void Set_HitSize(float SizeX, float SizeY) { m_tInfo.vHitSize = { SizeX, SizeY, 0.f }; }

	int Get_Damage() { return m_tCardInfo.iDamage; }
	int Get_Number() { return m_iNumber; }
	int Get_Gold() { return m_tCardInfo.iGold; }

public:
	void Set_Cost(int a) { m_tCardInfo.iCost = a; }
	void Set_Damage(int a) { m_tCardInfo.iDamage = a; }
	void Set_Block(int a) { m_tCardInfo.iBlock = a; }
	void Set_Draw(int a) { m_tCardInfo.iDraw = a; }
	void Set_Gold(int a) { m_tCardInfo.iGold = a; }
	void Set_CardCount() { m_iCardCount++; }
	void Set_CardCountZero() { m_iCardCount = 0; }

private:
	FRAME m_tFrame;
	int m_iCulNumber;
	bool m_bClick; //클릭(드래그)중인가
	bool m_bMouseHit;
	
	int m_iCardUp;

	int m_iNumber = 0;	//패에서 몇번째 카드인가
	int m_iCardCount = 0;


	bool m_bCostqnwhr = false;
	float m_bCostTime = 0;

	CARDINFO m_tCardInfo;
	CARD::ID m_CardName;
	D3DXVECTOR3 m_vCurPos;
};

