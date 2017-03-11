#include "stdafx.h"
#include <string>
class VitualRetangle{
public:
	VitualRetangle();
	double x0;
	double y0;
	double w;
	double h;
	std::string  vitualState_Id;
    VitualRetangle *Next;
};