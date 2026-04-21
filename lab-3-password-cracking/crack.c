//This program brute-forces a given password hash by trying all possible
//passwords of a given length.
//
//Usage:
//crack <threads> <keysize> <target>
//
//Where <threads> is the number of threads to use, <keysize> is the maximum
//password length to search, and <target> is the target password hash.
//
//For example:
//
//./crack 1 5 na3C5487Wz4zw
//
//Should return the password 'apple'

#include <stdio.h>
#include <unistd.h>
#include <crypt.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


struct thread_struct {
  char start_char;
  char end_char;
  int max_keysize;
  char* target_hash;
  char* salt;
};

void crack_password(char* current_pass, int current_length, int max_length, char* salt, char* target) {
    if (current_length > 0) {
      struct crypt_data data;
      data.initialized = 0;

      char* hash = crypt_r(current_pass, salt, &data);

      if (strcmp(hash, target) == 0) {
        printf("%s\n", current_pass);
        exit(0);
      }
    }

    if (current_length == max_length) {
      return;
    }

    for (char c = 'a'; c <= 'z'; c++) {
      current_pass[current_length] = c;
      current_pass[current_length + 1] = '\0';

      crack_password(current_pass, current_length + 1, max_length, salt, target);
    }

  }

void* thread_entry(void* arg) {
  struct thread_struct* data = (struct thread_struct*)arg;
  char password_buffer[9] = {0};

  for (char c = data->start_char; c <= data->end_char; c++) {
    password_buffer[0] = c;
    password_buffer[1] = '\0';

    crack_password(password_buffer, 1, data->max_keysize, data->salt, data->target_hash);
  }

  return NULL;
}



    



int main( int argc, char* argv[] ){

    if (argc != 4) {
      printf("Should be in format: ./crack <threads> <keysize> <target>\n");
      return (1);
    }

    int num_threads = atoi(argv[1]);
    int keysize = atoi(argv[2]);
    char* target = argv[3];

    char salt[3];
    strncpy(salt, target, 2);
    salt[2] = '\0';

    pthread_t threads[num_threads];
    struct thread_struct thread_args[num_threads];

    int letters_per_thread = 26 / num_threads;

    for (int i = 0; i < num_threads; i++) {
      thread_args[i].start_char = 'a' + (i * letters_per_thread);

      if (i == num_threads - 1) {
        thread_args[i].end_char = 'z';
      } else {
        thread_args[i].end_char = thread_args[i].start_char + letters_per_thread - 1;
      }

      thread_args[i].max_keysize = keysize;
      thread_args[i].target_hash = target;
      thread_args[i].salt = salt;

      pthread_create(&threads[i], NULL, thread_entry, &thread_args[i]);

    }

    for (int i = 0; i < num_threads; i++) {
      pthread_join(threads[i], NULL);
    }

    // char password_buffer[9] = {0};
    // crack_password(password_buffer, 0, keysize, salt, target);



return 0; 
}
