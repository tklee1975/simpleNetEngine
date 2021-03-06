cmake_minimum_required(VERSION 3.10)

project(SimpleNet)

# tell CMake to use CTest extension
enable_testing()

## Variable Setup 
set(DEMO1_BIN_NAME      "app1")
set(DEMO1_PATH          "_DemoApp1")

set(CORE_LIB_NAME       "CoreLib")
set(CORE_LIB_PATH       "Library/CoreLib")

set(NET_ENGINE_NAME     "NetEngine")
set(NET_ENGINE_PATH     "Library/NetEngine")

set(UNIT_TEST_PATH      "UnitTest")

#find_package(fmt CONFIG REQUIRED)

## Vcpkg 
find_package(fmt CONFIG REQUIRED)
find_package(eastl CONFIG REQUIRED)
find_package(eabase CONFIG REQUIRED)

## Define the library and main source 
add_subdirectory(${CORE_LIB_PATH})
add_subdirectory(${NET_ENGINE_PATH})

## Define 
add_executable(app1 ${DEMO1_PATH}/Main.cpp ${DEMO1_PATH}/pch.h)


## Setup Compile and Link 
target_precompile_headers(app1 PRIVATE ${DEMO1_PATH}/pch.h)

target_link_libraries(app1 PRIVATE ${CORE_LIB_NAME})
target_link_libraries(app1 PRIVATE ${NET_ENGINE_NAME})
target_link_libraries(app1 PRIVATE fmt::fmt)

# For Testing 
add_executable(test_main ${UNIT_TEST_PATH}/TestMain.cpp)
target_link_libraries(test_main PRIVATE ${CORE_LIB_NAME})
target_link_libraries(test_main PRIVATE ${NET_ENGINE_NAME})
target_link_libraries(test_main PRIVATE fmt::fmt)
target_link_libraries(test_main PRIVATE EASTL)

# now register the executable with CTest
#add_test(NAME my_test COMMAND my_test)


