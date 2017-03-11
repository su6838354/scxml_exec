// scxml_layout_test_MFCDoc.h : interface of the Cscxml_layout_test_MFCDoc class
//


#pragma once
#include "../scxml_layout//ScxmlLayout.h"

class Cscxml_layout_test_MFCDoc : public CDocument 
{
public: // create from serialization only
	Cscxml_layout_test_MFCDoc();
	DECLARE_DYNCREATE(Cscxml_layout_test_MFCDoc)

// Attributes
public:
	ScxmlLayout* m_Layout;
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~Cscxml_layout_test_MFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};


