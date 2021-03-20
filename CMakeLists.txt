cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE "./externals/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
project(SimpleNet)

set(CMAKE_CXX_STANDARD 17)

# tell CMake to use CTest extension
enable_testing()


## Variable Setup 
set(DEMO1_BIN_NAME      "app1")
set(DEMO1_PATH          "_DemoApp1")

set(CORE_LIB_NAME       "CoreLib")
set(CORE_LIB_PATH       "Library/CoreLib")

set(NET_ENGINE_NAME     "NetEngine")
set(NET_ENGINE_PATH     "Library/NetEngine")

set(IMGUI_HELPER_NAME   "ImguiHelper")
set(IMGUI_HELPER_PATH   "Library/ImguiHelper")

set(UNIT_TEST_PATH      "UnitTest")

#find_package(fmt CONFIG REQUIRED)

## Vcpkg 
find_package(fmt CONFIG REQUIRED)
find_package(EASTL CONFIG REQUIRED)
find_package(EABase CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

## Define the library and main source 
add_subdirectory(${CORE_LIB_PATH})
add_subdirectory(${NET_ENGINE_PATH})
add_subdirectory(${IMGUI_HELPER_PATH})

## Define 
add_executable(app1
                ${DEMO1_PATH}/Main.cpp
                ${DEMO1_PATH}/pch.h
                ${DEMO1_PATH}/SimpleSocketServer.cpp
                ${DEMO1_PATH}/SimpleSocketServer.h
                ${DEMO1_PATH}/SimpleNetAppSession.h                
                ${DEMO1_PATH}/SimpleNetAppSession.cpp
                ${DEMO1_PATH}/SimpleNetApp.h
                ${DEMO1_PATH}/SimpleNetApp.cpp
            )


## Setup Compile and Link 
target_precompile_headers(app1 PRIVATE ${DEMO1_PATH}/pch.h)

target_link_libraries(app1 PRIVATE ${CORE_LIB_NAME})
target_link_libraries(app1 PRIVATE ${NET_ENGINE_NAME})
target_link_libraries(app1 PRIVATE ${IMGUI_HELPER_NAME})
target_link_libraries(app1 PRIVATE fmt::fmt)
target_link_libraries(app1 PRIVATE EASTL)
target_link_libraries(app1 PRIVATE EABase)
target_link_libraries(app1 PRIVATE imgui::imgui)


# For Testing 
add_executable(test_main
                    ${UNIT_TEST_PATH}/TestMain.cpp
                    ${DEMO1_PATH}/SimpleNetAppSession.h                
                    ${DEMO1_PATH}/SimpleNetAppSession.cpp
                    ${DEMO1_PATH}/SimpleNetApp.h
                    ${DEMO1_PATH}/SimpleNetApp.cpp  
                    ${UNIT_TEST_PATH}/TestNetSession.cpp
                    ${UNIT_TEST_PATH}/TestNetSession.h
            )
target_link_libraries(test_main PRIVATE ${CORE_LIB_NAME})
target_link_libraries(test_main PRIVATE ${NET_ENGINE_NAME})
target_link_libraries(test_main PRIVATE fmt::fmt)
target_link_libraries(test_main PRIVATE EASTL)
target_link_libraries(test_main PRIVATE EABase)
target_link_libraries(test_main PRIVATE imgui::imgui)
target_link_libraries(test_main PRIVATE ${IMGUI_HELPER_NAME})

# For Testing 
add_executable(test_gui
                ${UNIT_TEST_PATH}/TestGuiMain.cpp
                ${UNIT_TEST_PATH}/TestGuiApp.h
                ${UNIT_TEST_PATH}/TestGuiApp.cpp
                ${DEMO1_PATH}/SimpleNetAppSession.h                
                ${DEMO1_PATH}/SimpleNetAppSession.cpp
                ${DEMO1_PATH}/SimpleNetApp.h
                ${DEMO1_PATH}/SimpleNetApp.cpp
            )
target_link_libraries(test_gui PRIVATE ${CORE_LIB_NAME})
target_link_libraries(test_gui PRIVATE ${NET_ENGINE_NAME})
target_link_libraries(test_gui PRIVATE ${IMGUI_HELPER_NAME})
target_link_libraries(test_gui PRIVATE fmt::fmt)
target_link_libraries(test_gui PRIVATE imgui::imgui)

# now register the executable with CTest
#add_test(NAME my_test COMMAND my_test)

# find_package(imgui CONFIG REQUIRED)
#     target_link_libraries(main PRIVATE imgui::imgui)


