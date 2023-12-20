#!/usr/bin/env bash

# Compile the hello.c source file with warning flags, debugging information, and produce an executable named "hello"
gcc -Wall -g -o hello hello.c

# Compile the count.c source file with warning flags, debugging information, and produce an executable named "count"
gcc -Wall -g -o count count.c

# Compile the echo_arg.c source file with warning flags, debugging information, and produce an executable named "echo_arg"
gcc -Wall -g -o echo_arg echo_arg.c

# Compile the echo_stdin.c source file with warning flags, debugging information, and produce an executable named "echo_stdin"
gcc -Wall -g -o echo_stdin echo_stdin.c
