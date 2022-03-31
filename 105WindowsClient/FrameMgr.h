#pragma once
class CFrameMgr
{
public:
	CFrameMgr();
	~CFrameMgr();
public:
	void Initialize(float fFPS);
	bool LockFrame(); 
	void RenderFPS(); 

	// 1 / 60
private:
	LARGE_INTEGER m_OldTime; 
	LARGE_INTEGER m_CPUTick; 
	LARGE_INTEGER m_CurTime; 

	// 1/ ���� ���ϴ� �����Ӽ�. �������Ӵ� �������� ���. 
	float		m_fSPF; 
	int			m_iFPS; 
	TCHAR		m_szFPS[MIN_STR]; 
	float		m_fFrameTime; 
	float		m_fDeltaTime; 

};

