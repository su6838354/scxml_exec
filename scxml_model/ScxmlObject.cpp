
#include "stdafx.h"
#include "MyGlobal.h"
#include "ScxmlObject.h"

ScxmlObject::ScxmlObject(void)
{
	this->m_Final=new Final;
	this->m_Initial=new Initial;
	this->m_State=new State;
	this->m_Transition=new Transition;
	this->m_OnEntry=new OnEntry;
	this->m_Log=new Log;
	this->m_Send=new Send;
	this->m_Assign=new Assign;
	this->m_Parallel=new Parallel;
	this->m_Raise=new Raise;
	this->m_OnExit=new OnExit;
}

ScxmlObject::~ScxmlObject(void)
{
	delete this->m_Assign;
	this->m_Assign=NULL;

}


Final::Final()
{
	this->m_Id="";
	this->m_ParentStateId="";
	//this->next=NULL;
}
Final::~Final()
{
	//this->next=NULL;
}

Initial::Initial()
{
	//this->m_InitialId="";
	//this->m_ParentStateId="";
	this->m_TargetStateId="";
	//this->next=NULL;
}
Initial::~Initial()
{

}

Parallel::Parallel()
{

}
Parallel::~Parallel()
{

}
int Assign::m_Num=0;

Assign::Assign()
{
	this->m_Expr=NULL;
	this->m_Id=NULL;
	this->m_Loaction=NULL;
	this->Next=NULL;
}
Assign::~Assign()
{

}


bool Assign::Add(Assign* newAssign)
{
	if (newAssign==NULL)
	{
		return false;
	}
	else
	{
		if (m_Num==0)
		{
			this->m_Num++;
			this->m_Expr=newAssign->m_Expr;
			this->m_Loaction=newAssign->m_Loaction;
			this->m_Id=MyGlobal::StrCat(m_Num,"Assign");
		}
		else
		{
			Assign* cur=this;
			while(cur->Next==NULL)
			{
				cur=cur->Next;
			}
			this->m_Num++;
			cur->Next=newAssign;
			newAssign->m_Id=MyGlobal::StrCat(m_Num,"Assign");
			return true;
		}
	}
}
int Send::m_Num=0;

Send::Send()
{
	this->m_Event=NULL;
	this->m_Id=NULL;
	this->m_Namelist=NULL;
	this->m_Target=NULL;
	this->m_Type=NULL;
}

Send::~Send()
{

}
bool Send::Add(Send* newSend)
{
	if (newSend==NULL)
	{
		return false;
	}
	else
	{
		if (m_Num==0)
		{
			this->m_Num++;
			this->m_Event=newSend->m_Event;
			this->m_Namelist=newSend->m_Namelist;
			this->m_Target=newSend->m_Target;
			this->m_Type=newSend->m_Type;
			this->m_Id=MyGlobal::StrCat(m_Num,"Send");
		}
		else
		{
			Send* cur=this;
			while(cur->Next==NULL)
			{
				cur=cur->Next;
			}
			this->m_Num++;
			cur->Next=newSend;
			newSend->m_Id=MyGlobal::StrCat(m_Num,"Assign");
			return true;
		}
	}
}
int OnEntry::m_Num=0;
OnEntry::OnEntry()
{
	this->m_Assign=new Assign;
	this->m_Id=NULL;
	this->m_Log=new Log;
	this->m_parentStateId=NULL;
	this->m_Raise=new Raise;
	this->m_Send=new Send;
	this->Next=NULL;
}
OnEntry::~OnEntry()
{

}
bool OnEntry::Add(OnEntry* newOnEntry)
{
	if (newOnEntry==NULL)
	{
		return false;
	}
	else
	{
		if (m_Num==0)
		{
			this->m_Num++;
			this->m_Assign=newOnEntry->m_Assign;
			this->m_Log=newOnEntry->m_Log;
			this->m_parentStateId=newOnEntry->m_parentStateId;
			this->m_Raise=newOnEntry->m_Raise;
			this->m_Send=newOnEntry->m_Send;
			this->m_Id=MyGlobal::StrCat(m_Num,"OnEntry");
		}
		else
		{
			OnEntry* cur=this;
			while(cur->Next!=NULL)
			{
				cur=cur->Next;
			}
			this->m_Num++;
			cur->Next=newOnEntry;
			newOnEntry->m_Id=MyGlobal::StrCat(m_Num,"OnEntry");
			return true;
		}
	}
}

int Raise::m_Num=0;
Raise::Raise()
{
	this->m_Event=NULL;
	this->m_Id=NULL;
}
Raise::~Raise()
{

}
bool Raise::Add(Raise *newRaise)
{
	if (newRaise==NULL)
	{
		return false;
	}
	else
	{
		if (this->m_Num==0)
		{
			this->m_Num++;
			this->m_Event=newRaise->m_Event;
			this->m_Id=MyGlobal::StrCat(m_Num,"Raise");
		}
		else
		{
			Raise* cur=this;
			while(cur->Next!=NULL)
			{
				cur=cur->Next;
			}
			this->m_Num++;
			cur->Next=newRaise;
			newRaise->m_Id=MyGlobal::StrCat(m_Num,"Raise");
		}
	}
	return true;
}

Log::Log()
{
	this->m_Expr=NULL;
	this->m_Id=NULL;
	this->Next=NULL;
}
int Log::m_Num=0;
Log::~Log()
{

}
bool Log::Add(Log* newLog)
{
	if (newLog==NULL)
	{
		return false;
	}
	else
	{
		if (this->m_Num==0)
		{
			this->m_Num++;
			this->m_Expr=newLog->m_Expr;
			this->m_Id=MyGlobal::StrCat(m_Num,"Log");
		}
		else
		{
			Log* cur=this;
			while(cur->Next!=NULL)
			{
				cur=cur->Next;
			}
			this->m_Num++;
			cur->Next=newLog;
			newLog->m_Id=MyGlobal::StrCat(m_Num,"Log");
		}
	}
	return true;
}
int OnExit::m_Num=0;

OnExit::OnExit()
{
	this->m_Log=NULL;
	this->m_ParentStateId=NULL;
	this->m_Id=NULL;
	this->Next=NULL;
}
OnExit::~OnExit()
{
	delete this->m_Log;
	this->m_Log=NULL;
	delete this->m_ParentStateId;
	this->m_ParentStateId=NULL;
	delete this->Next;
	this->Next=NULL;
	delete this->m_Id;
	this->m_Id=NULL;
}

void OnExit::Add(OnExit* newOnExit)
{
	if (newOnExit==NULL)
	{
		return;
	}
	else
	{
		if (this->m_Num==0)
		{
			this->m_Num++;
			this->m_Log=newOnExit->m_Log;
			this->m_ParentStateId=newOnExit->m_ParentStateId;
			this->m_Id=MyGlobal::StrCat(m_Num,"OnExit");
		}
		else
		{
			OnExit* cur=this;
			while(cur->Next!=NULL)
			{
				cur=cur->Next;
			}
			this->m_Num++;
			cur->Next=newOnExit;
			newOnExit->m_Id=MyGlobal::StrCat(m_Num,"OnExit");
		}
	}
	return;
}