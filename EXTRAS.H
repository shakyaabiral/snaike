#include"beta\constants.h"
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
	char *players[3]={"Single Player","Double Player","vs Computer"};
	draw_menu_bar();
	setcolor(WHITE);
	settextstyle(0,0,2);
	outtextxy(90,180,"CHOOSE GAME MODE");
	display(3,players);
	highlight(1);
	while(1){
		key=getch();
		if(key=='\r'){//enter
			return(menu_active);
		}
		if(key==27){   //escape
			exit(0);
		}
		if(key==0){//cursors
			key1=getch();
			if(key1==DOWN && menu_active<3){
				menu_active++;
				unhighlight(menu_active-1);
				highlight(menu_active);
			}
			else if(key1==UP && menu_active>1){
				menu_active--;
				unhighlight(menu_active+1);
				highlight(menu_active);
			}
			//else if(
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