#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int race = 0;
pthread_mutex_t mutex;




void* adder(void* arg) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 20000000; i++) {
        race++;
    }
    pthread_mutex_unlock(&mutex);

}

void* subtractor(void* arg) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 20000000; i++) {
        race--;
    }
    pthread_mutex_unlock(&mutex);

}

int main() {
    pthread_t thread1, thread2;



    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("error setting up mutex");
        exit(1);
    }

    if (pthread_create(&thread1, NULL, adder, &mutex) != 0) {
        printf("error with thread 1");
        exit(1);
    }

    if (pthread_create(&thread2, NULL, subtractor, &mutex) != 0) {
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