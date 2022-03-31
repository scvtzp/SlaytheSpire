#pragma once

namespace OBJ
{
	enum ID {OBJ_TERRAIN, OBJ_MONSTER, OBJ_PLAYER, OBJ_EFFECT,OBJ_BUTTON, OBJ_CARD,  OBJ_END };
}
namespace SCENE
{
	enum ID { SCENE_TITLE
		, SCENE_SELECT_PLAYER
		, SCENE_STAGE
		, SCENE_MAP1
		, SCENE_MAP2
		, SCENE_MAP3
		, STAGE_Looter
		, STAGE_Byrd
		, STAGE_Darkling
		, STAGE_GiantHead
		, STAGE_Transient
		, SCENE_STAGE_GUARDIAN
		, STAGE_DoDe
		, STAGE_Hexa
		, SCENE_SHOP
		, SCENE_Sleep

		, SCENE_END};
}

//카드
namespace CARD
{
	enum ID { 
		//전사
		Strike, //타격X
		Defend,  //방어X
		Whirlwind, //소용돌이X
		Pommel_Strick, //품멜타격X
		Bash,  //강타
		Anger, //분노
		BodySlam, //몸통 박치기X
		Cleave, //절단X
		Sword_Boomerang, //부메랑 칼날
		Carnage, //대학살X
		Barricade, //바리케이트
		Feed, //포식
		FiendFire, //지옥불
		SeeinfRed, //혈안
		Headbutt, //박치기

		//도적
		CARD_END };
}

namespace BUFF
{
	enum ID {Buff_Barricade, BUFF_END};
}

namespace DEBUFF
{
	enum ID { Debuff_Vulnerable //취약
		, DEBUFF_END };
}

namespace BUTTON
{
	enum ID { TURNEND, M_TestMonster, M_Looter, M_Byrd, M_Darkling, M_GiantHead, M_Transient, M_Slime, B_Guardian, B_DoDe, B_Hexa, Get_Gold, Get_Card, D_Shop, D_Camp, D_GoMap1, D_GoMap2, D_GoMap3	};
}
