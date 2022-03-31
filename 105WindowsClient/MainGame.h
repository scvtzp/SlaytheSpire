#pragma once
class CPlayer; 
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize(); 
	void Update(); 
	void LateUpdate(); 
	void Render(CFrameMgr& rFrameMgr); 
	void Release(); 

private:
};

