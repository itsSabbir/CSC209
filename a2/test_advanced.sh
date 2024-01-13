#!/bin/bash

# Test Script for 'kar' Program

# Function to create a test directory structure
create_test_directory() {
    mkdir -p D1/D2 D_empty D2F5/D1/D2
    echo "File: 1" > f1.txt
    echo "File: 2" > f2.txt
    echo "File: 3" > D1/f3.txt
    echo "File: 4" > D1/D2/f4.txt
    ln -s f1.txt symlink_to_f1.txt
}

# Function to create a specific directory tree
create_specific_directory_tree() {
    echo "Test file 0" > f0.txt
    echo "Test file 1" > D2F5/f1.txt
    echo "Test file 2" > D2F5/D1/f2.txt
    echo "Test file 3" > D2F5/D1/D2/f3.txt
    echo "Test file 4" > D2F5/D1/D2/f4.txt
    echo "Test file 5" > D2F5/D1/f5.txt
}

# Function to create a large file (100 MB)
create_large_file() {
    dd if=/dev/urandom of=large_file.txt bs=1M count=100
}

# Function to clean up test files and directories
clean_up() {
    rm -rf D1 D_empty f1.txt f2.txt archive.kar extracted symlink_to_f1.txt large_file.txt D2F5 f0.txt
}

# Function to verify extracted files
verify_extracted_files() {
    diff ../f1.txt f1.txt
    diff ../f2.txt f2.txt
    diff ../D1/f3.txt D1/f3.txt
    diff ../D1/D2/f4.txt D1/D2/f4.txt
    diff -r ../D_empty D_empty
    diff ../large_file.txt large_file.txt
    diff -r ../symlink_to_f1.txt symlink_to_f1.txt
}

# Function to verify the specific directory tree
verify_specific_directory_tree() {
    diff ../f0.txt f0.txt
    diff ../D2F5/f1.txt D2F5/f1.txt
    diff ../D2F5/D1/f2.txt D2F5/D1/f2.txt
    diff ../D2F5/D1/D2/f3.txt D2F5/D1/D2/f3.txt
    diff ../D2F5/D1/D2/f4.txt D2F5/D1/D2/f4.txt
    diff ../D2F5/D1/f5.txt D2F5/D1/f5.txt
}

# Creating Test Directory Structure
echo "Creating test directory structure..."
create_test_directory
create_large_file
create_specific_directory_tree

# Testing 'kar create' for general structure
echo "Testing 'kar create' for general structure..."
./kar create archive.kar f1.txt f2.txt D1/ D_empty/ symlink_to_f1.txt large_file.txt
if [ $? -eq 0 ]; then
    echo "Archive created successfully."
else
    echo "Failed to create archive."
    exit 1
fi

# Testing 'kar extract' for general structure
echo "Testing 'kar extract' for general structure..."
mkdir extracted
cd extracted
../kar extract ../archive.kar
if [ $? -eq 0 ]; then
    echo "Archive extracted successfully."
else
    echo "Failed to extract archive."
    exit 1
fi

# Verifying extracted files for general structure
echo "Verifying extracted files for general structure..."
verify_extracted_files

# Clean up general structure
echo "Cleaning up general structure..."
cd ..
clean_up

echo "All tests for general structure passed successfully!"

# Testing 'kar create' for specific directory tree
echo "Testing 'kar create' for specific directory tree..."
./kar create archive.kar f0.txt D2F5/
if [ $? -eq 0 ]; then
    echo "Archive created successfully."
else
    echo "Failed to create archive."
    exit 1
fi

# Testing 'kar extract' for specific directory tree
echo "Testing 'kar extract' for specific directory tree..."
mkdir extracted
cd extracted
../kar extract ../archive.kar
if [ $? -eq 0 ]; then
    echo "Archive extracted successfully."
else
    echo "Failed to extract archive."
    exit 1
fi

# Verifying extracted files for specific directory tree
echo "Verifying extracted files for specific directory tree..."
verify_specific_directory_tree

# Clean up specific directory tree
echo "Cleaning up specific directory tree..."
cd ..
clean_up

echo "All tests for specific directory tree passed successfully!"
