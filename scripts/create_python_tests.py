#!/usr/bin/env python3
import os
import glob

def create_python_test_files():
    # Base paths
    cpp_tests_path = "testing/tests"
    python_tests_path = "testing/pythontesting"
    
    # Get all .cpp test files
    cpp_files = glob.glob(f"{cpp_tests_path}/**/*.cpp", recursive=True)
    
    # Create pythontesting directory if it doesn't exist
    if not os.path.exists(python_tests_path):
        os.makedirs(python_tests_path)
        print(f"Created directory: {python_tests_path}")
    
    for cpp_file in cpp_files:
        # Get the relative path from cpp tests directory
        rel_path = os.path.relpath(os.path.dirname(cpp_file), cpp_tests_path)
        
        # Create corresponding directory in pythontesting
        python_dir = os.path.join(python_tests_path, rel_path)
        if not os.path.exists(python_dir):
            os.makedirs(python_dir)
            print(f"Created directory: {python_dir}")
        
        # Get the base name without extension
        base_name = os.path.splitext(os.path.basename(cpp_file))[0]
        
        # Create Python test file
        python_file = os.path.join(python_dir, f"{base_name}.py")
        if not os.path.exists(python_file):
            with open(python_file, 'w') as f:
                f.write(f"""import unittest
import numpy as np

class Test{base_name.title()}(unittest.TestCase):
    def setUp(self):
        # Setup code here
        pass
        
    def test_{base_name}_basic(self):
        # Basic test case
        pass
        
    def test_{base_name}_edge_cases(self):
        # Edge cases test
        pass
        
    def test_{base_name}_random_input(self):
        # Random input test
        pass
        
if __name__ == '__main__':
    unittest.main()
""")
            print(f"Created {python_file}")

if __name__ == "__main__":
    create_python_test_files()