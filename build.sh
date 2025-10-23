#!/bin/bash

echo "Building Webcam ASCII..."

#opencv installed ?
if ! pkg-config --exists opencv4 && ! pkg-config --exists opencv; then
    echo "Error: OpenCV not found!"
    echo ""
    echo "Please install OpenCV first:"
    echo "  Ubuntu/Debian: sudo apt install libopencv-dev"
    echo "  Fedora:        sudo dnf install opencv-devel"
    echo "  macOS:         brew install opencv"
    echo "  Arch:          sudo pacman -S opencv"
    exit 1
fi

#create build dir
mkdir -p build
cd build

#run cmake
echo "⚙️  Configuring with CMake..."
cmake .. || { echo "CMake configuration failed"; exit 1; }

#build
echo "🔧 Compiling..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 2) || { echo "Build failed"; exit 1; }

echo ""
echo "Build successful!"
echo ""
echo "Run with: ./build/webcam-ascii"
echo "Or install system-wide: cd build && sudo make install"
echo ""
echo "Try these commands:"
echo "  ./build/webcam-ascii --help"
echo "  ./build/webcam-ascii -p detailed --color fire"
echo ""