#pragma once
class CDevice
{
public:
	enum MODE {MODE_FULL, MODE_WIN	};
public:
DECLARE_SINGLETON(CDevice)
private:
	CDevice();
	~CDevice();
public:
	LPDIRECT3DDEVICE9 Get_Device()
	{
		return m_pDevice; 
	}
	LPD3DXSPRITE Get_Sprite()
	{
		return m_pSprite; 
	}
	LPD3DXFONT Get_Font()
	{
		return m_pFont; 
	}
public:
	HRESULT InitDevice(MODE eMode, DWORD dwWinCX, DWORD dwWINCY);
	void Release(); 

public:
	void Render_Begin();
	void Render_End(HWND hWnd = nullptr); 

private:
	LPD3DXFONT m_pFont; // DirectX���� �������ִ� com ��ü ���� ���� 
	LPDIRECT3D9 m_p3D;
	// IDirect3D9 �� ������ �����̴�. �� ��ü�� �ϴ� ������ ��ġ�� ���� ������ �����ϰ� ��ġ�� �����ϴ� ������ �ϴ� com ��ü. 
	LPD3DXSPRITE m_pSprite; 
	LPDIRECT3DDEVICE9 m_pDevice;
	//�������� �׷��� ī�带 �����ϴ� �İ�ü. 

	//com ��ü - component Object Model
	/*
	�츮�� ���� �ִ� DirectX�� 3D �������� �ϱ� ���� API�̴�. �׷����� �����ϱ� ���ؼ��� ���� ��Ұ� �ʿ��ϴ�.
	�׷��� �츮�� �� ��Ҹ� ���� ������ ���Ѵ�. 
	��? �̰͵� �ٸ����� ��� �׷��� ī�带 �˾ƾ� �ϱ� ������. 
	�׷��� ���ҿ��� �̹� ��ǰ�������� �� ����� ����. �츮�� ������Ʈ�� �̿��Ͽ� ���������ν� ���α׷��� �ϼ� �ϴ� ��. 

	*/

};

