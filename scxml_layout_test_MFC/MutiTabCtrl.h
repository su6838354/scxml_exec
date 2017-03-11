#ifndef MUTI_TAB_CTRL
#define MUTI_TAB_CTRL

#define HEIGHT 25

class CMutiTabCtrl : public CTabCtrl
{
public:
	CMutiTabCtrl();
	virtual ~CMutiTabCtrl();
protected:
	//{{AFX_MSG(CMutiTabCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif //MUTI_TAB_CTRL