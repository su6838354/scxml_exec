// scxml_layout_test_MFCView.cpp : implementation of the Cscxml_layout_test_MFCView class
//

#include "stdafx.h"
#include "scxml_layout_test_MFC.h"


#include "scxml_layout_test_MFCDoc.h"
#include "scxml_layout_test_MFCView.h"
#include "MainFrm.h"
#include <gdiplus.h> 
#pragma comment( lib, "gdiplus.lib" )
using namespace Gdiplus;
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif


// Cscxml_layout_test_MFCView

IMPLEMENT_DYNCREATE(Cscxml_layout_test_MFCView, CView)

BEGIN_MESSAGE_MAP(Cscxml_layout_test_MFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_PAINT()
//	ON_WM_PARENTNOTIFY()
ON_WM_SIZE()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDBLCLK()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// Cscxml_layout_test_MFCView construction/destruction

Cscxml_layout_test_MFCView::Cscxml_layout_test_MFCView()
{
	// TODO: add construction code here
	m_DrawGraph=new DrawGraph;
}

Cscxml_layout_test_MFCView::~Cscxml_layout_test_MFCView()
{
}

BOOL Cscxml_layout_test_MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cscxml_layout_test_MFCView drawing

void Cscxml_layout_test_MFCView::OnDraw(CDC* /*pDC*/)
{
	Cscxml_layout_test_MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// Cscxml_layout_test_MFCView printing

//BOOL Cscxml_layout_test_MFCView::OnPreparePrinting(CPrintInfo* pInfo)
//{
//	// default preparation
//	return DoPreparePrinting(pInfo);
//}

//void Cscxml_layout_test_MFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//{
//	// TODO: add extra initialization before printing
//}

//void Cscxml_layout_test_MFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//{
//	// TODO: add cleanup after printing
//}


// Cscxml_layout_test_MFCView diagnostics

#ifdef _DEBUG
void Cscxml_layout_test_MFCView::AssertValid() const
{
	CView::AssertValid();
}

void Cscxml_layout_test_MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cscxml_layout_test_MFCDoc* Cscxml_layout_test_MFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cscxml_layout_test_MFCDoc)));
	return (Cscxml_layout_test_MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// Cscxml_layout_test_MFCView message handlers

void Cscxml_layout_test_MFCView::OnDestroy()
{
	// TODO: Add your message handler code here
	CView::OnDestroy();
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->DeleteView(this);
}

void Cscxml_layout_test_MFCView::OnInitialUpdate()
{
	// TODO: Add your specialized code here and/or call the base class
	CView::OnInitialUpdate();
	CString aCString = CString(_T("A string"));
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->AddView(GetDocument()->m_Layout->layout_Id,this, aCString);
}

void Cscxml_layout_test_MFCView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: Add your specialized code here and/or call the base class
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
	if(bActivate)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->OnActivateView(pActivateView);
}


//void Cscxml_layout_test_MFCView::OnParentNotify(UINT message, LPARAM lParam)
//{
//	CView::OnParentNotify(message, lParam);
//
//	// TODO: Add your message handler code here
//}

//void Cscxml_layout_test_MFCView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
//{
//	// TODO: Add your specialized code here and/or call the base class
//
//
//}

//void Cscxml_layout_test_MFCView::OnSize(UINT nType, int cx, int cy)
//{
//	CView::OnSize(nType, cx, cy);
//
//	// TODO: Add your message handler code here
//}

void Cscxml_layout_test_MFCView::OnPaint()
{
	Cscxml_layout_test_MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	//Cscxml_layout_test_MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	ULONG_PTR m_gdiplusToken;
	GdiplusStartupInput m_gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);

	CWindowDC dc2(this);//this为当前窗口指针
	HDC hDC2=dc2.GetSafeHdc();
	RECT rc;
	GetClientRect(&rc);

	//TODO:
	//invoke draw
	//(this->GetSafeHwnd(),TRUE);
	m_DrawGraph->m_Graphics=new Graphics(hDC2);
	m_DrawGraph->m_ScxmlLayout=pDoc->m_Layout;


	HWND hwnd=GetSafeHwnd();
	RECT rct;
	GetClientRect(&rct);
	m_DrawGraph->m_ScxmlLayout->Resize(rc.right,rc.bottom);
	m_DrawGraph->DrawGraphAll();
}

void Cscxml_layout_test_MFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnMouseMove(nFlags, point);
	this->m_DrawGraph->Selected(point.x,point.y);//更新DrawGraph中的图形
	Invalidate(false);
}

void Cscxml_layout_test_MFCView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CView::OnLButtonDblClk(nFlags, point);
	//skip to 
	if (this->m_DrawGraph->m_SelectedRectId==NULL)
	{
		return;
	}
	else
	{
		//根据Id找到对于的wnd，并activity
		hash_map <const char*, CView*>::const_iterator hm_it;
		CMainFrame *pMain=(CMainFrame*)AfxGetApp()->m_pMainWnd;  
		Cscxml_layout_test_MFCApp* ap=(Cscxml_layout_test_MFCApp*)AfxGetApp()->m_pMainWnd;
		int num=pMain->m_WndHash.count(this->m_DrawGraph->m_SelectedRectId);
		if (num==0)
		{
			return;
		}
		hm_it=pMain->m_WndHash.find(this->m_DrawGraph->m_SelectedRectId);
		CWnd* pa=hm_it->second->GetParentFrame();
		pMain->MDIActivate(pa);
	}
}

void Cscxml_layout_test_MFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);

}
