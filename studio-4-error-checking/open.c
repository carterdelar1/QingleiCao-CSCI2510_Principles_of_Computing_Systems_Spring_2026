#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char buffer[1000];
ssize_t bytes;

int main(int argc, char *argv[]) {
    if (argc!= 2) {
        perror("Error: Not correct amount of arguments.\n");
        exit(-1);
    }

    int input_filedir = open(argv[1], O_RDONLY);
    if (input_filedir == -1) {
        perror("Error opening file.\n");
        exit(-1);
    } 

    bytes = read(input_filedir, buffer, 1000);
    printf("%s", buffer);
}