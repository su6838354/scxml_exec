// scxml_parser_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ScxmlParser.h"

int _tmain(int argc, _TCHAR* argv[])
{
	ScxmlParser *scxmlP=new ScxmlParser;
	ScxmlObject *myScxmlObject=	scxmlP->GetScxmlObject("scxml.xml");
	//
	printf ("--test result of scxml.xml ---");
	printf ("1.the number of state[%s] --\n","");

	if (myScxmlObject!=NULL)
	{
		return 1;
	}
	return 0;
}

