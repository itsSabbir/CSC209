/*
** This file is part of the CSC209 -- Fall 2023 Assignment 2
**
** All of the files in this directory and all subdirectories are:
** Copyright (c) 2023 Demetres Kostas
**
** This is archive.c
**
** This file contains the functions necessary for creating a .kar archive
** from a list of files and directories. The archive will store all the
** file and directory names, their metadata, and their content if they
** are files.
*/

#include "kar_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

// Define a struct to hold file metadata
typedef struct file_metadata {
    mode_t mode;    // File permissions
    uid_t uid;      // User ID of owner
    gid_t gid;      // Group ID of owner
    time_t mtime;   // Time of last modification
} file_metadata;

/*
 * Create a tree node for a given file or directory.
 * The function recursively creates nodes for directory contents.
 */
arch_tree_node* create_tree_node(char *filepath) {
    // Get file metadata
    struct stat file_stat;
    if (lstat(filepath, &file_stat) == -1) {
        perror("Failed to get file metadata");
        return NULL;
    }

    // Allocate memory for the tree node
    arch_tree_node *node = malloc(sizeof(arch_tree_node));
    if (!node) {
        perror("Failed to allocate memory for node");
        return NULL;
    }

    // Set the filename and ensure it is null-terminated
    strncpy(node->name, filepath, sizeof(node->name) - 1);
    node->name[sizeof(node->name) - 1] = '\0';

    // Set the file size and type
    node->size = file_stat.st_size;
    node->is_directory = S_ISDIR(file_stat.st_mode);
    node->next_file = NULL;
    node->dir_contents = NULL;

    // If the node is a directory, process its contents
    if (node->is_directory) {
        DIR *dir = opendir(filepath);
        if (!dir) {
            perror("Failed to open directory");
            free(node);
            return NULL;
        }

        struct dirent *entry;
        arch_tree_node **current = &node->dir_contents;
        while ((entry = readdir(dir)) != NULL) {
            // Skip the current and parent directory entries
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                char full_path[FILENAME_MAX];
                snprintf(full_path, FILENAME_MAX, "%s/%s", filepath, entry->d_name);
                *current = create_tree_node(full_path);
                if (*current == NULL) {
                    closedir(dir);
                    free_tree(node);
                    return NULL;
                }
                current = &((*current)->next_file);
            }
        }
        closedir(dir);
    }

    return node;
}

/*
 * Write a tree of archive nodes to an archive file.
 * This function is called recursively to process directories.
 */
void write_tree_to_archive(FILE *archive, arch_tree_node *node) {
    if (!node) {
        return;
    }

    // Write the node to the archive
    fwrite(node, sizeof(arch_tree_node), 1, archive);

    // If the node is a file, write its metadata and content
    if (!node->is_directory) {
        struct stat file_stat;
        if (lstat(node->name, &file_stat) == -1) {
            perror("Failed to get file metadata");
            return;
        }

        file_metadata metadata = {
            .mode = file_stat.st_mode,
            .uid = file_stat.st_uid,
            .gid = file_stat.st_gid,
            .mtime = file_stat.st_mtime
        };
        fwrite(&metadata, sizeof(file_metadata), 1, archive);

        FILE *file = fopen(node->name, "rb");
        if (!file) {
            perror("Failed to open file for reading");
            return;
        }

        buffered_read_write(file, archive, node->size, WRITE_BUFFER_SIZE);
        fclose(file);
    }

    // Process the directory contents or the next file in the directory
    if (node->is_directory) {
        write_tree_to_archive(archive, node->dir_contents);
    }
    write_tree_to_archive(archive, node->next_file);
}

/*
 * Create a .kar archive from a list of files and directories.
 */
int create_archive(char *archive_name, int num_files, char *files_to_add[num_files]) {
    // Open the archive file for writing
    FILE *archive = fopen(archive_name, "wb");
    if (!archive) {
        perror("Failed to open archive file");
        return 1;
    }

    // Initialize the root of the archive tree
    kar_tree root;
    root.root = NULL;
    arch_tree_node **current = &root.root;

    // Create nodes for each file or directory and add them to the archive tree
    for (int i = 0; i < num_files; i++) {
        *current = create_tree_node(files_to_add[i]);
        if (!(*current)) {
            fclose(archive);
            free_tree(root.root);
            return 1;
        }
        current = &((*current)->next_file);
    }

    // Write the archive tree to the archive file
    write_tree_to_archive(archive, root.root);
    free_tree(root.root);
    fclose(archive);
    return 0;
}
