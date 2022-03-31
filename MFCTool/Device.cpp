#include "stdafx.h"
#include "Device.h"

CDevice* CDevice::m_pInstance = nullptr;
CDevice::CDevice()
	:m_p3D(nullptr)
	,m_pDevice(nullptr)
	,m_pSprite(nullptr)
	,m_pFont(nullptr)
{
}


CDevice::~CDevice()
{
	Release(); 
}

HRESULT CDevice::InitDevice()
{
	//1.��ġ�� �����ϴ� �İ�ü�� ���� �Ұ�. (m_p3D)
	//2.��ġ�� �����ϴ� �İ�ü(m_p3D)�� �̿��Ͽ� �׷��� ī���� ���� ������ �����Ѵ�. ������ ���� �ϴ���. 
	//3.m_p3D��ü�� �̿��Ͽ� ��ġ�� �����ϴ� �İ�ü�� ���� �� ��.(m_pDevice)

	//1.��ġ�� �����ϴ� �İ�ü�� ����. 
	D3DCAPS9 DeviceCaps; 
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT //�� ���ڴ� ���� ������ �ִ� �׷���ī���� ������ �����ϰڴٶ�� ��. 
		, D3DDEVTYPE_HAL // HAL�� ���� ���� ������ �����ڴ�. 
			//HAL - �ϵ���� �߻� ����, �׷��� ī�帶�� �����ϴ� ���� ��� �� �ٸ����� ���� �÷����� ���ư��� ����� �����͸� ������ �־�� �Ѵ�. 
			// �װ��� HAL�̶�� ������ ��Ƶд�. ���� ��û�ؼ�? ���Ұ� ��û�ؼ�. 
		, &DeviceCaps
	)))
	{
		AfxMessageBox(L"GetDeviceCaps Failed!");
		return E_FAIL; 
	}

	// ���ؽ� ���μ����� ������ �����ؾ� �Ѵ�. 
	// ������ȭ + ������ 
	DWORD vp = 0; 
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	
	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	// ������� ����
	d3dpp.BackBufferWidth = WINCX;
	//������� ����
	d3dpp.BackBufferHeight = WINCY;
	// ����� � �Ѱ��� �츰 1�� 
	d3dpp.BackBufferCount = 1;

	// �⺻ �ȼ� ������ ��� ����� ���� �츮�� ���� 8��Ʈ, ���� 8��Ʈ �׸� 8��Ʈ ��� 8��Ʈ ����ϰڴ�. 
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	// ��Ƽ���ø� - �̹����� ǥ���ϴµ� �־� ��Ÿ���� ��ģ �̹����� �ε巴�� ����� ���. 
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE; 
	// ��Ƽ ���ø��� ����Ƽ�� ���Ѵ�. �Ⱦ��� 0
	d3dpp.MultiSampleQuality = 0;
	// _D3DSWAPEFFECT 3���� �̳Ѱ��� ����. 
	//D3DSWAPEFFECT_DISCARD - ����ü�� ����� ����ϰڴ�. ��������۸��� ����ȣȯ����. 
	// ���� ���ۿ� �ĸ� ���� �ΰ��� �ΰ� �ĸ�ο� �׸��� �׸��� ������ۿ� �ٲٴ� ����. 
	// �׸��� �̰� ������ �ϸ� ��ġ ü�θ���̶� �ؼ� ����ü��. 

	//D3DSWAPEFFECT_FLIP - �̰Ŵ� ���� ���� �ٽ� �����ؿ�. 

	//D3DSWAPEFFECT_COPY - �츮�� ����ϴ� ������۸�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.Windowed = TRUE; 
	// TRUE - â 
	// FALSE - ��ü 

	// ���̰��� ������ ���ۿ� ���׽� ���۸� �˾Ƽ� �ϰԲ� ����� �ٰ�. 
	d3dpp.EnableAutoDepthStencil = TRUE; 
	// ������ ���̹��۸� ����� ���� ����. �� ? ���ʿ� z���� ���� ����. 2D�ϱ�. 
	// ���ٽǵ� 3d �Ѿ�� ����. 
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	// ���̰� 24��Ʈ ���, ���ٽ� 8��Ʈ ��� 

	// 
	// �ֻ��� ���ߴ� ����. 
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; 

	// ���� �ٽ� �˾ƿ�. 
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; 

	if (FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWND, vp,&d3dpp, &m_pDevice)))
	{
		AfxMessageBox(L"CreateDevice Func Failed!");
		return E_FAIL; 
	}
	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		AfxMessageBox(L"CreateSprite Func Failed!"); 
		return E_FAIL; 
	}
	// ������ ��Ʈ�� ���� ������ ���� ����ü. 
	D3DXFONT_DESCW tFontInfo; 
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));
	tFontInfo.Width = 10; 
	tFontInfo.Height = 20; 
	tFontInfo.Weight = FW_HEAVY; // �β���. 
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"�ü�");
	// D3DXCreateFontIndirect - ��Ʈ ����ü ������ ���� ��Ʈ ��ü�� �����ϴ� �Լ�. 
	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo,&m_pFont)))
	{
		AfxMessageBox(L"CreateFont Failed!"); 
		return E_FAIL; 
	}

	return S_OK;
}

void CDevice::Release()
{
	if (m_pFont)
		m_pFont->Release(); 

	if (m_pSprite)
		m_pSprite->Release();

	// LPDIRECT3DDEVICE9 �ȿ��� ���������� LPDIRECT3D9�� �����ϰ� �ֱ� ������ m_pDevice���� ���� ��� �Ѵ�. 
	if (m_pDevice)
		m_pDevice->Release();

	if (m_p3D)
		m_p3D->Release();

	// ���� �߿� ! ���۸� �����͸� �����ϱ� ���� ���۷��� ī��Ʈ ��� ����� ����ϰ� ����. 

}

void CDevice::Render_Begin()
{
	// �츮�� ���� �׸��� �׸��� ��� �Ұų� . 
	// �׸��׸��� ���� - �ĸ���۸� ����� -> �ĸ���ۿ� �׸��� �׸��� -> �ĸ���ۿ� ���� ���۸� ��ü�Ѵ�. 

	m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB(255, 0, 0, 255), 0, 0);
	m_pDevice->BeginScene();
	// ��������Ʈ ��ü�� ����ؼ� �׸��� �׸��ڴ� ��� ���� �־���� �Ѵ�. 
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDevice::Render_End(HWND hWnd /*= nullptr*/)
{
	m_pSprite->End();
	m_pDevice->EndScene(); 

	// ������۷� ��ü! 
	// 3��° ���ڸ� �������. 
	// 3��° ���ڴ� ��� ������â�� �׸� ���ΰ�. 
	// ���� nullptr �־��ٸ� �츮�� ������ �־��� g_hWND�� ����Ʈ�� ������. 
	// ���� �ٸ� ������ â�� �׸��� �׸��� �ʹٸ�!? 3��° ���ڿ� ���� �׸����� �ϴ� ������ â�� �ڵ��� �־��ָ� �ȴ�. 
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);
}
