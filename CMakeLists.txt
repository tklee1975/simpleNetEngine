cmake_minimum_required(VERSION 3.10)

project(SimpleNet)

## Variable Setup 
set(DEMO1_BIN_NAME      "app1")
set(DEMO1_PATH          "_DemoApp1")

set(CORE_LIB_NAME       "CoreLib")
set(CORE_LIB_PATH       "Library/CoreLib")

set(NET_ENGINE_NAME     "NetEngine")
set(NET_ENGINE_PATH     "Library/NetEngine")

#find_package(fmt CONFIG REQUIRED)



## Define the library and main source 
add_subdirectory(${CORE_LIB_PATH})
add_subdirectory(${NET_ENGINE_PATH})

add_executable(app1 ${DEMO1_PATH}/Main.cpp ${DEMO1_PATH}/pch.h)


## Setup Compile and Link 
target_precompile_headers(app1 PRIVATE ${DEMO1_PATH}/pch.h)

target_link_libraries(app1 PRIVATE ${CORE_LIB_NAME})
target_link_libraries(app1 PRIVATE ${NET_ENGINE_NAME})
#target_link_libraries(app1 PRIVATE fmt::fmt-header-only)
