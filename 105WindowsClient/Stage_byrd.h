#pragma once
#include "Scene.h"
class CStage_byrd :
	public CScene
{
public:
	CStage_byrd();
	virtual ~CStage_byrd();
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

