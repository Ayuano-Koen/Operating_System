

#include <iostream>
#include<vector>
#include <pthread.h>
using namespace std;
// Matrix dimensions
#define size 3

//intialise our vectors
vector<vector<int>> vecA (size, vector<int> (size, 0));
vector<vector<int>> vecB (size, vector<int> (size, 0));
vector<vector<int>> vecC (size, vector<int> (size, 0));
vector<vector<int>> vecD (size, vector<int> (size, 0));
vector<vector<int>> vecE (size, vector<int> (size, 0));

void* SumC(void* t);
void* diff_D(void* t);
void multiplication();
void printvec (vector<vector<int>> &vecE);
int i,j,k;

int main() {
    cout<<"Enter your first A matrix :\n";
      for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
        cin>>vecA[i][j];
        }
        }
        cout<<"Enter your first B matrix :\n";
      for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
        cin>>vecB[i][j];
        }
        }
    // Create threads to compute C and D
    pthread_t thread_1, thread_2;
    pthread_attr_t att;
    pthread_attr_init(&att);
    pthread_attr_setdetachstate(&att, PTHREAD_CREATE_JOINABLE);
    pthread_create(&thread_1, &att, SumC, NULL);
    pthread_create(&thread_2, &att, diff_D, NULL);

    // Wait for threads to finish
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
       cout<<"our Multiplication matrix is C : A+B :\n";
    printvec(vecC);
       cout<<"our Multiplication matrix is D : A-B :\n";
    printvec(vecD);
    multiplication();
    
    cout<<"our Multiplication matrix is E : C*D :\n";
    printvec(vecE);


   
    pthread_attr_destroy(&att);
    pthread_exit(NULL);

    return 0;
}
// Thread function to compute C = A + B
void* SumC(void* t) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            vecC[i][j] = vecA[i][j] + vecB[i][j];
        }
    }
    pthread_exit(NULL);
}

// Thread function to compute D = A - B
void* diff_D(void* t) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            vecD[i][j] = vecA[i][j] - vecB[i][j];
        }
    }
    pthread_exit(NULL);
}
void multiplication(){
 for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            vecE[i][j] = 0;
            for (int k = 0; k < size; k++) {
                vecE[i][j] += vecC[i][k] * vecD[k][j];
            }
        }
    }

}
void printvec (vector<vector<int>> &vecE){
  for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            cout << vecE[i][j] << " ";
        }
        cout << endl;
    }
}

// to run this code run this  commands

// g++ -pthread assignment7.cpp -o assignment7
//  ./assignment7
