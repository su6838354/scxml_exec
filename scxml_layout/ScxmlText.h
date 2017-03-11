#pragma once
#include "stdafx.h"
#include<string>
struct ScxmlText{
	ScxmlText();
	double x;
	double y;
	std::string content; 
	ScxmlText *next;
};