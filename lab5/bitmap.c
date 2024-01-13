#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"


/*
 * Read in the location of the pixel array, the image width, and the image 
 * height in the given bitmap file.
 */
void read_bitmap_metadata(FILE *image, int *pixel_array_offset, int *width, int *height) {
    // Seek to the location of pixel_array_offset and read its value
    fseek(image, 10, SEEK_SET);
    if (fread(pixel_array_offset, sizeof(int), 1, image) != 1) {
        fprintf(stderr, "Failed to read pixel_array_offset from the bitmap file.\n");
        exit(1);
    }

    // Seek to the location of width and read its value
    fseek(image, 18, SEEK_SET);
    if (fread(width, sizeof(int), 1, image) != 1) {
        fprintf(stderr, "Failed to read width from the bitmap file.\n");
        exit(1);
    }

    // Seek to the location of height and read its value
    fseek(image, 22, SEEK_SET);
    if (fread(height, sizeof(int), 1, image) != 1) {
        fprintf(stderr, "Failed to read height from the bitmap file.\n");
        exit(1);
    }
}

/*
 * Read in pixel array by following these instructions:
 *
 * 1. First, allocate space for m `struct pixel *` values, where m is the 
 *    height of the image.  Each pointer will eventually point to one row of 
 *    pixel data.
 * 2. For each pointer you just allocated, initialize it to point to 
 *    heap-allocated space for an entire row of pixel data.
 * 3. Use the given file and pixel_array_offset to initialize the actual 
 *    struct pixel values. Assume that `sizeof(struct pixel) == 3`, which is 
 *    consistent with the bitmap file format.
 *    NOTE: We've tested this assumption on the Teaching Lab machines, but 
 *    if you're trying to work on your own computer, we strongly recommend 
 *    checking this assumption!
 * 4. Return the address of the first `struct pixel *` you initialized.
 */
struct pixel **read_pixel_array(FILE *image, int pixel_array_offset, int width, int height) {
    // Allocate space for pointers to rows of pixel data
    struct pixel **pixels = malloc(height * sizeof(struct pixel *));
    if (pixels == NULL) {
        fprintf(stderr, "Memory allocation failed for pixel rows.\n");
        exit(1);
    }

    // Allocate space for each row of pixel data and read in the pixel values
    for (int i = 0; i < height; i++) {
        pixels[i] = malloc(width * sizeof(struct pixel));
        if (pixels[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for pixel row %d.\n", i);
            exit(1);
        }

        // Seek to the correct position in the file and read in the pixel data for this row
        fseek(image, pixel_array_offset + i * width * sizeof(struct pixel), SEEK_SET);
        if (fread(pixels[i], sizeof(struct pixel), width, image) != width) {
            fprintf(stderr, "Failed to read pixel data for row %d.\n", i);
            exit(1);
        }
    }

    return pixels;
}


/*
 * Print the blue, green, and red colour values of a pixel.
 * You don't need to change this function.
 */
void print_pixel(struct pixel p) {
    printf("(%u, %u, %u)\n", p.blue, p.green, p.red);
}
