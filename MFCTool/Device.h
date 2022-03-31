#pragma once
class CDevice
{
public:
	static CDevice* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CDevice; 

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance; 
			m_pInstance = nullptr; 
		}
	}
private:
	CDevice();
	~CDevice();
	CDevice(CDevice& rDevice) {}; 
	void operator=(CDevice& rDevice) {}
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
	HRESULT InitDevice(); 
	void Release(); 

public:
	void Render_Begin();
	void Render_End(HWND hWnd = nullptr); 

private:
	static CDevice* m_pInstance; 
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

