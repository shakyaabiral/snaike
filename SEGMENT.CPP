#define NULL 0
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
	void setup(int x,int y);//,int dir);
	void add(int,int);
	SegmentPtr getFirstSegment();
	SegmentPtr getLastSegment();
}
Snake::Snake(){
	first=0;
	last=0;
	length=2;
	}
void Snake::setup(int x, int y){//, int dir=1){
	first=new Segment;
	//length=1;
	first->x=x*10;
	first->y=y*10;
	first->next=NULL;
	last=first;
	add((x-1)*10,y);
	}
void Snake::add(int x,int y){
	SegmentPtr newPtr;
	newPtr=new Segment;
	newPtr->x=x;
	newPtr->y=y;
	newPtr->next=NULL;
	last->next=newPtr;
	last=newPtr;
	}
SegmentPtr Snake::getFirstSegment(){
	return(first);
	}
SegmentPtr Snake::getLastSegment(){
	return(last);
	}