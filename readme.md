# Introduction 

This is a simple network engine.
Phase 1: Peer to Peer networking 

# setup 
define the VCPKG_ROOT in Environment 
```
export VCPKG_ROOT=/Users/JohnDoe/workspace/cpp/vcpkg
```

# How to 
- create the GCC project: `./script/gen_prj.sh`  # used cmake here
- build the GCC project: `./script/build.sh` 
- run the GCC project: `./script/app1`

# File Organisation 
./Library       - the Library folder
    ./CoreLib           - the Core Library 
    ./NetworkEngine     - Network Engine Layer
./MyApp         - the Main application
./UnitTest      - Unit Tests 
./doc           - Document folder 

## Class Prefix 
SN - Standard for Simple Network 


# Code Convention (Draft)
## Naming 
First Upper Camel Case for 
- Source Folder
- Class

First lower Camel Case for 
- variable 
- functions 

All Capital Case with underscore for 
- constant (#define stuff)

All lower case with underscore for 
- script files


