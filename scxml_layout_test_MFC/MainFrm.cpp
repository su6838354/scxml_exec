// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "scxml_layout_test_MFC.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here

}

CMainFrame::~CMainFrame()
{
}
BOOL CMainFrame::AddView(CString sLabel, CView *pView, CString sTooltip)
{	
	int ndx = m_TabBarsWnd.InsertItem(m_TabBarsWnd.GetItemCount(),sLabel,pView);
	if(ndx>=0)
	{
		m_TabBarsWnd.SetCurSel(ndx);
		//m_TabBarsWnd.SetItemTooltipText(ndx,sTooltip);
		CFrameWnd* wnd=pView->GetParentFrame();
		MDIActivate(wnd);
		return TRUE;
	}
	return FALSE;
}

BOOL CMainFrame::DeleteView(CView *pView)
{
	for(int i=0; i<m_TabBarsWnd.GetItemCount(); i++)
	{
		CView* view;
		m_TabBarsWnd.GetItemData(i,view);
		if(view == pView)
		{
			m_TabBarsWnd.DeleteItem(i);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMainFrame::OnActivateView(CView *pView)
{
	for(int i=0; i<m_TabBarsWnd.GetItemCount(); i++)
	{
		CView* view;
		m_TabBarsWnd.GetItemData(i,view);
		if(view == pView)
		{
			if(i!=m_TabBarsWnd.GetCurSel())
				m_TabBarsWnd.SetCurSel(i);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMainFrame::SetCurView(int nNdx)
{
	if(nNdx >= 0 && nNdx < m_TabBarsWnd.GetItemCount())
	{
		if(nNdx != m_TabBarsWnd.GetCurSel())
			m_TabBarsWnd.SetCurSel(nNdx);
		CView* view=NULL;
		m_TabBarsWnd.GetItemData(nNdx, view);
		CWnd* pa=view->GetParentFrame();
		MDIActivate(pa);
		return TRUE;
	}
	return FALSE;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	CRect cRect;

	m_TabBarsWnd.Create(NULL, "TabBar",WS_CHILD | WS_CLIPSIBLINGS|CBRS_TOOLTIPS|CBRS_SIZE_DYNAMIC, cRect, this, IDD_TAB_CONTROL_BAR);

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

void CMainFrame::RecalcLayout(BOOL bNotify)
{
	CMDIFrameWnd::RecalcLayout(bNotify);
	CRect rect;
	CWnd * pMDIClientWnd = CWnd::FromHandle(CMDIFrameWnd::m_hWndMDIClient);
	pMDIClientWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	if(IsWindow(m_TabBarsWnd))
		m_TabBarsWnd.MoveWindow(rect.left, rect.top - HEIGHT, rect.Width(), HEIGHT);

	m_bInRecalcLayout = FALSE; 
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers



