#include"beta\constants.h"
class SnakeAi{
	int x,y,dir,length;
	char score_str[5];
	char level_str[5];
	int score;
	unsigned int key,key2;
	Queue queue;
	struct coordinate snake[55];
public:
	SnakeAi(int,int,int);
	friend void rungame(SnakeAi*,food*,game*);
	friend int rungame2(SnakeAi*,food*,game*,SnakeAi* );
	friend int rungameai(SnakeAi* s1,SnakeAi *s2,food* f1,game* g1,c_path* newpath);
	void drawsnake(int color);
	int detectcollision();
	int getdirection(int);
	void setdirectionai(int b);
	void go();
	void updatescore(int,int);
	void displayscore(int);
	void addscore();
	int getdir();
	void setdir(int dir1);
	int getlength();
	int getscore();
	void addlength();
	int headcollision(struct coordinate s1[]);
};
void SnakeAi::addscore(){
		score++;
	}
int SnakeAi::getdir(){
		return dir;
	}
void SnakeAi::setdir(int dir1){
		dir=dir1;
	}
int SnakeAi::getlength(){
		return(length);
	}
int SnakeAi::getscore(){
		return(score);
	}
SnakeAi::SnakeAi(int initx=4,int inity=3, int direction=1){
	dir=direction;
	length=3;
	score=0;
	if(direction==3){
		for(int i=0;i<length;i++){/*set snake initial position*/
			snake[i].x=(initx+i)*10;
			snake[i].y=inity*10;
			a[snake[i].y/10][snake[i].x/10]=1;
		}
	}else if(direction==1){
		for(int i=0;i<length;i++){/*set snake initial position*/
			snake[i].x=(initx-i)*10;
			snake[i].y=inity*10;
			a[snake[i].y/10][snake[i].x/10]=1;
		}
	}
	x=snake[0].x;
	y=snake[0].y;
}
void SnakeAi::addlength(){
		int x,y;
		length++;
		snake[length-1].x=snake[length-2].x;
		snake[length-1].y=snake[length-2].y;
		x=snake[length-1].x;
		y=snake[length-1].y;
		a[y][x]=1;
	}
int SnakeAi::headcollision(struct coordinate s1[]){
	if(snake[0].x==s1[0].x && snake[0].y==s1[0].y){
		setcolor(RED);
		setfillstyle(INTERLEAVE_FILL,RED);
		bar3d(snake[0].x,snake[0].y,snake[0].x+10,snake[0].y+10,0,0);//head of snake
		return(1);
	}
	else{
		return(0);
	}
}
/***********************draw snake***********************************/
void SnakeAi::drawsnake (int color){
	int delx,dely;
	delx=snake[length-1].x;//last portion coordinates
	dely=snake[length-1].y;
	for(int j=0;j<length;j++){
		a[snake[j].y/10][snake[j].x/10]=1;
	}
	a[snake[0].y/10][snake[0].x/10]=1;
	a[dely/10][delx/10]=0;
	//swap coordinates
	for(int i=length-1;i>0;i--){
		snake[i].x=snake[i-1].x;
		snake[i].y=snake[i-1].y;
	}
	snake[0].x=x;
	snake[0].y=y;
	//overwrite last part with background color so that it becomes invisible
	setcolor(boardcolor);
	setfillstyle(SOLID_FILL,boardcolor);
	bar3d(delx,dely,delx+10,dely+10,0,0);
	//head of snake
	setcolor(color);
	setfillstyle(SOLID_FILL,color);
	bar3d(snake[0].x,snake[0].y,snake[0].x+10,snake[0].y+10,0,0);
	//draw snake body
	setcolor(boardcolor);
	setfillstyle(SOLID_FILL,color);
	for(i=1;i<length;i++){
	       bar3d(snake[i].x,snake[i].y,snake[i].x+10,snake[i].y+10,0,0);//body of snake
	}
}
/*******************detectcollision*********************/
int SnakeAi::detectcollision(){
	if(a[snake[0].y/10][(snake[0].x)/10]==1){
		setcolor(RED);
		setfillstyle(INTERLEAVE_FILL,RED);
		bar3d(snake[0].x,snake[0].y,snake[0].x+10,snake[0].y+10,0,0);//head of snake
		return(1);
	}
	return(0);
}
/***********getdirection************************************************/
/**************sets the direction as per keyhit obtained from the  kbhit function*/
//sets direction and also returns 1 if the user has chosen to end the game
int SnakeAi::getdirection(int a){
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
void SnakeAi::setdirectionai(int b){
	switch(b){
		case 1:
			if(dir !=3){
				dir=1;
			}
		case 3://a:left
			if(dir!=1){
				dir=3;
			}
			break;
		case 2://s:down
			if(dir!=4){
				dir=2;
			}
			break;
		case 4://w:up
			if(dir!=2){
				dir=4;
			}
			break;
		}
}
/*****************adds coordinates as per the direction****************/
void SnakeAi::go(){
	switch(dir){
	case 1://right
		x+=10;
		if(x>=map_width*10){
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
void SnakeAi::updatescore(int x,int score){
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
void SnakeAi::displayscore(int x){
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
		setcolor(BLUE);//player 2's color
		outtextxy(30,395,"PLAYER 2");
		setcolor(0);
		setfillstyle(SOLID_FILL,15);
		bar3d(240,380,340,440,0,0);
		setcolor(8);
		settextstyle(0, HORIZ_DIR, 5);
		outtextxy(250,390,"0");
	}
}
