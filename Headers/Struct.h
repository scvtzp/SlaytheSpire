#ifndef __STRUCT_H__
#define __STRUCT_H__

#include "Enum.h"

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9 pTexture; 
		// 너네가 예전에 썼던 hBitmap 역할을 할 com객체 
	// 그림한장을 관리 제어 하기 위한 컴객체. 

	D3DXIMAGE_INFO tImageInfo; 
		// 그림의 정보를 가지고 있을 구조체. 
}TEXINFO;
typedef struct tagInfo
{
	D3DXVECTOR3 vPos = {0.f, 0.f, 0.f};
	D3DXVECTOR3 vPastPos = { 0.f, 0.f, 0.f };
	D3DXVECTOR3 vSize = { 0.f, 0.f, 0.f };
	D3DXVECTOR3 vHitSize = { 0.f, 0.f, 0.f };
	D3DXVECTOR3 vLook = { 0.f, 0.f, 0.f };
	D3DXVECTOR3 vDir = { 0.f, 0.f, 0.f };
	D3DXMATRIX matWorld; 

}INFO;

typedef struct tagUnitInfo
{
	tagUnitInfo() 
		:iAtt(10)
	{}
#ifdef _AFX
	CString strName; 
#else 
	wstring strName;
#endif
	int iAtt = 0; // 이 행위 자체가 이니셜라이져문법을 호출하는 행위이다. 
	int iDef = 0;
	BYTE byClass = 0;
	BYTE byItem =0 ;
}UNIT;

typedef struct tagFrame
{
	float fFrameStart; 
	float fFrameEnd; 
}FRAME;
typedef struct tagImagePath
{
	wstring wstrPath = L""; 
	wstring wstrObjectKey = L""; 
	wstring wstrStateKey = L""; 
	int iCount = 0; 

}IMAGEPATH;


typedef struct tagStatus
{
	int		iHp= 0;
	int		iMaxHp = 0;
	int		iRealMaxHp = 0;

	int		iPastHp = 0;
	
	int		iAtt = 0;
	int		iAttBuff = 0;

	int		iGold = 0;

	int		iCost = 0;
	int		iMaxCost = 0;

	int		iBlock = 0;

	BUFF::ID Buff = BUFF::BUFF_END;
	DEBUFF::ID DeBuff = DEBUFF::DEBUFF_END;

	vector<BUFF::ID> VecBuff;
	vector<DEBUFF::ID> VecDebuff;

	////몬스터
	int		iReflect=0;
	int		iAttXXX = 0;
	int		iPastAtt = 0;

}STATUS;

typedef struct cardInfo
{
	int		iCost=0;
	int		iDamage=0;
	int		iBlock = 0;
	int		iDraw = 0;
	int		iGold = 0;
}CARDINFO;

#endif



