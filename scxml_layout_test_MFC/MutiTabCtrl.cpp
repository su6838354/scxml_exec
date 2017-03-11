#include "StdAfx.h"
#include "MutiTabCtrl.h"
#include "MainFrm.h"

BEGIN_MESSAGE_MAP(CMutiTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CMyTabCtrl)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMutiTabCtrl::CMutiTabCtrl()
{

}

CMutiTabCtrl::~CMutiTabCtrl()
{

}

void CMutiTabCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CTabCtrl::OnLButtonDown(nFlags, point);
	int tabCurrent = GetCurFocus();
	if(tabCurrent >= 0)
	{
		CMainFrame* cF=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		cF->SetCurView(tabCurrent);
	}
}