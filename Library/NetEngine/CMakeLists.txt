# Setting 
cmake_minimum_required(VERSION 3.10)


set(PROJECT_NAME NetEngine) 
message("=== ${PROJECT_NAME} ===")
project(${PROJECT_NAME})

# Define Source 

set(CORE_LIB_NAME       "CoreLib")
set(CORE_LIB_PATH       "Library/CoreLib")


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


add_library(${PROJECT_NAME} ${search_src_files})


# Define the Target 
target_include_directories(${PROJECT_NAME} PUBLIC ./src/)
#set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER simpleNet)

# Linked Library  
target_link_libraries(${PROJECT_NAME} PRIVATE ${CORE_LIB_NAME})
