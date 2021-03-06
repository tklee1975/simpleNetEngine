# Clean up 

#cmake -B ./build/ ./

VCPKG_ROOT=/Users/kenlee/workspace/cpp/vcpkg

CMAKE_SCRIPT=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake 

cmake -B ./build/ -D CMAKE_TOOLCHAIN_FILE=$CMAKE_SCRIPT ./
