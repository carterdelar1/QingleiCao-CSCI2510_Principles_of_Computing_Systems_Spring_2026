#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct thread_struct{
        int arg1;
        char arg2[256];
        int ret;
    };

void* thread_entry(void* arg) {
    printf("Thread entry function running\n");
    struct thread_struct* arg_ptr = (struct thread_struct*) arg;
    printf("thread arg1: %d\n", arg_ptr->arg1);
    printf("thread arg2: %s\n", arg_ptr->arg2);
    printf("thread ret: %d\n", arg_ptr->ret);

    arg_ptr->ret = 10;
    return NULL;
}



int main() {

    // struct thread_struct main_struct;
    // main_struct.arg1 = 15;
    // strcpy(main_struct.arg2, "hello");
    // main_struct.ret = 0;

    // pthread_t thread;

    

    // if (pthread_create(&thread, NULL, thread_entry, &main_struct) != 0) {
    //     printf("error\n");
    //     exit(1);
    // }

    // pthread_join(thread, NULL);

    // printf("ret value after thread entry: %d\n", main_struct.ret);


    int num_threads = 5;
    unsigned bufSize = 100;

    pthread_t threads[num_threads];
    struct thread_struct args[num_threads];

    for (int i = 0; i < num_threads; i++) {
        args[i].arg1 = i;
        args[i].ret = 0;
        snprintf(args[i].arg2, bufSize, "This is thread %d", i);

        if (pthread_create(&threads[i], NULL, thread_entry, &args[i]) != 0) {
        printf("error\n");
        exit(1);
        }
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }




    return 0;



}