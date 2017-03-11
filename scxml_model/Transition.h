#pragma once
#include "stdafx.h"
class Transition
{
public:
	Transition(void);
	~Transition(void);
	char* m_TransId;//自定义主键
	static int num;
	string m_Event;// execute ecent
	string m_SourceStateId;
	string m_TargetStateId;
	Transition* Next;

	//************************************
	// Method:    AddTransition
	// Description: 创建新的transition对象添加
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: Transition * newTransition
	//************************************
	bool AddTransition(Transition* newTransition);
};
