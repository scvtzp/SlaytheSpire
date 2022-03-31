#include "stdafx.h"
#include "Device.h"

IMPLEMENT_SINGLETON(CDevice)
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

HRESULT CDevice::InitDevice(MODE eMode, DWORD dwWinCX, DWORD dwWINCY)
{
	//1.장치를 조사하는 컴객체를 생성 할것. (m_p3D)
	//2.장치를 조사하는 컴객체(m_p3D)를 이용하여 그래픽 카드의 지원 수준을 조사한다. 어디까지 지원 하는지. 
	//3.m_p3D객체를 이용하여 장치를 제어하는 컴객체를 생성 할 것.(m_pDevice)

	//1.장치를 조사하는 컴객체를 생성. 
	D3DCAPS9 DeviceCaps; 
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT //이 인자는 현재 끼워져 있는 그래픽카드의 성능을 조사하겠다라는 것. 
		, D3DDEVTYPE_HAL // HAL을 통해 지원 수준을 얻어오겠다. 
			//HAL - 하드웨어 추상 계층, 그래픽 카드마다 지원하는 것이 모두 다 다르더라도 현재 플렛폼에 돌아가는 공통된 데이터를 가지고 있어야 한다. 
			// 그것을 HAL이라는 계층에 담아둔다. 누가 요청해서? 마소가 요청해서. 
		, &DeviceCaps
	)))
	{
		ERR_MSG(L"GetDeviceCaps Failed!");
		return E_FAIL; 
	}

	// 버텍스 프로세싱의 유무를 조사해야 한다. 
	// 정점변화 + 조명연산 
	DWORD vp = 0; 
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	
	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	// 백버퍼의 가로
	d3dpp.BackBufferWidth = dwWinCX;
	//백버퍼의 세로
	d3dpp.BackBufferHeight = dwWINCY;
	// 백버퍼 몇개 둘건지 우린 1개 
	d3dpp.BackBufferCount = 1;

	// 기본 픽셀 포멧을 어떻게 사용할 건지 우리는 알파 8비트, 레드 8비트 그린 8비트 블루 8비트 사용하겠다. 
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	// 멀티셈플링 - 이미지를 표현하는데 있어 나타나는 거친 이미지를 부드럽게 만드는 기술. 
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE; 
	// 멀티 셈플링의 퀄리티를 뜻한다. 안쓰니 0
	d3dpp.MultiSampleQuality = 0;
	// _D3DSWAPEFFECT 3가지 이넘값이 있음. 
	//D3DSWAPEFFECT_DISCARD - 스왑체인 방식을 사용하겠다. 더블버버퍼링의 상위호환형식. 
	// 전면 버퍼와 후면 버퍼 두개를 두고 후면부에 그림을 그리고 전면버퍼와 바꾸는 형식. 
	// 그리고 이걸 꾸준히 하면 마치 체인모양이라 해서 스왑체인. 

	//D3DSWAPEFFECT_FLIP - 이거는 내가 내일 다시 공부해옴. 

	//D3DSWAPEFFECT_COPY - 우리가 사용하던 더블버퍼링
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.Windowed = eMode; 
	// TRUE - 창 
	// FALSE - 전체 

	// 깊이값을 보관할 버퍼와 스테실 버퍼를 알아서 하게끔 만들어 줄것. 
	d3dpp.EnableAutoDepthStencil = TRUE; 
	// 지금은 깊이버퍼를 사용할 일이 없음. 왜 ? 애초에 z값이 없기 때문. 2D니깐. 
	// 스텐실도 3d 넘어가며 배울것. 
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	// 깊이값 24비트 사용, 스텐실 8비트 사용 

	// 
	// 주사율 맞추는 인자. 
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; 

	// 내일 다시 알아옴. 
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; 

	if (FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWND, vp,&d3dpp, &m_pDevice)))
	{
		ERR_MSG(L"CreateDevice Func Failed!");
		return E_FAIL; 
	}
	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		ERR_MSG(L"CreateSprite Func Failed!");
		return E_FAIL; 
	}
	// 생성할 폰트에 대한 정보를 갖는 구조체. 
	D3DXFONT_DESCW tFontInfo; 
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));
	tFontInfo.Width = 10; 
	tFontInfo.Height = 20; 
	tFontInfo.Weight = FW_HEAVY; // 두껍게. 
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"경기천년바탕 Bold");
	// D3DXCreateFontIndirect - 폰트 구조체 정보를 토대로 폰트 객체를 생성하는 함수. 
	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo,&m_pFont)))
	{
		ERR_MSG(L"CreateFont Failed!");
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

	// LPDIRECT3DDEVICE9 안에서 내부적으로 LPDIRECT3D9을 참조하고 있기 때문에 m_pDevice부터 지워 줘야 한다. 
	if (m_pDevice)
		m_pDevice->Release();

	if (m_p3D)
		m_p3D->Release();

	// 순서 중요 ! 뎅글링 포인터를 방지하기 위해 레퍼런스 카운트 라는 기법을 사용하고 있음. 

}

void CDevice::Render_Begin()
{
	// 우리가 이제 그림을 그릴때 어떻게 할거냐 . 
	// 그림그리는 순서 - 후면버퍼를 지운다 -> 후면버퍼에 그림을 그린다 -> 후면버퍼와 전면 버퍼를 교체한다. 

	m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB(255, 0, 0, 255), 0, 0);
	m_pDevice->BeginScene();
	// 스프라이트 객체를 사용해서 그림을 그리겠다 라는 것을 넣어줘야 한다. 
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDevice::Render_End(HWND hWnd /*= nullptr*/)
{
	m_pSprite->End();
	m_pDevice->EndScene(); 

	// 전면버퍼로 교체! 
	// 3번째 인자를 기억하자. 
	// 3번째 인자는 어느 윈도우창에 그릴 것인가. 
	// 내가 nullptr 넣었다면 우리가 위에서 넣어준 g_hWND가 디폴트로 잡힌다. 
	// 만약 다른 윈도우 창에 그림을 그리고 싶다면!? 3번째 인자에 내가 그리고자 하는 윈도우 창의 핸들을 넣어주면 된다. 
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);
}
