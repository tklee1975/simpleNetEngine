# IMGUI Notes 

## Setup IMGUI 
Step 1: Install the package for vcpkg 

### Install the imgui for sdl2 and opengl3
```
// Both are required 
vcpkg install "imgui[sdl2-binding]" --recurse
vcpkg install "imgui[opengl3-glew-binding]" --recurse
```

Step 2: Add find page in CMakeList 
```
find_package(SDL2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
```

Step 3: Add find page in CMakeList 
```
find_package(SDL2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
```

Step 4: Add link library in CMakeList 
target_link_libraries(MyApp PRIVATE imgui::imgui)


