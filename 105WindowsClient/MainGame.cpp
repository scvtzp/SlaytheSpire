#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "Device.h"
#include "KeyMgr.h"
#include "time.h"
CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release(); 
}

void CMainGame::Initialize()
{
	srand(unsigned int(time(NULL)));
	GET_INSTANCE(CTimeMgr)->Initialize(); 
	ShowCursor(false);


	GET_INSTANCE(CDevice)->InitDevice(CDevice::MODE_WIN, WINCX, WINCY);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/cursors.png", L"Cursors");

	////맵
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/map/map/map1.png", L"map1");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/map/map/map2.png", L"map2");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/map/map/map3.png", L"map3");

	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/map/chest.png", L"chest");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/map/elite.png", L"elite");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/map/event.png", L"event");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/map/monster.png", L"monster");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/map/rest.png", L"rest");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/map/shop.png", L"shop");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/map/circle5.png", L"circle5");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/camp.png", L"camp");


	//////////////////////////////////스테이지
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Stage/BottomScene.jpg", L"BottomScene");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Stage/CityScene.png", L"CityScene");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Stage/beyondScene.png", L"beyondScene");

	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/Topbar.png", L"Topbar");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/endTurnButton.png", L"endTurnButton");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/endTurnButtonGlow.png", L"endTurnButtonGlow");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/deckbase.png", L"deckbase");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/discardbase.png", L"discardbase");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/cancelButton.png", L"cancelButton");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/cancelButtonON.png", L"cancelButtonON");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/gold.png", L"gold");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/rewardListItemPanel.png", L"rewardListItemPanel");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/rewardScreenSheet.png", L"rewardScreenSheet");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/normalCardReward.png", L"normalCardReward");

	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/BLACK.png", L"BLACK");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/WHITE.png", L"WHITE");

	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/HpBar/PlayerHP.png", L"PlayerHP");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/HpBar/MonHP.png", L"MonHP");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/HpBar/block.png", L"block");

	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/proceedButton.png", L"proceedButton");

	/////////////////행동 표시
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/intent/attack/attack_intent_3.png", L"attack_intent_3");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/intent/buff1L.png", L"buff1L");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/intent/attack/attack_intent_4.png", L"attack_intent_4");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/intent/defendL.png", L"defendL");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/intent/escapeL.png", L"escapeL");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/intent/stunL.png", L"stunL");

	////////////////////////버프라인
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/BuffLine/bronzeScales.png", L"bronzeScales");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/BuffLine/shiny.png", L"shiny");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/BuffLine/tough_enemies.png", L"tough_enemies");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/BuffLine/endless.png", L"endless");

	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/intent/attack/attack_intent_4.png", L"attack_intent_4");

	/////////////////////////////이펙트
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/effect/combat/slash_1.png", L"slash");
	///////////////////////////////////플레이어
	//Player->ironclad/idle
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Player/ironclad/Idle/Idle (%d).png", L"Player", L"Idle", 267);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Player/ironclad/Hit/hit (%d).png", L"Player", L"Hit", 14);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/energy/red/layer1.png", L"layer1");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/energy/red/layer1d.png", L"layer1d");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/energy/red/layer2.png", L"layer2");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/energy/red/layer2d.png", L"layer2d");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/energy/red/layer3.png", L"layer3");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/energy/red/layer3d.png", L"layer3d");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/energy/red/layer4.png", L"layer4");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/energy/red/layer4d.png", L"layer4d");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/energy/red/layer5.png", L"layer5");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/energy/red/layer5d.png", L"layer5d");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/ui/energy/red/layer6.png", L"layer6");
	////////////////////////////////////////Shop
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/npc/merchant/idle/idle (%d).png", L"Merchant", L"Idle", 160);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/npc/merchant/merchantObjects.png", L"MerchantObj");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/shop/merchantHand.png", L"merchantHand");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/shop/purge.png", L"purge");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/shop/rug.png", L"rug");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/shop/sale_tag.png", L"sale_tag");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/shop/sold_out.png", L"sold_out");

	/////////////////////////////////////몬스터
	//Monster->cultist/idle
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/cultist/idle/idle (%d).png", L"Monster", L"idle", 131);
	//Monster->Guardian/idle
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/guardian/idle/idle (%d).png", L"Monster_guardian", L"idle", 160);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/guardian/defensive/defensive (%d).png", L"Monster_guardian", L"defensive", 160);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/guardian/transition/trans (%d).png", L"Monster_guardian", L"trans", 80);
	//Looter
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/looter/idle/idle (%d).png", L"looter", L"idle", 320);
	//Byrd
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/byrd/flying/flying (%d).png", L"byrd", L"flying", 100);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/byrd/ground/ground (%d).png", L"byrd", L"ground", 320);
	//Darkling
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/darkling/Att/Att (%d).png", L"darkling", L"Att", 40);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/darkling/Hit/hit (%d).png", L"darkling", L"Hit", 14);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/darkling/idle/idle (%d).png", L"darkling", L"idle", 102);
	//GiantHead
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/GiantHead/trans_close/trans_close (%d).png", L"GiantHead", L"trans_close", 80);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/GiantHead/trans_open/trans_open (%d).png", L"GiantHead", L"trans_open", 80);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/GiantHead/idle_open/idle_open (%d).png", L"GiantHead", L"idle_open", 400);
	//transient
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/transient/idle/idle (%d).png", L"transient", L"idle", 320);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/transient/Hit/hit (%d).png", L"transient", L"Hit", 14);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/transient/Att/Att (%d).png", L"transient", L"Att", 40);
	//Donu
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/donu/idle/idle (%d).png", L"donu", L"idle", 59);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/donu/Hit/Hit (%d).png", L"donu", L"Hit", 14);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/donu/Att/Att (%d).png", L"donu", L"Att", 40);
	//Deca
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/deca/idle/idle (%d).png", L"deca", L"idle", 48);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/deca/Hit/Hit (%d).png", L"deca", L"Hit", 14);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Monster/deca/Att/Att (%d).png", L"deca", L"Att", 40);
	//Deca
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Monster/ghost/core.png", L"core");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Monster/ghost/plasma1.png", L"plasma1");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Monster/ghost/plasma2.png", L"plasma2");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Monster/ghost/plasma3.png", L"plasma3");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Monster/ghost/shadow.png", L"shadow");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Monster/ghost/fire1.png", L"fire1");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Monster/ghost/fire2.png", L"fire2");

	GET_INSTANCE(CSceneMgr)->Scene_Change(SCENE::SCENE_TITLE);
}

void CMainGame::Update()
{
	GET_INSTANCE(CTimeMgr)->UpdateTime();
	GET_INSTANCE(CSceneMgr)->Update();
}

void CMainGame::LateUpdate()
{
	GET_INSTANCE(CSceneMgr)->LateUpdate();
	CKeyMgr::Get_Instance()->Key_Update();
}

void CMainGame::Render(CFrameMgr& rFrameMgr)
{
	GET_INSTANCE(CDevice)->Render_Begin(); 
	GET_INSTANCE(CSceneMgr)->Render();

	//rFrameMgr.RenderFPS();
	GET_INSTANCE(CDevice)->Render_End();
}

void CMainGame::Release()
{
	for (auto& pObj : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_PLAYER))
	{
		Safe_Delete(pObj);
	}
	GET_INSTANCE(CObjMgr)->clearList(OBJ::OBJ_MONSTER);
	for (auto& pObj : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_CARD))
	{
		Safe_Delete(pObj);
	}
	GET_INSTANCE(CObjMgr)->clearList(OBJ::OBJ_MONSTER);
	for (auto& pObj : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_MONSTER))
	{
		Safe_Delete(pObj);
	}
	GET_INSTANCE(CObjMgr)->clearList(OBJ::OBJ_MONSTER);
	for (auto& pObj : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_BUTTON))
	{
		Safe_Delete(pObj);
	}
	GET_INSTANCE(CObjMgr)->clearList(OBJ::OBJ_BUTTON);

	CKeyMgr::Destroy_Instance();
	GET_INSTANCE(CTimeMgr)->Destroy_Instance();
	GET_INSTANCE(CScrollMgr)->Destroy_Instance(); 
	GET_INSTANCE(CSceneMgr)->Destroy_Instance();
	GET_INSTANCE(CTextureMgr)->Destroy_Instance();
	GET_INSTANCE(CObjMgr)->Destroy_Instance(); 
	GET_INSTANCE(CDevice)->Destroy_Instance();
	GET_INSTANCE(CKeyMgr)->Destroy_Instance();
}
