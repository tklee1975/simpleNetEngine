cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME net_engine_test)
message("==== ${PROJECT_NAME} ====")
project(${PROJECT_NAME})

## Fetch the sources and add the the library
file(GLOB_RECURSE search_src_files 
	"src/*.cpp"
	"src/*.h"
)
## message("search_src_files = ${search_src_files}")
foreach(FILE ${search_src_files}) 
	get_filename_component(PARENT_DIR "${FILE}" PATH)    
	file(RELATIVE_PATH PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${PARENT_DIR})
	string(REPLACE "/" "\\" GROUP "${PARENT_DIR}")
	set(GROUP "${GROUP}")
	source_group("${GROUP}" FILES "${FILE}")
endforeach()

# message("CoreLibTest: search_src_files = ${search_src_files}")

add_executable(${PROJECT_NAME} ${search_src_files})
#add_executable(${PROJECT_NAME} src/TestCoreLib.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE CoreLib)
target_link_libraries(${PROJECT_NAME} PRIVATE NetEngine)