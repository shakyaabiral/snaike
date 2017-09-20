#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<iostream.h>
#include<stdlib.h>
#include "snake\queue.h"
#include "new\wayfinder.h"
#define levellimit 25
#define initial_pause_length 200
#define pause_length_change 20
#define backgroundcolor 7
#define boardcolor 0
#define wallcolor  6
#define foodcolor 14
#define snakecolor 10
#define snake2color BLUE
#define headcolor 2
#define UP 72
#define RIGHT 77
#define LEFT 75
#define DOWN 80
#define END 79
#define map_width 40
#define map_height 30
class c_snake;
class food;
class game;
struct coordinate{
	int x;
	int y;
};
struct queue q1,q2;
struct queue *queue1=&q1;
struct queue *queue2=&q2;
char buff[4000];
class food{
	int foodx,foody,foodstat;
public:
	void new_food_pos();
	int checkfoodhit(struct coordinate[]);
	void drawfood();
	int getx(){
		return foodx;
	}
	int gety(){
		return foody;
	}
};
/********************************function checkfoodhittest**************************/
int food::checkfoodhit(struct coordinate snake[]){
	if(snake[0].x==foodx && snake[0].y==foody){
		return(1);
	}else{
		return(0);
	}
}
/**********************gets new food position****************************/

void food::new_food_pos(){
	int food_check=1;
	do{//to check food doesn't overlap on the snake or wall
		randomize();
		foodx=(rand()%(map_width-2))*10+10; //+10 is done to exclude(0,0)
		foody=(rand()%(map_height-2))*10+10;
/*min x=10 max x=620 max y=290 and min y=10. returns value between 10 and 280 in the multiples of 10.since snake coordinates are multiples of 10.it helps detect collision */
		if(a[foody/10][foodx/10]==1){
			food_check=1;
			continue;
			/*for(int i=0;i<length;i++){
				if((foodx==snake[i].x && foody==snake[i].y) ){
					food_check=1;
					break;
				}else{
					food_check=0;
					continue;
				}
			} */
		}
		else{
			food_check=0;
			break;
		}
	}while(food_check==1);
}
/**************draw food**************************************************/
void food::drawfood(){
	setfillstyle(SOLID_FILL,foodcolor);
	setcolor(foodcolor);
	circle(foodx+5,foody+5,4);
	floodfill(foodx+5,foody+5,foodcolor);
}
class c_snake{
	int x,y,dir,length;
	char score_str[5];
	char level_str[5];
	int score;
	unsigned int key,key2;
public:
	struct coordinate snake[50];
	c_snake(int,int,int);
	void drawsnake(int color);
	int detectcollision();
	int hitothersnake(struct coordinate[],int length);
	int getdirection(int);
	void setdirection2(int);
	void setdirectionai(int b);
	int getdir(){
		return dir;
	}
	void setdir(int dir1){
		dir=dir1;
	}
	void go();
	void reset(int, int);
	int getlength(){
		return(length);
	}
	void updatescore(int,int);
	void displayscore(int);
	void addscore(){
		score++;
	}
	int getscore(){
		return(score);
	}
	void addlength(){
		int x,y;
		length++;
		snake[length-1].x=snake[length-2].x;
		snake[length-1].y=snake[length-2].y;
		x=snake[length-1].x;
		y=snake[length-1].y;
		a[y][x]=1;

	}
	int headcollision(struct coordinate s1[]){
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
};
class game{
	int level,score,status;
	int pause_length;
	char score_str[5];
	char level_str[5];
public:
	void display_speed();
	void drawmap();
	void displayscore();
	void displaylevel();
	void changelevel();
	void changestatus();
	int gamestatus();
	int getlevel();
	int get_pause(){
		return(pause_length);
	}
	void addscore();
	int getscore();
	void updatescore();
	void updatelevel();
	game(int lvl=0,int pause=initial_pause_length){
		pause_length=pause;
		level=lvl;
		score=0;
		status=1;
	}
};
/****************c_snake constructor***********************/
c_snake::c_snake(int initx=4,int inity=3, int direction=1){
	dir=direction;
	length=3;
	score=0;
	init_queue(queue1);
	init_queue(queue2);
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
void c_snake::reset(int cx=3,int cy=4){
	dir=1;
	length=2;
	init_queue(queue1);
	for(int i=0;i<length;i++){
		snake[i].x=(cx-i)*10;
		snake[i].y=cy*10;
		a[snake[i].y/10][snake[i].x/10]=1;
	}
	x=snake[0].x;
	y=snake[0].y;
}

/***********************draw snake***********************************/
void c_snake::drawsnake (int color){
	int delx,dely;
	delx=snake[length-1].x;//last portion coordinates
	dely=snake[length-1].y;
	/*swap coordinates*/
	for(int i=length-1;i>0;i--){
		snake[i].x=snake[i-1].x;
		snake[i].y=snake[i-1].y;
	}
	snake[0].x=x;
	snake[0].y=y;
	/*overwrite last part with background color so that it becomes invisible*/
	setcolor(boardcolor);
	setfillstyle(SOLID_FILL,boardcolor);
	bar3d(delx,dely,delx+10,dely+10,0,0);
	/*draw snake body*/
	setcolor(color);
	setfillstyle(SOLID_FILL,color);
	bar3d(snake[0].x,snake[0].y,snake[0].x+10,snake[0].y+10,0,0);//head of snake
	setcolor(boardcolor);
	setfillstyle(SOLID_FILL,color);
	for(i=1;i<length;i++){
	       bar3d(snake[i].x,snake[i].y,snake[i].x+10,snake[i].y+10,0,0);//body of snake
	}
}
/***********************hitothersnake ***************************/
int c_snake:: hitothersnake(struct coordinate s1[],int l){
	for(int i=0;i<l;i++){
		if(snake[0].x==s1[i].x && snake[0].y==s1[i].y){
			setcolor(RED);
			setcolor(RED);
			setfillstyle(INTERLEAVE_FILL,RED);
			bar3d(snake[0].x,snake[0].y,snake[0].x+10,snake[0].y+10,0,0);//head of snake
			return(1);
		}
	}
	return(0);
}
/*******************detectcollision*********************/
int c_snake::detectcollision(){
	if(a[(snake[0].y)/10][(snake[0].x)/10]==1){
		setcolor(RED);
		setfillstyle(INTERLEAVE_FILL,RED);
		bar3d(snake[0].x,snake[0].y,snake[0].x+10,snake[0].y+10,0,0);//head of snake
		return(1);
	}
	for(int j=0;j<length-1;j++){
		a[snake[j].y/10][snake[j].x/10]=1;
	}
	a[snake[length-1].y/10][snake[length-1].x/10]=0;
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
void c_snake::setdirection2(int b){
	switch(b){
		case 100:
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
	}

}
/*****************adds coordinates as per the direction****************/
void c_snake::go(){
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


/********************function change status********************************************/
void game::changestatus(){
	if (status==0){
		status=1;
	}else if(status==1){
		status=0;
	}
}

void game::updatelevel(){

}
/********************function gamestatus**********************************************/
int game::gamestatus(){
	return(status);
}
void game::addscore(){
	score++;
}
int game::getscore(){
	return (score);
}
int game::getlevel(){
	return(level);
}

/*****************draw map ********************************************/
void game::drawmap(){
	if(level==1){
		for(int tr=0;tr<map_height;tr++){
			for(int tc=0;tc<map_width;tc++){
				a[tr][tc]=level1[tr][tc];
			}
		}
	}
	else if(level==2){

		for(int tr=0;tr<map_height;tr++){
			for(int tc=0;tc<map_width;tc++){
				a[tr][tc]=level2[tr][tc];
			}
		}

	}
	else if(level==3){

		for(int tr=0;tr<map_height;tr++){
			for(int tc=0;tc<map_width;tc++){
				a[tr][tc]=level3[tr][tc];
			}
		}


	}
	else if(level==4){

		for(int tr=0;tr<map_height;tr++){
			for(int tc=0;tc<map_width;tc++){
				a[tr][tc]=level4[tr][tc];
			}
		}


	}
	else if(level==5){

		for(int tr=0;tr<map_height;tr++){
			for(int tc=0;tc<map_width;tc++){
				a[tr][tc]=level5[tr][tc];
			}
		}


	}
	else if(level==6){

		for(int tr=0;tr<map_height;tr++){
			for(int tc=0;tc<map_width;tc++){
				a[tr][tc]=level6[tr][tc];
			}
		}


	}
	else{

		for(int tr=0;tr<map_height;tr++){
			for(int tc=0;tc<map_width;tc++){
				a[tr][tc]=level7[tr][tc];
			}
		}


	}
	for(int tr=0;tr<map_height;tr++){
		for(int tc=0;tc<map_width;tc++){
			if(a[tr][tc]==1){
				setcolor(boardcolor);
				setfillstyle(SOLID_FILL,wallcolor);
				bar3d(tc*10,tr*10,tc*10+10,tr*10+10,0,0);
			}
			else{
				setcolor(boardcolor);
				setfillstyle(SOLID_FILL,boardcolor);
				bar3d(tc*10,tr*10,tc*10+10,tr*10+10,0,0);
			}
		}
	}
}
/******changes the level **************************************************/

void game::changelevel(){
	if(level==0){// begining of the game
		level++;
		drawmap();
		getimage(10,140,200,160,buff);
		setcolor(15);
		setfillstyle(SOLID_FILL,0);
		bar3d(10,140,200,160,0,0);
		settextstyle(0, HORIZ_DIR,1);
		outtextxy(15,145,"press 'y' key to start");
		while(getch()!='y'){
			continue;
		}
		putimage(10,140,buff,COPY_PUT);
	}else{

		level++;
		pause_length-=pause_length_change;
		drawmap();
		getimage(10,140,200,160,buff);
		setcolor(15);
		setfillstyle(SOLID_FILL,0);
		bar3d(10,140,200,160,0,0);
		settextstyle(0, HORIZ_DIR,1);
		outtextxy(15,145,"press 'y' key to start");
		while(getch()!='y'){
			continue;
		}
		putimage(10,140,buff,COPY_PUT);

	}
	status=1;

}
/***********************************************************/
/*///////////////******************************************/

void display(int num, char *menu[]){
	setcolor(WHITE);
	settextstyle(0,0,1);
	for(int i=0;i<num;i++){
		outtextxy(100,200+(15*i),menu[i]);
	}
}
void highlight(int index){
	index=index-1;
	setcolor(RED);
	rectangle(98,197+(15*index),210,210+(15*index));
	setfillstyle(SOLID_FILL,RED);
	bar3d(85,200+(15*index),95,205+(15*index),0,0);
}
void unhighlight(int index){
	setcolor(BLACK);
	rectangle(98,182+(15*index),210,195+(15*index));
	setfillstyle(SOLID_FILL,BLACK);
	bar3d(85,185+(15*index),95,190+(15*index),0,0);

}
void draw_menu_bar(){
	setcolor(WHITE);

	setfillstyle(SOLID_FILL,BLACK);
	bar3d(80,170,400,300,0,0);
	settextstyle(0,0,1);
	outtextxy(80,310,"Press ENTER TO Select");
	outtextxy(80,330,"Press ESC to Exit");
}
int choose_game_mode(){
	unsigned char key,key1;
	int menu_active=1;
	char *game_mode[2]={"Normal","Advanced"};
	draw_menu_bar();
	setcolor(WHITE);
	settextstyle(0,0,2);
	outtextxy(90,180,"CHOOSE GAME MODE");
	display(2,game_mode);
	highlight(1);
	while(1){
		key=getch();
		if(key=='\r'){
			return(menu_active);
		}
		if(key==27){
			return(0);
		}
		if(key==0){
			key1=getch();
			if(key1==DOWN && menu_active==1){
				menu_active=2;
				unhighlight(1);
				highlight(2);
			}
			else if(key1==UP && menu_active==2){
				menu_active=1;
				unhighlight(2);
				highlight(1);
			}
		}
	}

}
int choose_player(){
	unsigned char key,key1;
	int menu_active=1;
	char *players[2]={"Single Player","Double Player"};
	draw_menu_bar();
	setcolor(WHITE);
	settextstyle(0,0,2);
	outtextxy(90,180,"CHOOSE GAME MODE");
	display(2,players);
	highlight(1);
	while(1){
		key=getch();
		if(key=='\r'){
			return(menu_active);
		}
		if(key==27){
			exit(0);
		}
		if(key==0){
			key1=getch();
			if(key1==DOWN && menu_active==1){
				menu_active=2;
				unhighlight(1);
				highlight(2);
			}
			else if(key1==UP && menu_active==2){
				menu_active=1;
				unhighlight(2);
				highlight(1);
			}
		}
	}
}
int choose_maze(){
	int menu_active=1;
	unsigned char key,key1;
	char *maze[7]={"Maze 1","Maze 2","Maze 3","Maze 4","Maze 5","Maze 6","Maze 7"};
	draw_menu_bar();
	setcolor(WHITE);
	settextstyle(0,0,2);
	outtextxy(90,180,"CHOOSE MAZE");
	display(7,maze);
	highlight(1);
	while(1){
		key=getch();
		if(key=='\r'){
			return(menu_active);
		}
		if(key==27){
			return(0);
		}
		else if(key==0){
			key1=getch();
			if(key1==DOWN && menu_active<7){
				menu_active++;
				highlight(menu_active);
				unhighlight(menu_active-1);
			}
			else if(key1==UP && menu_active>1){
				menu_active--;
				highlight(menu_active);
				unhighlight(menu_active+1);
			}
		}

	}
}

int choose_difficulty(){
	int menu_active=1;
	unsigned char key,key1;
	char *difficulty[5]={"Easy","Standard","Moderate","Hard","Hardest"};
	draw_menu_bar();
	settextstyle(0,0,2);
	setcolor(WHITE);
	outtextxy(90,180,"CHOOSE GAME SPEED");
	display(5,difficulty);
	highlight(1);
	while(1){
		key=getch();
		if(key=='\r'){
			return(menu_active);
		}
		if(key==27){
			return(0);
		}
		else if(key==0){
			key1=getch();
			if(key1==DOWN && menu_active<5){
				menu_active++;
				highlight(menu_active);
				unhighlight(menu_active-1);
			}
			else if(key1==UP && menu_active>1){
				menu_active--;
				highlight(menu_active);
				unhighlight(menu_active+1);
			}
		}

	}
}
void  displaykeys();
int start_msg();
void rungame(c_snake*,food*,game*);
int rungame2(c_snake*,food*,game*,c_snake* );
int ai_getdirection(int sx,int sy,int fx,int fy,int dir);
int rungameai(c_snake* s1,c_snake *s2,food* f1,game* g1,c_path* newpath);
void display_developers();
///********************************************************////////////
/****************************MAIN FUNCITON***************************/
///********************************************************//////////

/******************************RUNGAME SINGLEPLAYER START******************/

void rungame(c_snake* s1,food* f1,game* g1){

	int a,key2;
	while(kbhit()){//checks if key hit is available
		if(getch()==0){/*checks the first byte of the keyboard buffer if it is 0 means an extended code has been pressed so key2 stores the extended code*/
			key2=getch();
			if(key2==UP || key2==DOWN || key2==LEFT || key2==RIGHT || key2==END){
				if(key2!=queue1->data[queue1->rear]){
					insert(queue1,key2);
				}
			}
		}
	}
	if(checkunderflow(queue1)!=1){
		a=remove1(queue1);
		if(s1->getdirection(a)==0){//status=0,ie you chose to exit
			g1->changestatus();
		}
	}
	//sets direction as per keyhit
	s1->go();/*adds coordinates according to the direction to move the snake in the required direction*/
	s1->drawsnake(snakecolor);
	if(f1->checkfoodhit(s1->snake)==1){
		s1->addscore();
		s1->addlength();
		s1->updatescore(1,s1->getscore());
		f1->new_food_pos();//sets new food position
		f1->drawfood();
	}
	if(s1->detectcollision()==1){
		g1->changestatus();
		settextstyle(0, HORIZ_DIR, 2);
		setcolor(WHITE);
		outtextxy(100,140,"GAME OVER");
		settextstyle(0, HORIZ_DIR, 1);
		outtextxy(100,160,"Press Esc to exit");
		while(getch()!=27){
			continue;
		}

	}
}
/******************************RUNGAME SINGLEPLAYER END*********************/
/******************************RUNGAME MULTIPLAYER START********************/

int rungame2(c_snake* s1,food* f1,game* g1,c_snake* s2)
{
	int a,b;
	int key,key2;
	int collide1,collide2;
	while(kbhit()){//checks if key hit is available
		key=getch();
		if(key!=0){/*checks the first byte of the keyboard buffer if it is 0 means an extended code has been pressed so key2 stores the extended code*/
			if(key==97 || key==115 || key==100 || key==119){
				if(key!=queue2->data[queue2->rear]){
					insert(queue2,key);
				}
			}
		}else{
			key2=getch();
			if(key2==UP || key2==DOWN || key2==LEFT || key2==RIGHT || key2==END){
				if(key2!=queue1->data[queue1->rear]){
					insert(queue1,key2);
				}
			}
		}
	}
	if(checkunderflow(queue2)!=1){
		b=remove1(queue2);
		s2->getdirection(b);
	}
	if(checkunderflow(queue1)!=1){
		a=remove1(queue1);
		if(s1->getdirection(a)==0){//status=0,ie you chose to exit
			g1->changestatus();
		}
	}
	s2->go();
	s1->go();
	if(f1->checkfoodhit(s1->snake)==1){
		s1->addscore();
		s1->addlength();
		s1->updatescore(1,s1->getscore());
		f1->new_food_pos();//sets new food position
		f1->drawfood();
	}
	if(f1->checkfoodhit(s2->snake)==1){
		s2->addscore();
		s2->addlength();
		s2->updatescore(2,s2->getscore());
		f1->new_food_pos();//sets new food position
		f1->drawfood();
	}

	if(s1->headcollision(s2->snake)==1){
		if(s1->getscore()==s2->getscore()){
			settextstyle(0, HORIZ_DIR, 2);
			setcolor(WHITE);
			outtextxy(100,140,"DRAW!!!!!!");
			settextstyle(0, HORIZ_DIR, 1);
			outtextxy(100,160,"Press Esc to exit");
			while(getch()!=27){
				continue;
			}
		}
		else if(s1->getscore()<s2->getscore()){
			settextstyle(0, HORIZ_DIR, 2);
			setcolor(WHITE);
			outtextxy(100,140,"Player 2 wins");
			settextstyle(0, HORIZ_DIR, 1);
			outtextxy(100,160,"Press Esc to exit");
			while(getch()!=27){
				continue;
			}
		}else if(s1->getscore()>s2->getscore()){
			settextstyle(0, HORIZ_DIR, 2);
			setcolor(WHITE);
			outtextxy(100,140,"Player 1 wins");
			settextstyle(0, HORIZ_DIR, 1);
			outtextxy(100,160,"Press Esc to exit");
			while(getch()!=27){
				continue;
			}

		}
		g1->changestatus();
		return(0);


	}//else{ if((collide1==0) && (collide2==1)){
	if(s2->detectcollision()==1){
		g1->changestatus();
		settextstyle(0, HORIZ_DIR, 2);
		setcolor(WHITE);
		outtextxy(100,140,"Player 1 wins");
		settextstyle(0, HORIZ_DIR, 1);
		outtextxy(100,160,"Press Esc to exit");
		while(getch()!=27){
			continue;
		}
		return(0);
	}
	 if(s1->detectcollision()==1){//(collide1==1) && (collide2==0)){
		g1->changestatus();
		settextstyle(0, HORIZ_DIR, 2);
		setcolor(WHITE);
		outtextxy(100,140,"Player 2 wins");
		settextstyle(0, HORIZ_DIR, 1);
		outtextxy(100,160,"Press Esc to exit");
		while(getch()!=27){
			continue;
		}
		return(0);
	}
/*adds coordinates according to the direction to move the snake in the required direction*/
	s1->drawsnake(snakecolor);
	s2->drawsnake(snake2color);
	return(0);
}
/****************RUNGAME MULTIPLAYER END********************************/
int start_msg(){
	setcolor(0);
	setfillstyle(SOLID_FILL, 0);
	bar3d(0,0,640,480,0,0);
	setcolor(0);
	setfillstyle(SOLID_FILL, 3);
	bar3d(75, 10, 550,160, 10, 1);
	setcolor(WHITE);
	settextstyle(0, HORIZ_DIR, 5);
	outtextxy(80,20,"Welcome !!!");
	settextstyle(0, HORIZ_DIR, 4);
	outtextxy(100,80,"to SNAKES");
	settextstyle(0, HORIZ_DIR, 2);
	setcolor(YELLOW);
	return(0);

}
/***********************funciton updatescore*********************/
void c_snake::updatescore(int x,int score){
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
	setcolor(8);
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
	setcolor(8);
	outtextxy(30,395,"PLAYER 2");
	setcolor(0);
	setfillstyle(SOLID_FILL,15);
	bar3d(240,380,340,440,0,0);
	setcolor(8);
	settextstyle(0, HORIZ_DIR, 5);
	outtextxy(250,390,"0");
}
}
/********************************display level*************************/
void game::displaylevel(){
	itoa(level,level_str,10);
	setcolor(0);
	setfillstyle(SOLID_FILL,15);
	bar3d(20,380,230,440,0,0);
	settextstyle(0, HORIZ_DIR, 5);
	setcolor(8);
	outtextxy(30,395,"MAZE");
	setcolor(0);
	setfillstyle(SOLID_FILL,15);
	bar3d(240,380,340,440,0,0);
	setcolor(8);
	outtextxy(250,390,level_str);
}
/****************display keys*****************************************/
void displaykeys(){
	setcolor(15);
	setfillstyle(SOLID_FILL,0);
	bar3d(410,0,630,480,0,0);
	settextstyle(0,0,2);
	outtextxy(415,10,"HELP");
	settextstyle(0,0,1);
	outtextxy(415,40,"Make the snake grow larger");
	outtextxy(415,50,"by directing it to the    ");
	outtextxy(415,60,"food. You cannot stop the ");
	outtextxy(415,70,"snake or make it go       ");
	outtextxy(415,80,"backwards. Try not to hit ");
	outtextxy(415,90,"the walls or the tail.   ");
	outtextxy(415,100,"After a score of 25 your ");
	outtextxy(415,110,"level & maze will increase");
	outtextxy(415,120,"and game will be more    ");
	outtextxy(415,130,"difficult.");
	outtextxy(415,140,"For two players, player  ");
	outtextxy(415,150,"having greater score or  ");
	outtextxy(415,160,"not hitting the wall wins.");
	outtextxy(415,170,"In case of collision,    ");
	outtextxy(415,180,"player who hits others   ");
	outtextxy(415,190,"tail or its own will lose.");
	settextstyle(0,0,2);
	outtextxy(415,250,"CONTROLS");
	settextstyle(0,0,1);
	outtextxy(415,280,"Move UP - UP arrow/w");
	outtextxy(415,290,"Move DOWN - DOWN arrow/s");
	outtextxy(415,300,"Move RIGHT - RIGHT arrow/d");
	outtextxy(415,310,"Move LEFT - LEFT arrow/a");
	outtextxy(415,320,"PAUSE/EXIT - END key");
	setcolor(15);
	//setfillstyle(SOLID_FILL,0);
	//bar3d(410,300,630,450,0,0);
	settextstyle(0,0,2);
	outtextxy(415,380,"Developers");
	settextstyle(0,0,1);
	outtextxy(415,410,"Abiral Shakya");
	outtextxy(415,420,"Biman Shrestha");
	outtextxy(415,430,"Deeyo Ranjan Dongol");
	outtextxy(415,440,"Ocean Karki");
}
void main()
{
	int driver,mode;
	int maze,difficulty;
	int gamemode,player;
	driver=DETECT;
	clrscr();
	_setcursortype(_NOCURSOR);
	initgraph(&driver,&mode,"c:\\tc\\bgi");
	while(1)
	{
		clrscr();
		setcolor(backgroundcolor);
		setfillstyle(SOLID_FILL, backgroundcolor);
		bar3d(0,0,640,480,10,1);
		displaykeys();
		{//object scope start
			game g1;
			c_snake s1;
			c_snake s2(36,27,3);
			init_queue(queue1);
			init_queue(queue2);
			food f1;
			food *food_ptr=&f1;
			c_snake *snake_ptr=&s1;
			game *game_ptr=&g1;
			c_snake *snake_ptr2=&s2;
			c_path newpath;
			c_path *path_ptr=&newpath;
			s1.displayscore(2);
			g1.changelevel();
			f1.new_food_pos();
			f1.drawfood();
		/*game g1;
		c_snake s1(3,4);
		c_snake s2(10,4);
		food f1;
		c_path newpath;
		c_path *path_ptr=&newpath;
		//c_snake s2(3,4);
		food *food_ptr=&f1;
		c_snake *snake_ptr=&s1;
		c_snake *snake_ptr2=&s2;
		game *game_ptr=&g1;
		s1.displayscore(1);
		g1.displaylevel();
		*/
		while(g1.gamestatus()!=0){//continues forever until game is over
			/*if(s1.getscore()==g1.getlevel()*levellimit){//if score reaches level changing state
				if(s1.getscore()!=0){
					setcolor(1);
					settextstyle(0, HORIZ_DIR,2);
					outtextxy(10,140,"Level Completed");
					delay(2000);
				}
				g1.changelevel();
				f1.new_food_pos();
				f1.drawfood();
				g1.displaylevel();
				//c_snake s2(10,4);
				s1.reset();
				s2.reset(10,4);
				//set snake to initial position
			} */
		rungameai(snake_ptr,snake_ptr2,food_ptr,game_ptr,path_ptr);
		delay(g1.get_pause());
		}//end status loop
		}//object scope end
	}//end while of GUI
}
int rungameai(c_snake* s1,c_snake *s2,food* f1,game* g1,c_path* newpath)
{
	int a,b;
	int key,key2;
	int cx,cy,fx,fy,dir,dir1;
	int collide1,collide2;
	while(kbhit()){//checks if key hit is available
		key=getch();
		if(key==0){//checks the first byte of the keyboard buffer if it is 0 means an extended code has been pressed so key2 stores the extended code
			/*if(key==97 || key==115 || key==100 || key==119){
				if(key!=queue2->data[queue2->rear]){
					insert(queue2,key);
				}
			}
		}else{  */
			key2=getch();
			if(key2==UP || key2==DOWN || key2==LEFT || key2==RIGHT || key2==END){
				if(key2!=queue2->data[queue2->rear]){
					insert(queue2,key2);
				}
			}
		}
	}
	if(checkunderflow(queue2)!=1){
		b=remove1(queue2);
		s2->getdirection(b);
	}
	cx=s1->snake[0].x/10;
	cy=s1->snake[0].y/10;
	fx=f1->getx()/10;
	fy=f1->gety()/10;
	newpath->reset();
	newpath->set(cx,cy,fx,fy);
	dir1=newpath->finddir();
	if(dir1!=0){
		//s1->setdirectionai(dir1);
		dir=dir1;
	}
	s1->setdirectionai(dir);
/*	if(checkunderflow(queue1)!=1){
		a=remove1(queue1);
		if(s1->getdirection(a)==0){//status=0,ie you chose to exit
			g1->changestatus();
		}
	}
*/
	s2->go();
	s1->go();
	if(f1->checkfoodhit(s1->snake)==1){
		s1->addscore();
		s1->addlength();
		s1->updatescore(1,s1->getscore());
		f1->new_food_pos();//sets new food position
		f1->drawfood();
	}
	if(f1->checkfoodhit(s2->snake)==1){
		s2->addscore();
		s2->addlength();
		s2->updatescore(2,s2->getscore());
		f1->new_food_pos();//sets new food position
		f1->drawfood();
	}

	//collide2=s2->detectcollision();
	//collide1=s1->detectcollision();
	//cout<<"collide2 ="<<collide2;
	//cout<<"collide1 ="<<collide1;
	if(s1->headcollision(s2->snake)==1){
	//if((collide1==1) && (collide2==1)){
//		outtextxy(40,140,"both hit");
		if(s1->getscore()==s2->getscore()){
			settextstyle(0, HORIZ_DIR, 2);
			setcolor(WHITE);
			outtextxy(100,140,"DRAW!!!!!!");
			settextstyle(0, HORIZ_DIR, 1);
			outtextxy(100,160,"Press Esc to exit");
			while(getch()!=27){
				continue;
			}
		}
		else if(s1->getscore()<s2->getscore()){
			settextstyle(0, HORIZ_DIR, 2);
			setcolor(WHITE);
			outtextxy(100,140,"Player 2 wins");
			settextstyle(0, HORIZ_DIR, 1);
			outtextxy(100,160,"Press Esc to exit");
			while(getch()!=27){
				continue;
			}
		}else if(s1->getscore()>s2->getscore()){
			settextstyle(0, HORIZ_DIR, 2);
			setcolor(WHITE);
			outtextxy(100,140,"Player 1 wins");
			settextstyle(0, HORIZ_DIR, 1);
			outtextxy(100,160,"Press Esc to exit");
			while(getch()!=27){
				continue;
			}

		}
		g1->changestatus();
		return(0);


	}//else{ if((collide1==0) && (collide2==1)){
	if(s2->detectcollision()==1){
		g1->changestatus();
		settextstyle(0, HORIZ_DIR, 2);
		setcolor(WHITE);
		outtextxy(100,140,"Player 1 wins");
		settextstyle(0, HORIZ_DIR, 1);
		outtextxy(100,160,"Press Esc to exit");
		while(getch()!=27){
			continue;
		}
		exit(0);
		//return(0);
	}
	 if(s1->detectcollision()==1){//(collide1==1) && (collide2==0)){
		g1->changestatus();
		settextstyle(0, HORIZ_DIR, 2);
		setcolor(WHITE);
		outtextxy(100,140,"Player 2 wins");
		settextstyle(0, HORIZ_DIR, 1);
		outtextxy(100,160,"Press Esc to exit");
		while(getch()!=27){
			continue;
		}
		exit(0);
		//return(0);
	}
//adds coordinates according to the direction to move the snake in the required direction
	s1->drawsnake(snakecolor);
	s2->drawsnake(snake2color);
	return(0);
}
/*
void rungame(c_snake* s1,food* f1,game* g1){

	int a,key2;
	while(kbhit()){//checks if key hit is available
		if(getch()==0){//checks the first byte of the keyboard buffer if it is 0 means an extended code has been pressed so key2 stores the extended code
			key2=getch();
			if(key2==UP || key2==DOWN || key2==LEFT || key2==RIGHT || key2==END){
				if(key2!=queue1->data[queue1->rear]){
					insert(queue1,key2);
				}
			}
		}
	}
	if(checkunderflow(queue1)!=1){
		a=remove1(queue1);
		if(s1->getdirection(a)==0){//status=0,ie you chose to exit
			g1->changestatus();
		}
	}
	//sets direction as per keyhit
	s1->go();//adds coordinates according to the direction to move the snake in the required direction
	s1->drawsnake(snakecolor);
	if(f1->checkfoodhit(s1->snake)==1){
		s1->addscore();
		s1->addlength();
		s1->updatescore(1,s1->getscore());
		f1->new_food_pos();//sets new food position
		f1->drawfood();
	}
	if(s1->detectcollision()==1){
		g1->changestatus();
		settextstyle(0, HORIZ_DIR, 2);
		setcolor(WHITE);
		outtextxy(100,140,"GAME OVER");
		settextstyle(0, HORIZ_DIR, 1);
		outtextxy(100,160,"Press Esc to exit");
		while(getch()!=27){
			continue;
		}

	}
*/