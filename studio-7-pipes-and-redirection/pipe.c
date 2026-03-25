#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t fork1;
    pid_t fork2;

    int fd[2];
    pipe(fd);

    fork1 = fork();

    if (fork1 == 0) {
        dup2(fd[1], STDOUT_FILENO);

        close(fd[0]);

        char* cmd = "./program1";
        char* myargv[] = {"program1", '\0'};
        int ret = execvp(cmd, myargv);
        if (ret == -1) {
                perror("Error executing print");
            }
    } else {
        fork2 = fork();
        
        if (fork2 == 0) {
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            char* cmd = "./program2";
            char* myargv[] = {"program2", '\0'};
            int ret = execvp(cmd, myargv);
            if (ret == -1) {
                perror("Error executing print");
            }
        } else {
            close(fd[1]);
            close(fd[0]);
            waitpid(fork1, NULL, 0);
            waitpid(fork2, NULL, 0);    
        }
    }
}