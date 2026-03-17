//Runlength compression in C
// Usage: ./rle <input file> <output file> <runlength> <mode>
//        Where mode=0 is compress and mode=1 is decompress

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

void compress_file(int input_filedir, int output_filedir, int K) {
    unsigned char *current_pattern = malloc(K);
    unsigned char *next_pattern = malloc(K);
    unsigned char count = 1;

    ssize_t bytes_read = read(input_filedir, current_pattern, K);
    if (bytes_read <= 0) {
        free(current_pattern);
        free(next_pattern);
        return;
    }

    int current_len = bytes_read;

    // while statement so it reads until it's 0. this is because it could be less than the first chunk, if it's
    // at the end
    while ((bytes_read = read(input_filedir, next_pattern, K)) > 0) {
        if (bytes_read == current_len && memcmp(current_pattern, next_pattern, current_len) == 0 &&
        count < 255) {
            count++;
        } else {
            write(output_filedir, &count, 1);
            write(output_filedir, current_pattern, current_len);

            memcpy(current_pattern, next_pattern, bytes_read);
            current_len = bytes_read;
            count = 1;
        }
    }

    write(output_filedir, &count, 1);
    write(output_filedir, current_pattern, current_len);

    free(current_pattern);
    free(next_pattern);

}


void decompress_file(int input_filedir, int output_filedir, int K) {
    unsigned char N;
    unsigned char *buffer = malloc(K);
    ssize_t bytes_read;

    while (read(input_filedir, &N, 1) > 0) {
        bytes_read = read(input_filedir, buffer, K);

        if (bytes_read > 0) {
            for (int i = 0; i < N; i++) {
                write(output_filedir, buffer, bytes_read);
            }
        }
    }
    free(buffer);
}


int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Error: Need correct parameters: rle <input file> <output file> <compression length> <mode>\n");
        exit(-1);
    }

    int input_filedir = open(argv[1],O_RDONLY);
    int output_filedir = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, 0644);

    int K = atoi(argv[3]);
    int mode = atoi(argv[4]);

    if (K < 1) {
        printf("Error: Compression length must be >= 1\n");
        exit(-1);
    }

    if (mode != 0 && mode != 1) {
        printf("Error: Mode must be 0 (compress) or 1 (decompress)\n");
        exit(-1);
    }

    if (mode == 0) {
        compress_file(input_filedir, output_filedir, K);
    } else {
        decompress_file(input_filedir, output_filedir, K);
    }




}