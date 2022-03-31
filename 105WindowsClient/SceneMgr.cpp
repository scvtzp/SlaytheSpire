#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Stage.h"
#include "Stage_Guardian.h"
#include "Shop.h"
#include "Title.h"
#include "Select_Player.h"
#include "MyMap.h"
#include "MyMap2.h"
#include "MyMap3.h"
#include "Camp.h"
#include "Stage_lotter.h"
#include "Stage_byrd.h"
#include "Stage_Darkling.h"
#include "Stage_GiantHead.h"
#include "Stage_Transient.h"
#include "Stage_DoDe.h"
#include "Stage_Hexa.h"

IMPLEMENT_SINGLETON(CSceneMgr)
CSceneMgr::CSceneMgr()
	:m_eCurScene(SCENE::SCENE_END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENE::ID eNextID)
{
	m_eNextScene = eNextID; 
	if (m_eNextScene != m_eCurScene)
	{
		// 무언가 바껴야되는 상황. 
		Safe_Delete(m_pScene); 
		switch (m_eNextScene)
		{
		case SCENE::SCENE_TITLE:
			m_pScene = new CTitle; 
			break;
		case SCENE::SCENE_SELECT_PLAYER:
			m_pScene = new CSelect_Player;
			break;
		case SCENE::SCENE_STAGE:
			 m_pScene = new CStage;
			break;
		case SCENE::SCENE_MAP1:
			m_pScene = new CMyMap;
			break;
		case SCENE::SCENE_MAP2:
			m_pScene = new CMyMap2;
			break;
		case SCENE::SCENE_MAP3:
			m_pScene = new CMyMap3;
			break;
		case SCENE::SCENE_STAGE_GUARDIAN:
			m_pScene = new CStage_Guardian;
			break;
		case SCENE::SCENE_SHOP:
			m_pScene = new CShop;
			break;
		case SCENE::STAGE_Looter:
			m_pScene = new CStage_lotter;
			break;
		case SCENE::STAGE_Byrd:
			m_pScene = new CStage_byrd;
			break;
		case SCENE::STAGE_Darkling:
			m_pScene = new CStage_Darkling;
			break;
		case SCENE::STAGE_GiantHead:
			m_pScene = new CStage_GiantHead;
			break;
		case SCENE::STAGE_Transient:
			m_pScene = new CStage_Transient;
			break;
		case SCENE::STAGE_DoDe:
			m_pScene = new CStage_DoDe;
			break;
		case SCENE::STAGE_Hexa:
			m_pScene = new CStage_Hexa;
			break;
		case SCENE::SCENE_Sleep:
			m_pScene = new CCamp;
			break;
		case SCENE::SCENE_END:
			break;
		default:
			break;
		}
		m_pScene->Initialize();

		m_eCurScene = m_eNextScene; 
	}
}

void CSceneMgr::Scene_Check()
{
	if (m_Scene != SCENE::SCENE_END)
	{
		Scene_Change(m_Scene);
		m_Scene = SCENE::SCENE_END;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update(); 
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate(); 
}

void CSceneMgr::Render()
{
	m_pScene->Render(); 
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}
