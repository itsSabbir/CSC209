#!/usr/bin/env bash

# Run the echo_arg program with the argument "csc209" and redirect its output to a file named echo_out.txt
./echo_arg csc209 > echo_out.txt

# Redirect the content of the file echo_stdin.c as input to the echo_stdin program
./echo_stdin < echo_stdin.c

# Use the count program to count the number of digits in numbers from 0 to 209, then use wc -m to count the total number of characters (digits) output by count
./count 209 | wc -m 

# List files in the current directory in descending order of size and then use echo_stdin to print the name of the largest file (which is the first in the list)
ls -S | ./echo_stdin
