#pragma once
#include "Scene.h"
class CStage_Guardian :
	public CScene
{
public:
	CStage_Guardian();
	virtual ~CStage_Guardian();

	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

