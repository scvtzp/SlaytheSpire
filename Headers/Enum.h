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

//ī��
namespace CARD
{
	enum ID { 
		//����
		Strike, //Ÿ��X
		Defend,  //���X
		Whirlwind, //�ҿ뵹��X
		Pommel_Strick, //ǰ��Ÿ��X
		Bash,  //��Ÿ
		Anger, //�г�
		BodySlam, //���� ��ġ��X
		Cleave, //����X
		Sword_Boomerang, //�θ޶� Į��
		Carnage, //���л�X
		Barricade, //�ٸ�����Ʈ
		Feed, //����
		FiendFire, //������
		SeeinfRed, //����
		Headbutt, //��ġ��

		//����
		CARD_END };
}

namespace BUFF
{
	enum ID {Buff_Barricade, BUFF_END};
}

namespace DEBUFF
{
	enum ID { Debuff_Vulnerable //���
		, DEBUFF_END };
}

namespace BUTTON
{
	enum ID { TURNEND, M_TestMonster, M_Looter, M_Byrd, M_Darkling, M_GiantHead, M_Transient, M_Slime, B_Guardian, B_DoDe, B_Hexa, Get_Gold, Get_Card, D_Shop, D_Camp, D_GoMap1, D_GoMap2, D_GoMap3	};
}
