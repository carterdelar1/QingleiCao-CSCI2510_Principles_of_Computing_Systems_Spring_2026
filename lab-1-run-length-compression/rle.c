//Runlength compression in C
// Usage: ./rle <input file> <output file> <runlength> <mode>
//        Where mode=0 is compress and mode=1 is decompress

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

// compresses the file using rle
void compress_file(int input_filedir, int output_filedir, int K) {

    // allocates memory for the current pattern size k
    unsigned char *current_pattern = malloc(K);

    if (current_pattern == NULL) {
        perror("pointer is null");
        exit(-1);
    }

    // allocates memory for the next pattern size k
    unsigned char *next_pattern = malloc(K);

    if (next_pattern == NULL) {
        perror("pointer is NULL");
        exit(-1);
    }

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
        // checks if they're equal and less than 255
        if (bytes_read == current_len && memcmp(current_pattern, next_pattern, current_len) == 0 &&
        count < 255) {
            count++;
        } else {
            // writes the count of repetitions the pattern has
            if (write(output_filedir, &count, 1) == -1) {
                perror("Error with writing");
                exit(-1);
            };
            // writes the pattern after the count
            if (write(output_filedir, current_pattern, current_len) == -1) {
                perror("Error with writing");
                exit(-1);
            };

            memcpy(current_pattern, next_pattern, bytes_read);
            current_len = bytes_read;
            count = 1;
        }
    }

    // writes the last count
    if (write(output_filedir, &count, 1) == -1) {
        perror("Error with writing");
        exit(-1);
    };
    // writes the last pattern
    if (write(output_filedir, current_pattern, current_len) == -1) {
        perror("Error with writing");
        exit(-1);
    };

    free(current_pattern);
    free(next_pattern);

}

// decompresses the compressed file
void decompress_file(int input_filedir, int output_filedir, int K) {
    unsigned char N;
    unsigned char *buffer = malloc(K);

    if (buffer == NULL) {
        perror("pointer is null");
        exit(-1);
    }

    ssize_t bytes_read;
    // reads the number of repetitions
    while (read(input_filedir, &N, 1) > 0) {
        bytes_read = read(input_filedir, buffer, K);

        if (bytes_read == -1) {
            perror("error with reading");
            exit(-1);
        }

        // writes the pattern for however many repetitions there are
        if (bytes_read > 0) {
            for (int i = 0; i < N; i++) {
                if (write(output_filedir, buffer, bytes_read) == -1) {
                    perror("Error with writing");
                    exit(-1);
                };
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

    if (input_filedir == -1) {
        perror("Error reading file");
        exit(-1);
    }

    if (output_filedir == -1) {
        perror("Error reading output file");
        exit(-1);
    }

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


    if (close(input_filedir) == -1) {
        perror("Error closing input file");
        exit(-1);
    }

    if (close(output_filedir) == -1) {
        perror("Error closing output file");
        exit(-1);
    }


}