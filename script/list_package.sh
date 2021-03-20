#!/bin/sh 
# 
# This script help to list the package installed by Vcpkg
# 

## ken: TODO: determine the vcpkg already install or not 
VCPKG_DIR=./externals/vcpkg
VCPKG_CMD=$VCPKG_DIR/vcpkg

$VCPKG_CMD list 