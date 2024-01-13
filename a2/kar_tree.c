/*
** This file is part of the CSC209 -- Fall 2023 Assignment 2
**
** All of the files in this directory and all subdirectories are:
** Copyright (c) 2023 Demetres Kostas
**
** This file is kar_tree.c
**
** This file contains utility functions for working with the archive tree structure,
** as well as functions for reading from and writing to files in a buffered manner.
*/

#include "kar_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * free_tree: Recursively frees the memory allocated for the archive tree.
 * It traverses the tree, freeing the memory for each node and its contents.
 * 
 * Parameters:
 *   root - a pointer to the root of the tree or subtree to be freed.
 */
void free_tree(arch_tree_node *root) {
    // Base case: if the node is NULL, return
    if (!root) return;

    // First, free any directory contents
    if (root->is_directory) {
        free_tree(root->dir_contents);
    }

    // Then, free the next file in the directory
    free_tree(root->next_file);

    // Now, it's safe to free the current node
    free(root);
}

/*
 * only_filename: Modifies the provided file path to contain only the filename.
 * It searches for the last '/' character in the filepath and keeps everything after it.
 *
 * Parameters:
 *   filepath - a character array representing the file path.
 */
void only_filename(char* filepath) {
    int total_chars = strlen(filepath);

    // Remove trailing '/' if present
    if(filepath[total_chars - 1] == '/') {
        filepath[total_chars - 1] = '\0';
    }

    // Find the last '/' in the filepath
    char* filename = strrchr(filepath, '/');
    // If found, copy everything after it to the beginning of filepath
    for(size_t i = 0; filename && i <= strlen(filename); i++) {
        filepath[i] = filename[i + 1];
    }
}

/*
 * valid_path: Combines a directory and filename into a valid file path.
 * It ensures that there is exactly one '/' between the directory and filename.
 *
 * Parameters:
 *   path_buffer - a character array to store the resulting file path.
 *   directory - a string representing the directory.
 *   filename - a string representing the filename.
 */
void valid_path(char path_buffer[], char *directory, char *filename) {
    // Copy the directory to path_buffer
    strcpy(path_buffer, directory);
    size_t dir_len = strlen(path_buffer);
    // Ensure there is a '/' at the end of the directory
    if (dir_len > 0 && path_buffer[dir_len - 1] != '/') {
        strcat(path_buffer, "/");
    }
    // Append the filename to path_buffer
    strcat(path_buffer, filename);
}

/*
 * buffered_read_write: Reads from an input file and writes to an output file in a buffered manner.
 * It reads and writes up to buffer_size bytes at a time until read_remaining bytes have been processed.
 *
 * Parameters:
 *   input - a pointer to the input file.
 *   output - a pointer to the output file.
 *   read_remaining - the total number of bytes to read from the input file.
 *   buffer_size - the size of the buffer to use for reading and writing.
 *
 * Returns:
 *   0 on success, -1 on failure.
 */
int buffered_read_write(FILE *input, FILE *output, size_t read_remaining, size_t buffer_size) {
    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory for buffer");
        return -1;
    }

    size_t bytes_read;
    size_t next_read_size = buffer_size < read_remaining ? buffer_size : read_remaining;

    // Continue reading and writing until all bytes are processed
    while (read_remaining > 0 && (bytes_read = fread(buffer, 1, next_read_size, input)) > 0) {
        int to_write = bytes_read;

        char *buf_pt = buffer;
        // Write the buffer to the output file
        while(to_write > 0) {
            size_t num_written = fwrite(buf_pt, 1, to_write, output);
            to_write -= num_written;
            buf_pt += num_written;
        }
        read_remaining -= bytes_read;
        next_read_size = buffer_size < read_remaining ? buffer_size : read_remaining;
    }
    free(buffer);
    return 0;
}
