#pragma once
#include "Scene.h"
class CStage_Transient :
	public CScene
{
public:
	CStage_Transient();
	virtual ~CStage_Transient();
public:
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

