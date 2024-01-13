#!/bin/bash

# Test Script for 'kar' Program

# Function to create a test directory structure
create_test_directory() {
    mkdir -p D1/D2
    echo "File: 1" > f1.txt
    echo "File: 2" > f2.txt
    echo "File: 3" > D1/f3.txt
    echo "File: 4" > D1/D2/f4.txt
}

# Function to clean up test files and directories
clean_up() {
    rm -rf D1 f1.txt f2.txt archive.kar extracted
}

# Creating Test Directory Structure
echo "Creating test directory structure..."
create_test_directory

# Testing 'create' command
echo "Testing 'kar create'..."
./kar create archive.kar f1.txt f2.txt D1/
if [ $? -eq 0 ]; then
    echo "Archive created successfully."
else
    echo "Failed to create archive."
    exit 1
fi

# Testing 'extract' command
echo "Testing 'kar extract'..."
mkdir extracted
cd extracted
../kar extract ../archive.kar
if [ $? -eq 0 ]; then
    echo "Archive extracted successfully."
else
    echo "Failed to extract archive."
    exit 1
fi

# Verifying extracted files
echo "Verifying extracted files..."
diff ../f1.txt f1.txt
diff ../f2.txt f2.txt
diff ../D1/f3.txt D1/f3.txt
diff ../D1/D2/f4.txt D1/D2/f4.txt

# Clean up
echo "Cleaning up..."
cd ..
clean_up

echo "All tests passed successfully!"
