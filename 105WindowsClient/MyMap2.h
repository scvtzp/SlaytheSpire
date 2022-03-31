#pragma once
#include "Scene.h"
class CMyMap2 :
	public CScene
{
public:
	CMyMap2();
	virtual ~CMyMap2();
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float ScrollX = WINCX / 2, ScrollY = WINCY / 2;
};

