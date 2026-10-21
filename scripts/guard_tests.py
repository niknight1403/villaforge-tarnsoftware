#!/usr/bin/env python3
"""
Pre-Verification Guard: Ensures that test files exist in the workspace before any Q-Gate submission.
"""
import os
import sys
from pathlib import Path

def check_tests_exist(workspace_dir: str = ".") -> bool:
    workspace = Path(workspace_dir)
    # Search for test files or test source files
    test_patterns = ["*test*.cpp", "*test*.py", "*test*.h", "test_*.py", "*.test.js", "*test*"]
    found_tests = []
    
    for pattern in test_patterns:
        for p in workspace.rglob(pattern):
            if p.is_file() and "build" not in p.parts and ".git" not in p.parts:
                found_tests.append(p)
                
    if not found_tests:
        print("[ERROR] Q-Gate Guard: No test files found in workspace! Submission blocked.")
        return False
        
    print(f"[OK] Q-Gate Guard: Found {len(found_tests)} test file(s).")
    return True

if __name__ == "__main__":
    success = check_tests_exist()
    if not success:
        sys.exit(1)
    sys.exit(0)
