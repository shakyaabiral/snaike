#include"beta2\constants.h"
#include"beta2\segment.h"
class c_snake{
	int x,y,dir,length;
	char score_str[5];
	char level_str[5];
	int score;
	unsigned int key,key2;
	Queue queue;
public:
	Snake segment;
	c_snake(int,int,int);
	friend int checkFoodHit(c_snake* s1,food* f[]);
	friend void rungame(c_snake*,food *f[],game*);
	friend int rungame2(c_snake*,food*,game*,c_snake* );
	friend int rungameai(SnakeAi* s1,SnakeAi* s2,food* f1,game* g1,c_path* newpath);
	void drawsnake(int color);
	int detectcollision();
	int hitothersnake(struct coordinate[],int length);
	int getdirection(int);
	void setdirectionai(int b);
	int getdir();
	void setdir(int dir1);
	void go();
	void reset(int, int,int);
	int getlength();
	void updatescore(int,int);
	void displayscore(int);
	void addscore(int point);
	int getscore();
	int headcollision(struct coordinate s1[]);
	int headcollision(c_snake* s1);
};
c_snake::c_snake(int initx=4,int inity=3, int direction=1){
	dir=direction;
	length=2;
	score=0;
	segment.setup(initx,inity);
	x=segment.firstSegment()->x;
	y=segment.firstSegment()->y;
}
int c_snake::getlength(){
	return(length);
	}
void c_snake::addscore(int x=1){
	score+=x;
	}
int c_snake::getscore(){
	return(score);
	}
int c_snake::getdir(){
	return dir;
	}
void c_snake::setdir(int dir1){
	dir=dir1;
	}
void c_snake::reset(int cx=3,int cy=4,int direction=1){
	dir=direction;
	length=2;
	segment.reset(cx,cy);
	x=segment.firstSegment()->x;
	y=segment.firstSegment()->y;
}
int c_snake::headcollision(c_snake* s1){
	int x1,y1,x2,y2;
	x1=segment.firstSegment()->x;
	y1=segment.firstSegment()->y;
	x2=s1->segment.firstSegment()->x;
	y2=s1->segment.firstSegment()->y;
	if(x1==x2 && y1==y2){
		setcolor(RED);
		setfillstyle(INTERLEAVE_FILL,RED);
		bar3d(segment.firstSegment()->x,segment.firstSegment()->y,segment.firstSegment()->x+10,segment.firstSegment()->y+10,0,0);
		return(1);
	}
	else{
		return(0);
	}

}
/***********************draw snake***********************************/
void c_snake::drawsnake (int color){
	int delx,dely;
	int x1,y1;
	SegmentPtr newPtr;
	delx=segment.lastSegment()->x;
	dely=segment.lastSegment()->y;
	segment.shift(x,y);
	//overwrite last part with background color so that it becomes invisible
	setcolor(boardcolor);
	setfillstyle(SOLID_FILL,boardcolor);
	bar3d(delx,dely,delx+10,dely+10,0,0);
	a[dely/10][delx/10]=0;
	//head of snake
	setcolor(color);
	setfillstyle(SOLID_FILL,color);
	bar3d(segment.firstSegment()->x,segment.firstSegment()->y,segment.firstSegment()->x+10,segment.firstSegment()->y+10,0,0);
	//draw snake body
	setcolor(boardcolor);
	setfillstyle(SOLID_FILL,color);
	newPtr=segment.lastSegment();
	while(newPtr!=segment.firstSegment()){
		x1=newPtr->x;
		y1=newPtr->y;
		a[y1/10][x1/10]=1;
		bar3d(newPtr->x,newPtr->y,newPtr->x+10,newPtr->y+10,0,0);
		newPtr=newPtr->next;
	}
	a[segment.lastSegment()->y/10][segment.lastSegment()->x/10]=1;
}
/*******************detectcollision*********************/
int c_snake::detectcollision(){
	if(a[(segment.firstSegment()->y)/10][(segment.firstSegment()->x)/10]==1){
		setcolor(RED);
		setfillstyle(INTERLEAVE_FILL,RED);
		bar3d(segment.firstSegment()->x,segment.firstSegment()->y,segment.firstSegment()->x+10,segment.firstSegment()->y+10,0,0);//head of snake
		return(1);
	}
	return(0);
}
/***********getdirection************************************************/

/**************sets the direction as per keyhit obtained from the  kbhit function*/
int c_snake::getdirection(int a){
	int gamestat=1;
	switch (a){
		case 77://right
			if(dir!=3){
				dir=1;
			}
			break;
		case 75://left
			if(dir!=1){
				dir=3;
			}
			break;
		case 80://down
			if(dir!=4){
				dir=2;
			}
			break;
		case 72://up
			if(dir!=2){
				dir=4;
			}
			break;
		case 100://d:right
			if(dir !=3){
				dir=1;
			}
		case 97://a:left
			if(dir!=1){
				dir=3;
			}
			break;
		case 115://s:down
			if(dir!=4){
				dir=2;
			}
			break;
		case 119://w:up
			if(dir!=2){
				dir=4;
			}
			break;

		case 79://end button to pause
			getimage(70,100,230,130,buff);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL,BLACK);
			bar3d(70,100,230,130,0,0);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 2);
			outtextxy(80,110,"EXIT? y/n");
			while(1){
				key=getch();
				if(key=='y'){
					gamestat=0;
					break;
				}else if (key=='n'){
					putimage(70,100,buff,COPY_PUT);
					break;
				}
				else{
					continue;
				}
			}
			break;
	}
	return(gamestat);
}
void c_snake::setdirectionai(int b){
	if(b==1 && dir !=3){
		dir=1;
	}
	else if(b==2 && dir !=4){
		dir=2;
	}
	else if(b==3 && dir !=1){
		dir=3;
	}
	else if(b==4 && dir !=2){
		dir=4;
	}
}
/*****************adds coordinates as per the direction****************/
void c_snake::go(){
	switch(dir){
	case 1://right
		x+=10;
		if(x>=map_width*10){//if snake goes beyond map then return it on the other end
			x=0;
		}
		break;
	case 2://bottom
		y+=10;
		if(y>=map_height*10){
			y=0;
		}
		break;
	case 3://left
		x-=10;
		if(x<0){
			x=10*(map_width-1);
		}
		break;
	case 4://top
		y-=10;
		if(y<0){
			y=10*(map_height-1);
		}
		break;
	}

}
/***********************funciton updatescore*********************/
void c_snake::updatescore(int x,int score){//update the score
if(x==1){
	itoa(score,score_str,10);
	setcolor(0);
	setfillstyle(SOLID_FILL,15);
	bar3d(240,310,340,370,0,0);
	setcolor(8);
	settextstyle(0, HORIZ_DIR, 5);
	outtextxy(250,320,score_str);
}else if(x==2){
	itoa(score,score_str,10);
	setcolor(0);
	settextstyle(0, HORIZ_DIR, 5);
	setfillstyle(SOLID_FILL,15);
	bar3d(240,380,340,440,0,0);
	setcolor(8);
	outtextxy(260,390,score_str);
}
}
/****************display score***********************************************/
void c_snake::displayscore(int x){
	if(x==1){
		setcolor(0);
		setfillstyle(SOLID_FILL,15);
		bar3d(20,310,230,370,0,0);
		settextstyle(0, HORIZ_DIR, 5);
		setcolor(8);
		outtextxy(30,320,"SCORE");
		setcolor(0);
		setfillstyle(SOLID_FILL,15);
		bar3d(240,310,340,370,0,0);
		setcolor(8);
		outtextxy(250,320,"0");
	}else if(x==2){
		setcolor(0);
		setfillstyle(SOLID_FILL,15);
		bar3d(20,310,230,370,0,0);
		settextstyle(0, HORIZ_DIR, 3);
		setcolor(GREEN);//player 1's color
		outtextxy(30,320,"PLAYER 1");
		setcolor(0);
		setfillstyle(SOLID_FILL,15);
		bar3d(240,310,340,370,0,0);
		setcolor(8);
		settextstyle(0, HORIZ_DIR, 5);
		outtextxy(250,320,"0");
		setcolor(0);
		setfillstyle(SOLID_FILL,15);
		bar3d(20,380,230,440,0,0);
		settextstyle(0, HORIZ_DIR, 3);
		setcolor(BLUE);//players 2's color
		outtextxy(30,395,"PLAYER 2");
		setcolor(0);
		setfillstyle(SOLID_FILL,15);
		bar3d(240,380,340,440,0,0);
		setcolor(8);
		settextstyle(0, HORIZ_DIR, 5);
		outtextxy(250,390,"0");
	}
}
