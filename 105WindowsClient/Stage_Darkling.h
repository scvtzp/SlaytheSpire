#pragma once
#include "Scene.h"
class CStage_Darkling :
	public CScene
{
public:
	CStage_Darkling();
	virtual ~CStage_Darkling();

public:
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

};

