/////////////////////////////////////////////////////////////////////
// SimpleWnd.h: interface for the CSimpleWnd class.
//
//////////////////////////////////////////////////////////////////////
#pragma  once
#include "stdafx.h"
#include <Windows.h>
#include "DrawGraph.h"
#ifndef SIMPLEWND_H
#define SIMPLEWND_H
class CSimpleWnd  
{
public:
	
		//////////////////////////////////////////////////////////////////////////
		//需要添加图形数据对象，窗口和该对象绑定，不同窗口绘出的图形也不同，便于重绘
		//在创建之前绑定，或者在Create中传入该参数
	DrawGraph* m_DrawGraph;
//
	BOOL Create(HINSTANCE hInst,HWND hWndParent);
	BOOL ShowWindow(BOOL bShow);    
	CSimpleWnd();
	BOOL DrawMachine();
	void SkipToSubWnd();
	virtual ~CSimpleWnd();

//protected:
	BOOL RegisterWnd(HINSTANCE hInst,HWND hWndParent);
	LRESULT WndProc(HWND h, UINT u, LPARAM l, WPARAM w);
	//LRESULT WndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT StaticWndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
	HWND m_hWndParent;
	HINSTANCE m_hInst;
};

#endif //#ifndef SIMPLEWND_H
