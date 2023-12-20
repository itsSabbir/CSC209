#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void read_image(int num_rows, int num_cols, int arr[num_rows][num_cols], FILE *fp);
void print_image(int num_rows, int num_cols, int arr[num_rows][num_cols]);
int count_cells(int num_rows, int num_cols, int arr[num_rows][num_cols]);

int main(int argc, char **argv) {
    // Check the number of command-line arguments to ensure correct usage
    // (either just the file name or file name plus the -p flag)
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: count_cells <imagefile.txt> [-p]\n");
        return 1; // Exit with error code
    }

    // If there are 3 arguments, ensure the third one is the "-p" flag
    if (argc == 3 && strcmp(argv[2], "-p") != 0) {
        fprintf(stderr, "Usage: count_cells <imagefile.txt> [-p]\n");
        return 1; // Exit with error code
    }

    // Open the image file for reading
    FILE *fp = fopen(argv[1], "r");
    // Check if the file was opened successfully
    if (fp == NULL) {
        perror("Error opening file!");
        return 1; // Exit with error code
    }

    // Variables to store the dimensions of the image
    int num_rows, num_cols;
    // Read the dimensions from the file
    fscanf(fp, "%d %d", &num_rows, &num_cols);

    // Declare a 2D array to hold the image data
    int image[num_rows][num_cols];

    // Read the image data from the file into the 2D array
    read_image(num_rows, num_cols, image, fp);

    // If the "-p" flag is provided, print the image data to the console
    if (argc == 3 && strcmp(argv[2], "-p") == 0) {
        print_image(num_rows, num_cols, image);
    }

    // Call the count_cells function to count the number of cells in the image
    int cell_count = count_cells(num_rows, num_cols, image);
    // Print the result to the console
    printf("Number of Cells is %d\n", cell_count);

    // Close the file now that we're done with it
    fclose(fp);

    return 0; // Indicate successful execution
}
