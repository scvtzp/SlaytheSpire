#pragma once
#include "Scene.h"
class CSelect_Player :
	public CScene
{
public:
	CSelect_Player();
	virtual ~CSelect_Player();

	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

	bool Key_Down(int _key);
	void Key_Update();

	enum Player {Ironclad, silent, Defect, Watcher, Player_End};

public:
	Player m_eSelect = Player::Player_End;
	Player m_eCulSelect = Player::Player_End;

private:
	bool				m_bKeyState[VK_MAX];

};

