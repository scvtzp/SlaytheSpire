#pragma once
#include "Scene.h"
class CStage_Hexa :
	public CScene
{
public:
	CStage_Hexa();
	virtual ~CStage_Hexa();
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

