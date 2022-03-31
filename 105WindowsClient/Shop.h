#pragma once
#include "Scene.h"
class CShop :
	public CScene
{
public:
	CShop();
	virtual ~CShop();

	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

	bool ShopOpen();

private:
	FRAME m_tFrame;
	INFO m_tInfo;
	vector<CCardID*> m_VecShop;
	bool m_bShopCheck;
	bool m_bPurgeHit;
	bool m_bSold_Out= false;
public:
	bool Key_Pressing(int _key);
	bool Key_Down(int _key);
	bool Key_Up(int _key);
	void Key_Update();
	bool				m_bKeyState[VK_MAX];
	bool Down;

};

