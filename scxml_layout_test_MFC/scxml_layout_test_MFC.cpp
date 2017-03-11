// scxml_layout_test_MFC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "MainFrm.h"

#include "ChildFrm.h"
#include "scxml_layout_test_MFCDoc.h"
#include "scxml_layout_test_MFCView.h"
#include "../scxml_layout/ScxmlLayout.h"
#include "../scxml_model/ScxmlObject.h"
#include "../scxml_parser/ScxmlParser.h"
#include "scxml_layout_test_MFC.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cscxml_layout_test_MFCApp

BEGIN_MESSAGE_MAP(Cscxml_layout_test_MFCApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &Cscxml_layout_test_MFCApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, AddViews)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_APP_EXIT, &Cscxml_layout_test_MFCApp::OnAppExit)
END_MESSAGE_MAP()

void Cscxml_layout_test_MFCApp::AddViews()
{
	//1解析文件
	this->m_ScxmlParser=new ScxmlParser;
	ScxmlObject *myScxmlObject=	m_ScxmlParser->GetScxmlObject("scxml.xml");
	//invoke scxmllayout
	this->m_ScxmlLayout=new ScxmlLayout;
	RECT rc;
	GetClientRect( AfxGetMainWnd()->m_hWnd,&rc);
	m_ScxmlLayout->setScxmlObject(myScxmlObject,rc.right,rc.bottom);
	ScxmlLayout* tmpLayout=m_ScxmlLayout;
	while(tmpLayout)
	{
		//2根据layout数量创建相应的document
		Cscxml_layout_test_MFCDoc* pdocTmp=(Cscxml_layout_test_MFCDoc*)this->m_pDocTemplate->CreateNewDocument();
		pdocTmp->m_Layout=tmpLayout;
		CFrameWnd* pframe=this->m_pDocTemplate->CreateNewFrame(pdocTmp,NULL);
		pdocTmp->OnNewDocument();
		this->m_pDocTemplate->InitialUpdateFrame(pframe,pdocTmp,TRUE);
		
		//3解析的数据绑定到documen中
		POSITION po=pdocTmp->GetFirstViewPosition();
		CView* cv=pdocTmp->GetNextView(po);
		CMainFrame* CF=(CMainFrame*)this->m_pMainWnd;
		(CF->m_WndHash)[tmpLayout->layout_Id]=cv;
		tmpLayout=tmpLayout->Next;
	}
}


// Cscxml_layout_test_MFCApp construction

Cscxml_layout_test_MFCApp::Cscxml_layout_test_MFCApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	this->m_ScxmlLayout=NULL;
	this->m_ScxmlParser=NULL;
}


// The one and only Cscxml_layout_test_MFCApp object

Cscxml_layout_test_MFCApp theApp;


// Cscxml_layout_test_MFCApp initialization


BOOL Cscxml_layout_test_MFCApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	
	m_pDocTemplate = new CMultiDocTemplate(IDR_scxml_layout_teTYPE,
		RUNTIME_CLASS(Cscxml_layout_test_MFCDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(Cscxml_layout_test_MFCView));
	if (!m_pDocTemplate)
		return FALSE;
	AddDocTemplate(m_pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	//if (!ProcessShellCommand(cmdInfo))
	//	return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void Cscxml_layout_test_MFCApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// Cscxml_layout_test_MFCApp message handlers


void Cscxml_layout_test_MFCApp::OnAppExit()
{
	// TODO: Add your command handler code here
}

Cscxml_layout_test_MFCApp::~Cscxml_layout_test_MFCApp()
{
	delete this->m_ScxmlParser;
	this->m_ScxmlParser=NULL;
	delete this->m_ScxmlLayout;
	this->m_ScxmlLayout=NULL;
}