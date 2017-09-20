#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<string.h>
void main(){
clrscr();
	int b;
	char name[30];
	b=8634;
	int c=1324;
	strcpy(name,"abiral");
	ofstream outf("highscore.txt");
	outf<<name<<"\n";
	outf<<b<<"\n";
	outf.close();
	a=0;
	b=0;
	ifstream inf("highscore.txt");
	inf>>name;
	inf>>b;
	inf.close();
	cout<<name<<"\n";
	cout<<b;
getch();
}