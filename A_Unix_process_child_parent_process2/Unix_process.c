


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#define p pid_t
#define MAX 127
#define MIN 0

int find_max(int *arr, int l, int r) {
    int max= *arr;
    for(int i = l+1; i <= r; i++) {
        if(*(arr+i) > max) {
            max = *(arr+i);
        }
    }
    return max;
}

void recur_create_process(int a[], int l, int r) {
    p pid;
    int maxi;
    int status_l, status_r;
    int mid = (l + r) / 2;
    int count = r - l + 1;
   
    if(count < 10) {
    int maxi= find_max(a, l, r);
        printf("Process %d (parent %d): Maximum value in chunk [%d, %d] is %d\n", getpid(), getppid(), l, r, maxi);
        exit(maxi);
    }
   
    p pid_l = fork();
    if(pid_l == 0) {
        recur_create_process(a, l, mid);// creating a left process
        exit(0);
    } else if(pid_l < 0) {
        printf("Failed to fork process\n");
        exit(0);//1
    }
   
    p pid_r = fork();
    if(pid_r == 0) {
        recur_create_process(a, mid+1, r);// creating the right process
        exit(0);
    } else if(pid_r < 0) {
  printf("Failed to fork process\n");
        exit(1);
    }
   
    waitpid(pid_l, &status_l, 0);
    waitpid(pid_r, &status_r, 0);
   
    if(WIFEXITED(status_l) && WIFEXITED(status_r)) {// it is function see the status where child process is exited normally or not
        int max_l = WEXITSTATUS(status_l);
        int max_r = WEXITSTATUS(status_r);
        maxi = (max_l > max_r) ? max_l : max_r;
        printf("Process %d (parent %d): Maximum value in array in between %d and %d is %d\n", getpid(), getppid(), l, r, maxi);
        exit(maxi);
    }
}


int main(int argc, char* argv[]) {
    int num, i;
   
    if(argc != 2) {
        printf("Usage: %s <count>\n", argv[0]);
        exit(0);//1
    }
   
    num = atoi(argv[1]);  // convert character into integer.
   
    if(num < 1) {
        printf("Invalid value for count\n");
        exit(0);//1
    }
   
   
    int arr[num];
   
    for(i = 0; i < num; i++) {
        arr[i] = rand() % (MAX - MIN + 1) + MIN;
           printf("%d ", arr[i]);
    }
   
    printf("\n");
   
    recur_create_process(arr, 0, num-1);
   
    return 0;
}