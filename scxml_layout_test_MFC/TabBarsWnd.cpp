#include "StdAfx.h"

#include "TabBarsWnd.h"

#define ID_TAB          1000

BEGIN_MESSAGE_MAP(CTabBarsWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

CTabBarsWnd::CTabBarsWnd()
{
	m_pFont = NULL;
}

int CTabBarsWnd::DestroyWindow()
{
	return 0;
}

CTabBarsWnd::~CTabBarsWnd(void)
{
	if (m_pFont != NULL)
	{
		m_pFont->DeleteObject();
		delete m_pFont;
	}
	DestroyWindow();
}

int CTabBarsWnd::SetCurSel(int index)
{
	return m_TabCtrl.SetCurSel(index);
}

int CTabBarsWnd::InsertItem(int nItem, CString sText, CView* view)
{
	m_TabCtrl.InsertItem(TCIF_TEXT | TCIF_PARAM, nItem, sText, NULL, (LPARAM)view);
	Invalidate(TRUE);
	return nItem;
}

int CTabBarsWnd::DeleteItem(int nItem)
{
	m_TabCtrl.DeleteItem(nItem);
	return 0;
}

void CTabBarsWnd::DeleteAllItems()
{
	m_TabCtrl.DeleteAllItems();
}

void CTabBarsWnd::GetItemData(int index, CView*& view)
{
	if(index < 0)
		return;

	TCITEM pTabCtrlItem;
	m_TabCtrl.GetItem(index, &pTabCtrlItem);
	view = (CView*)pTabCtrlItem.lParam;
}

int CTabBarsWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_TabImages.Create(16, 16, ILC_COLOR8 | ILC_MASK, 10, 5);

	DWORD dwSty = TCS_TABS | TCS_FIXEDWIDTH | WS_CHILD | WS_VISIBLE;
	SetRedraw(FALSE);
	m_TabCtrl.Create(dwSty, CRect(0, 0, 400, 300), this, ID_TAB);
	DWORD dwExStyle = m_TabCtrl.GetExtendedStyle();
	m_TabCtrl.SetExtendedStyle(dwExStyle  | TCS_EX_FLATSEPARATORS);
	// use a font smaller than default
	CFont *pFont = new CFont();
	pFont->CreatePointFont(80, _T("MS Sans Serif"));
	SetTabFont(pFont);
	m_TabCtrl.SetPadding(CSize(2, 2));
	m_TabCtrl.SetFont(pFont, TRUE);
	SetRedraw(TRUE);
	RedrawWindow();
	m_TabCtrl.SetImageList(&m_TabImages);
	return 0;
}

void CTabBarsWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	if(IsWindow(m_hWnd))
	{
		m_TabCtrl.MoveWindow(0, 0, cx, cy);
	}
}

void CTabBarsWnd::SetTabFont(CFont *pFont)
{
	if (m_pFont != NULL)
	{
		m_pFont->DeleteObject();
		delete m_pFont;
	}

	m_pFont = pFont;
	SetFont(m_pFont, FALSE);
	m_TabCtrl.SetFont(m_pFont, TRUE);
	CDC cDC;
	cDC.CreateCompatibleDC(NULL);
	CFont *pOldFont = cDC.SelectObject(m_pFont);
	cDC.SelectObject(pOldFont);
	cDC.DeleteDC();
}

















