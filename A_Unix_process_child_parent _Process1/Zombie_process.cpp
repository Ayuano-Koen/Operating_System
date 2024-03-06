// write a os program to show the zombie process.
#include<iostream>
#include<bits/stdc++.h>
#include<stdio.h>
#include<unistd.h>
using namespace std;
#define l int
#define z pid_t
int main(){

  z child;
  child=fork(); // it is inbuilt function which is used to create  child
  if (child<0){
   cout<<"This process will not work\n";
   cout<<"Error!!!!\n";
  }
   else if (child== 0) {
        // Child process
       printf("Child process: pid:%d", getpid());
       cout<<endl;
       printf(" It's Parent ppid : %d ",getppid());
       cout<<endl;
       cout<<"TASK :1\n";
        printf("Completion!");
        cout<<endl;
        exit(0);}
        else{
        // creating a parent process 
         sleep(5); // Sleep for 5 second to leave child as zombie
         printf("Parent process: pid=%d", getpid());
                cout<<endl;
       printf(" It's child ppid : %d ",child);
       cout<<endl;
       cout<<"Task: 2\n";
        cout<<"completion!";
        cout<<endl;}

        return 0;
       