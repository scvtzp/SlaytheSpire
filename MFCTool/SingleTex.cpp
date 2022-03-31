#include "stdafx.h"
#include "SingleTex.h"


CSingleTex::CSingleTex()
{
	ZeroMemory(&m_tTexInfo, sizeof(TEXINFO));
}


CSingleTex::~CSingleTex()
{
	Release();
}

HRESULT CSingleTex::InsertTexture(const wstring & wstrFilePath, const wstring & wstrStateKey /*= L""*/, const int & rCount /*= 0*/)
{
	// 이미지를 불러와야함. 
	//그림 하드 에 저장되어 있음. 
	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_tTexInfo.tImageInfo)))
	{
		wstring wstrFailed = wstrFilePath + L"싫어다붙여서쓸꺼야나이제띄어쓰기안함.Load ImageInfo Failed "; 
		AfxMessageBox(wstrFailed.c_str()); 
		return E_FAIL; 
	}
	// 다음이시간에투비컨티뉴...ㅋㅋㅋㅋ
	if (FAILED(D3DXCreateTextureFromFileEx(CDevice::Get_Instance()->Get_Device() // 장치를 제어하는 컴객체를 요구 
	,wstrFilePath.c_str()// 파일의 경로 
	, m_tTexInfo.tImageInfo.Width // 가로
	,m_tTexInfo.tImageInfo.Height// 세로
	,m_tTexInfo.tImageInfo.MipLevels
	,0// 0 디폴트로 사용하겠다. 
	,m_tTexInfo.tImageInfo.Format //그림의 포멧 형식. 
	, D3DPOOL_MANAGED // 메모리 공간을 어딜 사용하겠냐라는 인자. 
		// 지금 넣어준 인자는 그래픽카드의 메모리 공간을 사용하되 공간이 모질라면 램을 사용한다. 
	,D3DX_DEFAULT// 이미지 필터. 
	,D3DX_DEFAULT// mipleveles 을 어떻게 사용할 것인가. 디폴트로 사용하게따. 
	,0// 제거할 색상. 
	,nullptr// 이미지 정보를 요구 
	,nullptr// 팔레트 - 예전엔 썼으나 요즘엔 쓰이지 않는 인자 .
	,&m_tTexInfo.pTexture// 최종 결과물이 pTexture에 들어간다. 이건 TexInfo안에 보면 LPDirec3dTexture9 이라는 객체 
		)))
	{
		AfxMessageBox(L"우왕그림못생성하뮤ㅠ"); 
		return E_FAIL;
	}

	return S_OK;
}

void CSingleTex::Release()
{
	if (m_tTexInfo.pTexture)
	{
		m_tTexInfo.pTexture->Release();
	}
}

TEXINFO * CSingleTex::Get_TexInfo(const wstring & wstrStateKey /*= L""*/, const int & rCount/* = 0*/)
{
	return &m_tTexInfo;
}
