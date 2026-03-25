#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char input_string[100];
    int i = 0;
    while (i == 0) {
        if (fgets(input_string, sizeof(input_string), stdin) == NULL) break;
        printf("Program 2 got: %s\n", input_string);
    }

    return 0;
}