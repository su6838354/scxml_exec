#include "stdafx.h"
#include"ScxmlLayout.h"
//the scxmllayout constructed function
ScxmlLayout::ScxmlLayout(){
	so = NULL;
	scxmlline = NULL;
	rect = NULL;
	Next=NULL;
	centreX=0;
	centreY=0;
}
void ScxmlLayout::setScxmlObject(ScxmlObject *so1,double x,double y){
	so = so1;
	this->getPositionScxmlRectangle(x,y);
	this->getPositionLine(this);
	this->subStateCount(so->m_State->m_subState);
}
// get the ScxmlRectangle center point and it's width and hight
void ScxmlLayout::getPositionScxmlRectangle(double x,double y){
	x=x-80;
	y=y-80;
	this->rect = new ScxmlRectangle();
	this->rect->x0 = double(x / 2);
	this->rect->y0 = double(y / 2);
	this->rect->w =  double(x / 2);
	this->rect->h =  double(y / 2);
	this->rect->m_Id = "Root";
	this->layout_Id="TheFirstWindow";
	centreX=double(x/2);
    centreY=double(y/2);
	//	getPositionScxmlCircle();
	getPositon(this,so->m_State);
	ScxmlLayout *scxmllayout=this;
	while(scxmllayout!=NULL){
		scxmllayout->rect=scxmllayout->rect->nextScxmlRectangle;
		scxmllayout=scxmllayout->Next;
	}
	this->changeRectangularSize(this,TRUE);
}
//get the ScxmlRectangle center point
void ScxmlLayout::getPositon(ScxmlLayout *scxmllayout,State *state){
	int i = 0;
	State *state1 = state;
	if (state1 != NULL){
		while (state1 != NULL){
			state1 = state1->Next;
			i++;
		}

		scxmllayout->LayoutAlgorithm(i,scxmllayout,state);
		state1 = state;
		State *state2=state;
		while (state1 != NULL){
			state2 = state2->m_subState;
			if (state2!=NULL&&state2->Next!=NULL){
                scxmllayout->Next=new ScxmlLayout();
                scxmllayout=scxmllayout->Next;
				scxmllayout->layout_Id=state2->m_ParentStateId;
				scxmllayout->rect = new ScxmlRectangle();
				scxmllayout->rect->x0 = this->rect->x0;
				scxmllayout->rect->y0 = this->rect->x0;
				scxmllayout->rect->w = this->rect->w;
				scxmllayout->rect->h = this->rect->h;
				scxmllayout->rect->m_Id = "Root";
                scxmllayout->centreX=this->centreX;
				scxmllayout->centreY=this->centreY;
                scxmllayout->so=this->so;
				getPositon(scxmllayout,state2);
			}
			state2 = state1->Next;
			state1 = state2;
		}
	}

}
// get the ScxmlRectangle center point and it's width and hight
void ScxmlLayout::LayoutAlgorithm(int n,ScxmlLayout*scxmllayout, State *state1){
     int i;
	//painting rectangle basic of circle 
	        ScxmlRectangle *rect1=scxmllayout->rect;
		for (i = 0; i < n; i++){
			ScxmlRectangle *rect2 = new ScxmlRectangle();
			rect1->nextScxmlRectangle = rect2;
			rect2->x0 = scxmllayout->rect->x0 + (scxmllayout->rect->w - scxmllayout->rect->w /n)*cos(2 * i*PI / n);
			rect2->y0 = scxmllayout->rect->y0 + (scxmllayout->rect->h - scxmllayout->rect->h /n)*sin(2 * i*PI / n);
			if(n>=3){
			rect2->w = scxmllayout->rect->w /n;
			rect2->h = scxmllayout->rect->h /n;
			}
			else if(n==2){
				rect2->w = scxmllayout->rect->w /(1.5*n);
				rect2->h = scxmllayout->rect->h /(1.5*n);

			}
			else{
				rect2->w = scxmllayout->rect->w /(2*n);
				rect2->h = scxmllayout->rect->h /(2*n);
			}


			if(state1->m_Id!=NULL){
				rect2->m_Id = state1->m_Id;
				rect2->stateId=new ScxmlText();
				rect2->stateId->content=state1->m_Id;
				rect2->parent_Id=scxmllayout->rect->m_Id;
			}
			rect2->flag=state1->flag;
			if(rect2->flag==0||rect2->flag==2){
				rect2->h=rect2->h/2;
                rect2->w=rect2->h;
			}
			if (state1 != NULL)
				state1 = state1->Next;
			rect1 = rect2;

		}
	
}


void ScxmlLayout::getPositionLine(ScxmlLayout *scxmllayout){
	Transition *tra = this->so->m_Transition;
	int flag3=0;
	ScxmlRectangle *rect1;
	ScxmlRectangle *rect2;
	ScxmlLine *scxmlline1 = new ScxmlLine();
	ScxmlLine *scxmlline2 = scxmllayout->scxmlline;
	ScxmlLine *scxmlline3=scxmllayout->scxmlline;
	if(scxmlline3==NULL)
		scxmllayout->scxmlline=scxmlline1;
	else{
		while(scxmlline3->nextScxmlLine!=NULL)
			scxmlline3=scxmlline3->nextScxmlLine;
		scxmlline3->nextScxmlLine=scxmlline1;
	}

	scxmllayout->virtualRect=new VitualRetangle();
    VitualRetangle *virtualRect1=scxmllayout->virtualRect;
	scxmllayout->virtualLine=new VirtualLine();
	VirtualLine *virtualLine1=scxmllayout->virtualLine;
	double x1,y1,x2,y2,w1, h1, w2, h2,k;
	int flag1,flag2;
	while (tra != NULL){
		flag1 = 0;
		flag2 = 0;
		rect1 =scxmllayout->rect;
		scxmlline1->event = tra->m_Event;
		while (rect1 != NULL){
			if (rect1->m_Id == tra->m_SourceStateId&&flag1==0){
				x1 = rect1->x0;
				y1 = rect1->y0;
				w1 = rect1->w;
				h1 = rect1->h;
				rect2=rect1;
				flag1++;
			}
			else if (rect1->m_Id == tra->m_TargetStateId&&flag2==0){
				x2 = rect1->x0;
				y2 = rect1->y0;
				w2 = rect1->w;
				h2 = rect1->h;
				flag2++;
			}
			if (flag1 == 1&&flag2==1){
				flag3=1;
				break;
			}
			rect1 = rect1->nextScxmlRectangle;
		}
		//Get the appropriate starting point and end point
		if(flag1==1&&flag2==1){
			if (x1 == x2){
				if (y2 > y1){
					scxmlline1->x1 = x1;
					scxmlline1->y1 = y1 + h1;
					scxmlline1->x2 = x2;
					scxmlline1->y2 = y2 - h2;
				}
				else{
					scxmlline1->x1 = x1;
					scxmlline1->y1 = y1 - h1;
					scxmlline1->x2 = x2;
					scxmlline1->y2 = y2 + h2;
				}
			}
			else{
				k = (y2 - y1) / (x2 - x1);
				if (k >= -h1 / w1&&k <= h1 / w1){
					if (x2 > x1){
						scxmlline1->y1 = y1;
						scxmlline1->x1 = x1 + w1;
						scxmlline1->y2 = y2;
						scxmlline1->x2 = x2 - w2;
					}
					else{
						scxmlline1->y1 = y1;
						scxmlline1->x1 = x1 - w1;
						scxmlline1->y2 = y2;
						scxmlline1->x2 = x2 + w2;
					}
				}
				else{
					if (y2 > y1){
						scxmlline1->y1 = y1 + h1;
						scxmlline1->x1 = x1;
						scxmlline1->y2 = y2 - h2;
						scxmlline1->x2 = x2;
					}
					else{
						scxmlline1->y1 = y1 - h1;
						scxmlline1->x1 = x1;
						scxmlline1->y2 = y2 + h2;
						scxmlline1->x2 = x2;
					}

				}
			}
		}
		if(flag1==1&&flag2!=1){
			if(rect2->x0>scxmllayout->centreX)
				x1=rect2->x0-rect2->w;
			else if(rect2->x0<scxmllayout->centreX)
				x1=rect2->x0+rect2->w;
			else
				x1=rect2->x0;

			if(rect2->y0>scxmllayout->centreY)
				h1=rect2->y0-rect2->h;
			else if(rect2->y0<scxmllayout->centreY)
				h1=rect2->y0+rect2->h;
			else
				y1=rect2->y0;
          virtualRect1->Next=new VitualRetangle();
		  virtualRect1->Next->x0=(x1+scxmllayout->centreX)/2;
		  virtualRect1->Next->y0=(y1+scxmllayout->centreY)/2;
		  virtualRect1->Next->w=rect2->w/4;
		  virtualRect1->Next->h=rect2->h/4;
		  x1 = rect2->x0;
		  y1 = rect2->y0;
		  w1 = rect2->w;
		  h1 = rect2->h;
		  x2 = virtualRect1->Next->x0;
		  y2 = virtualRect1->Next->y0;
		  w2 = virtualRect1->Next->w;
		  h2 = virtualRect1->Next->h;
		  
         virtualRect1=virtualRect1->Next;

		 virtualLine1->Next=new VirtualLine();
		  k = (y2 - y1) / (x2 - x1);
		  if (k >= -h1 / w1&&k <= h1 / w1){
			  if (x2 > x1){
				  virtualLine1->Next->y1 = y1;
				  virtualLine1->Next->x1 = x1 + w1;
				  virtualLine1->Next->y2 = y2;
				  virtualLine1->Next->x2 = x2 - w2;
					}
			  else{
				  virtualLine1->Next->y1 = y1;
				  virtualLine1->Next->x1 = x1 - w1;
				  virtualLine1->Next->y2 = y2;
				  virtualLine1->Next->x2 = x2 + w2;
					}
		  }
		  else{
			  if (y2 > y1){
				  virtualLine1->Next->y1 = y1 + h1;
				  virtualLine1->Next->x1 = x1;
				  virtualLine1->Next->y2 = y2 - h2;
				  virtualLine1->Next->x2 = x2;
					}
			  else{
				  virtualLine1->Next->y1 = y1 - h1;
				  virtualLine1->Next->x1 = x1;
				  virtualLine1->Next->y2 = y2 + h2;
				  virtualLine1->Next->x2 = x2;
					}
		  }
		}
		tra = tra->Next;
		if(tra!=NULL&&flag1==1&&flag2==1){
			scxmlline1->nextScxmlLine=new ScxmlLine();
            scxmlline2=scxmlline1;
			scxmlline1=scxmlline1->nextScxmlLine;
		}
	    
    }
	if(scxmlline2==NULL)
       scxmllayout->scxmlline=NULL;
	if(scxmlline2!=NULL&&flag3==1) 
	scxmlline2->nextScxmlLine=NULL;
	//set flag of a state starting point  is another state ending point and  a state ending point  is another state starting point 
	scxmlline1 = scxmllayout->scxmlline;
	while (scxmlline1 != NULL){
		scxmlline2 = scxmlline1->nextScxmlLine;
		while (scxmlline2 != NULL){
			if (((scxmlline1->x1 == scxmlline2->x2) && (scxmlline1->y1 == scxmlline2->y2) && (scxmlline1->x2 == scxmlline2->x1) && (scxmlline1->y2 == scxmlline2->y1))||
			((scxmlline1->x1 == scxmlline2->x1) && (scxmlline1->y1 == scxmlline2->y1) && (scxmlline1->x2 == scxmlline2->x2) && (scxmlline1->y2 == scxmlline2->y2)))
			{
	           scxmlline2->flag=1;
				break;
			}
			scxmlline2 = scxmlline2->nextScxmlLine;
		}
		scxmlline1 = scxmlline1->nextScxmlLine;
	}	
    if(scxmllayout->Next!=NULL)
            getPositionLine(scxmllayout->Next);
}
int ScxmlLayout::RectCount()
{
   int count=0;
   ScxmlRectangle*rect1=this->rect;
	while (rect1 != NULL&&rect1->m_Id!=""){
		count++;
		rect1 = rect1->nextScxmlRectangle;
	}
	return count;
}
int ScxmlLayout::LineCount()
{
	int count=0;
		ScxmlLine *scxmlline1 = this->scxmlline;
		while (scxmlline1 != NULL){
			count++;
			scxmlline1 = scxmlline1->nextScxmlLine;
		}
	return count;
}

int ScxmlLayout::subStateCount(State *state){
	if(state==NULL)
		return 0;
	return subStateCount(state->Next)+subStateCount(state->m_subState)+1;
}
void ScxmlLayout::changeRectangularSize(ScxmlLayout *scxmllayout,bool repeat){
	ScxmlRectangle *scxmlRectangle=scxmllayout->rect;
    OnEntry *onenry=NULL;
	ScxmlText *text=NULL;
	while(scxmlRectangle!=NULL){
		onenry=this->so->m_OnEntry;
		referenceY=0;
/*		scxmlRectangle->stateId=changeRectangularSizeLength(scxmlRectangle->stateId,scxmlRectangle,scxmllayout);
		scxmlRectangle->scxmlRectangleLine=new ScxmlLine();
		scxmlRectangle->scxmlRectangleLine->x1=scxmlRectangle->x0-scxmlRectangle->w;
		scxmlRectangle->scxmlRectangleLine->y1=scxmlRectangle->y0-scxmlRectangle->h+referenceY;
		scxmlRectangle->scxmlRectangleLine->x2=scxmlRectangle->x0+scxmlRectangle->w;
		scxmlRectangle->scxmlRectangleLine->y2=scxmlRectangle->y0-scxmlRectangle->h+referenceY;
		scxmlRectangle->scxmlRectangleLine->event=scxmlRectangle->m_Id;
        scxmlRectangle->scxmlRectangleLine->flag=0;*/
    	while(onenry!=NULL){
			if(string(onenry->m_parentStateId)==scxmlRectangle->m_Id)
				break;
			onenry=onenry->Next;
		}
		if(onenry!=NULL){
			if(onenry->m_Assign!=NULL&&onenry->m_Assign->m_Loaction!=NULL&&onenry->m_Assign->m_Expr!=NULL){
				scxmlRectangle->onentryaction=new ScxmlText();
				scxmlRectangle->onentryaction->content="<assign: location="+string(onenry->m_Assign->m_Loaction)+"expr="+string(onenry->m_Assign->m_Expr)+"/>";
                scxmlRectangle->onentryaction=changeRectangularSizeLength(scxmlRectangle->onentryaction,scxmlRectangle,scxmllayout);
			}
			if(onenry->m_Log!=NULL&&onenry->m_Log->m_Expr!=NULL){
				if(scxmlRectangle->onentryaction!=NULL){
					text=scxmlRectangle->onentryaction;
                    while(text->next!=NULL)
						text=text->next;
					text->next=new ScxmlText();
					text=text->next;
				}
				else{
					scxmlRectangle->onentryaction=new ScxmlText();
					text=scxmlRectangle->onentryaction;
				}
				 text->content=text->content+"<log: expr="+string(onenry->m_Log->m_Expr)+"/>";
				 scxmlRectangle->onentryaction=changeRectangularSizeLength(text,scxmlRectangle,scxmllayout);
			}
			if(onenry->m_Send!=NULL&&onenry->m_Send->m_Event!=NULL){
					if(scxmlRectangle->onentryaction!=NULL){
						text=scxmlRectangle->onentryaction;
						while(text->next!=NULL)
							text=text->next;
						text->next=new ScxmlText();
						text=text->next;
					}
					else{
					scxmlRectangle->onentryaction=new ScxmlText();
					text=scxmlRectangle->onentryaction;
					}
					if(onenry->m_Send->m_Target!=NULL)
						text->content=text->content+"<send: event="+string(onenry->m_Send->m_Event)+string(onenry->m_Send->m_Target)+"/>";
					else
						text->content=text->content+"<send: event="+string(onenry->m_Send->m_Event)+"/>";
					scxmlRectangle->onentryaction=changeRectangularSizeLength(text,scxmlRectangle,scxmllayout);
			}
			if(onenry->m_Raise!=NULL&&onenry->m_Raise->m_Event!=NULL){
				if(scxmlRectangle->onentryaction!=NULL){
					text=scxmlRectangle->onentryaction;
					while(text->next!=NULL)
						text=text->next;
					text->next=new ScxmlText();
					text->content=text->content+"<raise: event="+string(onenry->m_Raise->m_Event)+"/>";
				}
				else{
					scxmlRectangle->onentryaction=new ScxmlText();
					scxmlRectangle->onentryaction->content="<log: expr="+string(onenry->m_Log->m_Expr)+"/>";
			}
		 }
		}
//		scxmlRectangle->scxmlRectangleLine->event="";
		scxmlRectangle=scxmlRectangle->nextScxmlRectangle;
	}
	if(scxmllayout->Next!=NULL&&repeat==TRUE)
	changeRectangularSize(scxmllayout->Next,TRUE);
}

ScxmlText *ScxmlLayout::changeRectangularSizeLength(ScxmlText *text,ScxmlRectangle *scxmlRectangle,ScxmlLayout *scxmllayout){
	int number=0;
	int l=(text->content).length();
	int n=scxmlRectangle->w/4;
	int start=0; 
	int end=n;
	if(l<=end){
		referenceY=referenceY+15;
		return text;
	}
/*	ScxmlRectangle *scxmlRectangle1=scxmllayout->rect;
	while(scxmlRectangle1!=NULL){
		number++;
        scxmlRectangle1=scxmlRectangle1->nextScxmlRectangle;
	}
	if(number>=4&&scxmlRectangle->biggerFlag!=1&&scxmlRectangle->scxmlRectangleLine!=NULL){
	scxmlRectangle->flag=1;*/
/*	if(scxmllayout->centreX>scxmlRectangle->x0)
      scxmlRectangle->x0=scxmlRectangle->x0+scxmlRectangle->w;
    else if(scxmllayout->centreX<scxmlRectangle->x0)
       scxmlRectangle->x0=scxmlRectangle->x0-scxmlRectangle->w;
	else
       scxmlRectangle->x0=scxmlRectangle->x0;
    if(scxmllayout->centreY>scxmlRectangle->y0)
       scxmlRectangle->y0=scxmlRectangle->y0+scxmlRectangle->h;
	else if(scxmllayout->centreY<scxmlRectangle->y0)
		scxmlRectangle->y0=scxmlRectangle->y0-scxmlRectangle->h;
	else
        scxmlRectangle->y0=scxmlRectangle->y0;*/

/*    scxmlRectangle->scxmlRectangleLine->y1= (scxmlRectangle->y0-2*scxmlRectangle->h)+(scxmlRectangle->scxmlRectangleLine->y1-(scxmlRectangle->y0-scxmlRectangle->h));
    scxmlRectangle->scxmlRectangleLine->y2=scxmlRectangle->scxmlRectangleLine->y1;
	scxmlRectangle->scxmlRectangleLine->x1=scxmlRectangle->scxmlRectangleLine->x1-scxmlRectangle->w;
    scxmlRectangle->scxmlRectangleLine->x2=scxmlRectangle->scxmlRectangleLine->x2+scxmlRectangle->w;
	scxmlRectangle->w=2*scxmlRectangle->w;
	scxmlRectangle->h=2*scxmlRectangle->h;
	if(scxmlRectangle->x0+scxmlRectangle->w>scxmllayout->centreX*2){
   			scxmlRectangle->scxmlRectangleLine->x1=scxmlRectangle->scxmlRectangleLine->x1-(scxmlRectangle->x0+scxmlRectangle->w-scxmllayout->centreX*2);
			scxmlRectangle->scxmlRectangleLine->x2=scxmlRectangle->scxmlRectangleLine->x2-(scxmlRectangle->x0+scxmlRectangle->w-scxmllayout->centreX*2);
            scxmlRectangle->x0=centreX*2-scxmlRectangle->w;
	}
	if(scxmlRectangle->x0-scxmlRectangle->w<0){
			scxmlRectangle->scxmlRectangleLine->x1=scxmlRectangle->scxmlRectangleLine->x1+(scxmlRectangle->w-scxmlRectangle->x0);
			scxmlRectangle->scxmlRectangleLine->x2=scxmlRectangle->scxmlRectangleLine->x2+(scxmlRectangle->w-scxmlRectangle->x0);
			scxmlRectangle->x0=scxmlRectangle->w;
	}

	if(scxmlRectangle->y0+scxmlRectangle->h>scxmllayout->centreY*2){
			scxmlRectangle->scxmlRectangleLine->y1=scxmlRectangle->scxmlRectangleLine->y1-(scxmlRectangle->y0+scxmlRectangle->h-scxmllayout->centreY*2);
			scxmlRectangle->scxmlRectangleLine->y2=scxmlRectangle->scxmlRectangleLine->y2-(scxmlRectangle->y0+scxmlRectangle->h-scxmllayout->centreY*2);
			scxmlRectangle->y0=centreY*2-scxmlRectangle->h;
	}
	if(scxmlRectangle->y0-scxmlRectangle->h<0){
			scxmlRectangle->scxmlRectangleLine->y1=scxmlRectangle->scxmlRectangleLine->y1+(scxmlRectangle->h-scxmlRectangle->y0);
			scxmlRectangle->scxmlRectangleLine->y2=scxmlRectangle->scxmlRectangleLine->y2+(scxmlRectangle->h-scxmlRectangle->y0);
			scxmlRectangle->y0=scxmlRectangle->h;
	}

	}*/
	double x=scxmlRectangle->x0-scxmlRectangle->w+2;
	double y=scxmlRectangle->y0-scxmlRectangle->h+referenceY+2;
	ScxmlText *text1=new ScxmlText();
	text->next=text1;
	while(l>end){
		text1->content=text->content.substr(start,end-1);
		text1->x=x;
		text1->y=y+15;
		start=end;
		end=2*end;
		if(l>start){
			text1->next=new ScxmlText();
			text1=text1->next;
			if(l<=end)
				text1->content=text->content.substr(start,end-1);
		}
	}
	text=text->next;
	referenceY=text1->y;
	return text;
}
void ScxmlLayout::Resize(double width,double height)
{
	int i,n=0;
	this->centreX=width/2;
	this->centreY=height/2;
 	ScxmlRectangle *rectangle1=this->rect;
    while (rectangle1!=NULL)
    {
		n++;
		rectangle1=rectangle1->nextScxmlRectangle;
    }
	  rectangle1=this->rect;
	for (i = 0; i < n&&rectangle1!=NULL; i++){
		rectangle1->x0 = this->centreX+ (this->centreX - this->centreX /n)*cos(2 * i*PI / n);
		rectangle1->y0 = this->centreY + (this->centreY - this->centreY /n)*sin(2 * i*PI / n);
		if(n>=3){
		rectangle1->w=this->centreX/(n);
        rectangle1->h=this->centreY/(n);
		}
		else if(n==2){
		rectangle1->w=this->centreX/(1.5*n);
		rectangle1->h=this->centreY/(1.5*n);
		}
		else{
		rectangle1->w=this->centreX/(2*n);
		rectangle1->h=this->centreY/(2*n);
		}
		if (rectangle1->flag==0||rectangle1->flag==2)
		{
			rectangle1->h=rectangle1->h/2;
			rectangle1->w=rectangle1->h;

		}

		rectangle1=rectangle1->nextScxmlRectangle;
	}
	this->changeRectangularSize(this,FALSE);
	this->scxmlline=NULL;
	this->getPositionLine(this);
}