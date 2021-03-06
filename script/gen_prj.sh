# Clean up 

#cmake -B ./build/ ./

VCPKG_ROOT=`echo $VCPKG_ROOT`

echo "Your VCPCK_ROOT=$VCPKG_ROOT"
CMAKE_SCRIPT=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake 

cmake -B ./build/ \
    -D CMAKE_TOOLCHAIN_FILE=$CMAKE_SCRIPT \
    ./
