#pragma once
#include "Obj.h"
class CMyButton : public CObj
{
public:
	CMyButton();
	virtual ~CMyButton();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

	void ShowCardIn(const wstring & wstrObjectKey);

public:
	void Set_Button(BUTTON::ID ID) { m_ButtonID = ID; }

private:
	BUTTON::ID m_ButtonID;
	wstring m_TexID;
	bool m_bMouseHit;
	bool m_bRenderCK = true;
	bool m_bGetCard;
	bool BShowCard = false;
	wstring ObjectKey;
};