#include "stdafx.h"
#include "State.h"

State::State(void)
{
	m_Id="";
	flag=1;
	Next=NULL;
	m_subState=NULL;
	m_ParentStateId="";
}

State::~State(void)
{
}

void State::SetStateID(const char* stateId)
{
	if (stateId!=NULL)
	{
		m_Id=stateId;
		m_StateNum++;
	}
}

void State::AddBrother(State* brother)
{
	if (brother!=NULL)
	{
		Next=brother;
	}
}

bool State::InsertByParent(State* inserState)
{
	State* parentState=FindState(this,inserState->m_ParentStateId);
	if (parentState==NULL)
	{
		return false;
	}
	else
	{
		//执行插入操作
		State* tmp=	parentState->m_subState;
		State* newState=new State(*inserState);
		parentState->m_subState=newState;//需要做一个克隆
		newState->Next=tmp;
		m_StateNum++;
		return true;
	}
}

State* State::FindState(State* myState,const char* id)
{
	if (id==NULL)
	{
		return NULL;
	}
	State* result;
	if(myState!=NULL)
	{
		if (!strcmp(myState->m_Id,id))
		{
			return myState;
		}
		else//brother
		{
			State* tmpState=myState->Next;
			if(tmpState!=NULL)
			{
				if ((result=FindState(tmpState,id))!=NULL)
				{
					return result;
				}			 
			}
			//兄弟节点也找不到，查找sub节点
			tmpState=myState->m_subState;
			if (tmpState!=NULL)
			{
				if ((result=FindState(tmpState,id))!=NULL)
				{
					return result;
				}	
			}
		}
	}
	return NULL;
}

int State::m_StateNum=0;
char* State::m_Name="state";