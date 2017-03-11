// MainFrm.h : interface of the CMainFrame class
//


#pragma once
#if !defined(AFX_MAINFRM_H__DEF5919C_BAAF_491E_8D41_A9655E68E3EF__INCLUDED_)
#define AFX_MAINFRM_H__DEF5919C_BAAF_491E_8D41_A9655E68E3EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabBarsWnd.h"
#include <hash_map>
using namespace std;
using namespace stdext;
struct CharLess:public binary_function<const char*,const char*,bool>
{
public:
	result_type operator()(const first_argument_type& _Left,const second_argument_type& _Right) const
	{
		return(stricmp(_Left, _Right) < 0 ? true : false);  
	}
};

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
	BOOL AddView(CString sLabel, CView *pView, CString sTooltip);
	BOOL DeleteView(CView *pView);
	BOOL OnActivateView(CView *pView);
	BOOL SetCurView(int nNdx);

// Attributes
public:
	hash_map<const char*,CView*,hash_compare<const char*,CharLess>> m_WndHash;
// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void RecalcLayout(BOOL bNotify);
// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CTabBarsWnd m_TabBarsWnd;


// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};
#endif // !defined(AFX_MAINFRM_H__DEF5919C_BAAF_491E_8D41_A9655E68E3EF__INCLUDED_)

