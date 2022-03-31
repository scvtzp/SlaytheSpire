#ifndef __STRUCT_H__
#define __STRUCT_H__

#include "Enum.h"

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9 pTexture; 
		// �ʳװ� ������ ��� hBitmap ������ �� com��ü 
	// �׸������� ���� ���� �ϱ� ���� �İ�ü. 

	D3DXIMAGE_INFO tImageInfo; 
		// �׸��� ������ ������ ���� ����ü. 
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
	int iAtt = 0; // �� ���� ��ü�� �̴ϼȶ����������� ȣ���ϴ� �����̴�. 
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

	////����
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



