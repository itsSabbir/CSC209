#include <stdio.h>

int main() {
    // Declare a string to store the phone number. 
    // We allocate space for 11 characters to account for the 10-digit phone number 
    // and the null terminator that indicates the end of the string.
    char phone[11];
    
    // Declare an integer to store the user's input.
    int index;

    // Read the phone number and the integer from standard input.
    scanf("%s %d", phone, &index);

    // Check the value of the integer.
    if (index == -1) {
        // If the integer is -1, print the entire phone number.
        printf("%s\n", phone);
    } else if (index >= 0 && index <= 9) {
        // If the integer is between 0 and 9 (inclusive), 
        // print the character at that position in the phone number.
        printf("%c\n", phone[index]);
    } else {
        // If the integer is outside the range [-1, 9], print an error message.
        printf("ERROR\n");
        return 1; // Exit with an error code.
    }

    return 0; // Exit successfully.
}
