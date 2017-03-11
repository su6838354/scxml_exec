#pragma once
#include "stdafx.h"
#include<string>
// the struct of scxmlline
struct ScxmlLine
{

	double x1;
	double y1;
	double x2;
	double y2;
	int flag;
	ScxmlLine *nextScxmlLine;
	std::string event;
	ScxmlLine();
};



