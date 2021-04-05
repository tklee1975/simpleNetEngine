cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME DemoApp2)
message("==== ${PROJECT_NAME} ====")
project(${PROJECT_NAME})

set(APP_NAME      "app2")

set(CORE_LIB_NAME       "CoreLib")
set(NET_ENGINE_NAME     "NetEngine")
set(IMGUI_HELPER_NAME   "ImguiHelper")



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

add_executable(${APP_NAME} ${search_src_files})

## Setup Compile and Link 
target_precompile_headers(${APP_NAME} PRIVATE src/pch.h)

target_link_libraries(${APP_NAME} PRIVATE ${CORE_LIB_NAME})
target_link_libraries(${APP_NAME} PRIVATE ${NET_ENGINE_NAME})
target_link_libraries(${APP_NAME} PRIVATE ${IMGUI_HELPER_NAME})
target_link_libraries(${APP_NAME} PRIVATE fmt::fmt)
target_link_libraries(${APP_NAME} PRIVATE EASTL)
target_link_libraries(${APP_NAME} PRIVATE EABase)
target_link_libraries(${APP_NAME} PRIVATE imgui::imgui)

