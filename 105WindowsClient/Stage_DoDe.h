#pragma once
#include "Scene.h"
class CStage_DoDe :
	public CScene
{
public:
	CStage_DoDe();
	virtual ~CStage_DoDe();
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

