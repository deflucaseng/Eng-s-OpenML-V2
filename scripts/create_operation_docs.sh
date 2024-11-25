#!/bin/bash

# Directory containing operation folders
OPERATIONS_DIR="src/operations"

# Ensure we're in the right directory by checking for the operations directory
if [ ! -d "$OPERATIONS_DIR" ]; then
    echo "Error: $OPERATIONS_DIR directory not found!"
    echo "Please run this script from the project root directory."
    exit 1
fi

# Function to create a markdown file with basic content
create_markdown_file() {
    local dir_name=$1
    local file_path="$OPERATIONS_DIR/$dir_name/$dir_name.md"
    
    # Only create the file if it doesn't already exist
    if [ ! -f "$file_path" ]; then
        echo "Creating documentation file: $file_path"
        
        # Create the file with a basic documentation template
        cat > "$file_path" << EOL
# ${dir_name}

## Description
Brief description of the ${dir_name} operation.

## Implementation Details
Explain how the operation is implemented.

## Complexity Analysis
- Time Complexity: O(?)
- Space Complexity: O(?)

## Usage Example
\`\`\`cpp
// Add usage example here
\`\`\`

## Edge Cases and Limitations
- List any edge cases
- Note any limitations

## References
- Add relevant references or citations
EOL
    else
        echo "File already exists: $file_path"
    fi
}

# Find all directories in the operations directory and create corresponding markdown files
for dir in "$OPERATIONS_DIR"/*/ ; do
    if [ -d "$dir" ]; then
        # Extract just the directory name
        dir_name=$(basename "$dir")
        create_markdown_file "$dir_name"
    fi
done

echo "Documentation file creation complete!"