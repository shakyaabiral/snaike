#include<iostream.h>
#include<fstream.h>
#include<conio.h>
void main(){
clrscr();
	ofstream outf("highscore.txt");
	ifstream inf("highscore.txt");
	int a;
	inf>>a;
	cout<<a;
getch();
}