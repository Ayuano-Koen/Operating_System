
#include <iostream>
#include<stdio.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define READ_END 0
#define WRITE_END 1
#define MIN 0
#define MAX 1
#define WIN 10

using namespace std;

int c_score = 0;
int d_score = 0;

void handle_signal(int sig) {
    if (c_score== WIN) 
    {	
    	cout << "Child C wins!" << endl;
    }
else {
        cout << "Child D wins!" << endl;
     }
    exit(0);
}

int main() {
 //time_t t=1;
    int pc[2], pd[2];
    pid_t c_pid, d_pid;
  //  srand(time(NULL));
    //signal(SIGINT, handle_signal);

    // create pipes
    if (pipe(pc) == -1 || pipe(pd) == -1) {
        printf("Error creating pipes");
        exit(1);
    }

    // fork child processes
    c_pid = fork();
    if (c_pid == -1) {
        printf("Error forking child C");
        exit(1);
    } else if (c_pid == 0) {
        // child C PROCESS
        close(pc[0]); // close read end of pipe pc
        close(pd[0]); // close read end of pipe pd
        while (true) {
        srand(time(NULL));
            int x = rand() % 100;
            write(pc[1], &x, sizeof(int));
            cout << "Child C sends " << x << endl;
            sleep(1);
        }
    } else {
        d_pid = fork();
        if (d_pid == -1) {
            perror("Error forking child D");
            exit(1);
        } else if (d_pid == 0) {
            // child D PROCESS
            close(pc[0]); // close read end of pipe pc
            close(pd[0]); // close read end of pipe pd
            while (true) {
            srand(time(NULL));
                int random_num = rand() % 99+1 ;
                write(pd[1], &random_num , sizeof(int));
                cout << "Child D sends " << random_num  << endl;
                sleep(1);
            }
        } else {
            // parent P code
            close(pc[1]); // close write end of pipe pc
            close(pd[1]); // close write end of pipe pd
            while (true) {
             srand(time(NULL));
                int flag = rand() % 2;
                cout << "Parent P chooses " << (flag == MIN ? "MIN" : "MAX") << endl;
                int c, d;
                
                read(pc[0], &c, sizeof(int));
                read(pd[0], &d, sizeof(int));
                cout << "Parent P receives " << c << " from child C" << endl;
                cout << "Parent P receives " << d << " from child D" << endl;
                if (c == d) {
                    cout << "Round ignored" << endl;
                } else if ((flag == MIN && c < d) ||(flag == MAX && c > d)) {
                    cout << "Child C gets one point" << endl;
                    c_score++;
                } else {
                    cout << "Child D gets one point" << endl;
                    d_score++;
                }
                cout << "Score: Child C = " << c_score << ", Child D = " << d_score << endl;
                cout<<"\n";
                if (c_score >= WIN || d_score >= WIN) {
                    kill(c_pid, SIGINT);
                    kill(d_pid, SIGINT);
                        break;
                    }
                }
            }
        }
    

    // close all remaining file descriptors
    close(pc[READ_END]);
    close(pd[READ_END]);
    close(pc[WRITE_END]);
    close(pd[WRITE_END]);

    // wait for child processes to exit
    int status;
    waitpid(c_pid, &status, 0);
    waitpid(d_pid, &status, 0);
    handle_signal(SIGINT);

    return 0;
}