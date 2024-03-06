

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sys/stat.h>

using namespace std;


void who() {
    cout << "\ncurrent logged system is : " << getlogin() << endl;
}

void changeDirectory(char *dir_name) {
    if (dir_name == NULL) {
        cout << "Error " << endl;
    } else {
        if (chdir(dir_name) != 0) {
            cout << "\nNow, you have changed your directory to : " <<dir_name << "\n"<< endl;
        }
    }
}

void printWorkingDirectory() {
    char *cwd;
    cwd = getcwd(NULL, 0);
    cout <<"\nour current working directory : "<< cwd << endl << endl;
    free(cwd);
}

void makeDirectory(char *dir_name)
{
    if (dir_name == NULL) {
        cout << "Error " << endl;
    }
     
      mkdir(dir_name,0777);
      cout << "\nNew folder created : " << dir_name << endl<< endl;
       
   
}


void removeDirectory(char *dir_name) {
    if (dir_name == NULL) {
        cout << "Error " << endl;
    } else {
        if (rmdir(dir_name) != 0) {
            cout << "\nThis folder is removed : " << dir_name << endl<< endl;
        }
    }
}

void listFilesAndDirectories() {
    system("ls");
}


int main() {
    string input;
    char *command;
    char *dir_name;

    while (true) {
        // Prompt for user input
        cout << "Ayush Kumar> ";
        getline(cin, input);
        command = strtok(&input[0], " ");
        dir_name = strtok(NULL, " ");

        // Execute built-in commands
        if (strcmp(command, "who") == 0) {
            who();
        }
        else if (strcmp(command, "cd") == 0) {
            changeDirectory(dir_name);
        }
         else if (strcmp(command, "pwd") == 0) {
            printWorkingDirectory();
        }
         else if (strcmp(command, "mkdir") == 0) {
            makeDirectory(dir_name);
        }
        else if (strcmp(command, "rmdir") == 0) {
            removeDirectory(dir_name);
        }
        else if (strcmp(command, "ls") == 0) {
            listFilesAndDirectories();
        }
        else if (strcmp(command, "exit") == 0) {
            exit(0);
        }
        else {
          exit(0);
        }
    }

    return 0;
}