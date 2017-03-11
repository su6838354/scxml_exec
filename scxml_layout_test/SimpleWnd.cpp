//////////////////////////////////////////////////////////////////////
// SimpleWnd.cpp: implementation of the CSimpleWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SimpleWnd.h"
#include "stdlib.h"

//=====================================================================
//Macro define
#define WND_NAME        TEXT("SimpleWnd_name")
#define WND_CLASS        TEXT("SimpleWnd_cls")
//=====================================================================
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSimpleWnd::CSimpleWnd():
m_hWnd(NULL),
m_hWndParent(NULL),
m_hInst(NULL)
{
	this->m_DrawGraph=new DrawGraph;
	
}

CSimpleWnd::~CSimpleWnd()
{

}

//----------------------------------------------------------------------
//Description:
//    Initialize
//----------------------------------------------------------------------
BOOL CSimpleWnd::RegisterWnd(HINSTANCE hInst, HWND hWndParent)
{
    static bool s_bRegistered = FALSE;
    WNDCLASS wc;

    if(s_bRegistered == FALSE)
    {
        wc.style         = CS_HREDRAW | CS_VREDRAW;//0;
        wc.lpfnWndProc   = (WNDPROC)CSimpleWnd::StaticWndProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = m_hInst;
        wc.hIcon         = NULL; 
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)GetSysColorBrush(COLOR_WINDOW);
        wc.lpszMenuName  = NULL;
        wc.lpszClassName = WND_CLASS;
        
        if (RegisterClass(&wc))
        {
            s_bRegistered = TRUE;
        }
    }
    return s_bRegistered;

    /*
    WNDCLASS        wc;
    wc.style         = 0;
    wc.lpfnWndProc   = (WNDPROC)CSimpleWnd::StaticWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = m_hInst;
    wc.hIcon         = NULL; 
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetSysColorBrush(COLOR_WINDOW);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = WND_CLASS;
    
    if (RegisterClass(&wc) == FALSE)
    {
        return FALSE;
    }
    

    return TRUE;
    */
}

//----------------------------------------------------------------------
//Description: 根据点击的内容获取相应的id(char*),展示出对应的窗口
//    Static WndProc wrapper and actual WndProc
//
//----------------------------------------------------------------------
LRESULT CSimpleWnd::StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    CSimpleWnd *pObject = (CSimpleWnd*)GetWindowLong(hWnd, GWL_USERDATA);

    if(pObject)
    {
        return pObject->WndProc(hWnd,msg,wParam,lParam);
    }
    else
    {
        return DefWindowProc(hWnd,msg,wParam,lParam);
    }
}



//----------------------------------------------------------------------
//Description:
//    Actual WndProc
//
//----------------------------------------------------------------------
//LRESULT CSimpleWnd::WndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
//{
//	//HDC hdc;
//	//PAINTSTRUCT ps;
//	switch (wMsg)
//	{
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	case  WM_PAINT:
//		//hdc=BeginPaint(hWnd,&ps);
//		//添加重绘函数
//		DrawMachine();
//		break;
//		//EndPaint(hWnd, &ps);
//	default:
//		break;
//	}
//    return DefWindowProc(hWnd,wMsg,wParam,lParam);
//}
LRESULT CSimpleWnd::WndProc(HWND h, UINT u, LPARAM l, WPARAM w)
{
	switch (u)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		DrawMachine();
		break;
	case WM_MOUSEMOVE:
		POINT  pt;   
		GetCursorPos(&pt);   // 取地址
		this->m_DrawGraph->Selected(pt.x,pt.y);//更新DrawGraph中的图形selected
		DrawMachine();
		break;
	case WM_MBUTTONDBLCLK:
		SkipToSubWnd();
		break;
	default:
		break;
	}
	return DefWindowProcA(h, u, l, w);
}


//----------------------------------------------------------------------
//Description:
//    Show the window
//
//----------------------------------------------------------------------
BOOL CSimpleWnd::ShowWindow(BOOL bShow)
{
    if(m_hWnd == NULL)
    {
        return FALSE;
    }

    if(bShow == TRUE)
    {
        ::ShowWindow(m_hWnd,
			SW_SHOW//SW_SHOWNORMAL//
			);
        SetForegroundWindow(m_hWnd);

    }
    else
    {
        ::ShowWindow(m_hWnd,
			SW_HIDE//SW_SHOWNORMAL//
			);
    }

	UpdateWindow(m_hWnd);
    return TRUE;
}



//----------------------------------------------------------------------
//Description:
//    Create the window
//
//----------------------------------------------------------------------
BOOL CSimpleWnd::Create(HINSTANCE hInst,HWND hWndParent)
{
    m_hInst = hInst;
    m_hWndParent = hWndParent;

    RegisterWnd(m_hInst,m_hWndParent);

    m_hWnd = /*CreateWindowEx(0,
                WND_CLASS,
                WND_NAME,
                WS_VISIBLE,
                0,
                0,
                800,
                480,
                m_hWndParent, 
                NULL, 
                m_hInst, 
                0);*/
	CreateWindowEx(0,
		WND_CLASS,
		this->m_DrawGraph->m_ScxmlLayout->layout_Id,//wndName,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		1280,
		1024,
		NULL,//m_hWndParent,
		NULL,
		m_hInst,
		0);	

    
    if (IsWindow(m_hWnd) == FALSE)
    {
        return FALSE;
    }

    // If the window is created successfully, store this object so the 
    //static wrapper can pass calls to the real WndProc.
    SetWindowLong(m_hWnd, GWL_USERDATA, (DWORD)this);
    return TRUE;
}

//----------------------------------------------------------------------
//Description:重绘函数
//    Draw machine view
//
//----------------------------------------------------------------------
BOOL CSimpleWnd::DrawMachine()
{
	HDC	hdc=GetDC(this->m_hWnd);
	//graphics=graphics->FromHDC(hdc);
	RECT rc;
	//GetWindowRect(hwnd,&rc);
	GetClientRect(m_hWnd,&rc);

	//TODO:
	//invoke draw
	this->m_DrawGraph->m_Graphics=this->m_DrawGraph->m_Graphics->FromHDC(hdc);//获取该图形graphic
	this->m_DrawGraph->m_ScxmlLayout->Resize((double)rc.right,(double)rc.bottom);//重新计算图形size

	this->m_DrawGraph->DrawGraphAll();//绘图
	return TRUE; 
}

void CSimpleWnd::SkipToSubWnd()
{
	if (this->m_DrawGraph->m_SelectedRectId==NULL)
	{
		return;
	}
	else
	{

	}
	
}

