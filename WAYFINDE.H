#include<math.h>
#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include"beta/level.h"
#define NULL 0
struct TILE{
	int x,y;
	struct TILE* parent;
	int visited;//1 for visited,0 for not visited
	int cost;
};
typedef struct TILE* TILEPTR;
struct node{
	struct node* next;
	TILEPTR data;
	int c;
};
typedef struct node* NODEPTR;
int cost(int fx,int fy,int cx,int cy);
void addnode(int fx,int fy,int cx,int cy);
class list{
	NODEPTR listptr;
public:
	list();
	~list();
	void push(TILEPTR,int cost);
	void emptylist();
	int empty();
	TILEPTR pop();
}
list::list(){
	listptr=0;
}
list::~list(){
	NODEPTR p;
	while(listptr!=0){
		p=listptr;
		listptr=listptr->next;
		delete p;
	}
}
void list::emptylist(){
	NODEPTR p;
	while(listptr!=0){
		p=listptr;
		listptr=listptr->next;
		delete p;
	}
}

int list::empty(){
	if(listptr==0){
		return 1;
	}
	else{
		return 0;
	}
}
void list:: push(TILEPTR data,int cost){
	NODEPTR new1;
	NODEPTR head_ptr;
	NODEPTR back;
	new1=new node;
	new1->data=data;
	new1->c=cost;
	if(listptr==NULL){//if list is empty
		listptr=new1;
		new1->next=NULL;
	}
	else{
		if(cost<listptr->c){//insert at first posotion
			new1->next=listptr;
			listptr=new1;
		}else{//insert after the node whose cost is just less than current node
			back=listptr;
			head_ptr=listptr;
			while(cost>=head_ptr->c){
				back=head_ptr;
				head_ptr=head_ptr->next;
				if(head_ptr==NULL ){
					break;
				}
			}
			new1->next=head_ptr;
			back->next=new1;
		}
	}
}
TILEPTR list::pop(){
	NODEPTR p;
	TILEPTR t;
	if(listptr==0){
		//cout<<"empty list";
		return(0);

	}
	else{
		p=listptr;
		listptr=p->next;
		t=p->data;
		delete p;
		return(t);
	}
}

/***********************queue class ends***************/
/********pathfinder class**************************/
struct TILE tile[40][30];
class c_path{
	int sx,sy,fx,fy;
	list open;
public:
	void set(int,int,int ,int);
	int pathfinder();
	void addnode(int cx,int cy);
	int finddir();
	void makepath();
	void tracepath();
	void reset();
	~c_path();
};
/********pathfinder class ends**************************/
void c_path::reset(){
		for(int i=0;i<30;i++){
			for(int j=0;j<40;j++){
				tile[j][i].visited=0;
			}
		}
		open.emptylist();
	}
int cost(int fx,int fy,int cx,int cy){
	int b;
	b=abs(fx-cx)+abs(fy-cy);
	return b;
}
void c_path::set(int x1,int y1,int x2,int y2){
	sx=x1;
	sy=y1;
	fx=x2;
	fy=y2;
}
int c_path::pathfinder(){
	int cost1=0;
	int cx,cy;
	struct TILE newtile;
	struct TILE* tileptr;
	struct TILE* p;
	cx=sx;
	cy=sy;
	cost1=cost(fx,fy,cx,cy);
	tile[cx][cy].cost =cost1;
	tile[cx][cy].x=cx;
	tile[cx][cy].y=cy;
	tile[cx][cy].parent = NULL;
	tile[cx][cy].visited=1;
	open.push(&tile[cx][cy],cost1);
	while(open.empty()!=1){
		tileptr= open.pop();
		if(tileptr->x ==fx && tileptr->y==fy){
			return 1;
		}
		else{
		cx=tileptr->x;
		cy=tileptr->y;
		addnode(cx,cy-1);
		addnode(cx-1,cy);
		addnode(cx,cy+1);
		addnode(cx+1,cy);
		}
	}
	return 0;
}
void c_path::addnode(int cx,int cy){
	int cost1=cost(fx,fy,cx,cy);
	TILEPTR temp;
	int x=10000;
	if(tile[cx][cy].visited != 1 && a[cy][cx]!=1){
		tile[cx][cy].x=cx;
		tile[cx][cy].y=cy;
		tile[cx][cy].visited=1;
//check for neightbours to see if they are already visited,if visited make parent node with the lowest cost
		if(tile[cx+1][cy].visited==1 ){
			if(tile[cx+1][cy].cost<=x){
				x=tile[cx+1][cy].cost;
				temp=&tile[cx+1][cy];
				}
			}
		if(tile[cx][cy+1].visited==1 ){
			if(tile[cx][cy+1].cost<=x){
				temp=&tile[cx][cy+1];
				x=tile[cx][cy+1].cost;
				}
			}
		if(tile[cx-1][cy].visited==1){
			if(tile[cx-1][cy].cost<=x){
				temp=&tile[cx-1][cy];
				x=tile[cx-1][cy].cost;
				}
			}
		if(tile[cx][cy-1].visited==1){
			if(tile[cx][cy-1].cost<=x){
				temp=&tile[cx][cy-1];
				x=tile[cx][cy-1].cost;
				}
			}
		tile[cx][cy].parent=temp;
		tile[cx][cy].cost=cost1;
		open.push(&tile[cx][cy],cost1);
		}
	}
void c_path::tracepath(){
	TILEPTR p;
	int i=0;
	p=&tile[fx][fy];
	while(p->parent->parent!=NULL && i<100)
	{
		//cout<<"path,";
		//cout<<"("<<p->x<<","<<p->y<<")";
		//cout<<"("<<p->parent->x<<","<<p->parent->y<<")";
		i++;
		if(i>14){
			i=0;
		}
		setcolor(3);
		setfillstyle(SOLID_FILL,i);
		bar3d(p->x*10,p->y*10,p->x*10+10,p->y*10+10,0,0);
		p=p->parent;
	}
}
int c_path::finddir(){
	TILEPTR p;
	int success=0;
	if(sx==fx && sy==fy){
		return(0);
	}
	success=pathfinder();
	p=&tile[fx][fy];
	if(success==1){
//if path is found,then backtrace to reach the snake head node and the first step
		while(p->parent->parent!=NULL)
		{
			p=p->parent;
		}
//retunr direction as per the first step
		if(p->x>tile[sx][sy].x){
			return 1;
		}
		if(p->y>tile[sx][sy].y){
			return 2;
		}
		if(p->x<tile[sx][sy].x){
			return 3;
		}
		if(p->y<tile[sx][sy].y){
			return 4;
		}
	}
	return 0;
}
void c_path::~c_path(){
	for(int i=0;i<30;i++){
		for(int j=0;j<40;j++){
			tile[i][j].visited=0;
			tile[i][j].parent=0;
		}
	}
	open.emptylist();
}