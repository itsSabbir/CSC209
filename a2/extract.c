/*
** This file is part of the CSC209 -- Fall 2023 Assignment 2
**
** All of the files in this directory and all subdirectories are:
** Copyright (c) 2023 Demetres Kostas
**
** This is extract.c
**
** This file contains functions required for extracting the contents
** from a .kar archive file and recreating the original directory structure
** and files on the filesystem.
*/

#include "kar_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>  // Include this for chdir

/*
 * Read a single arch_tree_node from the archive file.
 * This function is used to reconstruct the directory tree structure
 * from the archive.
 */
arch_tree_node *read_node(FILE *archive) {
    arch_tree_node *node = malloc(sizeof(arch_tree_node));
    if (!node) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }

    if (fread(node, sizeof(arch_tree_node), 1, archive) != 1) {
        free(node);
        if (feof(archive)) {
            return NULL; // End of archive reached
        } else {
            perror("Failed to read from archive");
            exit(EXIT_FAILURE);
        }
    }
    return node;
}

/*
 * Extract the contents from the archive file recursively.
 * This function reads the directory tree structure from the archive
 * and creates directories and files on the filesystem accordingly.
 */
void extract_from_archive(FILE *archive, char *parent_path) {
    arch_tree_node *current;
    while ((current = read_node(archive)) != NULL) {
        // Construct the full path for the current file or directory
        char full_path[512];
        valid_path(full_path, parent_path, current->name);

        if (current->is_directory) {
            // Handle directory extraction
            printf("Extracting Directory: %s\n", full_path);

            // Using a default mode of 0755 for directories
            if (mkdir(full_path, 0755) == -1 && errno != EEXIST) {
                perror("Failed to create directory");
                fprintf(stderr, "Directory path: %s\n", full_path);
                exit(EXIT_FAILURE);
            }

            // Recursively extract the contents of the directory
            chdir(full_path);
            extract_from_archive(archive, ".");
            chdir("..");
        } else {
            // Handle file extraction
            printf("Extracting File: %s (Size: %u)\n", full_path, current->size);

            FILE *out_file = fopen(full_path, "wb");
            if (!out_file) {
                perror("Failed to create file");
                fprintf(stderr, "File path: %s\n", full_path);
                return;
            }

            if (buffered_read_write(archive, out_file, current->size, 4096) != 0) {
                fprintf(stderr, "Error occurred during file extraction\n");
            }

            fclose(out_file);
        }

        free(current);
    }
}

/*
 * Main function to extract the contents from a .kar archive file.
 * It opens the archive file for reading and starts the extraction
 * process by calling extract_from_archive.
 */
int extract_archive(char *archive_name) {
    FILE* archive = fopen(archive_name, "rb");
    if (!archive) {
        perror("Failed to open archive");
        return 1;
    }

    extract_from_archive(archive, ".");

    fclose(archive);
    return 0;
}
