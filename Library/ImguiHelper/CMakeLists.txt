# Setting 
cmake_minimum_required(VERSION 3.10)
project(ImguiHelperLibrary)

# Debug message 
# set(ABC "Hey")
# message("Hello World ${ABC}")
message("Imgui Helper Library")

find_package(fmt CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)


# Define Source 
set(CORE_LIB_NAME       "CoreLib")
set(CORE_LIB_PATH       "Library/CoreLib")


set(LIB_NAME       "ImguiHelper")
#set(LIB_PATH       "Library/ImguiHelper")


## Fetch the sources and add the the library
file(GLOB_RECURSE search_src_files 
	"*.cpp"
	"*.h"
)
## message("search_src_files = ${search_src_files}")
foreach(FILE ${search_src_files}) 
	get_filename_component(PARENT_DIR "${FILE}" PATH)    
	file(RELATIVE_PATH PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${PARENT_DIR})
	string(REPLACE "/" "\\" GROUP "${PARENT_DIR}")
	set(GROUP "${GROUP}")
	source_group("${GROUP}" FILES "${FILE}")
endforeach()

add_library(${LIB_NAME} ${search_src_files})


# Define the Target 
target_include_directories(${LIB_NAME} PUBLIC ./)
target_link_libraries(${LIB_NAME} PRIVATE fmt::fmt)
target_link_libraries(${LIB_NAME} PRIVATE imgui::imgui)
target_link_libraries(${LIB_NAME} PRIVATE ${CORE_LIB_NAME})