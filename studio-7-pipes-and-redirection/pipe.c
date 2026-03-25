#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t fork1;
    pid_t fork2;

    int fd[2];
    pipe(fd[2]);

    fork1 = fork();

    if (fork1 == 0) {
        char* cmd = "./program1";
        char* myargv[] = {"program1", '\0'};
        int ret = execvp(cmd, myargv);
        if (ret == -1) {
                perror("Error executing print");
            }
    } else {
        fork2 = fork();
        
        if (fork2 == 0) {
            char* cmd = "./program2";
            char* myargv[] = {"program2", '\0'};
            int ret = execvp(cmd, myargv);
            if (ret == -1) {
                perror("Error executing print");
            }
        } else {
            waitpid(fork1, fork2);
        }
    }
}