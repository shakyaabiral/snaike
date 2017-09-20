#include"beta\constants.h"
class game{
	int level,score,status;
	int pause_length;
	char score_str[5];
	char level_str[5];

public:
	int counter;
	friend void rungame(c_snake*,food*,game*);
	friend int rungame2(c_snake*,food*,game*,c_snake* );
	friend int rungameai(SnakeAi* s1,SnakeAi *s2,food* f1,game* g1,c_path* newpath);
	void display_speed();
	void drawmap();
	void displayscore();
	void displaylevel();
	void changelevel();
	void changestatus();

	int gamestatus();
	int getlevel();
	int get_pause();
	void addscore();
	int getscore();
	void updatescore();
	void updatelevel();
	game(int lvl,int pause);
};

game::game(int lvl=0,int pause=initial_pause_length){
		pause_length=pause;
		level=lvl;
		score=0;
		status=1;
		counter=0;
	}
int game::get_pause(){
		return(pause_length);
	}
/********************function change status********************************************/
void game::changestatus(){
	if (status==0){
		status=1;
	}else if(status==1){
		status=0;
	}
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
	for(int tr=0;tr<map_height;tr++){
		for(int tc=0;tc<map_width;tc++){
			a[tr][tc]=0;
		}
	}
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
	for(tr=0;tr<map_height;tr++){
		for(int tc=0;tc<map_width;tc++){
			if(a[tr][tc]==1){
				setcolor(boardcolor);
				setfillstyle(SOLID_FILL,wallcolor);
				bar3d(tc*10,tr*10,tc*10+10,tr*10+10,0,0);
			}else{
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
		/*getimage(10,140,200,160,buff);
		setcolor(15);
		setfillstyle(SOLID_FILL,0);
		bar3d(10,140,200,160,0,0);
		settextstyle(0, HORIZ_DIR,1);
		outtextxy(15,145,"press 'y' key to start");
		while(getch()!='y'){
			continue;
		}
		putimage(10,140,buff,COPY_PUT);*/
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