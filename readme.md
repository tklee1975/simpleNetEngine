# Introduction 

This is a simple network engine.
Phase 1: Peer to Peer networking 

# How to 
- create the GCC project: `./script/gen_prj.sh`  # used cmake here
- build the GCC project: `./script/build.sh` 
- run the GCC project: `./script/app1`

# File Organisation 
./CoreLib       - the Core Library 
./MyApp         - the Main application
./UnitTest      - Unit Tests 
./doc           - Document folder 
./NetCoreLib    - Network Engine Layer

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


