#!/bin/bash

# Directory containing test folders
TEST_DIR="testing/tests"

# Ensure we're in the right directory by checking for the test directory
if [ ! -d "$TEST_DIR" ]; then
    echo "Error: $TEST_DIR directory not found!"
    echo "Please run this script from the project root directory."
    exit 1
fi

# Function to create a test file with basic content
create_test_file() {
    local dir_name=$1
    local file_path="$TEST_DIR/$dir_name/$dir_name.cpp"
    
    # Create directory if it doesn't exist
    mkdir -p "$TEST_DIR/$dir_name"
    
    # Only create the file if it doesn't already exist
    if [ ! -f "$file_path" ]; then
        echo "Creating test file: $file_path"
        
        # Create the file with a basic test template
        cat > "$file_path" << EOL
#include <gtest/gtest.h>
#include <cmath>
#include "test_utils.hpp"

// Test suite for ${dir_name}
class ${dir_name^}Test : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code
    }

    void TearDown() override {
        // Cleanup code
    }
};

TEST_F(${dir_name^}Test, BasicTest) {
    // TODO: Implement test
    EXPECT_TRUE(true);
}
EOL
    else
        echo "File already exists: $file_path"
    fi
}

# Find all directories in the test directory and create corresponding test files
for dir in "$TEST_DIR"/*/ ; do
    if [ -d "$dir" ]; then
        # Extract just the directory name
        dir_name=$(basename "$dir")
        create_test_file "$dir_name"
    fi
done

echo "Test file creation complete!"