#pragma once
class CCardID;

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	// ��ü�� �������� �ʰ� ������ �����ڸ� ���� ȣ���� �����ϴ�!
	// ���ڷ� list�� �޴� ������ �浹 ��ü�� �ϳ���� Ȯ���� �� ����!
	// -> �� �� �� �浹 ó���� �˻��ϱ� ���� list�� �Ѱ��ش�.
	static void Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src);


	static bool Collision_Card_Mouse(RECT rect);
	static bool Collision_Monster_Mouse(CARDINFO tCardInfo, list<CObj*>& _Src, list<CObj*>& _Player);
	static void Set_Player_Block(list<CObj*>& _Player, int a);

	static void Whirlwind(list<CObj*>& _Monster, int Att, int Mana);



	static void Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src);
	static bool Check_Sphere(CObj * _Dst, CObj * _Src);
	//static void Collision_RectEx(list<CObj*>& _Dst, list<CObj*>& _Src);
	//static void Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src);

	//static bool Check_Sphere(CObj* _Dst, CObj* _Src);
	//static bool Check_Rect(CObj* _Dst, CObj* _Src, float* _fX, float* _fY);
};