#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<iostream.h>
#include<stdlib.h>
#include "beta2\globalvar.h"
#include "beta2\constants.h"
#include "beta2\queue.h"
#include "beta2\wayfinder.h"
#include "beta2\snake.h"
#include "beta2\snakeai.h"
#include "beta2\food.h"
#include "beta2\game.h"
#include "beta2\extras.h"
#include "beta2\rungame.h"
///********************************************************////////////
/****************************MAIN FUNCITON***************************/
///********************************************************//////////
void main()
{
	int driver,mode;
	int maze,difficulty;
	int gamemode,player;
	int counter=0;
	driver=DETECT;
	clrscr();
	_setcursortype(_NOCURSOR);
	initgraph(&driver,&mode,"c:\\tc\\bgi");
	while(1)
	{
		start_msg();
		if((player=choose_player())==1){
			if((gamemode=choose_game_mode())==2){//advanced move
				if((maze=choose_maze())==0){//user pressed escape so go back to previous menu
					continue;
				}
				if((difficulty=choose_difficulty())==0){//user pressed escape so go back to previous menu
					continue;
				}
				clrscr();
				setcolor(backgroundcolor);
				setfillstyle(SOLID_FILL, backgroundcolor);
				bar3d(0,0,640,480,10,1);
				displaykeys();
				{//object scope start
				game g1(maze-1,200-(difficulty*20));
				c_snake s1(6,3,1);
				c_snake *snake_ptr=&s1;
				game *game_ptr=&g1;
				s1.displayscore(1);
				g1.changelevel();
				g1.displaylevel();
				food* food_ptr[4];
				food_ptr[0]=new food(1,30,60);
				food_ptr[0]->drawfood();
				food_ptr[1]=new food(2,30,80);
				food_ptr[1]->drawfood();
				food_ptr[2]=new food(3,30,150);
				food_ptr[2]->drawfood();
				food_ptr[3]=new food(4,30,200);
				food_ptr[3]->drawfood();
				counter=0;
				while(g1.gamestatus()!=0){//continues forever until game is over
					rungame(snake_ptr,food_ptr,game_ptr);
					delay(g1.get_pause());
				}//end status loop
				}//object scope end
			}else if (gamemode==1){//classical mode
				clrscr();
				setcolor(backgroundcolor);
				setfillstyle(SOLID_FILL, backgroundcolor);
				bar3d(0,0,640,480,10,1);
				displaykeys();
				{//object scope start
				food* food_ptr[4];
				food_ptr[0]=new food(1,30,60);
				food_ptr[1]=new food(2,30,80);
				food_ptr[2]=new food(3,30,150);
				food_ptr[3]=new food(4,30,200);
				c_snake *snake_ptr=new c_snake(7,3,1);
				game *game_ptr=new game;
				snake_ptr->displayscore(1);
				game_ptr->displaylevel();
				while(game_ptr->gamestatus()!=0){//continues forever until game is over
					if(snake_ptr->getscore()==game_ptr->getlevel()*levellimit){//if score reaches level changing state
						if(snake_ptr->getscore()!=0){
							setcolor(1);
							settextstyle(0, HORIZ_DIR,2);
							outtextxy(10,140,"Level Completed");
							delay(2000);
						}
						game_ptr->changelevel();
						food_ptr[0]->new_food_pos();
						food_ptr[0]->drawfood();
						food_ptr[1]->new_food_pos();
						food_ptr[1]->drawfood();
						food_ptr[2]->new_food_pos();
						food_ptr[2]->drawfood();
						food_ptr[3]->new_food_pos();
						food_ptr[3]->drawfood();
						game_ptr->displaylevel();
						snake_ptr->reset();//set snake to initial position
					}
					rungame(snake_ptr,food_ptr,game_ptr);
					delay(game_ptr->get_pause());
				}//end status loop
				}//object scope end
			}//end gamemode
			else if(gamemode==0){
				continue;
			}
		}else if(player==3){//double player vs computer
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
			{//object scwope start
			game g1(maze-1,200-(difficulty*20));
			SnakeAi s1;
			SnakeAi s2(36,27,3);
			food f1;
			food *food_ptr=&f1;
			SnakeAi *snake_ptr=&s1;
			game *game_ptr=&g1;
			SnakeAi *snake_ptr2=&s2;
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
		else if(player==2){//double player vs human
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
			c_snake s2(36,27,3);
			food f1;
			food *food_ptr=&f1;
			c_snake *snake_ptr=&s1;
			game *game_ptr=&g1;
			c_snake *snake_ptr2=&s2;
			s1.displayscore(2);
			g1.changelevel();
			f1.new_food_pos();
			f1.drawfood();
			while(g1.gamestatus()!=0){//continues forever until game is over
				rungame2(snake_ptr,food_ptr,game_ptr,snake_ptr2);
				delay(g1.get_pause());
			}//end status loop
			}//object scope end
		}
	}//end while of GUI
}
