#include "stdafx.h"
#include "Card.h"
#include "CardID.h"
#include "CollisionMgr.h"

CCard::CCard()
	:m_iHandCount(0), m_iDiscardDeckCount(0)
{
}


CCard::~CCard()
{
}

HRESULT CCard::Initialize()
{
	m_tFrame = { 0, 1 };
	m_tInfo.vPos = { 500, 600.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vHitSize = { 100.f, 100.f, 0.f };
	m_iPastHandCount = m_iHandCount;

	//테스트로 카드 넣어보기
	for(int i=0 ;i<4;i++)
	{
		CCardID* pCardID = new CCardID;
		pCardID->Set_CardName(CARD::Strike);
		pCardID->Set_Cost(1);
		pCardID->Set_Damage(6);
		pCardID->Initialize();
		Add_Card(pCardID);
	}

	for (int i = 4; i<8; i++)
	{
		CCardID* pCardID = new CCardID;
		pCardID->Set_CardName(CARD::Defend);
		pCardID->Set_Cost(1);
		pCardID->Set_Block(5);
		pCardID->Initialize();
		Add_Card(pCardID);
	}
	for (int i = 8; i<11; i++)
	{
		CCardID* pCardID = new CCardID;
		pCardID->Set_CardName(CARD::Whirlwind);
		pCardID->Set_Damage(5);
		pCardID->Initialize();
		Add_Card(pCardID);
	}

	for (int i = 11; i<13; i++)
	{
		CCardID* pCardID = new CCardID;
		pCardID->Set_CardName(CARD::Carnage);
		pCardID->Set_Cost(2);
		pCardID->Set_Damage(20);
		pCardID->Initialize();
		Add_Card(pCardID);
	}	for (int i = 13; i < 15; i++)
	{
		CCardID* pCardID = new CCardID;
		pCardID->Set_CardName(CARD::BodySlam);
		pCardID->Set_Cost(1);
		pCardID->Set_Damage(0);
		pCardID->Initialize();
		Add_Card(pCardID);
	}
	/*
	for (int i = 15; i<17; i++)
	{
		CCardID* pCardID = new CCardID;
		pCardID->Set_CardName(CARD::Cleave);
		pCardID->Set_Cost(1);
		pCardID->Set_Damage(8);
		pCardID->Initialize();
		Add_Card(pCardID);
	}	
	for (int i = 17; i<19; i++)
	{
		CCardID* pCardID = new CCardID;
		pCardID->Set_CardName(CARD::FiendFire);
		pCardID->Set_Cost(2);
		pCardID->Set_Damage(0);
		pCardID->Initialize();
		Add_Card(pCardID);
	}

	for (int i = 19; i<21; i++)
	{
		CCardID* pCardID = new CCardID;
		pCardID->Set_CardName(CARD::Barricade);
		pCardID->Set_Cost(3);
		pCardID->Initialize();
		Add_Card(pCardID);
	}
	for (int i = 21; i<23; i++)
	{
		CCardID* pCardID = new CCardID;
		pCardID->Set_CardName(CARD::Feed);
		pCardID->Set_Cost(1);
		pCardID->Set_Damage(10);
		pCardID->Initialize();
		Add_Card(pCardID);
	}
	for (int i = 23; i<25; i++)
	{
		CCardID* pCardID = new CCardID;
		pCardID->Set_CardName(CARD::Bash);
		pCardID->Set_Cost(2);
		pCardID->Set_Damage(8);
		pCardID->Initialize();
		Add_Card(pCardID);
	}
	Set_Card(CARD::SeeinfRed, 1, 1);
	Set_Card(CARD::Anger, 1, 1);
	*/

	m_iDrawDeckCount = m_VecDrawDeck.size();

	//셔플 함수
	random_shuffle(m_VecDrawDeck.begin(), m_VecDrawDeck.end());

	//초기 1회 핸드 뽑기
	DrawCard();

	return S_OK;
}

void CCard::Add_Card(CCardID * pCardID)
{
	m_VecDrawDeck.emplace_back(pCardID);
}

int CCard::Update()
{
	int iUpdate[100] = {}; 
	int iCount = 0;

	if (m_iPastHandCount != m_iHandCount)
	{
		for (auto& Hand : m_VecHand)
		{
			dynamic_cast<CCardID*>(Hand)->Set_CardCount();
			//(85.f * (m_iPastHandCount - m_iHandCount))
		}
		m_iPastHandCount = m_iHandCount;
	}

	for (vector<CCardID*>::iterator& iter = m_VecHand.begin(); iter != m_VecHand.end(); ++iter)
	{
		iUpdate[iCount] = (*iter)->Update();
		iCount++;
	}


	///////////////////////////////
	iCount = 0;
	for (int i = 0; i < m_iHandCount; i++)
	{
		if (iUpdate[i] == -1) //사용한 카드 버린더미로
		{
			iCount++;
			m_VecDiscardDeck.emplace_back(m_VecHand.at(i));
			m_VecHand.erase(m_VecHand.begin() + i);
		}
		else if (iUpdate[i] == -2) //카드 소멸
		{
			iCount++;
			m_VecHand.erase(m_VecHand.begin() + i);
		}
		else if (iUpdate[i] == -3)
		{
			iCount++;
			m_VecDiscardDeck.emplace_back(m_VecHand.at(i));
			m_VecDiscardDeck.emplace_back(m_VecHand.at(i));
			m_VecHand.erase(m_VecHand.begin() + i);
		}
	}
	m_iHandCount -= iCount;

	//좌표 설정
	iCount = 0;
	for (auto& Hand : m_VecHand)
	{
		Hand->Set_Number(iCount);

		iCount++;
	}

	//버린 덱 크기조절
	for (auto& DisDeck : m_VecDiscardDeck)
	{
		DisDeck->Set_Size(0.8f);
	}
	// 덱 크기조절 + 삭제
	iCount = 0;
	for (auto& DrawDeck : m_VecDrawDeck)
	{
		iUpdate[iCount] = DrawDeck->Get_Number();

		DrawDeck->Set_Size(0.8f);
		++iCount;
	}
	//덱에 있는 카드 삭제
	for (int i = 0; i < m_VecDrawDeck.size(); i++)
	{
		if (iUpdate[i] == -2)
		{
			iCount++;
			m_VecDrawDeck.erase(m_VecDrawDeck.begin() + i);
		}
	}
	Key_Update();

	return 0;
}

void CCard::LateUpdate()
{
	DrawCard();
}

void CCard::Render()
{
	//핸드 출력
	for (auto& Hand : m_VecHand)
	{	
		Hand->Render();
	}

	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);
	if (pt.x >= 45 && pt.x <= 105 && pt.y <= 715 && pt.y >= 625)
		Render_SingleTex(L"deckbase", 70, 670, 0.9f, 0.9f);
	else
		Render_SingleTex(L"deckbase", 70, 670, 0.7f, 0.7f);
	if (pt.x >= 1175 && pt.x <= 1245 && pt.y <= 715 && pt.y >= 625)
		Render_SingleTex(L"discardbase", 1210, 670, 0.9f, 0.9f);
	else
		Render_SingleTex(L"discardbase", 1210, 670, 0.7f, 0.7f);

	TCHAR		m_szFPS[MIN_STR];
	D3DXMATRIX matScale, matTrans, matRotationZ, matWorld;

	swprintf_s(m_szFPS, L"%d", (int)m_VecDrawDeck.size());
	D3DXMatrixTranslation(&matTrans, 90, 685, 0.f);
	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
	GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 0, 0));

	swprintf_s(m_szFPS, L"%d", (int)m_VecDiscardDeck.size());
	D3DXMatrixTranslation(&matTrans, 1230, 685, 0.f);
	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matTrans);
	GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 0, 0));


	DeckButton();
}

void CCard::Release()
{
}

void CCard::MoveFrame(const float & fSpeed /*= 1*/)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * (GET_INSTANCE(CTimeMgr)->Get_DeltaTime() * fSpeed);

	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
		m_tFrame.fFrameStart = 0.f;
}

void CCard::DrawCard()
{
	for (int i = 0; i < m_iHandCount; i++)
	{
		if (m_VecHand.at(i)->Get_CardName() != CARD::Carnage) //대학살 거르기
			m_VecDiscardDeck.emplace_back(m_VecHand.at(i));
	}

	m_VecHand.clear();
	m_iHandCount = 5;
	m_iPastHandCount = 5;

	//카드 더미 리필
	if (m_iDrawDeckCount < 5)
	{
		for (auto& disDeck : m_VecDiscardDeck)
		{
			m_VecDrawDeck.emplace_back(disDeck);
		}

		m_iDrawDeckCount += m_VecDiscardDeck.size();
		m_iDiscardDeckCount = 0;

		m_VecDiscardDeck.clear();
		random_shuffle(m_VecDrawDeck.begin(), m_VecDrawDeck.end());
	}

	//핸드리필
	for (int i = 0; i < 5; i++)
	{
		m_VecDrawDeck.front()->Set_Number(i);
		m_VecDrawDeck.front()->Set_CardCountZero();
		m_VecHand.emplace_back(m_VecDrawDeck.front());
		m_VecHand.back()->Initialize();

		m_VecDrawDeck.erase(m_VecDrawDeck.begin());
	}

	m_iDrawDeckCount -= 5;
	m_iDiscardDeckCount += 5;
}

void CCard::Draw(int CardNum)
{
	for (int i = m_iHandCount; i < m_iHandCount+ CardNum; i++)
	{
		m_VecDrawDeck.front()->Set_Number(i);
		m_VecHand.emplace_back(m_VecDrawDeck.front());
		m_VecHand.back()->Initialize();

		m_VecDrawDeck.erase(m_VecDrawDeck.begin());
	}

	m_iHandCount += CardNum;
}

void CCard::DeckButton()
{
	bool Click = Key_Pressing(VK_LBUTTON);
	//덱버튼
	if (Click || m_bButtonShow)
	{
		if(!m_bButtonShow)
			ButtonShowY = 0.f;

		m_bButtonShow = true;

		if (GET_INSTANCE(CKeyMgr)->Get_Wheel() > 0)
		{
			ButtonShowY += 10.f;
		}
		else if (GET_INSTANCE(CKeyMgr)->Get_Wheel() < 0)
		{
			ButtonShowY -= 10.f;
		}
		GET_INSTANCE(CKeyMgr)->Wheel(0);

		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWND, &pt);
		//버튼1
		if (pt.x >= 45 && pt.x <= 105 && pt.y <= 715 && pt.y >= 625 || m_bButtonShowL)
		{
			if(!m_bButtonShowL)
				CSoundMgr::Get_Instance()->PlaySound(L"UI_Click.ogg", CSoundMgr::PLAYER);
			m_bButtonShowL = true;
			Render_SingleTex(L"BLACK", WINCX / 2, WINCY / 2, 1.f, 1.f, 200);
			int x = 200, y = 250;
			for (auto& Deck : m_VecDrawDeck)
			{
				Deck->Render_Button(x, y + (int)ButtonShowY);

				x += 200;
				if (x > 1000)
				{
					x = 200;
					y += 250;
				}
			}
			//뒤로가기
			if (pt.x >= 50 && pt.x <= 250 && pt.y <= 620 && pt.y >= 560)
			{
				Render_SingleTex(L"cancelButtonON", 150.f, 630.f, 0.7f, 0.7f);
				if (Click)
				{
					m_bButtonShow = false;
					m_bButtonShowL = false;
				}
			}
			else
				Render_SingleTex(L"cancelButton", 150.f, 630.f, 0.7f, 0.7f);
		}
		//버튼2
		else if (pt.x >= 1175 && pt.x <= 1245 && pt.y <= 715 && pt.y >= 625 || m_bButtonShowR)
		{
			if (!m_bButtonShowR)
				CSoundMgr::Get_Instance()->PlaySound(L"UI_Click.ogg", CSoundMgr::PLAYER);
			m_bButtonShowR = true;
			Render_SingleTex(L"BLACK", WINCX / 2, WINCY / 2, 1.f, 1.f, 200);
			int x = 200, y = 250;
			for (auto& Deck : m_VecDiscardDeck)
			{
				Deck->Render_Button(x, y + (int)ButtonShowY);

				x += 200;
				if (x > 1000)
				{
					x = 200;
					y += 250;
				}
			}

			//뒤로가기
			if (pt.x >= 50 && pt.x <= 250 && pt.y <= 630 && pt.y >= 560)
			{
				Render_SingleTex(L"cancelButtonON", 150.f, 630.f, 0.7f, 0.7f);
				if (Click)
				{
					m_bButtonShow = false;
					m_bButtonShowR = false;
				}
			}
			else
				Render_SingleTex(L"cancelButton", 150.f, 630.f, 0.7f, 0.7f);

		}
	}

	Key_Update();
}

void CCard::Set_Card(CARD::ID CardName, int Num, int Cost, int Att, int Block)
{
	for (int i = 0; i < Num; i++)
	{
		CCardID* pCardID = new CCardID;
		pCardID->Set_CardName(CardName);
		pCardID->Set_Cost(Cost);
		pCardID->Set_Damage(Att);
		pCardID->Set_Block(Block);

		pCardID->Initialize();
		Add_Card(pCardID);
	}
}