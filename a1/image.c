#include <stdio.h>

// Reads the image data from the file into the 2D array
void read_image(int num_rows, int num_cols, int arr[num_rows][num_cols], FILE *fp) {
    // Iterate over each row of the image
    for (int i = 0; i < num_rows; i++) {
        // Iterate over each column of the image
        for (int j = 0; j < num_cols; j++) {
            // Read the pixel value from the file and store it in the array
            fscanf(fp, "%d", &arr[i][j]);
        }
    }
}

// Prints the image data from the 2D array
void print_image(int num_rows, int num_cols, int arr[num_rows][num_cols]) {
    // Iterate over each row of the image
    for (int i = 0; i < num_rows; i++) {
        // Iterate over each column of the image
        for (int j = 0; j < num_cols; j++) {
            // Print the pixel value followed by a space
            printf("%d ", arr[i][j]);
        }
        // Print a newline after each row to format the output correctly
        printf("\n");
    }
}

// Flood fill function
void flood_fill(int i, int j, int num_rows, int num_cols, int arr[num_rows][num_cols], int visited[num_rows][num_cols]) {
    // Check if the current coordinates are out of the image boundaries
    if (i < 0 || i >= num_rows || j < 0 || j >= num_cols) {
        return;
    }

    // Check if the current pixel is black or has already been visited
    if (arr[i][j] == 0 || visited[i][j] == 1) {
        return;
    }

    // Mark the current pixel as visited
    visited[i][j] = 1;

    // Recursively flood fill the neighboring pixels (top, bottom, left, right)
    flood_fill(i + 1, j, num_rows, num_cols, arr, visited); // Bottom neighbor
    flood_fill(i - 1, j, num_rows, num_cols, arr, visited); // Top neighbor
    flood_fill(i, j + 1, num_rows, num_cols, arr, visited); // Right neighbor
    flood_fill(i, j - 1, num_rows, num_cols, arr, visited); // Left neighbor
}

// count_cells function
int count_cells(int num_rows, int num_cols, int arr[num_rows][num_cols]) {
    int count = 0; // Variable to store the number of cells found
    int visited[num_rows][num_cols]; // 2D array to track visited pixels

    // Initialize visited array to 0 (indicating not visited)
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            visited[i][j] = 0;
        }
    }

    // Iterate over each pixel in the image
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            // If the pixel is white (255) and hasn't been visited, it's a new cell
            if (arr[i][j] == 255 && visited[i][j] == 0) {
                flood_fill(i, j, num_rows, num_cols, arr, visited); // Flood fill the cell
                count++; // Increment the cell count
            }
        }
    }

    return count; // Return the total number of cells found
}
