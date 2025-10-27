#!/bin/bash

# Build script for Linux and macOS
# Usage: bash build.sh [clean]

set -e

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"

echo "==============================================="
echo "Building normalize project with CMake"
echo "==============================================="

# Check if clean is requested
if [ "$1" == "clean" ]; then
    echo "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
    echo "Done!"
    exit 0
fi

# Create build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure with CMake
echo "Configuring with CMake..."
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build
echo "Building..."
cmake --build . --config Release

echo ""
echo "==============================================="
echo "✓ Build successful!"
echo "==============================================="
echo ""
echo "Executable: $BUILD_DIR/normalize"
echo ""
echo "Usage examples:"
echo "  $BUILD_DIR/normalize ../tests/sample_data.csv baseline"
echo "  $BUILD_DIR/normalize ../tests/data_1000x10.csv quake"
echo "  $BUILD_DIR/normalize ../tests/data_1000x100.csv sse"
echo ""
