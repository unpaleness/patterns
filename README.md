# Software design patterns in C++

## Pre-requirements

cmake
llvm

## Generate

### Unix

`cmake -G"Unix Makefiles" -DCMAKE_CXX_COMPILER=clang++ -S . -B build`

### Windows (assume you have VS building suite)

`cmake -S . -B build`

## Build

### Single pattern

`cmake --build build --target {pattern_name}`

### All patterns

`cmake --build build`

## Run

### Unix

`./build/bin/{pattern_name}`

### Windows

`.\build\bin\{BuildType}\{pattern_name}.exe`

## Utils

### Format all .hpp and .cpp files in project (Unix-only)

`./smart-clang-format.sh`
