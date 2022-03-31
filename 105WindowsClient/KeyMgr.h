#pragma once
#define VK_MAX 0xff

class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)
private:
	CKeyMgr();
	~CKeyMgr();

public:
	bool Key_Pressing(int _key);
	bool Key_Down(int _key);
	bool Key_Up(int _key);
	void Key_Update();
	void Wheel(int a) { m_iMouseWheel = a; }
	int Get_Wheel() { return m_iMouseWheel; }

private:
	bool				m_bKeyState[VK_MAX];
	int					m_iMouseWheel = 0;
};