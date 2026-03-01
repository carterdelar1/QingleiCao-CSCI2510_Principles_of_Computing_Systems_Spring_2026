#include <stdio.h>
#include <unistd.h>

#define bufferSize 1
char buffer[bufferSize];
ssize_t cat_bytes;

int main() {
    while (fgets(buffer, bufferSize,stdin) != NULL) {
        fprintf(stdout, "%s", buffer);
    }

    return 0;
}