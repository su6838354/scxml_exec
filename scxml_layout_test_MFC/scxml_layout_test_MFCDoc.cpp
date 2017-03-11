// scxml_layout_test_MFCDoc.cpp : implementation of the Cscxml_layout_test_MFCDoc class
//

#include "stdafx.h"
#include "scxml_layout_test_MFC.h"

#include "scxml_layout_test_MFCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cscxml_layout_test_MFCDoc

IMPLEMENT_DYNCREATE(Cscxml_layout_test_MFCDoc, CDocument)

BEGIN_MESSAGE_MAP(Cscxml_layout_test_MFCDoc, CDocument)
END_MESSAGE_MAP()


// Cscxml_layout_test_MFCDoc construction/destruction

Cscxml_layout_test_MFCDoc::Cscxml_layout_test_MFCDoc()
{
	// TODO: add one-time construction code here
	m_Layout=NULL;

}

Cscxml_layout_test_MFCDoc::~Cscxml_layout_test_MFCDoc()
{
}

BOOL Cscxml_layout_test_MFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Cscxml_layout_test_MFCDoc serialization

void Cscxml_layout_test_MFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// Cscxml_layout_test_MFCDoc diagnostics

#ifdef _DEBUG
void Cscxml_layout_test_MFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cscxml_layout_test_MFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cscxml_layout_test_MFCDoc commands

BOOL Cscxml_layout_test_MFCDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here

	return TRUE;
}
