@REM run in root path 
　

@REM　git clone https://github.com/microsoft/vcpkg.git externals\vcpkg 

@REM　call externals\vcpkg\bootstrap-vcpkg.bat 

externals\vcpkg\vcpkg install fmt:x64-windows --recurse
externals\vcpkg\vcpkg install eastl:x64-windows --recurse
externals\vcpkg\vcpkg install imgui[sdl2-binding]:x64-windows --recurse
externals\vcpkg\vcpkg install imgui[opengl3-glew-binding]:x64-windows --recurse