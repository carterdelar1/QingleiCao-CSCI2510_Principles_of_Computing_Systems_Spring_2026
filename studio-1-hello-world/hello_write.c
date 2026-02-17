// Carter DeLargy // 2-17-2026 
// this writes hello world 
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    write(STDOUT_FILENO,"Hello, world!\n",14);
    return 0;
}

