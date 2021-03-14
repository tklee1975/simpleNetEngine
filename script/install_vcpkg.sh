#!/bin/sh 

## ken: TODO: determine the vcpkg already install or not 

git clone https://github.com/microsoft/vcpkg.git externals/vcpkg

# Mac
if [ "$(uname)" == "Darwin" ]; then
    brew install pkg-config
    brew install cmake
fi

sh externals/vcpkg/bootstrap-vcpkg.sh

externals/vcpkg/vcpkg install fmt --recurse
externals/vcpkg/vcpkg install eastl --recurse

## Imgui??
externals/vcpkg/vcpkg install "imgui[sdl2-binding]" --recurse
externals/vcpkg/vcpkg install "imgui[opengl3-glew-binding]" --recurse
