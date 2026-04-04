//SLUSH - The SLU SHELL
//
//This assignment reads user input, and executes that input as a sequence of
//programs to execute.
//
//Program execution commands have the form:
//
//prog_n [args] ( ... prog_3 [args] ( prog_2 [args] ( prog_1 [args]
//
//For example, "grep slush ( sort -r ( ls -l -a" returns a reverse sorted list
//of all files in the current directory that contain the string "slush" in
//
//See the lab writeup for more details and other requirements.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void execute_commands(char* processes[], int current_process) {
    if (current_process < 0) {
        return;
    }

    int fd[2];

    if (current_process > 0) {
        if (pipe(fd) == -1) {
            perror("error with the pipe");
            exit(1);
        }
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("error with the forking");
        exit(1);
    }

    if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        if (current_process > 0) {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
        }

        int max_args = 15;
        int max_argv_size = max_args + 2;
        char* my_argv[max_argv_size];

        int arg_count = 0;
        
        char* cmd = strtok(processes[current_process], " ");
        

        while (cmd != NULL && arg_count < max_args) {
            my_argv[arg_count] = cmd;
            arg_count++;
            cmd = strtok(NULL, " ");
        }

        my_argv[arg_count] = NULL;

        if (my_argv[0] != NULL) {
            int ret = execvp(my_argv[0], my_argv);
            if (ret == -1) {
                fprintf(stderr, "%s: Not found\n", my_argv[0]);
                exit(1);
            }
        }
        exit(0);
    } else {
        if (current_process > 0) {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
        }

        execute_commands(processes, current_process - 1);
        waitpid(pid, NULL, 0);

    }

}

void signal_handler(int signum) {
    // printf("\n");
    write(STDOUT_FILENO, "\nslush> ", 9);
}



int main() {
    signal(2, signal_handler);

    int max_args = 15;
    int max_argv_size = max_args + 2;
    char* cmd;
    char* my_argv[max_argv_size];
    

    char* processes[15];
    char* processes_ptr;

    char input_string[256];
    // while (printf("slush> "), fgets(input_string, sizeof(input_string), stdin) != NULL) {
    while (1) {
        printf("slush> ");

        

        if (fgets(input_string, sizeof(input_string), stdin) == NULL) {
            if (feof(stdin)) {
                break;
            }

           

            printf("\n");
            continue;
        }

        input_string[strcspn(input_string, "\n")] = 0;
        if (strlen(input_string) == 0) continue;

        if (strncmp(input_string, "cd ", 3) == 0) {
            char* path = input_string + 3;
            if (chdir(path) != 0) {
                perror("error with cd");
            }
            continue;
        }

        

        // checks to see if the last thing in the input string is a (
        // if so, it gives the error "Invalid null command"
        if (input_string[strlen(input_string) - 1] == '(') {
            fprintf(stderr, "Invalid null command\n");
            continue;
        }

        processes_ptr = strtok(input_string, "(");
        int process_count = 0;
        int error = 0;
        while (processes_ptr != NULL) {
           
            char* check = processes_ptr;
            while (*check == ' ') {
                check++;
            }

            if (*check == '\0') {
                fprintf(stderr, "Invalid null command\n");
                error = 1;
                break;
            }

            processes[process_count] = processes_ptr;
            process_count++;
            processes_ptr = strtok(NULL, "(");
        }

        if (error == 1 || process_count == 0) {
            continue;
        }

        
        // for (int i = 0; i < process_count; i++) {
        //     int arg_count = 0;
        //     cmd = strtok(processes[i], " ");
        //     while (cmd != NULL && arg_count < max_args) {
        //         my_argv[arg_count] = cmd;
        //         arg_count++;
        //         cmd = strtok(NULL, " ");
        //     }
            
        //     my_argv[arg_count] = NULL;

        
        // }

        pid_t main_pid = fork();
        if (main_pid == 0) {
            // execute the recursive function
            execute_commands(processes, process_count - 1);
            exit(0);
        }
        waitpid(main_pid, NULL, 0);

    }
   

    return 0;
}