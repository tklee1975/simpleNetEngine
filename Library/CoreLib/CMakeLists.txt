# Setting 
cmake_minimum_required(VERSION 3.10)
project(SimpleNetCoreLib)

# Debug message 
# set(ABC "Hey")
# message("Hello World ${ABC}")
message("Core Library")

# Define Source 

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

add_library(CoreLib ${search_src_files})


# Define the Target 
target_include_directories(CoreLib PUBLIC ./src/)
target_link_libraries(CoreLib PUBLIC fmt::fmt)
