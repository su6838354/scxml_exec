// scxml_layout_test_MFCView.h : interface of the Cscxml_layout_test_MFCView class
//


#pragma once

#include "DrawGraph.h"
class Cscxml_layout_test_MFCView : public CView
{
protected: // create from serialization only
	Cscxml_layout_test_MFCView();
	DECLARE_DYNCREATE(Cscxml_layout_test_MFCView)

// Attributes
public:
	Cscxml_layout_test_MFCDoc* GetDocument() const;
	DrawGraph* m_DrawGraph;
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnDestroy();
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
//	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
//	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
//	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);

// Implementation
public:
	virtual ~Cscxml_layout_test_MFCView();
		afx_msg void OnPaint();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	
public:

public:
//	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
protected:
//	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
public:
//	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in scxml_layout_test_MFCView.cpp
inline Cscxml_layout_test_MFCDoc* Cscxml_layout_test_MFCView::GetDocument() const
   { return reinterpret_cast<Cscxml_layout_test_MFCDoc*>(m_pDocument); }
#endif

