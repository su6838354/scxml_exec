// scxml_layout_test_MFC.h : main header file for the scxml_layout_test_MFC application
//
#pragma once
#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "../scxml_layout/ScxmlLayout.h"
#include "../scxml_parser/ScxmlParser.h"

// Cscxml_layout_test_MFCApp:
// See scxml_layout_test_MFC.cpp for the implementation of this class
//

class Cscxml_layout_test_MFCApp : public CWinApp
{

public:
	Cscxml_layout_test_MFCApp();
	~Cscxml_layout_test_MFCApp();
CMultiDocTemplate* m_pDocTemplate;

// Overrides
public:
	virtual BOOL InitInstance();

	//my method
	void AddViews();
// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	ScxmlParser* m_ScxmlParser;
	ScxmlLayout* m_ScxmlLayout;
	afx_msg void OnAppExit();
};

extern Cscxml_layout_test_MFCApp theApp;