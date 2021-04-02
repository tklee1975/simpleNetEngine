cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME core_test)
message("==== ${PROJECT_NAME} ====")
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} TestCoreLib.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE CoreLib)