#pragma once
#include "Scene.h"
class CStage_GiantHead :
	public CScene
{
public:
	CStage_GiantHead();
	virtual ~CStage_GiantHead();

public:
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

