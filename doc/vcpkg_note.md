# VK Package Notes 

## Setup Vcpkg 
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install


## Setup Fmt 
Reference: 
- https://fmt.dev/dev/usage.html
https://fmt.dev/latest/index.html
`vcpkg install fmt`

## Setup eastl 
Reference: 
https://github.com/electronicarts/EASTL
https://eastl.docsforge.com/master/modules/#module-list

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

Step 4: Add link library in CMakeList firstName
target_link_libraries(MyApp PRIVATE imgui::imgui)


