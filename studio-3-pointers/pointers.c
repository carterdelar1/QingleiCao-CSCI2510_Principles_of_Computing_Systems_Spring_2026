#include <stdio.h>

int main() {
    char *messagePtr = "HELLOWORLD!";

    // printf("%s\n", messagePtr);

    // for (int i = 0; i < strlen(messagePtr); i++) {
    //     char char_to_print = messagePtr[i];
    //     printf("%c\n", char_to_print);
    // };

    // printf("%c\n", *(messagePtr+2));

    // for (int i = 0; i < strlen(messagePtr); i++) {
    //     printf("%c\n", *(messagePtr + i));
    // }

    // int i = 0;
    // while (messagePtr[i] != NULL) {
    //     printf("%c\n", *(messagePtr + i));
    //     i++;
    // }

    void printReverse(char* string) {
        int i = 0;
        int string_length;

        while (string[i] != NULL) {
            i++;
        }
        string_length = i;

        for (string_length > 0; string_length--;) {
            printf("%c\n", *(string+string_length));
        }
    };

    printReverse(messagePtr);

    char *SecondString = "Another string!";

    printReverse(SecondString);



    return 0;
}