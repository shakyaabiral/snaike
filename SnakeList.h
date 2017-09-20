struct Segment{
	int x;
	int y;
	struct segment* next;
};
typedef struct Segment* SegmentPtr;
class Snake{
	SegmentPtr first;
	SegmentPtr last;
public:
	void add();
	SegmentPtr getFirstSegment(){
		return first;
	}
	SegmentPtr getFirstSegment(){
		return first;
	}
		
}