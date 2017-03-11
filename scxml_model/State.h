#pragma once
#include "Transition.h"
class State
{
public:
	State(void);
	~State(void);
	static	int m_StateNum;
	static char* m_Name;
	int flag;
	const char* m_Id;
	State* m_subState;
	State* Next;
	const char* m_ParentStateId;
public:
	void SetStateID(const char* stateId);
	void AddBrother(State* brother);
	//************************************
	// Method:    InsertByParent
	// Description:将找出的initial、final等插入state
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: State * inserState
	//************************************
	bool InsertByParent(State* inserState);
	State* FindState(State* myState,const char* id);
};



