// MiniView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MiniView.h"
#include "MainFrm.h"
#include "MFCToolView.h"
#include "Terrain.h"

// CMiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView()
{

}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniView 그리기입니다.

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	GET_INSTANCE(CDevice)->Render_Begin(); 
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	if (nullptr == pMain)
		return; 
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1)); 
	if (nullptr == pView)
		return; 

	pView->m_pTerrain->MiniRender(); 
	GET_INSTANCE(CDevice)->Render_End(m_hWnd);
}


// CMiniView 진단입니다.

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniView 메시지 처리기입니다.
