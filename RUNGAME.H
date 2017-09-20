#include"beta\constants.h"
#define SCORELIMIT 50
int rungameai(SnakeAi* s1,SnakeAi *s2,food* f1,game* g1,c_path* newpath)
{
	int success,pop;
	int leng;
	int key,key2;
	int cx,cy,fx,fy,dir,dir1;
	int collide1,collide2;
	while(kbhit()){//checks if key hit is available
		key=getch();
		if(key==0){//checks the first byte of the keyboard buffer if it is 0 means an extended code has been pressed so key2 stores the extended code
		key2=getch();
			if(key2==UP || key2==DOWN || key2==LEFT || key2==RIGHT || key2==END){
				if(key2!=s2->queue.getRear()){
					s2->queue.insert(key2);
				}
			}
		}
	}
	if(s2->queue.checkunderflow()!=1){
		pop=s2->queue.remove1();
		if(s2->getdirection(pop)==0){//status=0,ie you chose to exit
			g1->changestatus();
		}
	}
	cx=s1->snake[0].x/10;
	cy=s1->snake[0].y/10;
	a[s1->snake[1].y/10][s1->snake[1].x/10]=1;
	while(leng<s1->getlength()){
		a[s1->snake[leng].y/10][s1->snake[leng].x/10]=1;
	}
	fx=f1->getx()/10;
	fy=f1->gety()/10;
	newpath->reset();
	newpath->set(cx,cy,fx,fy);
	dir1=newpath->finddir();
	if(dir1!=0){
		dir=dir1;
	}else{
		if(a[s1->snake[0].y/10+1][s1->snake[0].x/10]!=1 && s1->getdir()!=4){
			dir=2;
		}else if(a[s1->snake[0].y/10][s1->snake[0].x/10+1]!=1 && s1->getdir()!=3){
			dir=1;
		}else if(a[s1->snake[0].y/10-1][s1->snake[0].x/10]!=1 && s1->getdir()!=2){
			dir=4;
		}else if(a[s1->snake[0].y/10][s1->snake[0].x/10-1]!=1 && s1->getdir()!=1){
			dir=3;
		}
	}
	s1->setdirectionai(dir);
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
/*if 2 snake collide head on then snake with high score wins */
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
	}
	collide1=0;
	collide2=0;
	collide1=s1->detectcollision();
	collide2=s2->detectcollision();
	if(collide2==1 && collide1==0){
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
	if(collide1==1 && collide2==0){
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
	if(collide1==1 && collide2==1){
		g1->changestatus();
		settextstyle(0, HORIZ_DIR, 2);
		setcolor(WHITE);
		outtextxy(100,140,"Draw!!!!!!!!!");
		settextstyle(0, HORIZ_DIR, 1);
		outtextxy(100,160,"Press Esc to exit");
		while(getch()!=27){
			continue;
		}
		return(0);
	}
//adds coordinates according to the direction to move the snake in the required direction
	s1->drawsnake(snakecolor);
	s2->drawsnake(snake2color);
	if(s1->getscore()==SCORELIMIT){//if player reaches score limit then declare winner and end game
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
	}else if(s2->getscore()==SCORELIMIT){
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
	if(g1->counter==0){

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
		g1->counter++;
	}
	return(0);

}
/************Rungame AI ENds*****************************/

/************Rungame Single PLayer Start*****************/
void rungame(c_snake* s1,food* f1[],game* g1){
	int a,key2,foodHit=0;
	while(kbhit()){//checks if key hit is available
		if(getch()==0){/*checks the first byte of the keyboard buffer if it is 0 means an extended code has been pressed so key2 stores the extended code*/
			key2=getch();
			if(key2==UP || key2==DOWN || key2==LEFT || key2==RIGHT || key2==END){
				if(key2!=s1->queue.getRear()){
					s1->queue.insert(key2);
				}
			}
		}
	}
	if(s1->queue.checkunderflow()!=1){
		a=s1->queue.remove1();
		if(s1->getdirection(a)==0){//status=0,ie you chose to exit
			g1->changestatus();
		}
	}
	//sets direction as per keyhit
	s1->go();/*adds coordinates according to the direction to move the snake in the required direction*/
	s1->drawsnake(snakecolor);
	foodHit=checkFoodHit(s1,f1);//foodhit returns the type(score) of food eaten
	if(foodHit!=0){
		if(foodHit==1){
			s1->addscore();
		}else if(foodHit==2){
			s1->addscore(2);
		}else if(foodHit==3){
			s1->addscore(3);
		}else if(foodHit==4){
			s1->addscore(4);
		}
		s1->segment.add();
		s1->updatescore(1,s1->getscore());
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
	if(g1->counter%25==0){
		f1[1]->removeFood();
		f1[1]->new_food_pos();
		f1[1]->drawfood();
	}
	if(g1->counter%35==0){
		f1[2]->removeFood();
		f1[2]->new_food_pos();
		f1[2]->drawfood();
	}if(g1->counter%45==0){
		f1[3]->removeFood();
		f1[3]->new_food_pos();
		f1[3]->drawfood();
	}
	if(g1->counter==0){
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
	g1->counter++;
	if(g1->counter>=45){
		g1->counter=1;
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
				if(key!=s2->queue.getRear()){
					s2->queue.insert(key);
				}
			}
		}else{
			key2=getch();
			if(key2==UP || key2==DOWN || key2==LEFT || key2==RIGHT || key2==END){
				if(key2!=s1->queue.getRear()){
					s1->queue.insert(key2);
				}
			}
		}
	}
	if(s2->queue.checkunderflow()!=1){
		b=s2->queue.remove1();
		s2->getdirection(b);
	}
	if(s1->queue.checkunderflow()!=1){
		a=s1->queue.remove1();
		if(s1->getdirection(a)==0){//status=0,ie you chose to exit
			g1->changestatus();
		}
	}
	s2->go();
	s1->go();
	if(f1->checkfoodhit(s1)==1){
		s1->segment.add();
		s1->addscore();
		s1->updatescore(1,s1->getscore());
		f1->new_food_pos();//sets new food position
		f1->drawfood();
	}
	if(f1->checkfoodhit(s2)==1){
		s2->segment.add();
		s2->addscore();
		s2->updatescore(2,s2->getscore());
		f1->new_food_pos();//sets new food position
		f1->drawfood();
	}
	if(s1->headcollision(s2)==1){
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
	collide1=0;
	collide2=0;
	collide1=s1->detectcollision();
	collide2=s2->detectcollision();
	if(collide2==1 && collide1==0){
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
	if(collide1==1 && collide2==0){
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
	if(collide1==1 && collide2==1){
		g1->changestatus();
		settextstyle(0, HORIZ_DIR, 2);
		setcolor(WHITE);
		outtextxy(100,140,"Draw!!!!!!!!!");
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
	if(g1->counter==0){

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
		g1->counter++;
	}
	return(0);
}
/****************RUNGAME MULTIPLAYER END********************************/