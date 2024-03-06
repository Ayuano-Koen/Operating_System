// write a os program to show the normal child process and parent process.
#include<iostream>
#include<bits/stdc++.h>
#include<stdio.h>
#include<unistd.h>
using namespace std;
#define l int
#define z pid_t
l minimum_val (vector<l>&v,l &n){
  l ans=v[0];
  for(l i=0;i<n;i++){
    if(v[i]<ans){
      ans=v[i];
    }
  }
  return ans;
}
l maxmum_val (vector<l>&v,l &n){
  l ans=v[0];
  for(l i=0;i<n;i++){
    if(v[i]>ans){
      ans=v[i];
    }
  }
  return ans;
}

int main(){
 l num;
 printf("Enter the number of integers: ");
 cin>>num;
 cout<<"Enter the number to be stored :\n";
 vector<l>vec(num,0);
 for(l i=0;i<num;i++){
    cin>>vec[i];
 }
 l min_value=minimum_val (vec,num);
 l max_value=maxmum_val(vec,num);
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
        printf("Minimum value: %d", min_value);
        cout<<endl;}
        else{
        // creating a parent process 
         sleep(2); // Sleep for 2 seconds to ensure that the child process finishes first
         printf("Parent process: pid=%d", getpid());
                cout<<endl;
       printf(" It's child ppid : %d ",child);
       cout<<endl;
       cout<<"Task: 2\n";
        printf("Maximum value: %d", max_value);
        cout<<endl;}

        return 0;
       
    }