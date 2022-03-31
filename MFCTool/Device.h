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
	LPD3DXFONT m_pFont; // DirectX에서 제공해주는 com 객체 폰드 관련 
	LPDIRECT3D9 m_p3D;
	// IDirect3D9 의 포인터 형식이다. 이 객체가 하는 역할은 장치의 지원 수준을 조사하고 장치를 생성하는 역할을 하는 com 객체. 
	LPD3DXSPRITE m_pSprite; 
	LPDIRECT3DDEVICE9 m_pDevice;
	//실질적인 그래픽 카드를 제어하는 컴객체. 

	//com 객체 - component Object Model
	/*
	우리가 배우고 있는 DirectX도 3D 랜더링을 하기 위한 API이다. 그래픽을 제어하기 위해서는 많은 요소가 필요하다.
	그러나 우리는 그 요소를 전부 만들지 못한다. 
	왜? 이것들 다만들라면 모든 그래픽 카드를 알아야 하기 때문에. 
	그래서 마소에서 이미 부품형식으로 다 만들어 놨다. 우리는 컴포넌트를 이용하여 조립함으로써 프로그램을 완성 하는 것. 

	*/

};

