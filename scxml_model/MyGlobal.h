#pragma once
#include <stdlib.h>
static class MyGlobal
{
public:
	static char* StrCat(int num,char* _name)
	{
		char* Name=(char*)malloc(30);
		char iNum[10];
		strcpy(Name,_name);
		_itoa_s(num,iNum,10);
		char* result= strcat(Name,iNum);
		return result;
	}
};