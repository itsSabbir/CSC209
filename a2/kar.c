/*
** This file is part of the CSC209 -- Fall 2023 Assignment 2
**
** All of the files in this directory and all subdirectories are:
** Copyright (c) 2023 Demetres Kostas
**
** This file is kar.c
**
** This file serves as the entry point for the kar utility, handling command-line
** arguments and directing the program to perform archiving or extraction as specified.
*/

#include "kar_tree.h"
#include <stdio.h>
#include <string.h>

/*
 * print_help: Prints out the usage information for the kar utility.
 * This function is called when the user provides incorrect input or
 * requests help with the --help command line option.
 */
void print_help() {
    printf("Usage: kar [COMMAND] [ARCHIVE]\n");
    printf("Creates or extracts files from the kar-formatted ARCHIVE.\n");
    printf("\n");
    printf("COMMAND may be one of the following:\n");
    printf("    create [ARCHIVE] [FILES/DIRS]\n");
    printf("    extract [ARCHIVE]\n");
    printf("    --help\n");
    printf("\n");
    printf("create:\n");
    printf("    Creates an archive with the name specified in [ARCHIVE] consisting of the listed files and dirs. Paths to the files are not preserved, but the structure inside the archive will be.\n");
    printf("\n");
    printf("extract:\n");
    printf("    Extracts the files from the [ARCHIVE] file into the current directory.\n");
    printf("\n");
    printf("--help:\n");
    printf("    Prints this message and exits.\n");
}

/*
 * main: The main function, serving as the entry point of the program.
 * It parses command-line arguments and calls the appropriate functions
 * for creating or extracting archives, or for printing help information.
 */
int main(int argc, char *argv[]) {
    // Ensure at least one command-line argument is provided
    if (argc < 2) {
        print_help();
        return 1;
    }

    // Handle the --help command
    if (strcmp(argv[1], "--help") == 0) {
        print_help();
        return 0;
    }
    // Handle the create command
    else if (strcmp(argv[1], "create") == 0) {
        // Ensure sufficient arguments are provided for the create command
        if (argc < 4) {
            fprintf(stderr, "Error: Missing arguments for create command.\n");
            return 1;
        }
        // Call the function to create an archive
        return create_archive(argv[2], argc - 3, &argv[3]);
    }
    // Handle the extract command
    else if (strcmp(argv[1], "extract") == 0) {
        // Ensure the correct number of arguments are provided for the extract command
        if (argc != 3) {
            fprintf(stderr, "Error: Incorrect arguments for extract command.\n");
            return 1;
        }
        // Call the function to extract an archive
        return extract_archive(argv[2]);
    }
    // Handle unrecognized commands
    else {
        fprintf(stderr, "Error: '%s' is not a recognized command.\n", argv[1]);
        print_help();
        return 1;
    }
}
