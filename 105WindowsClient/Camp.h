#pragma once
#include "Scene.h"
class CCamp :
	public CScene
{
public:
	CCamp();
	virtual ~CCamp();

	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

