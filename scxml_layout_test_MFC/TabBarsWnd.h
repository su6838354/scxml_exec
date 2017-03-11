#ifndef AFX_TABSWINDOW_H
#define AFX_TABSWINDOW_H

#include "MutiTabCtrl.h"

class CTabBarsWnd : public CWnd
{
public:
	CTabBarsWnd();
	virtual ~CTabBarsWnd();
	CMutiTabCtrl		m_TabCtrl;
	virtual BOOL DestroyWindow();
public:
	void SetTabFont(CFont *pFont);

	//Attributes

	int		GetItemCount() {return m_TabCtrl.GetItemCount();}
	int		GetCurSel() { return m_TabCtrl.GetCurSel(); }
	int		SetCurSel(int nItem);
	// Operations

	int		InsertItem(int nItem, CString sText, CView* view);
	int		DeleteItem(int nItem);
	void	DeleteAllItems();
	void	GetItemData(int index, CView*& view);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT, int, int);
	DECLARE_MESSAGE_MAP();
	CFont		*m_pFont;
	CImageList    m_TabImages;
	CRect         m_RectGripper;
public:

};

#endif // AFX_TABSWINDOW_H