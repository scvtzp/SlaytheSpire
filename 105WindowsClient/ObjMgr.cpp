#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
	:m_CardCheck(true)
{
}


CObjMgr::~CObjMgr()
{
	Release(); 
}

void CObjMgr::Add_Object(OBJ::ID eID, CObj * pObj)
{
	m_listObj[eID].emplace_back(pObj);
}

void CObjMgr::Update()
{
	for (int i = 0 ; i < OBJ::OBJ_END; ++i)
	{
		auto& iter_end = m_listObj[i].end(); 
		for (list<CObj*>::iterator iter = m_listObj[i].begin(); iter != iter_end;)
		{
			int iEvent = (*iter)->Update(); 			
			if (OBJ_DEAD == iEvent)
			{
				Set_Gold((*iter)->Get_Gold());
				Safe_Delete(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter; 
		}

	}
}

void CObjMgr::Update(int Number)
{
	if (Number == SHOP)
	{
		for (int i = 0; i < OBJ::OBJ_END; ++i)
		{
			auto& iter_end = m_listObj[i].end();
			for (list<CObj*>::iterator iter = m_listObj[i].begin(); iter != iter_end;)
			{
				//덱 업데이트 안돌림.
				if (i == OBJ::OBJ_CARD)
				{
					break;
				}

				int iEvent = (*iter)->Update();
				if (OBJ_DEAD == iEvent)
				{
					Safe_Delete(*iter);
					iter = m_listObj[i].erase(iter);
				}
				else
					++iter;
			}

		}
	}
}

void CObjMgr::LateUpdate()
{
	for (int i = 0 ; i < OBJ::OBJ_END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			if (i == OBJ::OBJ_PLAYER && m_CardCheck)
			{
				break;
			}
			else if (i == OBJ::OBJ_CARD && m_CardCheck)
			{
				break;
			}
			else if (i == OBJ::OBJ_MONSTER)
			{
				break;
			}
			else if (i == OBJ::OBJ_BUTTON)
			{
				m_CardCheck = true;
			}
			pObj->LateUpdate();
		}
	}

}

void CObjMgr::Render()
{
	for (int i = 0 ; i < OBJ::OBJ_END; ++i)
	{
		for (CObj* pObj : m_listObj[i])
		{
			pObj->Render();
		}
	}
}

void CObjMgr::Render(int Number)
{
	if (Number == SHOP)
	{
		for (int i = 0; i < OBJ::OBJ_END; ++i)
		{
			for (CObj* pObj : m_listObj[i])
			{
				if (i == OBJ::OBJ_PLAYER)
				{
					break;
				}
				else if (i == OBJ::OBJ_CARD)
				{
					break;
				}
				pObj->Render();
			}
		}
	}
}

void CObjMgr::MapRender()
{
	for (int i = OBJ::OBJ_BUTTON; i < OBJ::OBJ_BUTTON+1; ++i)
		{
			for (CObj* pObj : m_listObj[i])
			{
				pObj->Render();
			}
		}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJ::OBJ_END; ++i)
	{
		for (CObj* pObj : m_listObj[i])
		{
			Safe_Delete(pObj);
		}
		m_listObj[i].clear();
	}

}
