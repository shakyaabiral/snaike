#define NULL 0
#define INITLENGTH 2
struct Segment{
	int x;
	int y;
	struct Segment* next;
};
typedef struct Segment* SegmentPtr;
class Snake{
	SegmentPtr first;
	SegmentPtr last;
	int length;
public:
	Snake();
	void setup(int x,int y);
	void add();//(int,int);
	void shift(int x,int y);
	SegmentPtr firstSegment();
	SegmentPtr lastSegment();
	void drawSnake (int color);
	void reset(int,int);
}
Snake::Snake(){
	first=0;
	last=0;
	length=1;
	}
void Snake::setup(int x, int y){
	first=new Segment;
	SegmentPtr p,q,r;
	first->x=x*10;
	first->y=y*10;
	first->next=NULL;
	last=first;
	for(int i=1;i<INITLENGTH;i++){
		add();
	}
}
void Snake::reset(int x,int y){
	SegmentPtr p=first;
	SegmentPtr q;
	while(p!=NULL){
		q=p;
		p=p->next;
		free(q);
	}
	first=0;
	last=0;
	length=1;
	setup(x,y);
}
void Snake::shift(int x,int y){
	SegmentPtr newPtr=first;
	while(newPtr->next!=NULL){//exclude the first segment
		newPtr->x=newPtr->next->x;
		newPtr->y=newPtr->next->y;
		newPtr=newPtr->next;
	}
	last->x=x;
	last->y=y;
}
void Snake::add(){
	SegmentPtr newPtr;
	length++;
	newPtr=new Segment;
	newPtr->x=first->x;
	newPtr->y=first->y;
	newPtr->next=first;
	first=newPtr;
	}
SegmentPtr Snake::firstSegment(){
	return(last);
	}
SegmentPtr Snake::lastSegment(){
	return(first);
	}