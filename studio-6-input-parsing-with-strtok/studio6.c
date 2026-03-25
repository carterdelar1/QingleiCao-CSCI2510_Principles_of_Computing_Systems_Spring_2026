#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    // char input_string[100];

    // fgets(input_string, sizeof(input_string), stdin);

    // char *token = strtok(input_string, " \n");

    // while (token != NULL) {
    //     printf("%s\n", token);
    //     token = strtok(NULL, " \n");
    // }

int max_args = 15;
int max_argv_size = max_args + 2;
char* cmd;
char* my_argv[max_argv_size];

char input_string[100];
fgets(input_string, sizeof(input_string), stdin);

cmd = strtok(input_string, " \n");

my_argv[0] = cmd;
    
int i = 1;
while (i <= max_args) {
    char* res = strtok(NULL, " \n");
    my_argv[i] = res;

    if (res == NULL) break;
    i++;
} my_argv[i++] = '\0';

execvp(cmd, my_argv);


return 0;

}
