//// scxml_layout_test.cpp : Defines the entry point for the console application.
////
//
#pragma  once
#include "stdafx.h"

#include "SimpleWnd.h"
#include <math.h>
//#include <windows.h>

//#include <gdiplus.h> 
//#pragma comment( lib, "gdiplus.lib" )
//using namespace Gdiplus;
//static Graphics* graphics=new Graphics(*(new HDC));

LRESULT CALLBACK pre(HWND, UINT, LPARAM, WPARAM);
void DrawExample();
//void DrawArrow(PointF* p1,PointF* p2,double theta,int length,bool);
void DrawRects(const int rectCount);

static int DrawX;
static int DrawY;
static HWND hwnd;
int WINAPI WinMain(HINSTANCE h, HINSTANCE ph, LPSTR cmd, int cmds)
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR  gdiplusToken;
	// Initialize GDI+.kendie at the beging lost the init so that lost my much time
	Status st=GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	assert(st==Ok);
	if (st!=Ok)
	{
		return FALSE;
	}
	//////////////////////////////////////////////////////////////////////////
	//invoke parser
	ScxmlParser *scxmlP=new ScxmlParser;
	ScxmlObject *myScxmlObject=	scxmlP->GetScxmlObject("scxml.xml");
	//invoke scxmllayout
	ScxmlLayout *scxmlLayout=new ScxmlLayout;
	RECT rc;
	//GetClientRect(h,&rc);
	scxmlLayout->setScxmlObject(myScxmlObject,1024,1024);
	ScxmlLayout* tmpLayout=scxmlLayout;
	while(tmpLayout)
	{
		//循环创建SimpleWnd对象，并绘制
		CSimpleWnd* simpleWnd=new CSimpleWnd;
		simpleWnd->m_DrawGraph->m_ScxmlLayout=tmpLayout;
		simpleWnd->Create(h,NULL);//需要重构该函数,子窗口的创建绑定父窗口，绑定窗口text
		simpleWnd->ShowWindow(TRUE);
		tmpLayout=tmpLayout->Next;
	}
	//////////////////////////////////////////////////////////////////////////
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	};
	GdiplusShutdown(gdiplusToken);
	//ReleaseDC (hwnd, hdc) ; // 释放 hdc
}


//void DrawExample()
//{
//	//line
//	Pen pen(Color(255, 0, 0, 255));
//	graphics->DrawLine(&pen, 0, 0, 200, 100);
//
//	//rect
//	Rect rect(0,0,500,500);
//	graphics->DrawRectangle(&pen,rect);//1
//	graphics->DrawRectangle(&pen,500,500,10,20);//2
//    
//	//draw two rectangles
//	DrawRects(2);
//	//draw arrow
//	PointF* p1=new PointF(10,90);
//	PointF* p2=new PointF(200,800);
//	//DrawArrow(p1,p2,20,15,FALSE);
//
//    //draw a rect fill in some color
//	Pen blackPen(Color(255, 255, 0, 0), 3); 
//	Rect rectfill(0, 0, 500, 500); // 矩形 
//	graphics->DrawRectangle(&blackPen, rectfill); // 绘制一个矩形
//	HatchBrush newBrush( HatchStyleCross,Color(255, 0, 255, 0),Color(255, 0, 0, 255)); 
//	graphics->FillRectangle( &newBrush, 50, 50, 100, 60);// 在(50,50)处填充一个长为100，高为60的矩形区域
//}
//
//void DrawRects(const int rectCount)
//{
//	Pen pen(Color(Color.Red));
//	RectF* rectFs=new RectF[rectCount];
//	//packge receangles
//	rectFs[0].X=500;
//	rectFs[0].Y=500;
//	rectFs[0].Width=100;
//	rectFs[0].Height=50;
//	rectFs[1].X=500;
//	rectFs[1].Y=500;
//	rectFs[1].Width=200;
//	rectFs[1].Height=150;
//	graphics->DrawRectangles(&pen,rectFs,rectCount);
//}
