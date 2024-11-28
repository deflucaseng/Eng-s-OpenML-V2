#!/usr/bin/env python3
import os
import glob

def create_operation_files():
    # Base path for operations
    operations_path = "src/operations"
    
    # Get all subdirectories that contain .md files
    md_files = glob.glob(f"{operations_path}/**/*.md", recursive=True)
    
    for md_file in md_files:
        # Get the directory containing the .md file
        dir_path = os.path.dirname(md_file)
        # Get the base name without extension
        base_name = os.path.splitext(os.path.basename(md_file))[0]
        
        # Create .c file
        c_file_path = os.path.join(dir_path, f"{base_name}.c")
        if not os.path.exists(c_file_path):
            with open(c_file_path, 'w') as f:
                f.write(f"""#include "{base_name}.h"

// Implementation for {base_name}
""")
            print(f"Created {c_file_path}")
            
        # Create .cl file
        cl_file_path = os.path.join(dir_path, f"{base_name}.cl")
        if not os.path.exists(cl_file_path):
            with open(cl_file_path, 'w') as f:
                f.write(f"""// OpenCL kernel for {base_name}
__kernel void {base_name}_kernel(
    // Add kernel parameters here
)
{{
    // Kernel implementation
}}
""")
            print(f"Created {cl_file_path}")

if __name__ == "__main__":
    create_operation_files()