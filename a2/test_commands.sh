#!/bin/bash

# Function to print the output of a command
run_command() {
    echo "Running: $1"
    eval $1
    echo "---------------------"
}

echo "=== Testing --help Command ==="
run_command "./kar --help"

echo "=== Testing Error Handling ==="
# No arguments
run_command "./kar"

# Invalid command
run_command "./kar invalid_command"

# Missing arguments for create
run_command "./kar create"

# Missing arguments for extract
run_command "./kar extract"

# Missing files for create
run_command "./kar create archive.kar"

# Missing archive for extract
run_command "./kar extract archive.kar"

echo "Tests Completed"
