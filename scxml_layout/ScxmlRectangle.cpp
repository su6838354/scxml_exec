#include "stdafx.h"
#include"ScxmlRectangle.h"
//the scxmlrectangle constructed function
ScxmlRectangle::ScxmlRectangle(ScxmlRectangle *nextScxmlRectangle1){
	nextScxmlRectangle = nextScxmlRectangle1;
	biggerFlag=0;
	flag=1;
	stateId=NULL;
	onentryaction=NULL;
	onexitaction=NULL;
	m_Id="";
	parent_Id="";
	scxmlRectangleLine=NULL;
	this->m_Selected=false;
}
