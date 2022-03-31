
// MFCToolView.cpp : CMFCToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFCTool.h"
#endif

#include "MFCToolDoc.h"
#include "MFCToolView.h"
#include "SingleTex.h"
#include "Terrain.h"
#include "MainFrm.h"
#include "MiniView.h"
#include "MyForm.h"
HWND g_hWND; 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCToolView

IMPLEMENT_DYNCREATE(CMFCToolView, CScrollView)

BEGIN_MESSAGE_MAP(CMFCToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMFCToolView ����/�Ҹ�

CMFCToolView::CMFCToolView()
	:m_pTerrain(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_fAngle = 0.f;
	m_iChangeSpeed = 1;
	m_iColor = 0; 

}

CMFCToolView::~CMFCToolView()
{
	Safe_Delete(m_pTerrain); 

	GET_INSTANCE(CTextureMgr)->Destroy_Instance();
	CDevice::Destroy_Instance(); 
}

BOOL CMFCToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CMFCToolView �׸���

// �ݹ� �������� �Լ��� ȣ�� �ȴ�. 
//OnDraw��� �Լ��� WM_PAINT ��� �޽����� �߻������� ȣ��Ǵ� �Լ�. 
void CMFCToolView::OnDraw(CDC* pDC)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// ��� ? ������

// 	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Terrain", L"Tile",2 );
// 
// 	float fCenterX = pTexInfo->tImageInfo.Width / 2.f; 
// 	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f; 
// 
// 	D3DXMATRIX matScale, matRotZ, matTrans, matWorld; 
// 	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f); 
// 	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
// 	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f); 
// 
// 	matWorld = matScale * matRotZ * matTrans;
// 	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
// 
// 	CDevice::Get_Instance()->Render_Begin();
// 	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
// 		nullptr,
// 		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
// 		nullptr,
// 		D3DCOLOR_ARGB(255, 255, 255, 255));
// 
// 	CDevice::Get_Instance()->Render_End(); 
	GET_INSTANCE(CDevice)->Render_Begin(); 
	m_pTerrain->Render();
	GET_INSTANCE(CDevice)->Render_End(); 
}


// CMFCToolView �μ�

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFCToolView ����

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView �޽��� ó����

// ������ ȣ�� ���� ó�� ȣ��Ǵ� �Լ�. 
void CMFCToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SetTimer(0, 0, nullptr); 
	// SetScrollSizes ��ũ�� �����ϴ� �Լ� - 1.��ũ�� ������ �����ϴ� ����. MM_TEXT�ȼ������� ����ϰڴ�. 
	//2. ��ũ�� ��ü ũ��.  .
	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, TILEY * (TILECY / 2)));

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	/*
	���� ���� �ϰ��� �ϴ� ��. 
	MainFrame�� ũ�⸦ �����Ͽ� ��ü���� ���������� â ũ�⸦ ���� �ϴ� ��. 
	�ܼ� MainFrame�� ũ�⸦ WINCX, WINCY�� ���߰ԵǸ� �츮�� ���� �����ִ� view(Client)�� ũ��� WINCX, WINCY���� �۰� ���´�. �� ?
	�µθ� ũ����� WINCX, WINCY ���ԵǱ� ������. 

	*/
	// ���⼭ ���� MainFrame�� ũ�⸦ ������ �� ����. 
	//AfxGetApp - MainApp�� �����͸� ������ �Լ�. 
	// GetMainWnd - ���� ������ ������ ����Ʈ�� ������ �Լ�. 
	
	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	RECT rcMain = {}; 
	// ���� ���� �������� ũ�⸦ ���´�. 
	// ���� �� ���� ��ũ�� ��ǥ ����. 
	// ex) 200, 200 ��ġ���� �����̵Ǹ� left, top �� 200, 200 �� �ȴٴ� �Ҹ�. 
	pMainFrame->GetWindowRect(&rcMain);
	// view�� ũ�⸦ ���� �ǵ� view�� ũ��� Ŭ���̾�Ʈ ��ǥ�� ����. �׷��� �ΰ��� ��ǥ�� ���� ����. 
	::SetRect(&rcMain, 0, 0, rcMain.right - rcMain.left, rcMain.bottom - rcMain.top); 
	// rcMain = { 200, 200, 1200, 1200} 
	RECT rcView = {}; 
	GetClientRect(&rcView);
	int iWidth = rcMain.right - rcView.right ; 
	int iHeight = rcMain.bottom - rcView.bottom; 

	CSize tSize;
	GetScrollBarSizes(tSize);

	pMainFrame->SetWindowPos(nullptr, 0, 0, WINCX + iWidth , WINCY + iHeight , SWP_NOZORDER);
	/*
	SetWindowPos - ������â�� ũ�⸦ ���������ִ� �Լ�. 
	1. ��ġ�� �������� Z������ ���� ������. null�ϰ�� �ǵ帮�� �ʰڴ�. �׳� ���� �״�� ����ϰڴ� �� default 
	2.3. ��ġ. xy
	4,5. ���μ��� ũ�� 
	6. ���� ���� . ���� �־��� ���ڴ� ������ �ٲ��� �ʰڴ�. Ȥ�� �� ��ġ ���� �ɼ��̶���� �䷱ �͵� ��. 
	*/


	g_hWND = m_hWnd; 
	if (FAILED(GET_INSTANCE(CDevice)->InitDevice()))
	{
		AfxMessageBox(L"InitDevice Failed"); 
		return; 
	}
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Cube.png", L"Cube");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Stage/Terrain/Tile/Tile%d.png", L"Terrain", L"Tile", 38);

	if (nullptr == m_pTerrain)
	{
		m_pTerrain = new CTerrain; 
		if (FAILED(m_pTerrain->Initialize()))
		{
			AfxMessageBox(L"Terrain Initialize Failed"); 
			return; 
		}
		m_pTerrain->Set_View(this);
	}
}


void CMFCToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_SecondSplitterWnd.GetPane(1, 0));
	CMapTool* pMapTool = &(pMyForm->m_MapTool);
	D3DXVECTOR3 vMouse = { float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f };
	m_pTerrain->TileChange(vMouse, BYTE(pMapTool->m_dwDrawID));
	//InvalidateRect(nullptr, true);
	//Invalidate(0);

// 	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
// 	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMain->m_SecondSplitterWnd.GetPane(0, 0)); 
// 	pMiniView->Invalidate(0);

	CScrollView::OnLButtonDown(nFlags, point);
}


void CMFCToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	D3DXVECTOR3 vMouse = { float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f };
	if (GetAsyncKeyState(VK_LBUTTON))
		m_pTerrain->TileChange(vMouse, 20);

	//Invalidate(0);
	CScrollView::OnMouseMove(nFlags, point);
}


void CMFCToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	Invalidate(0);
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMain->m_SecondSplitterWnd.GetPane(0, 0));
	pMiniView->Invalidate(0);
	CScrollView::OnTimer(nIDEvent);
}


// �ƴ�
// �ƴѵ�
// ���� 
// �ƴϰŵ�? 
//������������������������������������������������������������������������
// �ø���
