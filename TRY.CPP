#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<iostream.h>
#include<stdlib.h>
#include "beta\globalvar.h"
#include "beta\queue.h"
#include "beta\wayfinder.h"
#include "beta\constants.h"
#include "beta\snake.h"
#include "beta\food.h"
#include "beta\game.h"
#include "beta\extras.h"
#include"beta\rungame.h"
void  displaykeys();
int start_msg();
void rungame(c_snake*,food*,game*);
int rungame2(c_snake*,food*,game*,c_snake* );
int rungameai(c_snake* s1,c_snake *s2,food* f1,game* g1,c_path* newpath);
int ai_getdirection(int sx,int sy,int fx,int fy,int dir);
void display_developers();
///********************************************************////////////
/****************************MAIN FUNCITON***************************/
///********************************************************//////////
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
		start_msg();
		if((player=choose_player())==1){
			if((gamemode=choose_game_mode())==2){
				if((maze=choose_maze())==0){
					continue;
				}
				if((difficulty=choose_difficulty())==0){
					continue;
				}
				clrscr();
				setcolor(backgroundcolor);
				setfillstyle(SOLID_FILL, backgroundcolor);
				bar3d(0,0,640,480,10,1);
				displaykeys();
				{//object scope start
				game g1(maze-1,200-(difficulty*20));
				c_snake s1;
				food f1;
				food* food_ptr=&f1;
				c_snake* snake_ptr=&s1;
				game* game_ptr=&g1;
				s1.displayscore(1);
				g1.changelevel();
				f1.new_food_pos();
				f1.drawfood();
				g1.displaylevel();
				while(g1.gamestatus()!=0){//continues forever until game is over
				rungame(snake_ptr,food_ptr,game_ptr);
					delay(g1.get_pause());
				}//end status loop
				}//object scope end
			}else if (gamemode==1){
				clrscr();
				setcolor(backgroundcolor);
				setfillstyle(SOLID_FILL, backgroundcolor);
				bar3d(0,0,640,480,10,1);
				displaykeys();
				{//object scope start
				game g1;
				c_snake s1;
				food f1;
				c_snake s2(3,4);
				food *food_ptr=&f1;
				c_snake *snake_ptr=&s1;
				game *game_ptr=&g1;
				s1.displayscore(1);
				g1.displaylevel();
				while(g1.gamestatus()!=0){//continues forever until game is over
					if(s1.getscore()==g1.getlevel()*levellimit){//if score reaches level changing state
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
						s1.reset();
					//set snake to initial position
					}
					rungame(snake_ptr,food_ptr,game_ptr);
					delay(g1.get_pause());
				}//end status loop
				}//object scope end
			}//end gamemode
			else if(gamemode==0){
				continue;
			}
		}else if(player==2){
			if((maze=choose_maze())==0){
					continue;
			}
			if((difficulty=choose_difficulty())==0){
					continue;
			}
			clrscr();
			setcolor(backgroundcolor);
			setfillstyle(SOLID_FILL, backgroundcolor);
			bar3d(0,0,640,480,10,1);
			displaykeys();
			{//object scope start
			game g1(maze-1,200-(difficulty*20));
			//game g1;
			c_snake s1;
			c_snake s2(36,27,3);
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
			while(g1.gamestatus()!=0){//continues forever until game is over
				rungameai(snake_ptr,snake_ptr2,food_ptr,game_ptr,path_ptr);
				delay(g1.get_pause());
			}//end status loop
			}//object scope end
		}//end player
	}//end while of GUI
}
