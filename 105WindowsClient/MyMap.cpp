#include "stdafx.h"
#include "MyMap.h"

CMyMap::CMyMap()
{
}


CMyMap::~CMyMap()
{
	Release();
}


HRESULT CMyMap::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Level1.ogg");

	CObj* pObj;
	if (GET_INSTANCE(CObjMgr)->Get_Map(1))
	{
		pObj = CAbstractFactory<CMyButton>::Create();
		pObj->Set_Pos(400.f, 860.f);
		pObj->Set_HitSize(100.f, 100.F);
		dynamic_cast<CMyButton*>(pObj)->Set_Button(BUTTON::M_TestMonster);
		GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_BUTTON, pObj);
	}
	if (GET_INSTANCE(CObjMgr)->Get_Map(2))
	{
		pObj = CAbstractFactory<CMyButton>::Create();
		pObj->Set_Pos(470.f, 660.f);
		pObj->Set_HitSize(100.f, 100.F);
		dynamic_cast<CMyButton*>(pObj)->Set_Button(BUTTON::M_Darkling);
		GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_BUTTON, pObj);
	}
	if (GET_INSTANCE(CObjMgr)->Get_Map(3))
	{
		pObj = CAbstractFactory<CMyButton>::Create();
		pObj->Set_Pos(400.f, 330.f);
		pObj->Set_HitSize(100.f, 100.F);
		dynamic_cast<CMyButton*>(pObj)->Set_Button(BUTTON::D_Shop);
		GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_BUTTON, pObj);

	}
	if (GET_INSTANCE(CObjMgr)->Get_Map(4))
	{
		pObj = CAbstractFactory<CMyButton>::Create();
		pObj->Set_Pos(370.f, 80.f);
		pObj->Set_HitSize(100.f, 100.F);
		dynamic_cast<CMyButton*>(pObj)->Set_Button(BUTTON::D_Camp);
		GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_BUTTON, pObj);

	}
	if (GET_INSTANCE(CObjMgr)->Get_Map(5))
	{
		pObj = CAbstractFactory<CMyButton>::Create();
		pObj->Set_Pos(425.f, -230.f);
		pObj->Set_HitSize(100.f, 100.F);
		dynamic_cast<CMyButton*>(pObj)->Set_Button(BUTTON::D_Camp);
		GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_BUTTON, pObj);
	}
	pObj = CAbstractFactory<CMyButton>::Create();
	pObj->Set_Pos(425.f, -430.f);
	pObj->Set_HitSize(100.f, 100.F);
	dynamic_cast<CMyButton*>(pObj)->Set_Button(BUTTON::B_Guardian);
	GET_INSTANCE(CObjMgr)->Add_Object(OBJ::OBJ_BUTTON, pObj);

	return S_OK;
}

void CMyMap::Update()
{
	GET_INSTANCE(CObjMgr)->Update();
	GET_INSTANCE(CObjMgr)->Set_GoldZero();
}

void CMyMap::LateUpdate()
{

	if (GET_INSTANCE(CKeyMgr)->Key_Pressing(VK_LEFT))
	{
		GET_INSTANCE(CSceneMgr)->Scene_Change(SCENE::SCENE_MAP1);
	}
	if (GET_INSTANCE(CKeyMgr)->Key_Pressing(VK_RIGHT))
	{
		GET_INSTANCE(CSceneMgr)->Scene_Change(SCENE::SCENE_MAP2);
	}
	if (GET_INSTANCE(CKeyMgr)->Key_Pressing(VK_RETURN))
	{
		GET_INSTANCE(CSceneMgr)->Scene_Change(SCENE::SCENE_MAP3);
	}

	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	if (GET_INSTANCE(CKeyMgr)->Key_Down(VK_LBUTTON) && (pt.y - ScrollY) < -300)
	{
		GET_INSTANCE(CSceneMgr)->Scene_Change(SCENE::SCENE_STAGE_GUARDIAN);
	}

	if (GET_INSTANCE(CKeyMgr)->Get_Wheel() > 0)
	{
		ScrollY += 30.f;

		if (ScrollY >= 1100)
		{
			ScrollY = 1100;
		}
	}
	else if (GET_INSTANCE(CKeyMgr)->Get_Wheel() < 0)
	{
		ScrollY -= 30.f;
		if (ScrollY <= -380)
		{
			ScrollY = -380;
		}
	}

	GET_INSTANCE(CObjMgr)->Set_Scroll(ScrollX, ScrollY);

	GET_INSTANCE(CKeyMgr)->Wheel(0);

	GET_INSTANCE(CObjMgr)->LateUpdate();

	GET_INSTANCE(CSceneMgr)->Scene_Check();
}

void CMyMap::Render()
{
	////?????? ??????
	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);


	Render_SingleTex(L"map1", ScrollX, ScrollY, 1.8f, 1.8f);

	Render_SingleTex(L"Cursors", pt.x + 10, pt.y + 10, 0.7f, 0.7f);
	
	GET_INSTANCE(CObjMgr)->MapRender();

	if (GET_INSTANCE(CObjMgr)->Get_Map(1))
		;
	else
		Render_SingleTex(L"circle5", 400.f, 860.f + GET_INSTANCE(CObjMgr)->Get_ScrollY(), 0.5f, 0.5f);
	if (GET_INSTANCE(CObjMgr)->Get_Map(2))
		;
	else
		Render_SingleTex(L"circle5", 470.f, 660.f + GET_INSTANCE(CObjMgr)->Get_ScrollY(), 0.5f, 0.5f);
	if (GET_INSTANCE(CObjMgr)->Get_Map(3))
		;
	else
		Render_SingleTex(L"circle5", 400.f, 330.f + GET_INSTANCE(CObjMgr)->Get_ScrollY(), 0.5f, 0.5f);
	if (GET_INSTANCE(CObjMgr)->Get_Map(4))
		;
	else
		Render_SingleTex(L"circle5", 370.f, 80.f + GET_INSTANCE(CObjMgr)->Get_ScrollY(), 0.5f, 0.5f);
	if (GET_INSTANCE(CObjMgr)->Get_Map(5))
		;
	else
		Render_SingleTex(L"circle5", 425.f, -230.f + GET_INSTANCE(CObjMgr)->Get_ScrollY(), 0.5f, 0.5f);
}

void CMyMap::Release()
{
	for (auto& pObj : GET_INSTANCE(CObjMgr)->Get_listObj(OBJ::OBJ_BUTTON))
	{
		Safe_Delete(pObj);
	}
	GET_INSTANCE(CObjMgr)->clearList(OBJ::OBJ_BUTTON);
	GET_INSTANCE(CObjMgr)->Set_Scroll(ScrollX, 0.f);

	GET_INSTANCE(CObjMgr)->Set_Count();
	GET_INSTANCE(CObjMgr)->Set_Map(GET_INSTANCE(CObjMgr)->Get_Count());
}
