#pragma once
class CTexture
{
public:
	CTexture();
	virtual ~CTexture();
public:
	virtual TEXINFO* Get_TexInfo(const wstring& wstrStateKey = L"", const int& rCount = 0)PURE;
public:
	virtual HRESULT InsertTexture(const wstring& wstrFilePath, 
		const wstring& wstrStateKey = L""/*��Ƽ�ý��Ŀ��� ����� ����*/, 
		// �츮 ���� �׸� ������ ������ƮŰ�� ������Ʈ Ű�� ������ ���� �� ��. 
		// ex) ObjectKey - Player or Monster or Bullet, NPC
		// ex) StateKey - Player�� IDle ���� Ȥ�� �ٱ� Ȥ�� ���� Ȥ�� �״� ��� ���� �� �� ��. 
		const int& rCount = 0/* �ֵ� ��Ƽ������ ����� ���� ����Ʈ �Ű����� ��� */)PURE;
	virtual void Release()PURE; 
};

