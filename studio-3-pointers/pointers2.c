#include <stdlib.h>

char* reverseString( char* input ){

//1. First count how many characters are in the input string
int i = 0;
int num_chars_in_input;

while (input[i] != NULL) {
    i++;
};
num_chars_in_input = i;

//This creates enough space to store the reversed string, plus one more byte
//for the null terminator
char* output = (char*)malloc( num_chars_in_input+1 );

//2. Copy the input string to the output string in reverse order. There are
//multiple ways to do this- consider using a counter, or consider using two
//pointers. 

int j = 0;
for (num_chars_in_input > 0; num_chars_in_input--;) {
    output[j] = input[num_chars_in_input];
    j++;
}

//REMEMBER THAT YOUR OUTPUT STRING MUST END WITH A NULL TERMINATOR. This is not
//provided for you automatically- you must put it there!

    return output; 
}

int main() {

    char *messagePtr = "HELLOWORLD!";

    char* reversedMessage = reverseString( messagePtr );
    printf("Reversed string: %s\n", reversedMessage);
    

    return 0;
}