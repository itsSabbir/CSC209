#include <stdio.h>
#include <string.h>


/*
    This program has two arguments: the first is a greeting message, and the
    second is a name.

    The message is an impersonal greeting, such as "Hi" or "Good morning".
    name is set to refer to a string holding a friend's name, such as
    "Emmanuel" or "Xiao".

    First copy the first argument to the array greeting. (Make sure it is
    properly null-terminated.)

    Write code to personalize the greeting string by appending a space and
    then the string pointed to by name.
    So, in the first example, greeting should be set to "Hi Emmanuel", and
    in the second it should be "Good morning Xiao".

    If there is not enough space in greeting, the resulting greeting should be
    truncated, but still needs to hold a proper string with a null terminator.
    For example, "Good morning" and "Emmanuel" should result in greeting
    having the value "Good morning Emmanu" and "Top of the morning to you" and
    "Patrick" should result in greeting having the value "Top of the morning ".

    Do not make changes to the code we have provided other than to add your
    code where indicated.
*/

#include <stdio.h>
#include <string.h>

/*
    This program expects two command-line arguments: a greeting message and a name.
    The goal is to create a personalized greeting by appending the name to the greeting message.

    The greeting is truncated if the combined length exceeds the size of the greeting buffer.

    This program demonstrates string manipulation in C, such as copying, concatenation, and truncation.
*/

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: greeting message name\n");
        return 1;
    }
    
    char greeting[20];
    char *name = argv[2];

    // Copy the greeting message to the greeting buffer.
    strncpy(greeting, argv[1], sizeof(greeting) - 1);  // Ensure null termination.
    greeting[sizeof(greeting) - 1] = '\0';  // Explicitly null-terminate.

    // Calculate remaining space in the greeting buffer after the greeting message and a space.
    int spaceLeft = sizeof(greeting) - strlen(greeting) - 2;  // -2 accounts for space and null terminator.

    // If there's room, append a space and then the name (or its truncated version).
    if (spaceLeft > 0) {
        strcat(greeting, " ");
        strncat(greeting, name, spaceLeft);
    }

    printf("%s\n", greeting);
    return 0;
}



