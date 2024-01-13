/*
** This file is part of the CSC209 -- Fall 2023 Assignment 2
**
** All of the files in this directory and all subdirectories are:
** Copyright (c) 2023 Demetres Kostas
*/

#ifndef KAR_TREE_H_
#define KAR_TREE_H_

#include <stdio.h>

#define WRITE_BUFFER_SIZE 4096
// Thanks to Jordan Malek for the tip on the following number
// You can use this for filenames and for path + filename,
// Just *make sure the headers in the archive only include the filename*
// usually, there would be 4096 possible characters in a path
#undef FILENAME_MAX
#define FILENAME_MAX 255

typedef struct arch_tree_node {
    char name[FILENAME_MAX];
    unsigned int size;
    unsigned char is_directory;
    struct arch_tree_node *next_file;
    struct arch_tree_node *dir_contents;
} arch_tree_node;

typedef struct kar_tree {
    arch_tree_node *root;
} kar_tree;

// In kar_tree.c
void free_tree(arch_tree_node *root);
void only_filename(char* filepath);
void valid_path(char path_buffer[], char *directory, char *filename);
int buffered_read_write(FILE *input, FILE *output, size_t read_remaining, size_t buffer_size);

/*
 * We often create .h files for everything, but for this project we're
 * keeping it simple.
*/
// In archive.c
int create_archive(char *archive_name, int num_files, char *files_to_add[num_files]);

// In extract.c
int extract_archive(char *archive_name);

#endif /* KAR_TREE_H_ */
