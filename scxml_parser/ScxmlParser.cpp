#include "stdafx.h"
#include "ScxmlParser.h"
#include "tinyxml.h"
#include "xpath_static.h"
#include "htmlutil.h"
#include <windows.h>
#include <string.h>
#include <exception>


#ifdef _DEBUG
#define TRACE   _trace
#else
#define TRACE
#endif


void _trace(char *prompt)
{
	char buf[2048];
	va_list argptr;
	int cnt;

	va_start(argptr, prompt);
	//cnt = vsprintf(buf, prompt, argptr);
	strcpy(buf,prompt);
	OutputDebugString(buf);
	va_end(argptr);
}


ScxmlParser::ScxmlParser(void)
{
	this->MyScxmlObject=new ScxmlObject;
}


ScxmlParser::~ScxmlParser(void)
{
}

State* ScxmlParser::GetStates(char* filePath)
{
	TiXmlDocument *XDp_doc=new TiXmlDocument;
	if (!XDp_doc->LoadFile(filePath))
	{
		TRACE("can't find the file");
		return NULL;
	}
	
	TiXmlElement *XEp_root;
	XEp_root=XDp_doc->RootElement();//get the root element
	//get each state node
	TiXmlNode *S_node=TinyXPath::XNp_xpath_node(XEp_root,"/scxml",0);
	State *myState=GetsubStates(S_node,"");
	return myState;
}


//this method is bad
//get all states into the object state
//State* ScxmlParser::GetsubStates(TiXmlDocument* XDp_doc,char* scxmlPath)
//{
//	State *myState=new State;
//	TiXmlElement *XEp_root;
//	XEp_root=XDp_doc->RootElement();//get the root element
//	//TODO:calculate the state num
//	char currentscpath[100]="";
//	strcat(currentscpath,scxmlPath);
//	strcat(currentscpath,"/state");
//
//	TIXML_STRING S_res;
//	char countscxmlState[100]="count(";
//	strcat(countscxmlState,currentscpath);
//	strcat(countscxmlState,")");
//	S_res=TinyXPath::S_xpath_string(XEp_root,countscxmlState);
//	int count=S_res.c_str()[0]-'0';//get the num
//	if (count<=0)
//	{
//		return NULL;
//	}
//
//	//get each state node
//	TiXmlNode *S_node;
//	TiXmlAttribute *S_attr;
//	State * tempState;
//	tempState=myState;
//	for (int i=0;i<count;i++)
//	{
//		char tmpChar[100]="";
//		strcat(tmpChar,currentscpath);
//		strcat(tmpChar,"[");
//		int ai=i+1;
//		char t[256];
//		string s;
//		sprintf(t, "%d", ai);
//		strcat(tmpChar,t);
//		//
//		char subscxmlPath[100]="";
//		strcat(subscxmlPath,tmpChar);
//		strcat(subscxmlPath,"]");
//		//
//		strcat(tmpChar,"]/attribute::id");
//		//S_node=TinyXPath::XNp_xpath_node(XEp_root,"/scxml/state[1]",i);
//		S_attr=TinyXPath::XAp_xpath_attribute(XEp_root,tmpChar ,0);
//		tempState->m_Id=S_attr->Value();
//		//TODO: find the state transition
//
//
//		tempState->m_subState=GetsubStates(XDp_doc,subscxmlPath);
//		if (i+1<count)
//		{
//			tempState->Brother=new State;
//		}
//		else
//		{
//			tempState->Brother=NULL;
//		}
//		tempState=tempState->Brother;
//
//	}
//	//tempState->Brother=NULL;
//	//tempState->m_subState=NULL;
//
//	//delete XDp_doc;
//	//S_node=TinyXPath::XNp_xpath_node(XNp_root,cp_expr,0);//sy
//	return myState;
//}

////use this method to get states
State* ScxmlParser::GetsubStates(TiXmlNode* S_node,const char* parentStateId)
{
	TiXmlNode* S_node_tmp;
	State * subState=new State;
	S_node_tmp=S_node->FirstChild("state");
	if (S_node_tmp==NULL)
	{
		return NULL;
	}
	State* tmpState=subState;
	tmpState->m_ParentStateId=parentStateId;//set the parent state id
	
	while (S_node_tmp!=NULL)
	{
		tmpState->SetStateID(S_node_tmp->ToElement()->Attribute("id"));
		//subState
		tmpState->m_subState=GetsubStates(S_node_tmp,tmpState->m_Id);
		//brotherState
		S_node_tmp=S_node_tmp->NextSibling("state");
		if (S_node_tmp!=NULL)
		{
			State* newState=new State;
			tmpState->AddBrother(newState);
			tmpState=tmpState->Next;
		}
	}
	return subState;
}


// get the transitions
Transition* ScxmlParser::GetTransitions(char* filePath)
{
	TiXmlDocument *XDp_doc;
	XDp_doc=new TiXmlDocument;
	if (!XDp_doc->LoadFile(filePath))
	{
		TRACE("can't find the file");
		return NULL;
	}
	Transition* Transitions= GetsubTransitions(XDp_doc,"/scxml");
	return Transitions;
}

///get all transitions
Transition* ScxmlParser::GetsubTransitions(TiXmlDocument* XDp_doc,char* scxmlPath)
{
	Transition *myTransition=new Transition();
	TiXmlElement *XEp_root;
	XEp_root=XDp_doc->RootElement();//get the root element
	TiXmlNode *T_node;
	TiXmlAttribute *T_attr;
	TiXmlElement *T_elem;
	int transCount=TinyXPath::i_xpath_int(XEp_root,"count(//transition)");
	if (transCount<=0)
	{
		return NULL;
	}
	//Transition* tmpTransition=myTransition;
	Transition* tmpTransition=new Transition;
	for (int i=0;i<transCount;i++)
	{
		T_node= TinyXPath::XNp_xpath_node(XEp_root,"//transition",i);
		T_elem=T_node->ToElement();
		if (T_elem->Attribute("target")==0&&T_elem->Attribute("next")==0)
		{
			tmpTransition->m_TargetStateId="";
		}
		else
		{
			tmpTransition->m_TargetStateId=T_elem->Attribute("target")==0?
				T_elem->Attribute("next"):
			T_elem->Attribute("target");
		}
		tmpTransition->m_Event= T_elem->Attribute("event")==0?"":T_elem->Attribute("event");
		tmpTransition->m_SourceStateId=T_node->Parent()->ToElement()->Attribute("id")==0?
			T_node->Parent()->Parent()->ToElement()->Attribute("id"):
		T_node->Parent()->ToElement()->Attribute("id");
		
		myTransition->AddTransition(tmpTransition);
		/*if (i<transCount-1)
		{
			tmpTransition->Next=new Transition();
			tmpTransition=tmpTransition->Next;
		}*/
	}
	return myTransition;
}

ScxmlObject* ScxmlParser::GetScxmlObject(char* scxmlPath)
{
	try
	{
		MyScxmlObject->m_State=GetStates(scxmlPath);
		MyScxmlObject->m_Parallel=GetParallels(scxmlPath);
		//MyScxmlObject->m_State=GetStatesByTemplate(scxmlPath);//This method is also right
		MyScxmlObject->m_Transition=GetTransitions(scxmlPath);
		MyScxmlObject->m_Final=GetFinals(scxmlPath);
		MyScxmlObject->m_Initial=GetInitials(scxmlPath);
		MyScxmlObject->m_OnEntry=this->GetOnEntry(scxmlPath);
		this->GetOnExit(scxmlPath);//对MyScxmlObject在该函数中已经执行

		//list parallel into state
		Parallel* tmpParallel=MyScxmlObject->m_Parallel;
		while(tmpParallel)
		{
			tmpParallel->flag=3;//
			MyScxmlObject->m_State->InsertByParent(tmpParallel);
			tmpParallel=(Parallel*)tmpParallel->Next;
		}

		//list final into the state
		Final* tmpFinal=MyScxmlObject->m_Final;
		while(tmpFinal)
		{
			tmpFinal->flag=2;//
			MyScxmlObject->m_State->InsertByParent(tmpFinal);
			tmpFinal=(Final*)tmpFinal->Next;
		}
		//list initial into state
		Initial* tmpInitial=MyScxmlObject->m_Initial;
		while(tmpInitial)
		{
			tmpInitial->flag=0;//initial flag is 0 
			MyScxmlObject->m_State->InsertByParent(tmpInitial);
			tmpInitial=(Initial*)tmpInitial->Next;
		}
		//list initial into transition
		Initial* tmpInitial2=MyScxmlObject->m_Initial;
		while(tmpInitial2)
		{
			//add into the transition
			Transition* newTransition=new Transition;
			newTransition->m_SourceStateId=tmpInitial2->m_Id;
			newTransition->m_TargetStateId=tmpInitial2->m_TargetStateId;
			MyScxmlObject->m_Transition->AddTransition(newTransition);
			tmpInitial2=(Initial*)tmpInitial2->Next;
		}
		return MyScxmlObject;
	}
	catch (exception * e)
	{
		throw e;
	}
	return NULL;
}

template <class T>
T* ScxmlParser::GetElementObject(TiXmlNode* E_node,const char* eleName,const char* eleparentNameId)
{
	TiXmlNode* E_node_tmp;
	T* subElem=new T;
	E_node_tmp=E_node->FirstChild(eleName);
	if (E_node_tmp==NULL)
	{
		return NULL;
	}
	T* tmpElem=subElem;
	tmpElem->m_ParentStateId=eleparentNameId;//set the parent state id
	while (E_node_tmp!=NULL)
	{
		//tmpElem->m_Id=E_node_tmp->ToElement()->Attribute("id");
		tmpElem->SetStateID(E_node_tmp->ToElement()->Attribute("id"));
		//subState
		tmpElem->m_subState=GetElementObject<T>(E_node_tmp,eleName,tmpElem->m_Id);

		E_node_tmp=E_node_tmp->NextSibling(eleName);
		if (E_node_tmp!=NULL)
		{
			T* newElem=new T;
			tmpElem->AddBrother(newElem);
			tmpElem=tmpElem->Next;
		}
	}
	return subElem;
}

State* ScxmlParser::GetStatesByTemplate(char* scxmlPath)
{
	TiXmlDocument *XDp_doc=new TiXmlDocument;
	if (!XDp_doc->LoadFile(scxmlPath))
	{
		TRACE("can't find the file");
		return NULL;
	}
	TiXmlElement *XEp_root;
	XEp_root=XDp_doc->RootElement();//get the root element
	//get each state node
	TiXmlNode *S_node=TinyXPath::XNp_xpath_node(XEp_root,"/scxml",0);
	State *myState=ScxmlParser::GetElementObject<State>(S_node,State.m_Name,"");
	return myState;
}

Final* ScxmlParser::GetFinals(char* scxmlPath)
{
	TiXmlDocument *XDp_doc=new TiXmlDocument;
	if (!XDp_doc->LoadFile(scxmlPath))
	{
		TRACE("can't find the file");
		return NULL;
	}
	TiXmlElement *XEp_root;
	XEp_root=XDp_doc->RootElement();//get the root element
	//get each final state
	int i=0;
	TiXmlNode *finalState=TinyXPath::XNp_xpath_node(XEp_root,"//final",i);
	if (finalState==NULL)
	{
		return NULL;
	}
	Final* newFinial= new Final;
	Final* tmpFinial= newFinial;
	while(finalState!=NULL)
	{
		//packag
		tmpFinial->m_Id=finalState->ToElement()->Attribute("id");
		tmpFinial->m_ParentStateId=finalState->Parent()->ToElement()->Attribute("id");
		i++;
		finalState=TinyXPath::XNp_xpath_node(XEp_root,"//final",i);
		if (finalState!=NULL)
		{
			tmpFinial->Next=new Final;
			tmpFinial=(Final*)tmpFinial->Next;
		}
	}
	return newFinial;
}

Initial* ScxmlParser::GetInitials(char* scxmlPath)
{
	TiXmlDocument *XDp_doc=new TiXmlDocument;
	if (!XDp_doc->LoadFile(scxmlPath))
	{
		TRACE("can't find the file");
		return NULL;
	}
	TiXmlElement *XEp_root;
	XEp_root=XDp_doc->RootElement();//get the root element
	//get each initial state
	int i=0;
	TiXmlNode *initialState=TinyXPath::XNp_xpath_node(XEp_root,"//initial",i);
	Initial* newInitial;
	Initial* tmpInitial;
	if (initialState!=NULL)
	{
		newInitial= new Initial; 
		tmpInitial= newInitial;
		while(initialState!=NULL)
		{
			//packag
			tmpInitial->m_TargetStateId=initialState->FirstChild("transition")->ToElement()->Attribute("target");
			tmpInitial->m_ParentStateId=initialState->Parent()->ToElement()->Attribute("id");
			char* st= (char *)malloc(30*sizeof(char));
			strcpy(st,"start");
			strcat(st,tmpInitial->m_TargetStateId);
			tmpInitial->m_Id=initialState->ToElement()->Attribute("id")==0?st:initialState->ToElement()->Attribute("id");
			i++;
			initialState=TinyXPath::XNp_xpath_node(XEp_root,"//initial",i);
			if (initialState!=NULL)
			{
				tmpInitial->Next=new Initial;
				tmpInitial=(Initial*)tmpInitial->Next;
			}
		}
	}
	
	//get the initial as a attribute in state
	int j=0;
	TiXmlNode *initialAttrs=TinyXPath::XNp_xpath_node(XEp_root,"//*[@initial]",j);
	if (initialAttrs!=NULL)
	{
		if (tmpInitial==NULL)
		{
			tmpInitial=new Initial;
		}
		else
		{
			tmpInitial->Next=new Initial;
			tmpInitial=(Initial*)tmpInitial->Next;
		}
		while(initialAttrs!=NULL)
		{
			tmpInitial->m_TargetStateId=initialAttrs->ToElement()->Attribute("initial");
			tmpInitial->m_ParentStateId=initialAttrs->ToElement()->Attribute("id");
			char* st= (char *)malloc(30*sizeof(char));
			strcpy(st,"start ");
			tmpInitial->m_Id=strcat(st,tmpInitial->m_TargetStateId);

			j++;
			initialAttrs=TinyXPath::XNp_xpath_node(XEp_root,"//*[@initial]",j);
			if (initialAttrs!=NULL)
			{
				tmpInitial->Next=new Initial;
				tmpInitial=(Initial*)tmpInitial->Next;
			}
		}
	}
	return newInitial;
}


Parallel* ScxmlParser::GetParallels(char* scxmlPath)
{
	TiXmlDocument *XDp_doc=new TiXmlDocument;
	if (!XDp_doc->LoadFile(scxmlPath))
	{
		TRACE("can't find the file");
		return NULL;
	}
	TiXmlElement *XEp_root;
	XEp_root=XDp_doc->RootElement();//get the root element
	//get each parallel
	int i=0;
	TiXmlNode *parallelNode=TinyXPath::XNp_xpath_node(XEp_root,"//parallel",i);
	Parallel* newParallel;
	Parallel* tmpParallel;
	if (parallelNode!=NULL)
	{
		newParallel= new Parallel;
		tmpParallel=newParallel;
		while(parallelNode!=NULL)
		{
			//packag
			tmpParallel->m_Id=parallelNode->ToElement()->Attribute("id");
			tmpParallel->m_ParentStateId=parallelNode->Parent()->ToElement()->Attribute("id");
			i++;
			parallelNode=TinyXPath::XNp_xpath_node(XEp_root,"//parallel",i);
			if (parallelNode!=NULL)
			{
				tmpParallel->Next=new Parallel;
				tmpParallel=(Parallel*)tmpParallel->Next;
			}
		}
	}
	return newParallel;
}

OnEntry* ScxmlParser::GetOnEntry(char* scxmlPath)
{
	TiXmlDocument *XDp_doc=new TiXmlDocument;
	if (!XDp_doc->LoadFile(scxmlPath))
	{
		TRACE("can't find the file");
		return NULL;
	}
	TiXmlElement *XEp_root;
	XEp_root=XDp_doc->RootElement();//get the root element
	//get each onentry

	int i=0;
	TiXmlNode *onentryNode=TinyXPath::XNp_xpath_node(XEp_root,"//onentry",i);
	if (onentryNode!=NULL)
	{
		while(onentryNode!=NULL)
		{
			OnEntry* tmpOnentry=new OnEntry;
			//packag
			tmpOnentry->m_parentStateId=onentryNode->Parent()->ToElement()->Attribute("id");
			TiXmlNode* chid=onentryNode->FirstChild("assign");
			if(chid!=NULL)
			{
				Assign* newAssign=new Assign;
				newAssign->m_Loaction=chid->ToElement()->Attribute("location");
				newAssign->m_Expr=chid->ToElement()->Attribute("expr");
				tmpOnentry->m_Assign=newAssign;
				//assign装箱
				MyScxmlObject->m_Assign->Add(newAssign);
			}
			chid=onentryNode->FirstChild("send");
			if (chid!=NULL)
			{
				Send* newSend=new Send;
				newSend->m_Event=chid->ToElement()->Attribute("event");
				newSend->m_Namelist=chid->ToElement()->Attribute("namelist");
				newSend->m_Target=chid->ToElement()->Attribute("target");
				newSend->m_Type=chid->ToElement()->Attribute("type");
				tmpOnentry->m_Send=newSend;
				//send装箱
				MyScxmlObject->m_Send->Add(newSend);
			}
			chid=onentryNode->FirstChild("raise");
			if (chid!=NULL)
			{
				Raise* newRaise=new Raise;
				newRaise->m_Event=chid->ToElement()->Attribute("event");
				tmpOnentry->m_Raise=newRaise;
				MyScxmlObject->m_Raise->Add(newRaise);
			}
			chid=onentryNode->FirstChild("log");
			if (chid!=NULL)
			{
				Log* newLog=new Log;
				newLog->m_Expr=chid->ToElement()->Attribute("expr");
				tmpOnentry->m_Log=newLog;
				MyScxmlObject->m_Log->Add(newLog);
			}
			MyScxmlObject->m_OnEntry->Add(tmpOnentry);
			i++;
			onentryNode=TinyXPath::XNp_xpath_node(XEp_root,"//onentry",i);
		}
	}
	return MyScxmlObject->m_OnEntry;
}

void ScxmlParser::GetOnExit(char* scxmlPath)
{
	TiXmlDocument *XDp_doc=new TiXmlDocument;
	if (!XDp_doc->LoadFile(scxmlPath))
	{
		TRACE("can't find the file");
		return;
	}
	TiXmlElement *XEp_root;
	XEp_root=XDp_doc->RootElement();//get the root element
	//get each onentry

	int i=0;
	TiXmlNode *onexitNode=TinyXPath::XNp_xpath_node(XEp_root,"//onexit",i);
	if (onexitNode!=NULL)
	{
		while(onexitNode!=NULL)
		{
			OnExit* tmpOnexit=new OnExit;
			//packag
			tmpOnexit->m_ParentStateId=onexitNode->Parent()->ToElement()->Attribute("id");
			TiXmlNode* chid=onexitNode->FirstChild("log");
			if (chid!=NULL)
			{
				Log* newLog=new Log;
				newLog->m_Expr=chid->ToElement()->Attribute("expr");
				tmpOnexit->m_Log=newLog;
				MyScxmlObject->m_Log->Add(newLog);
			}
			MyScxmlObject->m_OnExit->Add(tmpOnexit);
			i++;
			onexitNode=TinyXPath::XNp_xpath_node(XEp_root,"//onexit",i);
		}
	}
}