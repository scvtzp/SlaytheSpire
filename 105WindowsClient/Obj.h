#pragma once
#define VK_MAX 0xff

class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	virtual HRESULT Initialize() PURE;
	virtual int Update()PURE;
	virtual void LateUpdate()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

	enum Action { 
		PowerBuff //공격버프
		, Attack //일반공격
		, ShieldBuff //방어업
		, looter_Attack //도적 전용 일반공격
		, Run //도망치기
		, Stun //기절
		, AttackXXX //연타
		, Donu_Att 
		, Donu_Buff
		, Deca_Att
		, Deca_Buff
		, ACTION_END };

public:
	const RECT& Get_Rect() const { return m_tRect; }
	const D3DXVECTOR3& Get_Point(int a) const { return m_vPoint[a]; }
	int Get_Cost() { return m_tStatus.iCost; }
	int Get_HP() { return m_tStatus.iHp; }
	int Get_MaxHP() { return m_tStatus.iMaxHp; }

	int Get_Block() { return m_tStatus.iBlock; }
	int Get_Gold() { return m_tStatus.iGold; }
	float Get_PosX() { return m_tInfo.vPos.x; }
	float Get_PosY() { return m_tInfo.vPos.y; }

	void Set_Hp(int _iHp);
	void Set_MaxHp(int _iHp) 
	{ 
		m_tStatus.iHp += _iHp;  
		m_tStatus.iMaxHp += _iHp;
		m_tStatus.iRealMaxHp += _iHp;
	}

	void Set_Dead() { m_bDead = true; }
	void Set_Block(int _iBlock) { m_tStatus.iBlock += _iBlock; }
	void Set_BlockZero() { m_tStatus.iBlock = 0; }
	void Set_Pos(float x, float y);
	void Set_PosPlus(float x=0, float y=0);
	void Set_HitSize(float x, float y) { m_tInfo.vHitSize = { x,y,0.f }; }

	void Set_Gold(int a) { m_tStatus.iGold -= a; }
	void Set_Cost(int _iCost) { m_tStatus.iCost -= _iCost; }
	void Set_AttPlus(int AttP) { m_tStatus.iAtt += AttP;  m_tStatus.iAttBuff += AttP; m_tStatus.iPastAtt += m_tStatus.iAtt;}
	void Heil() { m_tStatus.iHp = m_tStatus.iMaxHp; }
	void Set_Buff(BUFF::ID BUFFID) {m_tStatus.Buff = BUFFID;}
	void Set_DeBuff(DEBUFF::ID DEBUFFID) { m_tStatus.DeBuff = DEBUFFID; }

	void Update_Rect();
	void Render_SingleTex(const wstring & wstrObjectKey, float x, float y, float _X=1.f, float _Y=1.f, int A=255, int R = 255, int G = 255, int B = 255);
	void Render_SingleTexRot(const wstring & wstrObjectKey, float x, float y, float Rot, float _X = 1.f, float _Y = 1.f, int A = 255, int R = 255, int G = 255, int B = 255);
	void Render_MultiTex(const wstring & wstrObjectKey, const wstring & wstrStateKey, const int & rImageIndex, float x, float y, int Alpha = 255, float _X = 1.f, float _Y = 1.f);
	void Render_HpBar(float x, float y, float _Y = 1.f);
/////////////////KeyMgr
public:
	bool Key_Pressing(int _key);
	bool Key_Down(int _key);
	bool Key_Up(int _key);
	void Key_Update();
	void HP_Update();

public:
	void Buff_Update();
	void Buff_Render();
	bool Check_Buff(BUFF::ID ID);
	bool Check_DeBuff(DEBUFF::ID ID);

protected:
	INFO m_tInfo; 
	RECT		m_tRect;
	STATUS		m_tStatus;

	bool		m_bDead;
	FRAME m_tFrame;

	D3DXVECTOR3		m_vPoint[4]; // Q
	D3DXVECTOR3		m_vOrigin[4]; // P
	float m_fAngle;
	int m_iDeadA;
	//몬스터 전용
	Action ActionID;
	int m_iAttMove = 0;

	////////키매니져
	bool				m_bKeyState[VK_MAX];
};

