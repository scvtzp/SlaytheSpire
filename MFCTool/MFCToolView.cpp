
// MFCToolView.cpp : CMFCToolView 適掘什税 姥薄
//

#include "stdafx.h"
// SHARED_HANDLERS澗 耕軒 左奄, 逐社毒 益顕 貢 伊事 琶斗 坦軒奄研 姥薄馬澗 ATL 覗稽詮闘拭辞 舛税拝 呪 赤生悟
// 背雁 覗稽詮闘人 庚辞 坪球研 因政馬亀系 背 掃艦陥.
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
	// 妊層 昔錫 誤敬脊艦陥.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMFCToolView 持失/社瑚

CMFCToolView::CMFCToolView()
	:m_pTerrain(nullptr)
{
	// TODO: 食奄拭 持失 坪球研 蓄亜杯艦陥.
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
	// TODO: CREATESTRUCT cs研 呪舛馬食 食奄拭辞
	//  Window 適掘什 暁澗 什展析聖 呪舛杯艦陥.

	return CScrollView::PreCreateWindow(cs);
}

// CMFCToolView 益軒奄

// 紬拷 莫縦生稽 敗呪亜 硲窒 吉陥. 
//OnDraw虞澗 敗呪澗 WM_PAINT 虞澗 五獣走亜 降持梅聖凶 硲窒鞠澗 敗呪. 
void CMFCToolView::OnDraw(CDC* pDC)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// 嬢恐暗 ? せせせ

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


// CMFCToolView 昔錫

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 奄沙旋昔 層搾
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 昔錫馬奄 穿拭 蓄亜 段奄鉢 拙穣聖 蓄亜杯艦陥.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 昔錫 板 舛軒 拙穣聖 蓄亜杯艦陥.
}


// CMFCToolView 遭舘

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // 巨獄益鞠走 省精 獄穿精 昔虞昔生稽 走舛桔艦陥.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView 五獣走 坦軒奄

// 持失切 硲窒 戚板 坦製 硲窒鞠澗 敗呪. 
void CMFCToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SetTimer(0, 0, nullptr); 
	// SetScrollSizes 什滴継 竺舛馬澗 敗呪 - 1.什滴継 骨是研 竺舛馬澗 昔切. MM_TEXT波漆舘是稽 域至馬畏陥. 
	//2. 什滴継 穿端 滴奄.  .
	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, TILEY * (TILECY / 2)));

	// TODO: 食奄拭 働呪鉢吉 坪球研 蓄亜 貢/暁澗 奄沙 適掘什研 硲窒杯艦陥.
	/*
	走榎 鎧亜 馬壱切 馬澗 闇. 
	MainFrame税 滴奄研 繕舛馬食 穿端旋昔 叔楳督析税 但 滴奄研 繕舛 馬澗 掻. 
	舘授 MainFrame税 滴奄研 WINCX, WINCY稽 限蓄惟鞠檎 酔軒亜 薄仙 左壱赤澗 view(Client)税 滴奄澗 WINCX, WINCY左陥 拙惟 蟹紳陥. 訊 ?
	殿砧軒 滴奄猿走 WINCX, WINCY 匂敗鞠奄 凶庚拭. 

	*/
	// 食奄辞 戚薦 MainFrame税 滴奄研 仙繕舛 拝 森舛. 
	//AfxGetApp - MainApp税 匂昔斗研 条嬢神澗 敗呪. 
	// GetMainWnd - 五昔 覗傾績 制亀酔 匂昔闘研 条嬢神澗 敗呪. 
	
	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	RECT rcMain = {}; 
	// 薄仙 五昔 覗傾績税 滴奄研 条嬢紳陥. 
	// 爽税 拝 依精 什滴鍵 疎妊 奄層. 
	// ex) 200, 200 是帖拭辞 持失戚鞠檎 left, top 戚 200, 200 戚 吉陥澗 社軒. 
	pMainFrame->GetWindowRect(&rcMain);
	// view税 滴奄研 条嬢臣 闇汽 view税 滴奄澗 適虞戚情闘 疎妊稽 条嬢身. 益掘辞 砧鯵税 疎妊研 限仲 爽切. 
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
	SetWindowPos - 制亀酔但税 滴奄研 仙繕舛背爽澗 敗呪. 
	1. 壕帖拝 制亀酔税 Z授辞拭 企廃 匂昔斗. null析井酔 闇球軒走 省畏陥. 益撹 据掘 益企稽 紫遂馬畏陥 聡 default 
	2.3. 是帖. xy
	4,5. 亜稽室稽 滴奄 
	6. 舛慶 授辞 . 走榎 隔嬢層 昔切澗 授辞研 郊荷走 省畏陥. 箸精 更 是帖 走舛 辛芝戚虞揮亜 推訓 依級 級嬢姶. 
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
	// TODO: 食奄拭 五獣走 坦軒奄 坪球研 蓄亜 貢/暁澗 奄沙葵聖 硲窒杯艦陥.

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
	// TODO: 食奄拭 五獣走 坦軒奄 坪球研 蓄亜 貢/暁澗 奄沙葵聖 硲窒杯艦陥.
	D3DXVECTOR3 vMouse = { float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f };
	if (GetAsyncKeyState(VK_LBUTTON))
		m_pTerrain->TileChange(vMouse, 20);

	//Invalidate(0);
	CScrollView::OnMouseMove(nFlags, point);
}


void CMFCToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 食奄拭 五獣走 坦軒奄 坪球研 蓄亜 貢/暁澗 奄沙葵聖 硲窒杯艦陥.
	Invalidate(0);
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMain->m_SecondSplitterWnd.GetPane(0, 0));
	pMiniView->Invalidate(0);
	CScrollView::OnTimer(nIDEvent);
}


// 焼艦
// 焼観汽
// すす 
// 焼艦暗窮? 
//せせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせ
// 獣献汽
