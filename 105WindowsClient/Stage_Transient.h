#pragma once
#include "Scene.h"
class CStage_Transient :
	public CScene
{
public:
	CStage_Transient();
	virtual ~CStage_Transient();
public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

