#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  This program evaluates two input arguments to determine their similarity.
  The output will be:
    - "Same\n" if both arguments are identical.
    - "Different\n" if they are distinct.
    - "Invalid\n" if an incorrect number of arguments is provided.

  Regardless of the result, the main function will always return 0.
*/

int main(int argCount, char *argList[]) {
    // The program expects 3 arguments in total: the program's name itself and two input strings.
    // If the total argument count is not 3, it means the user has not provided the correct number of arguments.
    if (argCount != 3) {
        printf("Invalid\n");
        return 0;  // Exit after printing "Invalid".
    }

    // Compare the two provided arguments.
    // `strcmp` returns 0 if the strings are identical.
    // If the result is non-zero, it means the strings differ.
    int comparisonResult = strcmp(argList[1], argList[2]);
    
    // If the comparison result is 0, the strings are the same.
    if (comparisonResult == 0) {
        printf("Same\n");
    } else {  // Otherwise, the strings are different.
        printf("Different\n");
    }

    return 0;  // The program ends with a return value of 0, indicating successful execution.
}
