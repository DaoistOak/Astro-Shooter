#!/usr/bin/env bash
set -e

# Create necessary directories
mkdir -p build/part

# Compile object files

g++ -c objects/objects.cpp -o build/part/objects.o

g++ -c menu/menu.cpp -o build/part/menu.o

# Link and build the final executable

g++ main.cpp build/part/objects.o build/part/menu.o -lncurses -o build/hello

echo "Build complete. Run with ./build/hello" 