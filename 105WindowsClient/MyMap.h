#pragma once
#include "Scene.h"
class CMyMap :
	public CScene
{
public:
	CMyMap();
	virtual ~CMyMap();

	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float ScrollX= WINCX / 2, ScrollY= -380;
};

