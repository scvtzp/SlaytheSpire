#pragma once
class CScene; 
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)
private:
	CSceneMgr();
	~CSceneMgr();

public:
	void Scene_Change(SCENE::ID eNextID);
	void Set_Scene(SCENE::ID eID) { m_Scene = eID; }
	void Scene_Check();

	void Update(); 
	void LateUpdate(); 
	void Render(); 
	void Release(); 

private:
	SCENE::ID m_eCurScene; 
	SCENE::ID m_eNextScene; 

	SCENE::ID m_Scene = SCENE::SCENE_END;

	CScene* m_pScene; 

};

