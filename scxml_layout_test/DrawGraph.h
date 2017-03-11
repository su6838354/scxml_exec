#include "stdafx.h"
using namespace Gdiplus;
class DrawGraph
{
public:
	DrawGraph();
	~DrawGraph();
	Graphics* m_Graphics;//get the draw device
	ScxmlLayout* m_ScxmlLayout;//what want to draw
	const	char* m_SelectedRectId;//选中的rectId
	void DrawGraphAll();//绘制
	void Selected(long x,long y);//寻找被选中的rect，并标记
	
private:
	void DrawRects();
	void DrawLines();
	void DrawTexts();
	void DrawArrow(PointF* p1,PointF* p2,double theta,int length,bool iscurve);
};