#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main () {
    pid_t fork1 = fork();

    char* child_argv[] = {"echo", "hello world", NULL};
    char* child_prog = child_argv[0];

    // printf("process pid: %d\n", fork1);
    if (fork1 == 0) {
        sleep(3);
        printf("i'm the child process. process id: %d\n", fork1);
        execvp(child_prog, child_argv);
    } else {
        waitpid(fork1, NULL, 0);
        printf("i'm the adult process. process id: %d\n", fork1);
    }
}