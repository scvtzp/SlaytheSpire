#pragma once
#include "Obj.h"
#include "CardID.h"
class CCard :
	public CObj
{
public:
	CCard();
	virtual ~CCard();
public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
public:
	void Add_Card(CCardID * pCardID);
	void MoveFrame(const float& fSpeed = 1);
	void DrawCard();
	void Draw(int CardNum);
	void DeckButton();
	void Set_Card(CARD::ID CardName, int Num, int Cost=0, int Att=0, int Block=0);

public:
	vector<CCardID*> Get_VecDeck() {return m_VecDrawDeck;}
	vector<CCardID*> Get_VecHand() { return m_VecHand; }

	int	Get_HandNum() {	return m_iHandCount;}

	//void Out_Card();
private:
	FRAME m_tFrame;

	vector<CCardID*> m_VecDrawDeck;
	vector<CCardID*> m_VecDiscardDeck;
	vector<CCardID*> m_VecHand;

	int m_iHandCount = 5;
	int m_iDrawDeckCount;
	int m_iDiscardDeckCount;
	int m_iPastHandCount = 5;

	float ButtonShowY = 0.f;

	bool m_bButtonShow = false;
	bool m_bButtonShowL = false;
	bool m_bButtonShowR = false;

};

