
// MFCToolView.cpp : CMFCToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMFCToolView 생성/소멸

CMFCToolView::CMFCToolView()
	:m_pTerrain(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.
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
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMFCToolView 그리기

// 콜백 형식으로 함수가 호출 된다. 
//OnDraw라는 함수는 WM_PAINT 라는 메시지가 발생했을때 호출되는 함수. 
void CMFCToolView::OnDraw(CDC* pDC)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// 어떤거 ? ㅋㅋㅋ

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


// CMFCToolView 인쇄

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCToolView 진단

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView 메시지 처리기

// 생성자 호출 이후 처음 호출되는 함수. 
void CMFCToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SetTimer(0, 0, nullptr); 
	// SetScrollSizes 스크롤 설정하는 함수 - 1.스크롤 범위를 설정하는 인자. MM_TEXT픽셀단위로 계산하겠다. 
	//2. 스크롤 전체 크기.  .
	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, TILEY * (TILECY / 2)));

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	/*
	지금 내가 하고자 하는 건. 
	MainFrame의 크기를 조정하여 전체적인 실행파일의 창 크기를 조정 하는 중. 
	단순 MainFrame의 크기를 WINCX, WINCY로 맞추게되면 우리가 현재 보고있는 view(Client)의 크기는 WINCX, WINCY보다 작게 나온다. 왜 ?
	태두리 크기까지 WINCX, WINCY 포함되기 때문에. 

	*/
	// 여기서 이제 MainFrame의 크기를 재조정 할 예정. 
	//AfxGetApp - MainApp의 포인터를 얻어오는 함수. 
	// GetMainWnd - 메인 프레임 윈도우 포인트를 얻어오는 함수. 
	
	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	RECT rcMain = {}; 
	// 현재 메인 프레임의 크기를 얻어온다. 
	// 주의 할 것은 스크린 좌표 기준. 
	// ex) 200, 200 위치에서 생성이되면 left, top 이 200, 200 이 된다는 소리. 
	pMainFrame->GetWindowRect(&rcMain);
	// view의 크기를 얻어올 건데 view의 크기는 클라이언트 좌표로 얻어옴. 그래서 두개의 좌표를 맞춰 주자. 
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
	SetWindowPos - 윈도우창의 크기를 재조정해주는 함수. 
	1. 배치할 윈도우의 Z순서에 대한 포인터. null일경우 건드리지 않겠다. 그냥 원래 그대로 사용하겠다 즉 default 
	2.3. 위치. xy
	4,5. 가로세로 크기 
	6. 정렬 순서 . 지금 넣어준 인자는 순서를 바꾸지 않겠다. 혹은 뭐 위치 지정 옵션이라던가 요런 것들 들어감. 
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	D3DXVECTOR3 vMouse = { float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f };
	if (GetAsyncKeyState(VK_LBUTTON))
		m_pTerrain->TileChange(vMouse, 20);

	//Invalidate(0);
	CScrollView::OnMouseMove(nFlags, point);
}


void CMFCToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Invalidate(0);
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMain->m_SecondSplitterWnd.GetPane(0, 0));
	pMiniView->Invalidate(0);
	CScrollView::OnTimer(nIDEvent);
}


// 아니
// 아닌데
// ㅉㅉ 
// 아니거든? 
//ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ
// 시른데
