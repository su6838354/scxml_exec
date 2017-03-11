#pragma once
#include "stdafx.h"
#include "State.h"


class Final:public State
{
public:
	Final();
	~Final();
	//const char* m_FinalId;
	//const char* m_ParentStateId;
	//Final* next;
};

class Initial:public State
{
public:
	Initial();
	~Initial();	
	//const char* m_InitialId;
	const char* m_TargetStateId;
	//const char* m_ParentStateId;
	//Initial* next;
};

class Parallel:public State
{
public:
	Parallel();
	~Parallel();
};



class Send
{
public:
	Send();
	~Send();
	const char* m_Id;//自定义主键
	const char* m_Target;
	const char* m_Type;
	const char* m_Event;
	const char* m_Namelist;
	char* ToString();
	//************************************
	// Method:    Add
	// Description:地址添加，不增加新的变量，和onentry中send的绑定
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: Assign * newSend
	//************************************
	bool Add(Send* newSend);
	static int m_Num;
	Send* Next;
};

class Log
{
public:
	Log();
	~Log();
	const char* m_Expr;
	char* ToString();
	static int m_Num;
	const char* m_Id;
	Log* Next;
	//************************************
	// Method:    Add
	// Description:地址添加，和其他元素内的绑定
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: Log * newLog
	//************************************
	bool Add(Log* newLog);
};

class Assign
{
public:
	Assign();
	~Assign();
	static int m_Num;
	const char* m_Id;//主键
	const char* m_Loaction;
	const char* m_Expr;
	char* ToString();
	Assign* Next;
	//************************************
	// Method:    Add
	// Description:地址添加，不增加新的变量，和onentry中assign的绑定
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: Assign * newAssign
	//************************************
	bool Add(Assign* newAssign);
};
class Raise
{
public:
	Raise();
	~Raise();
	char* m_Id;
	const char* m_Event;
	char* ToString();
	static int m_Num;
	Raise* Next;

	//************************************
	// Method:    Add
	// Description:地址添加
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: Raise newRaise
	//************************************
	bool Add(Raise* newRaise);
};
class OnEntry
{
public:
	OnEntry();
	~OnEntry();
	const char* m_Id;//自定义主键
	const char* m_parentStateId;//父stateid
	Send* m_Send;
	Assign* m_Assign;
	Log* m_Log;
	Raise* m_Raise;
	char* ToString();
	OnEntry* Next;
	static int m_Num;
	//************************************
	// Method:    Add
	// Description: create new object in storage as newOnEntry
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: OnEntry * newOnEntry
	//************************************
	bool Add(OnEntry* newOnEntry);
};
class OnExit
{
public:
	OnExit();
	~OnExit();
	static int m_Num;
	void Add(OnExit* newOnExit);
	Log* m_Log;
	const char* m_ParentStateId;
	OnExit* Next;
	const char* m_Id;
};
class IfElse
{
public:
	IfElse();
	~IfElse();
	const char* m_Id;
	char* m_Cond;
	Assign* m_assign;
};

//////////////////////////////////////////////////////////////////////////



class ScxmlObject
{
public:
	ScxmlObject(void);
	~ScxmlObject(void);
	State* m_State;
	Transition* m_Transition;
	Initial* m_Initial;
	Final* m_Final;//end
	Parallel* m_Parallel;
	OnEntry* m_OnEntry;
	OnExit* m_OnExit;
	Send* m_Send;
	Assign* m_Assign;
	Raise* m_Raise;
	Log* m_Log;
};



