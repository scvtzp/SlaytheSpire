#pragma once
#include "Scene.h"
class CStage_lotter :
	public CScene
{
public:
	CStage_lotter();
	virtual ~CStage_lotter();
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

