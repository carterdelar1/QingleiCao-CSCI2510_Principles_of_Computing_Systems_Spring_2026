#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int race = 0;

void* adder(void* arg) {
    for (int i = 0; i < 200000000; i++) {
        race++;
    }
}

void* subtractor(void* arg) {
    for (int i = 0; i < 200000000; i++) {
        race--;
    }
}

int main() {
    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, adder, NULL) != 0) {
        printf("error with thread 1");
        exit(1);
    }

    if (pthread_create(&thread2, NULL, subtractor, NULL) != 0) {
        printf("error with thread 2");
        exit(1);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("value of race: %d\n", race);

    

    // printf("value of race: %d\n", race);
    // adder(NULL);
    // printf("value of race: %d\n", race);
    // subtractor(NULL);
    // printf("value of race: %d\n", race);

    return 0;

}