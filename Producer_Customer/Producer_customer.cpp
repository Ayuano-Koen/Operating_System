


#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>
using namespace std;
# define BUFFERSIZE 10
int i=0;
int j=1;
// srand(time(NULL));
 struct queue{
   int buffer[BUFFERSIZE];
   int front;
   int rear;
   int count;
 };
 queue *q;
 // using peterson Algorithm
 int turn=0;
 bool flag[2];
 //producer=0
 //consumer=1;
 void producer(queue *q){
 int item;
 int count=0;
 while(count<6){
 flag[i]=true;
  turn=j;
  while(flag[j]==true && turn==j);
  
  while(q->count==BUFFERSIZE);
  // produce an item
  //cout<<"Enter the item to be produced : ";
    //cin>>item;
    item = rand()%5;
  cout<<"produced item : "<<" "<<item << endl;
 // sleep(2);

  //critical section 
 
  //insert
  q->buffer[q->front]=item;
  q->front = (q->front +1)%BUFFERSIZE ;
  q->count++;
   cout<<"No. of items in PRODUCER buffer :"<<q->count<<endl;
  //exit section
   flag[i]=false;
   count++;
 }
 }
  void consumer(queue *q){
 int item;
 int count=0;
 while(count<6){
   flag[j]=true;
  turn=i;
  while(flag[i]==true && turn==i);
  
  while(q->count==0);
  //

 // critical section;
 if(q->front==q->rear){
 printf("queue is empty");
 }
  //insert
  item=q->buffer[q->rear];
  q->rear = (q->rear+1)%BUFFERSIZE ;
  q->count--;
  int t=  q->count--;
 //exit section
  flag[j]=true;
  cout<<"consumed item"<<" "<<item<<endl;
   cout<<"No. of items in  CONSUMER buffer :"<<t<<endl;
   count++;
 }
 }
 
 int main(){
 int shmid=shmget(IPC_PRIVATE,sizeof(queue),IPC_CREAT | 0777);
 if(shmid==-1){
  cout<<"shared memory is not created"<<endl;
  exit(1);
 }
 q=(queue*)shmat(shmid,0,0);
 if(q==(queue*)-1){
 cout<<"shared memory is not created"<<endl;
  exit(1);
 }
 q->front=0;
 q->rear=0;
 q->count=0;
 int pid= fork();
 if(pid<0){
  cout<<"process not created\n";
  exit(1);
 }
 else if(pid==0){
  printf("consumer is started :\n");
  consumer(q);
   //cout<<"No. of items in buffer :"<<q->count<<endl;
 }
 else{
 
  printf("producer is started :\n");
 producer(q);
 //cout<<"No. of items in buffer :"<<q->count<<endl;
 }
  shmdt(q);
 shmctl(shmid,IPC_RMID,NULL);
 //wait(NULL);
 
 return 0;
 }
 

 