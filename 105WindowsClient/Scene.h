#pragma once
#include "MyButton.h"
class CScene
{
public:
	CScene();
	virtual ~CScene();
public:
	virtual HRESULT Initialize()PURE; 
	virtual void Update()PURE;
	virtual void LateUpdate()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

	void Render_Cursors();
	void Render_Gold(BUTTON::ID ID);

	void Render_SingleTex(const wstring & wstrObjectKey, float x, float y, float _X = 1.f, float _Y = 1.f, int A = 255);
	void Render_MultiTex(const wstring & wstrObjectKey, const wstring & wstrStateKey, const int & rImageIndex, float x, float y);

protected:
	bool m_bSceneDeadCheck = true;
};

