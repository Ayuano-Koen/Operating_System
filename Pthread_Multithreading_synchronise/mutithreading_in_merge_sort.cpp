
#include<iostream>
#include<climits>
#include<pthread.h>
#include<vector>
using namespace std;
// global variables
int n;
vector<int> a;
pthread_mutex_t lock;

struct thread_type{
 int start;
 int end;
};
void merge(int start,int mid, int end){
int n1=mid-start+1;
int n2= end-mid;
vector<int>v1(n1+1,0);
vector<int>v2(n2+1,0);
for(int i=0;i<n1;i++){
v1[i]=a[start+i];
}
for(int j=0;j<n2;j++){
v2[j]=a[mid+j+1];
}
v1[n1]=INT_MAX;
v2[n2]=INT_MAX;
int i=0,j=0;
for(int k=start;k<=end;k++){
if(v1[i]<=v2[j]){
 a[k]=v1[i];
 i++;
}
else{
  a[k]=v2[j];
  j++;
}

}

}
void *merge_sort(void *ptr) {
    struct thread_type *td = (struct thread_type*)ptr;
    int start = td->start;
    int end = td->end;
    if (start < end) {
        int mid = start + (end - start) / 2;
        pthread_t threadleft, threadright;
        struct thread_type threadleft1= {start, mid};
        struct thread_type threadright1 = {mid + 1, end};
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        pthread_create(&threadleft , NULL, merge_sort, (void*)&threadleft1);
        pthread_create(&threadright, NULL, merge_sort, (void*)&threadright1 );
        pthread_attr_destroy(&attr);
        pthread_join(threadleft , NULL);
        pthread_join(threadright, NULL);
        pthread_mutex_lock(&lock);
        merge(start, mid, end);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}
void display (vector<int> & vec){
     for (int i = 0; i < n; i++) {
        cout << vec[i] << " ";
    }
}
int main() {
    cout << "Enter the size of the array: ";
    cin >> n;
    cout << "Enter the elements of the array: ";
    vector<int> t(n, 0);
    for (int i = 0; i < n; i++) {
        cin>>t[i];
    }
     a=t;
    struct thread_type td = {0, n - 1};
    pthread_t single_thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
     pthread_mutex_init(&lock, NULL);
    pthread_create(&single_thread, &attr, merge_sort, (void *)&td);
    
    pthread_attr_destroy(&attr);
    
    pthread_join(single_thread, NULL);
    pthread_mutex_destroy(&lock);
    cout << "Sorted Array: ";
   display(a);
    cout << endl;
    return 0;
}
// to run this code run this  commands

// g++ -pthread assignment8.cpp -o assignment8
//  ./assignment8

