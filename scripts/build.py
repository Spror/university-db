#!/usr/bin/env python3


import os
import subprocess

def run_cmake_build(build_dir):
    # Make sure the build directory exists
    if not os.path.exists(build_dir):
        os.makedirs(build_dir)

    # Change directory to the build directory
    os.chdir(build_dir)

    # Run CMake to configure the project
    cmake_configure_command = ['cmake', '..']
    subprocess.run(cmake_configure_command, check=True)

    # Run the build command (e.g., make, ninja, etc.)
    build_command = ['cmake', '--build', '.']
    subprocess.run(build_command, check=True)

if __name__ == "__main__":
    build_dir = "../build"  # Change this to your desired build directory
    run_cmake_build(build_dir)