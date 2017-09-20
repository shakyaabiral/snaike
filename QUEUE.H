# define maxsize 4
class Queue{
	int data[maxsize];
	int front,rear;
	public:
	Queue();
	void insert(int);
	int remove1();
	int getRear();
	int checkunderflow();
}
Queue::Queue(){
	front=rear=maxsize-1;
	for(int i=0;i<maxsize;i++){
		data[i]=0;
	}
}
void Queue::insert(int value){
	if(rear==maxsize-1){
		rear=0;
	}else{
		rear++;
	}
	if(front==rear){
		//printf("\nQueue Full.Overflow Error\n");
		rear--;
	}
	else{
		data[rear]=value;
	}
}
int Queue::getRear(){
	if(front==rear){
		return (0);
		//printf("\nQueue empty.Underflow error\n");
	}
	else{
		return(data[front]);
	}
}
int Queue::remove1(){
	if(front==rear){
		return (0);
		//printf("\nQueue empty.Underflow error\n");
	}
	else{
		if(front==maxsize-1){
			front=0;
		}else{
			front++;
		}
		return(data[front]);
	}
}
int Queue::checkunderflow(){
	if(front==rear){
		return 1;
	}
	else{
		return 0;
	}
}