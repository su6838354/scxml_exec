#pragma once
#include "stdafx.h"
#include "State.h"
#include "xpath_static.h"
#include "ScxmlObject.h"
class ScxmlParser
{
private:
	State* GetStates(char* scxmlPath);
	State* GetsubStates(TiXmlNode* S_node,const char* parentStateId);
	//don't use this method
	State* GetsubStates(TiXmlDocument* XDp_doc,char* scxmlPath);
	Transition* GetTransitions(char* scxmlPath);
	Transition * GetsubTransitions(TiXmlDocument* tixdoc,char* subTransitionPath);
	
	//add one template method of GetElement into object as state
	template <class T> T* GetElementObject(TiXmlNode* E_node,const char* eleName,const char* parentNameId);
	State* GetStatesByTemplate(char* scxmlPath);
	Final* GetFinals(char* scxmlPath);
	Initial* GetInitials(char* scxmlPath);
	Parallel* GetParallels(char* scxmlPath);

	//************************************
	// Method:    GetOnEntry
	// Description:目前只考虑onentry下面只有一个assign、send，如有多个需要修改该方法以及assign类
	// Access:    private 
	// Returns:   OnEntry*
	// Qualifier:
	// Parameter: char * scxmlPath
	//************************************
	OnEntry* GetOnEntry(char* scxmlPath);
	//************************************
	// Method:    GetOnExit
	// Description:
	// Access:    private 
	// Returns:   void
	// Qualifier:
	// Parameter: char * scxmlPath
	//************************************
	void GetOnExit(char* scxmlPath);



public:
	ScxmlParser(void);
	~ScxmlParser(void);
	ScxmlObject* ScxmlParser::GetScxmlObject(char* scxmlPath);
	ScxmlObject* MyScxmlObject;
};
