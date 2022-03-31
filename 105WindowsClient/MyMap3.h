#pragma once
#include "Scene.h"
class CMyMap3 :
	public CScene
{
public:
	CMyMap3();
	virtual ~CMyMap3();	
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float ScrollX = WINCX / 2, ScrollY = WINCY / 2;
};

