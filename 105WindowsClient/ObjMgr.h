#pragma once
class CObj; 
class CObjMgr
{
public:
	DECLARE_SINGLETON(CObjMgr)
private:
	CObjMgr();
	~CObjMgr();
public:
	void Add_Object(OBJ::ID eID, CObj* pObj);
	void Update(); 
	void Update(int Number);
	void LateUpdate(); 
	void Render();
	void Render(int Number);
	void MapRender();
	void Release(); 
	list<CObj*> Get_listObj(OBJ::ID _ID)
	{
		return m_listObj[_ID];
	}

	void clearList(OBJ::ID _ID)
	{
		m_listObj[_ID].clear();
	}
	void Set_CardCheck()
	{
		m_CardCheck = false;
	}
	void Set_Scroll(float X, float Y) { ScrollX = X; ScrollY = Y; }
	float Get_ScrollX() { return ScrollX; }
	float Get_ScrollY() { return ScrollY; }

	void Set_Gold(int a) { Gold += a; }
	void Set_GoldZero() { Gold = 0; }
	int Get_Gold() { return Gold; }

	void Set_Map() 
	{ 
		for (int i = 0; i < 20; i++)
		{
			MapCheck[i] = true;
		}
	}

	void Set_Map(int i) { MapCheck[i] = false; }
	bool Get_Map(int i) { return MapCheck[i]; }

	void Set_Count(int i) { iCount = i; }
	void Set_Count() { iCount++; }
	int Get_Count() { return iCount; }

private:
	list<CObj*> m_listObj[OBJ::OBJ_END];
	float ScrollX=0, ScrollY=0;
	bool m_CardCheck;
	int Gold;
	bool MapCheck[20] = {true};
	int iCount = 0;
};

