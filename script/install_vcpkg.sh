#!/bin/sh 
# 
# This script help to install Vcpkg and corresponding packages 
# 

## ken: TODO: determine the vcpkg already install or not 
VCPKG_DIR=./externals/vcpkg

if [ ! -d "$VCPKG_DIR" ]; then
    git clone https://github.com/microsoft/vcpkg.git $VCPKG_DIR
fi 
# Mac
if [ "$(uname)" == "Darwin" ]; then
    brew list pkg-config > /dev/null || brew install pkg-config
    brew list cmake > /dev/null || brew install cmake
fi

VCPKG_CMD=$VCPKG_DIR/vcpkg

if [ ! -f "$VCPKG_CMD" ]; then
    echo "VCPKG CMD NOT FOUND"
    ${VCPKG_DIR}/bootstrap-vcpkg.sh
fi 
#

$VCPKG_CMD install fmt --recurse
$VCPKG_CMD install eastl --recurse

## Imgui??
$VCPKG_CMD install "imgui[sdl2-binding]" --recurse
$VCPKG_CMD install "imgui[opengl3-glew-binding]" --recurse

