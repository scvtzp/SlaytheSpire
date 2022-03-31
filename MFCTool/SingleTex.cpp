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
	// �̹����� �ҷ��;���. 
	//�׸� �ϵ� �� ����Ǿ� ����. 
	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_tTexInfo.tImageInfo)))
	{
		wstring wstrFailed = wstrFilePath + L"�Ⱦ�ٺٿ��������߳������������.Load ImageInfo Failed "; 
		AfxMessageBox(wstrFailed.c_str()); 
		return E_FAIL; 
	}
	// �����̽ð���������Ƽ��...��������
	if (FAILED(D3DXCreateTextureFromFileEx(CDevice::Get_Instance()->Get_Device() // ��ġ�� �����ϴ� �İ�ü�� �䱸 
	,wstrFilePath.c_str()// ������ ��� 
	, m_tTexInfo.tImageInfo.Width // ����
	,m_tTexInfo.tImageInfo.Height// ����
	,m_tTexInfo.tImageInfo.MipLevels
	,0// 0 ����Ʈ�� ����ϰڴ�. 
	,m_tTexInfo.tImageInfo.Format //�׸��� ���� ����. 
	, D3DPOOL_MANAGED // �޸� ������ ��� ����ϰڳĶ�� ����. 
		// ���� �־��� ���ڴ� �׷���ī���� �޸� ������ ����ϵ� ������ ������� ���� ����Ѵ�. 
	,D3DX_DEFAULT// �̹��� ����. 
	,D3DX_DEFAULT// mipleveles �� ��� ����� ���ΰ�. ����Ʈ�� ����ϰԵ�. 
	,0// ������ ����. 
	,nullptr// �̹��� ������ �䱸 
	,nullptr// �ȷ�Ʈ - ������ ������ ���� ������ �ʴ� ���� .
	,&m_tTexInfo.pTexture// ���� ������� pTexture�� ����. �̰� TexInfo�ȿ� ���� LPDirec3dTexture9 �̶�� ��ü 
		)))
	{
		AfxMessageBox(L"��ձ׸��������Ϲ¤�"); 
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
