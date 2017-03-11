#include "stdafx.h"
#include <string>
class VirtualLine{
public:
	VirtualLine();
	double x1;
	double y1;
	double x2;
	double y2;
	std::string V_event;
	VirtualLine *Next;
};