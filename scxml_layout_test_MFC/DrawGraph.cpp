#include "stdafx.h"
#include "DrawGraph.h"
#include "../scxml_layout/ScxmlText.h"

DrawGraph::DrawGraph()
{
	this->m_Graphics=new Graphics(*(new HDC));
	this->m_SelectedRectId=NULL;
	this->m_ScxmlLayout=NULL;
	this->m_SelectedRectId=NULL;
}
DrawGraph::~DrawGraph()
{

}

void DrawGraph::DrawLines()
{
	//line
	ScxmlLine *line1 = this->m_ScxmlLayout->scxmlline;
	while (line1 != NULL){
		PointF* p1=new PointF(line1->x1,line1->y1);
		PointF* p2=new PointF(line1->x2,line1->y2);
		PointF* mid=new PointF((p1->X+p2->X)/2,(p1->Y+p2->Y)/2);
		DrawArrow(p1,p2,30,10,line1->flag);
		//draw arrow title
		SolidBrush  brush(Color(255, 0, 0, 255));
		FontFamily  fontFamily(L"Times New Roman");
		Font        font(&fontFamily, 14, FontStyleRegular, UnitPixel);
		PointF      pointF(mid->X, mid->Y);
		wchar_t *wc = new wchar_t[strlen(line1->event.c_str()) +1];  
		swprintf(wc,L"%S",line1->event.c_str());   
		this->m_Graphics->DrawString(wc, -1, &font, pointF, &brush);
		line1 = line1->nextScxmlLine;
	}

}

void DrawGraph::DrawRects()
{
	//construct rect
	ScxmlRectangle *rect1 = this->m_ScxmlLayout->rect;
	Pen pen(Color(Color.Red));
	Pen penSelected(Color(Color.Green));
	//RectF* rectFs=new RectF[sxcmllayout.RectCount()];
	//int i=0;
	while (rect1 != NULL){
		RectF rectF=*(new RectF);
		rectF.X=rect1->x0-rect1->w;
		rectF.Y=rect1->y0-rect1->h;
		rectF.Width=rect1->w*2;
		rectF.Height=rect1->h*2;
		Pen* _pen;
		if (rect1->m_Selected)
		{
			_pen=&penSelected;
			//this->m_Graphics->DrawRectangle(&penSelected,rectF);
		}
		else
		{
			_pen=&pen;
			//this->m_Graphics->DrawRectangle(&pen,rectF);
		}
		SolidBrush* finalBrush = new SolidBrush(Color::Chocolate);
		SolidBrush* initalBrush=new SolidBrush(Color::BurlyWood);
		SolidBrush* parallelBrush=new SolidBrush(Color::CadetBlue);
		switch(rect1->flag)
		{
		case 0://initial
			this->m_Graphics->DrawEllipse(_pen,rectF.X,rectF.Y,rectF.Height,rectF.Height);
			this->m_Graphics->FillEllipse(initalBrush,rectF.X,rectF.Y,rectF.Height,rectF.Height);
			break;
		case 1://normal
			this->m_Graphics->DrawRectangle(_pen,rectF);
			break;
		case 2://final
			this->m_Graphics->DrawEllipse(_pen,rectF.X,rectF.Y,rectF.Height,rectF.Height);
			this->m_Graphics->FillEllipse(finalBrush,rectF.X,rectF.Y,rectF.Height,rectF.Height);
			break;
		case 3://paraller
			this->m_Graphics->DrawRectangle(_pen,rectF);
			this->m_Graphics->FillRectangle(parallelBrush,rectF.X,rectF.Y,rectF.Width,rectF.Height);
			break;
		default:
			break;
		}
		//框内线
		PointF p1(rectF.X,rectF.Y+15);
		PointF p2(rectF.X+rectF.Width,rectF.Y+15);
		this->m_Graphics->DrawLine(_pen,p1,p2);
		//////////////////////////////////////////////////////////////////////////
		//rectangle title
		SolidBrush  brush(Color(255, 0, 0, 255));
		FontFamily  fontFamily(L"Times New Roman");
		Font        font(&fontFamily, 14, FontStyleRegular, UnitPixel);
		PointF      pointF(rectF.X, rectF.Y);
		wchar_t *wc = new wchar_t[strlen(rect1->m_Id.c_str()) +1];  
		swprintf(wc,L"%S",rect1->m_Id.c_str());   
		this->m_Graphics->DrawString(wc, -1, &font, pointF, &brush);//rect text
		//i++;
		//rect Text
		ScxmlText* tempText=rect1->onentryaction;
		float textX=rectF.X;
		float textY=rectF.Y+15;
		while (tempText!=NULL)
		{
			textY=textY+15;
			wc = new wchar_t[strlen(tempText->content.c_str()) +1];  
			swprintf(wc,L"%S",tempText->content.c_str());   
			PointF pOnertry(textX,textY);
			this->m_Graphics->DrawString(wc,-1,&font,pOnertry,&brush);
			tempText=tempText->next;
		}
 

		//
		rect1 = rect1->nextScxmlRectangle;
		delete []wc; 
		wc=NULL;
	}
}

void DrawGraph::DrawTexts()
{
	//some information
	SolidBrush  brush(Color(Color.Black));
	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 14, FontStyleRegular, UnitPixel);
	PointF      pointF1(10, 25);
	PointF      pointF2(10, 40);
	wchar_t *info1 = new wchar_t[50];  
	wchar_t *info2 = new wchar_t[50];  
	
	swprintf(info1,L"the num of state：%d",this->m_ScxmlLayout->RectCount());   
	swprintf(info2,L"the num of line：%d",this->m_ScxmlLayout->LineCount());
	
	this->m_Graphics->DrawString(info1, -1, &font, pointF1, &brush);
	this->m_Graphics->DrawString(info2, -1, &font, pointF2, &brush);
	//string s(this->m_ScxmlLayout->layout_Id);
	//swprintf(info1,L"%ls",s);
	mbstowcs( info1,this->m_ScxmlLayout->layout_Id,50);
	pointF1.Y=10;
	this->m_Graphics->DrawString(info1,-1,&font,pointF1,&brush);
}

void DrawGraph::DrawGraphAll()
{
	DrawRects();
	DrawLines();
	DrawTexts();
}

void DrawGraph::DrawArrow(PointF* p1,PointF* p2,double theta,int length,bool iscurve)
{
	theta=3.1415926*theta/180;//转换为弧度
	double Px,Py,P1x,P1y,P2x,P2y;
	//以P2为原点得到向量P2P1（P）

	Px=p1->X-p2->X;
	Py=p1->Y-p2->Y;
	//向量P旋转theta角得到向量P1
	P1x=Px*cos(theta)-Py*sin(theta);
	P1y=Px*sin(theta)+Py*cos(theta);
	//向量P旋转-theta角得到向量P2
	P2x=Px*cos(-theta)-Py*sin(-theta);
	P2y=Px*sin(-theta)+Py*cos(-theta);
	//伸缩向量至制定长度
	double x1,x2;
	x1=sqrt(P1x*P1x+P1y*P1y);
	P1x=P1x*length/x1;
	P1y=P1y*length/x1;
	x2=sqrt(P2x*P2x+P2y*P2y);
	P2x=P2x*length/x2;
	P2y=P2y*length/x2;
	//平移变量到直线的末端
	P1x=P1x+p2->X;
	P1y=P1y+p2->Y;
	P2x=P2x+p2->X;
	P2y=P2y+p2->Y;

	PointF* p21=new PointF((float)P1x,(float)P1y);
	PointF* p22=new PointF(P2x,P2y);
	//CClientDC dc(this);//获取客户窗口DC
	Pen pen(Color(Color.Black));
	Pen pen1(Color(Color.Black));
	if (iscurve)
	{
		PointF* p=new PointF[3];
		p[0]=*p1;
		p[1]=*new PointF((p1->X+p2->X)/2+35,(p1->Y+p2->Y)/2+35);
		p[2]=*p2;
		this->m_Graphics->DrawLines(&pen,p,3);
	}
	else
	{
		this->m_Graphics->DrawLine(&pen,*p1,*p2);//
	}
	this->m_Graphics->DrawLine(&pen1,*p2,*p21);
	this->m_Graphics->DrawLine(&pen1,*p2,*p22);
}

void DrawGraph::Selected(long x,long y)
{
	//this->m_ScxmlLayout->rect->x0;
	if (this->m_ScxmlLayout==NULL)
	{
		return;
	}
	this->m_SelectedRectId=NULL;
	ScxmlRectangle* tmprect=this->m_ScxmlLayout->rect;
	while(tmprect!=NULL)
	{
		if ((abs(tmprect->x0-x)<tmprect->w)&&(abs(tmprect->y0-y)<tmprect->h))
		{
			//鼠标在该矩形中
			tmprect->m_Selected=true;
			this->m_SelectedRectId=(tmprect->m_Id).c_str();//该rect的name，可能是另一个窗口
		}
		else
		{
			tmprect->m_Selected=false;
		}
		tmprect=tmprect->nextScxmlRectangle;
	}
}