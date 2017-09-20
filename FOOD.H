#include"snake\constants.h"
#include<time.h>
class food{
	int foodx,foody,foodstat,point;
public:
	friend void rungame(c_snake*,food*,game*);
	friend int rungame2(c_snake*,food*,game*,c_snake* );
	friend int rungameai(SnakeAi* s1,SnakeAi *s2,food* f1,game* g1,c_path* newpath);
	friend int checkFoodHit(c_snake*,food* f[])
	food(int,int,int);
	void new_food_pos();
	int checkfoodhit(c_snake*);//struct coordinate[]);
	int checkfoodhit(struct coordinate snake[]);
	void drawfood();
	int getx();
	int gety();
	void removeFood();
	void setScore(int);
};


food::food(int x=1,int a=1, int b=1){
	point =x;
	foodx=a;
	foody=b;
	new_food_pos();
	//drawfood();
}
void food::removeFood(){
	setcolor(boardcolor);
	setfillstyle(SOLID_FILL,boardcolor);
	bar3d(foodx,foody,foodx+10,foody+10,0,0);
}
void food::setScore(int x){
	point=x;
}
int food::getx(){
		return foodx;
}
int food::gety(){
		return foody;
}
/********************************function checkfoodhittest**************************/
int food::checkfoodhit(struct coordinate snake[]){//for array typpe snake
	if(snake[0].x==foodx && snake[0].y==foody){
		return(1);
	}else{
		return(0);
	}
}
/*int checkWhichFoodHit(c_snake *s1,food[]){
	for(int i=1;i<5;i++){
		if(s1->segment.firstSegment()->x==food[i].x && s1->segment.firstSegment()->y==food[i].y){
			return(i);
		}
	}
	return(0);
} */
int food::checkfoodhit(c_snake* s1){//for linked list snake
	if(s1->segment.firstSegment()->x==foodx && s1->segment.firstSegment()->y==foody){
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
		if(a[foody/10][foodx/10]!=0){
			food_check=1;
			continue;
		}
		else{
			food_check=0;
			break;
		}
	}while(food_check==1);
	a[foody/10][foodx/10]=2;
}
/**************draw food**************************************************/
void food::drawfood(){
	if(point==1){
		setcolor(foodcolor);
		setfillstyle(SOLID_FILL,foodcolor);
		circle(foodx+5,foody+5,4);
		floodfill(foodx+5,foody+5,foodcolor);
	}else if(point==2){
		setfillstyle(SOLID_FILL,3);
		setcolor(3);
		circle(foodx+5,foody+5,4);
		floodfill(foodx+5,foody+5,3);
	}else if(point==3){
		setfillstyle(SOLID_FILL,4);
		setcolor(4);
		circle(foodx+5,foody+5,4);
		floodfill(foodx+5,foody+5,4);
	}else{
		setcolor(5);
		setfillstyle(SOLID_FILL,5);
		circle(foodx+5,foody+5,4);
		floodfill(foodx+5,foody+5,5);
	}
	a[foody][foodx]=2;

}
int checkFoodHit(c_snake* s1,food* f[]){
	for(int i=0;i<4;i++){
		if(s1->segment.firstSegment()->x==f[i]->foodx && s1->segment.firstSegment()->y==f[i]->foody){
			f[i]->new_food_pos();
			f[i]->drawfood();
			return i+1;
		}
	}
	return 0;
}