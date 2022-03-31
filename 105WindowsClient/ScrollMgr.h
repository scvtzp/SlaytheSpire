#pragma once
class CScrollMgr
{
	DECLARE_SINGLETON(CScrollMgr)
public:
	enum SCROLL {SCROLL_X, SCROLL_Y};
private:
	CScrollMgr();
	~CScrollMgr();
public:
	float Get_Scroll(SCROLL eScrollID); 
	D3DXVECTOR3& Get_Scroll();
	void Set_Scroll(const D3DXVECTOR3& rPos);


private:
	D3DXVECTOR3 m_vScroll; 
};

