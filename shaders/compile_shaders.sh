#!/bin/bash

echo "Compiling shaders..."

# Compile vertex shader
echo "Compiling vertex shader..."
glslangValidator -V -o vert.spv vert.vert
if [ $? -eq 0 ]; then
    echo "✓ Vertex shader compiled successfully"
else
    echo "✗ Failed to compile vertex shader"
    exit 1
fi

# Compile fragment shader
echo "Compiling fragment shader..."
glslangValidator -V -o frag.spv frag.frag
if [ $? -eq 0 ]; then
    echo "✓ Fragment shader compiled successfully"
else
    echo "✗ Failed to compile fragment shader"
    exit 1
fi

echo "All shaders compiled successfully!" 