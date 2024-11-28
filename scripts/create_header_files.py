#!/usr/bin/env python3
import os
import glob

def ensure_directory_exists(dir_path):
    """Create directory if it doesn't exist"""
    if not os.path.exists(dir_path):
        os.makedirs(dir_path)
        print(f"Created directory: {dir_path}")

def create_header_files():
    # Base paths
    operations_path = "src/operations"
    include_path = "src/include"
    
    # Get all subdirectories that contain .md files
    md_files = glob.glob(f"{operations_path}/**/*.md", recursive=True)
    
    for md_file in md_files:
        # Get the relative path from operations directory
        rel_path = os.path.relpath(os.path.dirname(md_file), operations_path)
        
        # Create corresponding directory structure in include
        include_dir = os.path.join(include_path, rel_path)
        ensure_directory_exists(include_dir)
        
        # Get the base name without extension
        base_name = os.path.splitext(os.path.basename(md_file))[0]
        
        # Create header file
        header_file = os.path.join(include_dir, f"{base_name}.h")
        if not os.path.exists(header_file):
            with open(header_file, 'w') as f:
                guard_name = f"{rel_path.replace('/', '_')}_{base_name}_h".upper()
                f.write(f"""#ifndef {guard_name}
#define {guard_name}

#ifdef __cplusplus
extern "C" {{
#endif

// Function declarations for {base_name}

#ifdef __cplusplus
}}
#endif

#endif // {guard_name}
""")
            print(f"Created {header_file}")

if __name__ == "__main__":
    create_header_files()