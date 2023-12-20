#include <stdio.h>

int main() {
    // Declare a string to store the phone number and an integer to store the user's input.
    char phone[11];
    int integer;

    // Read the phone number from standard input.
    scanf("%s", phone);

    // Continuously read integers from standard input until EOF (End Of File) is reached.
    while (scanf("%d", &integer) != EOF) {

        // If the integer is -1, print the entire phone number.
        if (integer == -1) {
            printf("%s\n", phone);
        } 
        // If the integer is between 0 and 9, print the corresponding digit from the phone number.
        else if (integer >= 0 && integer <= 9) {
            printf("%c\n", phone[integer]);
        } 
        // If the integer is out of range, print "ERROR" and exit with a return code of 1.
        else {
            printf("ERROR\n");
            return 1;
        }
    }

    // If the loop completes without errors, return 0.
    return 0;
}
