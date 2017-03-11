#pragma once
#include<iostream>
#include<windows.h>
#include"ScxmlObject.h"
//#include"ScxmlLine.h"
#include"ScxmlRectangle.h"
#include "VirtualRetangle.h"
#include "VirtualLine.h"
#include "ScxmlParser.h"
#include <math.h>
#define PI 3.1415926
static double referenceY;
class ScxmlLayout
{
private:
	void getPositionScxmlRectangle(double x,double y);
	void getPositionLine(ScxmlLayout *scxmllayout);
	void getPositon(ScxmlLayout *scxmllayout,State *state);
	void LayoutAlgorithm(int n, ScxmlLayout *scxmllayout,State *state); 
	void recalculate(ScxmlLayout *scxmllayout);
	void setPositionText();
	void changeRectangularSize(ScxmlLayout *scxmllayout,bool repeat);
	ScxmlText *ScxmlLayout::changeRectangularSizeLength(ScxmlText *text,ScxmlRectangle *scxmlRectangle,ScxmlLayout *scxmllayout);
	int subStateCount(State *state);
	void Add(ScxmlLayout* scxlayout);
public:
	ScxmlLayout();
	int RectCount();
	int LineCount();
	void Resize(double width,double height);
	void setScxmlObject(ScxmlObject *so1,double x,double y);
public:
	ScxmlObject *so;
	ScxmlLine *scxmlline;
	ScxmlRectangle *rect;
	VirtualLine *virtualLine;
	VitualRetangle *virtualRect;
	//指向下一个ScxmlLayout
	ScxmlLayout* Next;
	//图形layout的标记
    double centreX;
    double centreY;
	const char *layout_Id;
	static int m_LayoutNum;
};
