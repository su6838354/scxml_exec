#include "stdafx.h"
#include "Transition.h"
#include <stdlib.h>

Transition::Transition(void)
{
	this->m_TransId=NULL;
	this->Next=NULL;
	this->m_Event="";
	this->m_SourceStateId="";
	this->m_TargetStateId="";
}

Transition::~Transition(void)
{
}
bool Transition::AddTransition(Transition* newTransition)
{
	if (newTransition==NULL)
	{
		return false;
	}
	Transition* last=this;
	if(num==0)
	{
		last=new Transition(*newTransition);
		this->m_Event=last->m_Event;
		this->m_SourceStateId=last->m_SourceStateId;
		this->m_TargetStateId=last->m_TargetStateId;
		num++;
		char* transName=(char*)malloc(30);
		char iNum[10];
		strcpy(transName,"trans");
		_itoa_s(num,iNum,10);
		this->m_TransId=strcat(transName,iNum);
		
		return true;
	}
	else
	{
		while(last->Next!=NULL)
		{
			last=last->Next;
		}
		last->Next=new Transition(*newTransition);
		num++;
		char* transName=(char*)malloc(30);
		char iNum[10];
		strcpy(transName,"trans");
		_itoa_s(num,iNum,10);
		last->Next->m_TransId=strcat(transName,iNum);

		return true;
	}
}
int Transition::num=0;