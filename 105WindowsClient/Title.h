#pragma once
#include "Scene.h"
class CTitle :
	public CScene
{
public:
	CTitle();
	virtual ~CTitle();

	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

