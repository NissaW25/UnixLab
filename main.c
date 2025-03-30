#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_pid_t.h>
#include <unistd.h>

int main() {
    int i = 0;
    char *args[250];
    int stat;
    char sym[100]; //token
    pid_t child_pid;


    while(1) {
        printf("shell> ");

        /* Reading Input */
        if (fgets(sym, 250, stdin) == NULL) {
            perror("error");
            exit(1);
        };

        sym[strlen(sym) - 1] = '\0';

        if (strcmp(sym, "exit") == 0) {
            exit(0);
        }

        /* Tokenizing */
        args[i] = strtok(sym, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }


        /* Fork() Call */
        child_pid = fork(); //creates child process
        if (child_pid == -1) {
            perror("fork error");
            exit(1);
        }
        if (child_pid == 0) { //child process
            if (execvp(args[0], args) < 0) {//exec() call
                perror("Won't print if exec works\n");
            }
            exit(1);
        }
        else { // parent process
            waitpid(child_pid, &stat, 0); // wait() call
        }
    }
}


