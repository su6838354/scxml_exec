#include "stdafx.h"
#include<string>
#include "State.h"
#include"ScxmlText.h"
#include"ScxmlLine.h"
//the struct of scxmlrectangle
struct ScxmlRectangle
{
	double x0;   
	double y0;//Center point of Rectangle
	double w;   // half width of Rectangle
	double h;   // half hight of Rectangle 
	ScxmlRectangle *nextScxmlRectangle;
	std::string m_Id;
	std::string parent_Id;
	int biggerFlag;
	int flag;
	ScxmlText *stateId;
	ScxmlLine *scxmlRectangleLine;
	
	ScxmlText *onentryaction;
	ScxmlText *doaction;
	ScxmlText *onexitaction;
	ScxmlRectangle(ScxmlRectangle *nextScxmlRectangle1 = NULL);
	bool m_Selected;
};